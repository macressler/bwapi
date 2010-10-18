#define WIN32_LEAN_AND_MEAN   // Exclude rarely-used stuff from Windows headers

#include "../../svnrev.h"
#include "../../starcraftver.h"
#include "GameImpl.h"

#include <stdio.h>
#include <windows.h>
#include <tchar.h>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
#include <fstream>

#include <Util/FileLogger.h>
#include <Util/Exceptions.h>
#include <Util/Strings.h>
#include <Util/Foreach.h>
#include <Util/Gnu.h>

#include <BWAPI/ForceImpl.h>
#include <BWAPI/PlayerImpl.h>
#include <BWAPI/UnitImpl.h>
#include <BWAPI/BulletImpl.h>
#include <BWAPI/Command.h>
#include <BWAPI/Map.h>
#include <BWAPI/ScreenLogger.h>
#include <BWAPI/Flag.h>
#include <BWAPI.h>

#include <BW/Unit.h>
#include <BW/Bullet.h>
#include <BW/Offsets.h>
#include <BW/UnitTarget.h>
#include <BW/OrderTypes.h>
#include <BW/Latency.h>
#include <BW/TileType.h>
#include <BW/TileSet.h>
#include <BW/UnitType.h>
#include <BW/GameType.h>
#include <BW/WeaponType.h>
#include <BW/CheatType.h>
#include <BW/Dialog.h>
#include <BW/Path.h>

#include "BWAPI/AIModule.h"
#include "DLLMain.h"

#include "ShapeBox.h"
#include "ShapeCircle.h"
#include "ShapeEllipse.h"
#include "ShapeDot.h"
#include "ShapeLine.h"
#include "ShapeTriangle.h"
#include "ShapeText.h"
#include "BWtoBWAPI.h"
/*
  This files holds all functions of the GameImpl class that are not part of the Game interface.
 */
namespace BWAPI
{
  Game* Broodwar;
  GameImpl BroodwarImpl;

  //---------------------------------------------- CONSTRUCTOR -----------------------------------------------
  GameImpl::GameImpl()
      : onStartCalled(false)
      , unitsOnTileData(0, 0)
      , enabled(true)
      , client(NULL)
      , startedClient(false)
      , inGame(false)
      , calledOnEnd(false)
      , frameCount(-1)
      , endTick(0)
      , hasLatCom(true)
      , pathDebug(false)
  {
    BWAPI::Broodwar = static_cast<Game*>(this);

    /* initialize the unit types */
    BW::UnitType::initialize();
    BWtoBWAPI_init();

    try
    {
      /* create log handles */
      if (logging)
      {
        this->commandLog = new Util::FileLogger(std::string(logPath) + "\\commands", Util::LogLevel::MicroDetailed);
        this->newUnitLog = new Util::FileLogger(std::string(logPath) + "\\new_unit_id", Util::LogLevel::MicroDetailed);
      }
      else
      {
        this->commandLog = new Util::FileLogger(std::string(logPath) + "\\commands", Util::LogLevel::DontLog);
        this->newUnitLog = new Util::FileLogger(std::string(logPath) + "\\new_unit_id", Util::LogLevel::DontLog);
      }
      loadAutoMenuData();


      /* iterate through players and create PlayerImpl for each */
      for (int i = 0; i < PLAYER_COUNT; i++)
        players[i] = new PlayerImpl((u8)i);

      /* iterate through units and create UnitImpl for each */
      for (int i = 0; i < UNIT_ARRAY_MAX_LENGTH; i++)
        unitArray[i] = new UnitImpl(&BW::BWDATA_UnitNodeTable->unit[i],
                                    (u16)i);

      /* iterate through bullets and create BulletImpl for each */
      for (int i = 0; i < BULLET_ARRAY_MAX_LENGTH; i++)
        bulletArray[i] = new BulletImpl(&BW::BWDATA_BulletNodeTable->bullet[i],
                                        (u16)i);


      /* iterate through unit types and create UnitType for each */
      for (int i = 0; i < UNIT_TYPE_COUNT; i++)
        unitTypes.insert(BW::UnitType((u16)i));
    }
    catch (GeneralException& exception)
    {
      BWAPIError("Exception caught inside Game constructor: %s", exception.getMessage().c_str());
    }
  }
  //----------------------------------------------- DESTRUCTOR -----------------------------------------------
  GameImpl::~GameImpl()
  {
    /* destroy all UnitImpl */
    for (int i = 0; i < UNIT_ARRAY_MAX_LENGTH; i++)
      delete unitArray[i];

    /* destroy all PlayerImpl */
    for (int i = 0; i < PLAYER_COUNT; i++)
      delete players[i];

    /* destroy all log handles */
    delete this->commandLog;
    delete this->newUnitLog;
  }
  //------------------------------------------------- UPDATE -------------------------------------------------
  void GameImpl::update()
  {
    //this function is called every frame from a hook attached in DllMain.cpp
    this->inGame = true;

    //clear all shapes
    for (unsigned int i = 0; i < this->shapes.size(); ++i)
      delete this->shapes[i];
    this->shapes.clear();

    //menu dialog code
    if ( myDlg )
      myDlg->update();

    // Compute frame rate
    accumulatedFrames++;
    DWORD currentTickCount = GetTickCount();
    if ( currentTickCount >= lastTickCount + 1000 )
    {
      fps               = accumulatedFrames;
      averageFPS        = averageFPS*0.7+fps*0.3;
      lastTickCount     = currentTickCount;
      accumulatedFrames = 0;
    }

    //fix for restart game
    if (onStartCalled)
    {
      if (*BW::BWDATA_gwNextGameMode == 5 || *BW::BWDATA_gwNextGameMode == 6)
      {
        *BW::BWDATA_gwNextGameMode = 1;
        events.push_back(Event::MatchFrame());
        events.push_back(Event::MatchEnd(false));
        Util::Logger::globalLog->log("creating MatchEnd event");
        processEvents();
        server.update();
        events.clear();
        this->calledOnEnd = true;
        this->onGameEnd();
        this->inGame = false;
        events.push_back(Event::MenuFrame());
        this->server.update();
        this->onStartCalled = false;
        this->calledOnEnd = false;
        this->inGame = true;
      }
    }

    try
    {
      if ( this->calledOnEnd )
      {
        events.clear();
        events.push_back(Event::MenuFrame());
        processEvents();
        server.update();
        return;
      }

      //the first time update() is called, we also call onGameStart to initialize some things
      if (!onStartCalled)
      {
        this->onGameStart();
        Util::Logger::globalLog->log("calling onGameStart");
      }
      
      if ( !this->enabled )
        return;

      //check to see if the game has ended
      if ( !this->calledOnEnd )
      {
        if ( this->BWAPIPlayer )
        {
          if ( this->BWAPIPlayer->isVictorious() )
          {
            events.push_back(Event::MatchFrame());
            events.push_back(Event::MatchEnd(true));
            Util::Logger::globalLog->log("creating MatchEnd event");
            processEvents();
            server.update();
            events.clear();
            this->calledOnEnd = true;
            return;
          }
          if ( this->BWAPIPlayer->isDefeated() )
          {
            events.push_back(Event::MatchFrame());
            events.push_back(Event::MatchEnd(false));
            Util::Logger::globalLog->log("creating MatchEnd event");
            processEvents();
            server.update();
            events.clear();
            this->calledOnEnd = true;
            return;
          }
        }
        else
        {
          bool allDone = true;
          foreach(Player* p, this->playerSet)
          {
            if (((PlayerImpl*)p)->getIndex() >= 8) 
              continue;
            if (!p->isDefeated() && !p->isVictorious() && !p->leftGame())
              allDone = false;
          }
          if (allDone)
          {
            events.push_back(Event::MatchFrame());
            events.push_back(Event::MatchEnd(false));
            Util::Logger::globalLog->log("creating MatchEnd event");
            processEvents();
            server.update();
            events.clear();
            this->calledOnEnd = true;
            return;
          }
        }
      }
      //save the list of selected units and update the selected field of existing units
      refreshSelectionStates();

      //update players and check to see if they have just left the game.
      for (int i = 0; i < PLAYER_COUNT; i++)
      {
        bool prevLeftGame = this->players[i]->leftGame();
        this->players[i]->updateData();
        if (!prevLeftGame && this->players[i]->leftGame())
          events.push_back(Event::PlayerLeft((Player*)this->players[i]));
      }
      //update properties of Unit and Bullet objects
      this->updateUnits();
      this->updateBullets();

      //iterate through the list of intercepted messages
      foreach(std::string i, sentMessages)
        BroodwarImpl.onSendText(i.c_str());

      //clear all intercepted messages
      this->sentMessages.clear();
    }
    catch (GeneralException& exception)
    {
      BWAPIError("Exception caught inside Game::update: %s", exception.getMessage().c_str());
    }

    //on the first frame we check to see if the client process has connected.
    //if not, then we load the AI dll specified in bwapi.ini
    if ( !this->startedClient )
    {
      externalModuleConnected = false;
      char *pszModuleName = "<Nothing>";
      if (server.isConnected()) //check to see if the server is connected to the client
      {
        Util::Logger::globalLog->logCritical("Client connected, not loading AI module.");
        this->client = new AIModule();
        printf("BWAPI: Connected to AI Client process");
        pszModuleName = "<Client Connection>";
        externalModuleConnected = true;
      }
      else // if not, load the AI module DLL
      {
        char szDllPath[MAX_PATH];
        char szKeyName[MAX_PATH];
        hMod = NULL;

        if ( dwProcNum == 0 )
          strcpy(szKeyName, "ai_dll");
        else
          sprintf(szKeyName, "ai_dll_%u", dwProcNum);

        GetPrivateProfileString("ai", szKeyName, "NULL", szDllPath, MAX_PATH, BWAPICONFIG);
        if ( _strcmpi(szDllPath, "NULL") == 0)
        {
          BWAPIError("Could not find %s under ai in \"%s\".", szKeyName, BWAPICONFIG);
        }
        else
        {
          Util::Logger::globalLog->logCritical("Loading AI DLL from: %s", szDllPath);
          hMod = LoadLibrary(szDllPath);

          pszModuleName = szDllPath;
          if ( strchr(pszModuleName, '/') )
            pszModuleName = &strrchr(pszModuleName, '/')[1];

          if ( strchr(pszModuleName, '\\') )
            pszModuleName = &strrchr(pszModuleName, '\\')[1];
        }
        if ( !hMod )
        {
          //if hMod is a null pointer, there there was a problem when trying to load the AI Module
          Util::Logger::globalLog->logCritical("ERROR: Failed to load the AI Module");
          this->client = new AIModule();
          Broodwar->enableFlag(Flag::CompleteMapInformation);
          Broodwar->enableFlag(Flag::UserInput);
          printf("\x06" "ERROR:: Failed to load the AI Module.");
          externalModuleConnected = false;
        }
        else
        {
          Util::Logger::globalLog->logCritical("Loaded AI Module");
          Util::Logger::globalLog->logCritical("Importing by Virtual Function Table from AI DLL");

          typedef AIModule* (*PFNCreateA1)(BWAPI::Game*);
          Util::Logger::globalLog->logCritical("Creating an Object of AIModule");

          PFNCreateA1 newAIModule = (PFNCreateA1)GetProcAddress(hMod, TEXT("newAIModule"));
          this->client = newAIModule(this);
          Util::Logger::globalLog->logCritical("Created an Object of AIModule");
          printf("\x07" "BWAPI: Loaded the AI Module: %s", szDllPath);
          externalModuleConnected = true;
        }
      }
      //push the MatchStart event to the front of the queue so that it is the first event in the queue.
      events.push_front(Event::MatchStart());
      this->startedClient = true;
      sendText("BWAPI r%s %s is now live using \"%s\".", 
                SVN_REV_STR, 
                isDebug() ? "DEBUG" : "RELEASE", 
                pszModuleName );
    }

    //each frame we add a MatchFrame event to the queue
    events.push_back(Event::MatchFrame());

    //if the AI is a DLL, processEvents() will translate the events into AIModule callbacks.
    processEvents();

    //if the AI is a client process, this will signal the client to process the next frame
    server.update();

    //Before returning control to starcraft, we clear the unit data for units that are no longer accessible
    foreach(UnitImpl* u, evadeUnits)
      u->updateData();

    //We also kill the units that are dying on this frame.
    //We wait until after server.update() and processEvents() to do this so that the AI can
    //access the last frame of unit data during the onUnitDestroy callback.
    foreach(UnitImpl* u, dyingUnits)
    {
      deadUnits.push_back(u);
      int index = u->getIndex();
      unitArray[index] = new UnitImpl(&BW::BWDATA_UnitNodeTable->unit[index],(u16)index);
      u->die();
    }

    //increment frame count if the game is not paused
    if (!this->isPaused())
      this->frameCount++;

#ifdef _DEBUG
    // unitdebug
    if ( unitDebug )
    {
      // selected units
      foreach( Unit *_u, selectedUnitSet )
      {
        if ( !_u )
          continue;

        BW::Unit *u = ((UnitImpl*)_u)->getOriginalRawData;
        if ( !u )
          continue;

        //drawTextMap(u->position.x, u->position.y, "%u", u->unknown_timer_0x08D);
      }

      // all units
      foreach( UnitImpl *_u, aliveUnits )
      {
        if ( !_u )
          continue;

        BW::Unit *u = _u->getOriginalRawData;
        if ( !u )
          continue;

        //drawTextMap(u->position.x, u->position.y, "%p", u->stateFlags );

        //if ( u->unitType.isWorker() && u->worker.upgradeLevel )
        //  printf("u->worker.upgradeLevel: %p", u->worker.upgradeLevel );

      }
    }

    // pathdebug
    if ( pathDebug && BW::BWDATA_SAIPathing )
    {
      setTextSize(0);
      BWAPI::Position mouse  = getMousePosition() + getScreenPosition();
      BWAPI::Position scrPos = getScreenPosition();

      for ( int y = scrPos.y()/32-1; y < (scrPos.y()+480)/32+1; ++y )
        for ( int x = scrPos.x()/32-1; x < (scrPos.x()+640)/32+1; ++x )
          for ( int i = 0; i < 32; i += 4 )
          {
            drawLineMap(x*32 + 32, y*32 + i, x*32 + 32, y*32 + i + 2, BWAPI::Colors::Grey);
            drawLineMap(x*32 + i, y*32 + 32, x*32 + i + 2, y*32 + 32, BWAPI::Colors::Grey);
          }

      // iterate tile region owners
      for ( int y = 0; y < BW::BWDATA_MapSize->y; ++y )
      {
        for ( int x = 0; x < BW::BWDATA_MapSize->x; ++x )
        {
          u16 c = BW::BWDATA_SAIPathing->mapTileRegionId[y][x];
          // skip region 0 (bottom of the map), skip regions with no neighbors, skip inaccessable regions
          if ( c == 0 || 
               c >= 5000 ||
              BW::BWDATA_SAIPathing->regions[c].neighborCount == 0 || 
              BW::BWDATA_SAIPathing->regions[c].accessabilityFlags == 0x1FFD ||
              BW::BWDATA_SAIPathing->regions[c].tileCount <= 1 )
            continue;

          c &= 0xDF;
          if ( c < 0x20 )
            c += 0x20;

          int px = x * 32;
          int py = y * 32;
          for ( int i = 0; i < 32; i += 8 )
          {
            drawLineMap(px, py + 32 - i, px + i, py + 32, BWAPI::Color((u8)c) );
            drawLineMap(px + i, py, px + 32, py + 32 - i, BWAPI::Color((u8)c) );
            drawLineMap(px + 32, py + 32 - i, px + 32 - i, py + 32, BWAPI::Color((u8)c) );
            drawLineMap(px + 32 - i, py, px, py + 32 - i, BWAPI::Color((u8)c) );
          }
        }
      }

      // iterate regions
      for ( unsigned int i = 1; i < BW::BWDATA_SAIPathing->regionCount && i < 5000; ++i )
      {
        BW::region *rgn = getRegion(i);

        if ( rgn->unk_8 != 0 )
          printf("[%u] unk_8 = 0x%p", i, rgn->unk_8);

        if ( rgn->unk_24 != 0 )
          printf("[%u] unk_24 = 0x%p", i, rgn->unk_24);

        if ( rgn->unk_28 != 0 )
          printf("[%u] unk_28 = 0x%p", i, rgn->unk_28);

        BW::Position center = rgn->getCenter();
        if ( mouse.x() >= rgn->rgnBox.left   &&
             mouse.x() <= rgn->rgnBox.right  &&
             mouse.y() >= rgn->rgnBox.top    &&
             mouse.y() <= rgn->rgnBox.bottom )
        {
          drawTextMap(center.x, center.y, "%u", i);
          drawBoxMap(rgn->rgnBox.left, rgn->rgnBox.top, rgn->rgnBox.right, rgn->rgnBox.bottom, BWAPI::Colors::Orange);
        }
        //drawBoxMap(rgn->rgnBox.left, rgn->rgnBox.top, rgn->rgnBox.right, rgn->rgnBox.bottom, BWAPI::Colors::Orange);

        // skip inaccessable regions
        if ( rgn->accessabilityFlags == 0x1FFD )
          continue;

        BW::region *neighborRgns[256];
        u8 nCount = rgn->getAccessibleNeighbours(neighborRgns, 256);
        for ( u8 i = 0; i < nCount; ++i )
        {
          BW::Position targetCenter = neighborRgns[i]->getCenter();
          drawLineMap( center.x, center.y, targetCenter.x, targetCenter.y, BWAPI::Colors::White);
        }
      }

      BW::badpath tBuff[128];
      u32         tBuffSize = 0;

      BW::badpath *rgnStuff = BW::BWDATA_SAIPathing->badPaths;
      for ( unsigned int i = 0; rgnStuff[i].minitileMask != 0 && rgnStuff[i].rgn1 != 0 && rgnStuff[i].rgn2 != 0; ++i )
      {
        BW::Position rgn1 = getRegion(rgnStuff[i].rgn1)->getCenter();
        BW::Position rgn2 = getRegion(rgnStuff[i].rgn2)->getCenter();
        if ( mouse.x() >= (rgn1.x + rgn2.x)/2 - 32 &&
             mouse.x() <= (rgn1.x + rgn2.x)/2 + 32 &&
             mouse.y() >= (rgn1.y + rgn2.y)/2 - 32 &&
             mouse.y() <= (rgn1.y + rgn2.y)/2 + 32 &&
             tBuffSize < 128 )
        {
          drawLineMap(rgn1.x, rgn1.y, rgn2.x, rgn2.y, BWAPI::Colors::Blue);
          tBuff[tBuffSize] = rgnStuff[i];
          ++tBuffSize;
        }
        else
        {
          drawLineMap(rgn1.x, rgn1.y, rgn2.x, rgn2.y, BWAPI::Colors::Grey);
        }
      }

      for ( unsigned int t = 0; t < tBuffSize; ++t )
      {
        for ( int i = 0; i < 4; ++i )
        {
          drawBoxMouse(24 + t*32, i*6, 29 + t*32, i*6 + 5, (tBuff[t].minitileMask >> (i*4+0)) & 1 ? BWAPI::Colors::Red : BWAPI::Colors::Green);
          drawBoxMouse(30 + t*32, i*6, 35 + t*32, i*6 + 5, (tBuff[t].minitileMask >> (i*4+1)) & 1 ? BWAPI::Colors::Red : BWAPI::Colors::Green);
          drawBoxMouse(36 + t*32, i*6, 41 + t*32, i*6 + 5, (tBuff[t].minitileMask >> (i*4+2)) & 1 ? BWAPI::Colors::Red : BWAPI::Colors::Green);
          drawBoxMouse(42 + t*32, i*6, 47 + t*32, i*6 + 5, (tBuff[t].minitileMask >> (i*4+3)) & 1 ? BWAPI::Colors::Red : BWAPI::Colors::Green);
        }
        //drawTextMouse(24, 0 + t * 16, "%u->%u: 0x%04X", tBuff[t].rgn1, tBuff[t].rgn2, tBuff[t].unk_00);
      }

      // iterate contours
      BW::contourHub *cont = BW::BWDATA_SAIPathing->contoursMain;
      if ( cont )
      {
        for ( int i = 0; i < cont->contourCount[0]; ++i )
        {
          bool dtext = false;
          s16 y1 = cont->contours[0][i].v[0];
          s16 x1 = cont->contours[0][i].v[1];
          s16 x2 = cont->contours[0][i].v[2];
          BWAPI::Color c = BWAPI::Colors::Yellow;
          if ( mouse.x() >= x1 &&
               mouse.x() <= x2 &&
               mouse.y() >= y1 - 8 &&
               mouse.y() <= y1 + 8 )
          {
            dtext = true;
            c = BWAPI::Colors::Green;
          }
          drawLineMap(x1, y1, x2, y1, c );
          if ( dtext )
            drawTextMap(x1, y1, "%02X\n%02X", cont->contours[0][i].type, cont->contours[0][i].unk_07);
        }
        for ( int i = 0; i < cont->contourCount[1]; ++i )
        {
          bool dtext = false;
          s16 x1 = cont->contours[1][i].v[0];
          s16 y1 = cont->contours[1][i].v[1];
          s16 y2 = cont->contours[1][i].v[2];
          BWAPI::Color c = BWAPI::Colors::Yellow;
          if ( mouse.x() >= x1 - 8 &&
               mouse.x() <= x1 + 8 &&
               mouse.y() >= y1 &&
               mouse.y() <= y2 )
          {
            dtext = true;
            c = BWAPI::Colors::Green;
          }
          drawLineMap(x1, y1, x1, y2, c );
          if ( dtext )
            drawTextMap(x1, y1, "%02X\n%02X", cont->contours[1][i].type, cont->contours[1][i].unk_07);
        }
        for ( int i = 0; i < cont->contourCount[2]; ++i )
        {
          bool dtext = false;
          s16 y1 = cont->contours[2][i].v[0];
          s16 x1 = cont->contours[2][i].v[1];
          s16 x2 = cont->contours[2][i].v[2];
          BWAPI::Color c = BWAPI::Colors::Yellow;
          if ( mouse.x() >= x1 &&
               mouse.x() <= x2 &&
               mouse.y() >= y1 - 8 &&
               mouse.y() <= y1 + 8 )
          {
            dtext = true;
            c = BWAPI::Colors::Green;
          }
          drawLineMap(x1, y1, x2, y1, c );
          if ( dtext )
            drawTextMap(x1, y1, "%02X\n%02X", cont->contours[2][i].type, cont->contours[2][i].unk_07);
        }
        for ( int i = 0; i < cont->contourCount[3]; ++i )
        {
          bool dtext = false;
          s16 x1 = cont->contours[3][i].v[0];
          s16 y1 = cont->contours[3][i].v[1];
          s16 y2 = cont->contours[3][i].v[2];
          BWAPI::Color c = BWAPI::Colors::Yellow;
          if ( mouse.x() >= x1 - 8 &&
               mouse.x() <= x1 + 8 &&
               mouse.y() >= y1 &&
               mouse.y() <= y2 )
          {
            dtext = true;
            c = BWAPI::Colors::Green;
          }
          drawLineMap(x1, y1, x1, y2, c );
          if ( dtext )
            drawTextMap(x1, y1, "%02X\n%02X", cont->contours[3][i].type, cont->contours[3][i].unk_07);
        }
      }

/*
      // draw individual unit pathing
      foreach( UnitImpl *u, aliveUnits )
      {
        if ( !u->getType().isFlyer() )
        {
          BW::TilePosition srcPos = BW::TilePosition(u->getOriginalRawData->position);
          BW::TilePosition dstPos = BW::TilePosition(u->getOriginalRawData->moveToPos);
          if ( srcPos == dstPos || srcPos.x > 255 || srcPos.y > 255 || dstPos.x > 255 || dstPos.y > 255 )
            continue;

          u16 srcId = BW::BWDATA_SAIPathing->mapTileRegionId[srcPos.y][srcPos.x];
          u16 dstId = BW::BWDATA_SAIPathing->mapTileRegionId[dstPos.y][dstPos.x];

          if ( srcId >= 5000 || dstId >= 5000 )
            continue;

          if ( srcId == dstId )
            continue;

          BW::region *srcRgn = getRegion( srcId );
          BW::region *dstRgn = getRegion( dstId );

          BW::Position pts[256];
          u16 pCount = srcRgn->getPointPath(dstRgn, pts, 256);

          BW::Position last = u->getOriginalRawData->position;
          for ( u16 i = 0; i < pCount; ++i )
          {
            drawLineMap(last.x, last.y, pts[i].x, pts[i].y, BWAPI::Colors::Yellow);
            last = pts[i];
          }
        }
        else
        {
          BW::Position start = u->getOriginalRawData->position;
          BW::Position stop = u->getOriginalRawData->moveToPos;;
          drawLineMap(start.x, start.y, stop.x, stop.y, BWAPI::Colors::Yellow);
        }
      }
*/
    }
#endif
    //finally return control to starcraft
  }
  //------------------------------------------- LOAD AUTO MENU DATA ------------------------------------------
  void GameImpl::loadAutoMenuData()
  {
    //this function is called when starcraft loads and at the end of each match.
    //the function loads the parameters for the auto-menu feature such as auto_menu, map, race, enemy_race, enemy_count, and game_type
    char buffer[MAX_PATH];
    GetPrivateProfileString("config", "auto_menu", "OFF", buffer, MAX_PATH, BWAPICONFIG);
    this->autoMenuMode = std::string( strupr(buffer) );

    if ( autoMenuMode != "OFF" && autoMenuMode != "" )
    {
      GetPrivateProfileString("config", "map", "", buffer, MAX_PATH, BWAPICONFIG);

      //split path into path and filename
      char* mapPathAndNameI         = buffer;
      char* mapPathAndNameLastSlash = buffer;
      while(mapPathAndNameI[0] != '\0')
      {
        if (mapPathAndNameI[0] == '\\' || mapPathAndNameI[0] == '/')
          mapPathAndNameLastSlash = mapPathAndNameI + 1;
        mapPathAndNameI++;
      }
      autoMenuMapName = std::string(mapPathAndNameLastSlash);
      mapPathAndNameLastSlash[0] = '\0';
      autoMenuMapPath = std::string(buffer);
    }
    GetPrivateProfileString("config", "race", "RANDOM", buffer, MAX_PATH, BWAPICONFIG);
    autoMenuRace = std::string(buffer);
    GetPrivateProfileString("config", "enemy_race", "RANDOM", buffer, MAX_PATH, BWAPICONFIG);
    autoMenuEnemyRace = std::string(buffer);
    GetPrivateProfileString("config", "enemy_count", "1", buffer, MAX_PATH, BWAPICONFIG);
    autoMenuEnemyCount = std::string(buffer);
    GetPrivateProfileString("config", "game_type", "MELEE", buffer, MAX_PATH, BWAPICONFIG);
    autoMenuGameType = std::string(buffer);
  }
  //---------------------------------------------- ON MENU FRAME ---------------------------------------------
  void GameImpl::onMenuFrame()
  {
    if (GetTickCount() > endTick + 200)
    {
      onStartCalled = false;
      calledOnEnd   = false;
    }
    //this function is called each frame while starcraft is in the main menu system (not in-game).
    this->inGame = false;
    events.push_back(Event::MenuFrame());
    this->server.update();
    int menu = *BW::BWDATA_glGluesMode;
    BW::dialog *tempDlg;
    if ( autoMenuMode == "SINGLE_PLAYER" )
    {
      switch ( menu )
      {
//main menu
      case 0: 
        if ( !actMainMenu )
        {
          actMainMenu = true;
          if ( !BW::FindDialogGlobal("MainMenu")->findIndex(3)->activate() )
            actMainMenu = false;
        }
        tempDlg = BW::FindDialogGlobal("Delete");
        if ( tempDlg )
          tempDlg->findIndex(7)->activate();

        actRegistry = false;
        break;
//single player play custom / load replay selection screen
      case 22:
        actRegistry = false;
        strcpy(BW::BWDATA_menuMapRelativePath, autoMenuMapPath.c_str());
        strcpy(BW::BWDATA_menuMapFileName, autoMenuMapName.c_str());
        if ( !actRaceSel )
        {
          actRaceSel = true;
          if ( !BW::FindDialogGlobal("RaceSelection")->findIndex(10)->activate() )
            actRaceSel = false;
        }
        actCreate = false;
        break;
//create single/multi player game screen
      case 11: 
        actRaceSel = false;
        //the first time we enter the create game screen, it won't set the map correctly
        //so we need to cancel out and re-enter
        tempDlg = BW::FindDialogGlobal("Create");
        if ( *BW::BWDATA_menuStuff != -1 ) //Starcraft sets this to -1 after the first time we enter the create game screen
          this->pressKey( tempDlg->findIndex(13)->getHotkey() );
          //tempDlg->findIndex(13)->doEvent(14, 2);    // This is too efficient and will cause whatever trick being used to fail (infinite loop)
        else
        {
          int enemyCount = atoi(this->autoMenuEnemyCount.c_str());
          if (enemyCount < 1) enemyCount = 1;
          if (enemyCount > 7) enemyCount = 7;
          Race r = Races::getRace(this->autoMenuRace);
          if (r != Races::Unknown && r != Races::None)
            this->_changeRace(0, r);
          Race er = Races::getRace(this->autoMenuEnemyRace);
          if (er != Races::Unknown && er != Races::None)
          {
            for(int i = 0; i < enemyCount; i++)
              this->_changeRace(i + 1, er);
          }
          //close remaining slots
          for(int i = enemyCount; i < 7; i++)
            tempDlg->findIndex((short)(21 + i))->setSelectedIndex(0);

          GameType gt = GameTypes::getGameType(this->autoMenuGameType);
          if (gt != GameTypes::None && gt != GameTypes::Unknown)
            tempDlg->findIndex(17)->setSelectedByValue(gt.getID());

          this->pressKey( tempDlg->findIndex(12)->getHotkey() );
          /*if ( !actCreate )
          {
            actCreate = true;
            if ( !tempDlg->findIndex(12)->activate() )
              actCreate = false;
          }*/
        }
        break;
      }
    }
    else if (autoMenuMode == "LAN_UDP")
    {
      switch ( menu )
      {
//main menu
      case 0: 
        if ( !actMainMenu )
        {
          actMainMenu = true;
          if ( !BW::FindDialogGlobal("MainMenu")->findIndex(4)->activate() )
            actMainMenu = false;
        }
        tempDlg = BW::FindDialogGlobal("Delete");
        if ( tempDlg )
          tempDlg->findIndex(7)->activate();

        actConnSel = false;
        break;
// Select connection
      case 2:
        actMainMenu = false;

        /*tempDlg = BW::FindDialogGlobal("ConnSel");
        if ( tempDlg )
          tempDlg->findIndex(5)->setSelectedByString("Local Area Network (UDP)"); // This doesn't work yet
        */
        this->pressKey(VK_DOWN);
        this->pressKey(VK_DOWN);
        this->pressKey(VK_DOWN);
        this->pressKey(VK_DOWN);
        this->pressKey(VK_DOWN); // move 5 because of the custom SNP, doesn't affect people without it
        this->pressKey( BW::FindDialogGlobal("ConnSel")->findIndex(9)->getHotkey() );
        actRegistry = false;
        break;
      }

      if (autoMenuMapName.length() > 0)
      {
        switch ( menu )
        {
//lan games lobby
        case 10: 
          actRegistry = false;
          strcpy(BW::BWDATA_menuMapRelativePath, autoMenuMapPath.c_str());
          strcpy(BW::BWDATA_menuMapFileName, autoMenuMapName.c_str());
          if ( !actGameSel )
          {
            actGameSel = true;
            if ( !BW::FindDialogGlobal("GameSel")->findIndex(15)->activate() )
              actGameSel = false;
          }
          actCreate = false;
          break;
//create single/multi player game screen
        case 11: 
          actGameSel = false;
          //the first time we enter the create game screen, it won't set the map correctly
          //so we need to cancel out and re-enter
          tempDlg = BW::FindDialogGlobal("Create");
          if (*BW::BWDATA_menuStuff != -1) // Starcraft sets this to -1 after the first time we enter the create game screen
            this->pressKey( tempDlg->findIndex(13)->getHotkey() );
          else
          {
            GameType gt = GameTypes::getGameType(this->autoMenuGameType);
            if (gt != GameTypes::None && gt != GameTypes::Unknown)
              tempDlg->findIndex(17)->setSelectedByValue(gt.getID());

            this->pressKey( tempDlg->findIndex(12)->getHotkey() );
            /*if ( !actCreate )
            {
              actCreate = true;
              tempDlg->findIndex(12)->activate();
            }*/
          }
          break;
// in lobby
        case 3:
          actCreate = false;
          Race r = Races::getRace(this->autoMenuRace);
          if (r != Races::Unknown)
            this->_changeRace(0, r);
          break;
        }
      }
      else // wait for other computer to make game
      {
        switch ( menu )
        {
//lan games lobby
        case 10: 
          actRegistry = false;
          this->pressKey( BW::FindDialogGlobal("GameSel")->findIndex(13)->getHotkey() );
          //BW::FindDialogGlobal("GameSel")->findIndex(13)->activate();  // might bug
          break;
//multiplayer game ready screen
        case 3: 
          Race r = Races::getRace(this->autoMenuRace);
          if (r != Races::Unknown)
            this->_changeRace(1, r);
        }
      }
    }
    else if (autoMenuMode == "BATTLE_NET")
    {
      switch ( menu )
      {
//main menu
      case 0: 
        if ( !actMainMenu )
        {
          actMainMenu = true;
          if ( !BW::FindDialogGlobal("MainMenu")->findIndex(4)->activate() )
            actMainMenu = false;
        }
        tempDlg = BW::FindDialogGlobal("Delete");
        if ( tempDlg )
          tempDlg->findIndex(7)->activate();
        actConnSel = false;
        break;
//multiplayer select connection screen
      case 2: 
        actMainMenu = false;
        /*if ( !actConnSel )      // Broken
        {
          actConnSel = true;
          if ( !BW::FindDialogGlobal("ConnSel")->findIndex(9)->activate() )
            actConnSel = false;
        }*/
        this->pressKey( BW::FindDialogGlobal("ConnSel")->findIndex(9)->getHotkey() );
        break;
      }
    }


// Common
    if ( autoMenuMode != "" && autoMenuMode != "OFF" )
    {
      switch ( menu )
      {
//registry screen
      case 5: 
        actMainMenu = false;
        tempDlg = BW::FindDialogGlobal("gluPEdit");
        if ( tempDlg )
        {
          tempDlg->findIndex(4)->setText("BWAPI");
          tempDlg->findIndex(1)->activate();
        }
        else if ( !actRegistry )
        {
          actRegistry = true;
          if ( !BW::FindDialogGlobal("Login")->findIndex(4)->activate() )
            actRegistry = false;
        }
        actRaceSel = false;
        break;
// Score screen
      case 14: 
      case 15:
      case 16:
      case 17:
      case 18:
      case 19:
        actCreate = false;
        if ( !actEnd )
        {
          actEnd = true;
          if ( !BW::FindDialogGlobal("End")->findIndex(7)->activate() )
            actEnd = false;
        }
        break;
// Mission Briefings
      case 7:
      case 8:
      case 9:
        if ( !actBriefing )
        {
          actBriefing = true;
          if ( !BW::FindDialogGlobal("TerranRR")->findIndex(13)->activate() &&
               !BW::FindDialogGlobal("ReadyZ")->findIndex(13)->activate() )
           actBriefing = false;
        }
        break;
      }
    }
  }
  //---------------------------------------- REFRESH SELECTION STATES ----------------------------------------
  void GameImpl::refreshSelectionStates()
  {
    for (int i = 0; i < UNIT_ARRAY_MAX_LENGTH; ++i)
      this->unitArray[i]->setSelected(false);

    this->saveSelected();
    for (int i = 0; savedSelectionStates[i]; ++i)
      BWAPI::UnitImpl::BWUnitToBWAPIUnit(savedSelectionStates[i])->setSelected(true);
  }
  //--------------------------------------------- IS BATTLE NET ----------------------------------------------
  bool GameImpl::_isBattleNet()
  {
    return *BW::BWDATA_GameModule == 'TENB';
  }
  //-------------------------------------------- IS SINGLE PLAYER --------------------------------------------
  bool GameImpl::_isSinglePlayer() const
  {
    return *BW::BWDATA_GameModule == 0 || *BW::BWDATA_GameModule == -1;
  }
  //------------------------------------------------ IS IN GAME ----------------------------------------------
  bool GameImpl::_isInGame() const
  {
    return *BW::BWDATA_InGame != 0;
  }
  //----------------------------------------------- IN REPLAY ------------------------------------------------
  bool  GameImpl::_isReplay() const
  {
    return *BW::BWDATA_InReplay != 0;
  }

  //------------------------------------------------ MOUSE/KEY INPUT -----------------------------------------
  void GameImpl::pressKey(int key)
  {
    //simulates a key press using the winapi
    INPUT *keyp          = new INPUT;
    keyp->type           = INPUT_KEYBOARD;
    keyp->ki.wVk         = (WORD)key;
    keyp->ki.dwFlags     = 0;
    keyp->ki.time        = 0;
    keyp->ki.wScan       = 0;
    keyp->ki.dwExtraInfo = 0;
    SendInput(1,keyp,sizeof(INPUT));
    keyp->ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1,keyp,sizeof(INPUT));
  }
  void GameImpl::mouseDown(int x, int y)
  {
    //simulates a mouse press using the winapi
    INPUT *i          = new INPUT;
    i->type           = INPUT_MOUSE;
    i->mi.dx          = x;
    i->mi.dy          = y;
    i->mi.dwFlags     = MOUSEEVENTF_LEFTDOWN;
    i->mi.dwExtraInfo = 0;
    SendInput(1,i,sizeof(INPUT));
  }
  void GameImpl::mouseUp(int x, int y)
  {
    //simulates a mouse release using the winapi
    INPUT *i          = new INPUT;
    i->type           = INPUT_MOUSE;
    i->mi.dx          = x;
    i->mi.dy          = y;
    i->mi.dwFlags     = MOUSEEVENTF_LEFTUP;
    i->mi.dwExtraInfo = 0;
    SendInput(1,i,sizeof(INPUT));
  }

  //---------------------------------------------- CHANGE SLOT -----------------------------------------------
  void GameImpl::changeSlot(BW::Orders::ChangeSlot::Slot slot, u8 slotID)
  {
    QueueGameCommand((PBYTE)&BW::Orders::ChangeSlot(slot, slotID), 3);
  }
  //---------------------------------------------- CHANGE RACE -----------------------------------------------
  void  GameImpl::_changeRace(int slot, BWAPI::Race race)
  {
    BW::dialog *custom = BW::FindDialogGlobal("Create");
    if ( custom )
    {
      BW::dialog *slotCtrl = custom->findIndex((short)(28 + slot));  // 28 is the CtrlID of the first slot
      if ( slotCtrl )
        slotCtrl->setSelectedByValue(race.getID());
    }
    QueueGameCommand((PBYTE)&BW::Orders::ChangeRace(static_cast<u8>(race.getID()), (u8)slot), 3);
  }
  //----------------------------------------- ADD TO COMMAND BUFFER ------------------------------------------
  void GameImpl::addToCommandBuffer(Command* command)
  {
    //executes latency compensation code and added it to the buffer
    command->execute(0);
    this->commandBuffer[this->commandBuffer.size() - 1].push_back(command);
  }
  //--------------------------------------------- ON GAME START ----------------------------------------------
  void GameImpl::onGameStart()
  {
    /** This function is called at the start of every match */
    actMainMenu = false;
    actRegistry = false;
    actCreate   = false;
    actConnSel  = false;
    actGameSel  = false;
    actRaceSel  = false;
    actEnd      = false;
    actBriefing = false;

    /* initialize the variables */
    frameCount    = 0;
    textSize      = 1;
    onStartCalled = true;
    BWAPIPlayer   = NULL;
    calledOnEnd   = false;
    bulletCount   = 0;

    /* set all the flags to the default of disabled */
    for (int i = 0; i < Flag::Max; i++)
      this->flags[i] = false;

    /* load the map data */
    map.load();
    this->savedMapHash = Map::getMapHash();

    if (*(BW::BWDATA_InReplay)) /* set replay flags */
    {
      for (int i = 0; i < Flag::Max; i++)
        this->flags[i] = true;
    }
    else
    {
      /* Get the current player */
      if ( this->players[*BW::BWDATA_g_LocalHumanID] )
      {
        this->BWAPIPlayer = this->players[*BW::BWDATA_g_LocalHumanID];
      }
      else
      {
        this->commandLog->log("Error: Could not locate BWAPI player.");
        return;
      }
    }

    /* Clear our sets */
    this->startLocations.clear();
    this->playerSet.clear();
    this->forces.clear();

    /* get the set of start locations */
    BW::Position *StartLocs = BW::BWDATA_startPositions;
    BW::UnitType SLocType   = BW::UnitType(BW::UnitID::Start_Location);
    for ( int i = 0; i < PLAYABLE_PLAYER_COUNT ; ++i)
    {
      if ( (StartLocs[i].x != 0 || StartLocs[i].y != 0)/* && this->players[i]->isParticipating()*/ )
        startLocations.insert(BWAPI::TilePosition( (StartLocs[i].x - SLocType.dimensionLeft()) / TILE_SIZE,
                                                   (StartLocs[i].y - SLocType.dimensionUp()  ) / TILE_SIZE) );
    }

    // Get Player Objects
    this->server.clearAll();
    for (int i = 0; i < PLAYER_COUNT; ++i)
    {
      if ( this->players[i] && 
           BW::BWDATA_Players[i].nType != BW::PlayerType::None &&
           BW::BWDATA_Players[i].nType <  BW::PlayerType::Closed )
      {
        players[i]->setID(server.getPlayerID(players[i]));
        this->playerSet.insert(this->players[i]);
      }
    }

    // Get Force Objects, assign Force<->Player relations
    for ( int f = 0; f < 5; ++f )
    {
      ForceImpl *newForce;
      if ( f == 0 )
        newForce = new ForceImpl(std::string(""));
      else
        newForce = new ForceImpl( std::string(BW::BWDATA_ForceNames[f-1].name) );
      
      this->forces.insert( (Force*)newForce );
      for ( int p = 0; p < PLAYER_COUNT; ++p )
      {
        if ( this->players[p] && BW::BWDATA_Players[p].nTeam == f )
        {
          this->players[p]->force = newForce;
          if ( BW::BWDATA_Players[p].nType != BW::PlayerType::None &&
               BW::BWDATA_Players[p].nType <  BW::PlayerType::Closed )
            newForce->players.insert(this->players[p]);
        }
      }
    }

    this->unitsOnTileData.resize(Map::getWidth(), Map::getHeight());
  }
  //------------------------------------------- PLAYER ID CONVERT --------------------------------------------
  int GameImpl::stormIdToPlayerId(int dwStormId)
  {
    /* Translates a storm ID to a player Index */
    for (int i = 0; i < PLAYER_COUNT; i++)
    {
      if ( BW::BWDATA_Players[i].dwStormId == (u32)dwStormId )
        return i;
    }
    return -1;
  }
  int GameImpl::playerIdToStormId(int dwPlayerId)
  {
    /* Get storm ID */
    return BW::BWDATA_Players[dwPlayerId].dwStormId;
  }
  //----------------------------------------------- PARSE TEXT -----------------------------------------------
  bool GameImpl::parseText(const char* text)
  {
    /* analyze the string */
    std::string message = text;
    std::vector<std::string> parsed = Util::Strings::splitString(message, " ");

    /* fix for bad referencing */
    while (parsed.size() < 5)
      parsed.push_back("");

    /* commands list */
    if (parsed[0] == "/leave")
    {
      this->leaveGame();
    }
    else if (parsed[0] == "/latency")
    {
      printf("latency: %d", getLatency());
      printf("New latency?: %u frames; %ums", getLatencyFrames(), getLatencyTime());
    }
    else if (parsed[0] == "/speed")
    {
      if (parsed[1] != "")
        setLocalSpeed(atoi(parsed[1].c_str()));
      else
        setLocalSpeed();
    }
    else if (parsed[0] == "/cheats")
    {
      sendText("power overwhelming");
      sendText("operation cwal");
      sendText("the gathering");
      sendText("medieval man");
      sendText("black sheep wall");
      sendText("food for thought");
      sendText("modify the phase variance");
      sendText("something for nothing");
      sendText("something for nothing");
      sendText("something for nothing");
      sendText("show me the money");
      sendText("show me the money");
      sendText("show me the money");
      sendText("show me the money");
      sendText("show me the money");
    }
    else if (parsed[0] == "/restart")
    {
      restartGame();
    }
    else if (parsed[0] == "/jump")
    {
      if ( !this->isMultiplayer() )
      {
        *BW::BWDATA_gwGameMode    = 3;
        *BW::BWDATA_Ophelia       = 1;
        *BW::BWDATA_GameState     = 0;
        *BW::BWDATA_gwNextGameMode  = 4;
      }
    }
#ifdef _DEBUG
    else if (parsed[0] == "/dlgdebug")
    {
      if ( !myDlg )
      {
        // Create the dialog window
        myDlg = BW::CreateDialogWindow("Test Dialog", 100, 100, 300, 200);

        // Add additional controls to the window
        BW::dialog *test = new BW::dialog(BW::ctrls::cLIST, 1, "testing123", 8, 30, 200, 100);
        myDlg->addControl(test);

        // Initialize the dialog
        myDlg->initialize();
    
        // Add entries to the combo/list box
        test->addListEntry("Test");
        test->addListEntry("Test2");
        test->addListEntry("Test3");
        test->addListEntry("Test4");
        test->addListEntry("Test5");
        test->addListEntry("Test6");
        test->addListEntry("Test7");
        test->addListEntry("Test8");
        test->addListEntry("Test9");
        test->addListEntry("Test10");
      }
    }
    else if (parsed[0] == "/pathdebug")
    {
      pathDebug = !pathDebug;
      printf("pathdebug %s", pathDebug ? "ENABLED" : "DISABLED");
    }
    else if (parsed[0] == "/unitdebug")
    {
      unitDebug = !unitDebug;
      printf("unitdebug %s", unitDebug ? "ENABLED" : "DISABLED");
    }
#endif
    else
    {
      return false;
    }
    return true;
  }
  //---------------------------------------------- ON GAME END -----------------------------------------------
  void GameImpl::onGameEnd()
  {
    //this is called at the end of every match
    if (this->frameCount == -1)
      return;

    if ( myDlg )
    {
      delete myDlg;
      myDlg = NULL;
    }

    if ( !this->calledOnEnd )
    {
      bool win = true;
      if (this->_isReplay())
        win = false;
      else
      { 
        for(UnitImpl* i = UnitImpl::BWUnitToBWAPIUnit(*BW::BWDATA_UnitNodeList_VisibleUnit_First); i; i = i->getNext())
        {
          if (self()->isEnemy(i->_getPlayer) && i->_getType.isBuilding())
            win = false;
        }
      }
      events.push_back(Event::MatchFrame());
      events.push_back(Event::MatchEnd(win));
      Util::Logger::globalLog->log("creating MatchEnd event");
      processEvents();
      server.update();
      events.clear();
      this->calledOnEnd = true;
    }
    if ( this->client )
    {
      delete this->client;
      this->client = NULL;
    }
    //clear all sets
    aliveUnits.clear();
    dyingUnits.clear();
    discoverUnits.clear();
    accessibleUnits.clear();
    evadeUnits.clear();
    lastEvadedUnits.clear();
    selectedUnitSet.clear();
    emptySet.clear();
    startLocations.clear();
    unitTypes.clear();
    forces.clear();
    playerSet.clear();
    minerals.clear();
    geysers.clear();
    neutralUnits.clear();
    bullets.clear();
    pylons.clear();
    staticMinerals.clear();
    staticGeysers.clear();
    staticNeutralUnits.clear();

    //clear latency buffer
    this->commandBuffer.clear();

    //remove AI Module from memory (object was already deleted)
    FreeLibrary(hMod);
    Util::Logger::globalLog->logCritical("Unloaded AI Module");

    //clear all selection states
    for (int i = 0; i < 13; i++)
      this->savedSelectionStates[i] = NULL;

    this->invalidIndices.clear();
    this->selectedUnitSet.clear();
    this->startedClient = false;

    //delete all dead units
    foreach (UnitImpl* d, this->deadUnits)
      delete d;
    this->deadUnits.clear();

    //delete all shapes
    for (unsigned int i = 0; i < this->shapes.size(); ++i)
      delete this->shapes[i];
    this->shapes.clear();

    for(int i = 0 ; i < PLAYER_COUNT; ++i)
      if ( this->players[i] )
        this->players[i]->onGameEnd();

    //reset game speeds and text size
    this->setLocalSpeed(-1);
    this->setTextSize();

    //reset all Unit objects in the unit array
    for (int i = 0; i < UNIT_ARRAY_MAX_LENGTH; ++i)
    {
      if ( !unitArray[i] )
        continue;
      unitArray[i]->userSelected      = false;
      unitArray[i]->isAlive           = false;
      unitArray[i]->wasAlive          = false;
      unitArray[i]->wasAccessible     = false;
      unitArray[i]->wasVisible        = false;
      unitArray[i]->staticInformation = false;
      unitArray[i]->nukeDetected      = false;
      unitArray[i]->lastType          = UnitTypes::Unknown;
      unitArray[i]->lastPlayer        = NULL;
      unitArray[i]->setID(-1);
    }
    this->cheatFlags  = 0;
    this->bulletCount = 0;
    this->frameCount  = -1;
    this->endTick     = GetTickCount();

    //reload auto menu data (in case the AI set the location of the next map/replay)
    this->loadAutoMenuData();

    //clear everything in the server
    this->server.clearAll();

    // Reset menu activation variables
    actMainMenu = false;
    actRegistry = false;
    actCreate   = false;
    actConnSel  = false;
    actGameSel  = false;
    actRaceSel  = false;
    actEnd      = false;
    actBriefing = false;
  }
  //------------------------------------------------ GET UNIT FROM INDEX -------------------------------------
  UnitImpl* GameImpl::getUnitFromIndex(int index)
  {
    int i = (index & 0x7FF);
    return this->unitArray[i];
  }
  //----------------------------------------------- GET BULLET FROM INDEX ------------------------------------
  BulletImpl* GameImpl::getBulletFromIndex(int index)
  {
    int i = (index & 0x7F);
    return this->bulletArray[i];
  }
  //--------------------------------------------- SAVE SELECTED ----------------------------------------------
  void GameImpl::saveSelected()
  {
    memcpy(&savedSelectionStates, BW::BWDATA_CurrentPlayerSelectionGroup, 4 * 12);
    savedSelectionStates[12] = NULL;
    selectedUnitSet.clear();
    for (int i = 0; savedSelectionStates[i]; ++i)
      selectedUnitSet.insert(UnitImpl::BWUnitToBWAPIUnit(savedSelectionStates[i]));
  }
  //--------------------------------------------- LOAD SELECTED ----------------------------------------------
  void GameImpl::loadSelected()
  {
    int unitCount = 0;
    while (savedSelectionStates[unitCount])
      unitCount++;

    if (unitCount > 0)
      BW::selectUnits(unitCount, savedSelectionStates);
  }
  //------------------------------------------ copy Map To Shared Memory -------------------------------------
  void GameImpl::copyMapToSharedMemory()
  {
    map.copyToSharedMemory();
  }
  bool inline isAlive(UnitImpl* i, bool isHidden = false)
  {
    //this function determines if a unit in one of the alive unit lists is actually "alive" according to BWAPI
    //this function is only used in computeUnitExistence and shouldn't be called from any other function

    if ( i->getOriginalRawData->orderID == BW::OrderID::Die )
      return false;

    u16 uId = i->getOriginalRawData->unitType.id;
    UnitType _getType = BWAPI::UnitType(uId);
    if ( uId == BW::UnitID::Resource_MineralPatch1 ||
         uId == BW::UnitID::Resource_MineralPatch2 ||
         uId == BW::UnitID::Resource_MineralPatch3)
    {
      _getType = UnitTypes::Resource_Mineral_Field;
    }

    int hitpoints = i->getOriginalRawData->hitPoints;
    if ( !i->_getType.isInvincible() && hitpoints <= 0 )
      return false;

    if ( !i->getOriginalRawData->sprite )
      return false;

    if ( isHidden ) //usually means: is inside another unit?
    {
      if (_getType == UnitTypes::Unknown)
        return false;//skip subunits if they are in this list

      if (_getType == UnitTypes::Protoss_Scarab ||
          _getType == UnitTypes::Terran_Vulture_Spider_Mine ||
          _getType == UnitTypes::Terran_Nuclear_Missile)
        return false;

    }
    return true;
  }
  //------------------------------------------ Compute Unit Existence ----------------------------------------
  void GameImpl::computeUnitExistence()
  {
    foreach(UnitImpl* u, aliveUnits) //all alive units are dying until proven alive
    {
      u->wasAlive = true;
      u->isAlive  = false;
    }
    lastEvadedUnits = evadeUnits;//save last evaded units for updating shared memory (Server.cpp)

    //set the wasAccessible and wasVisible fields
    foreach(UnitImpl* u, accessibleUnits)
      u->wasAccessible = true;
    foreach(UnitImpl* u, evadeUnits)
      u->wasAccessible = false;

    //fill dyingUnits set with all aliveUnits and then clear the aliveUnits set.
    dyingUnits = aliveUnits;
    aliveUnits.clear();
    //Now we will add alive units to the aliveUnits set and remove them from the dyingUnits set based on the Broodwar unit lists:

    //compute alive and dying units
    for(UnitImpl* u = UnitImpl::BWUnitToBWAPIUnit(*BW::BWDATA_UnitNodeList_VisibleUnit_First); u; u = u->getNext())
    {
      if (isAlive(u))
      {
        u->isAlive = true;
        aliveUnits.insert(u);
        dyingUnits.erase(u);
        u->updateInternalData();
      }
    }
    for(UnitImpl* u = UnitImpl::BWUnitToBWAPIUnit(*BW::BWDATA_UnitNodeList_HiddenUnit_First); u; u = u->getNext())
    {
      if (isAlive(u,true))
      {
        u->isAlive = true;
        aliveUnits.insert(u);
        dyingUnits.erase(u);
        u->updateInternalData();
      }
    }
    for(UnitImpl* u = UnitImpl::BWUnitToBWAPIUnit(*BW::BWDATA_UnitNodeList_ScannerSweep_First); u; u = u->getNext())
    {
      if (isAlive(u))
      {
        u->isAlive = true;
        aliveUnits.insert(u);
        dyingUnits.erase(u);
        u->updateInternalData();
      }
    }
    //set the exists field to false for all dying units (though we don't update/clear their data yet)
    foreach(UnitImpl* u, dyingUnits)
      u->self->exists = false;
  }
  //------------------------------------------ Compute Client Sets -------------------------------------------
  void GameImpl::computePrimaryUnitSets()
  {
    //this frame computes the set of accessible units and visible units.
    accessibleUnits.clear();

    //discoverUnits is the set of units that have entered the accessibleUnits set this frame
    discoverUnits.clear();

    //evadeUnits is the set of units that have left the accessibleUnits set this frame
    evadeUnits.clear();

    //computes sets, also generating UnitCreate, UnitDiscover, UnitShow, UnitDestroy, UnitEvade, and UnitHide callbacks
    foreach(UnitImpl* u, aliveUnits)
    {
      if (u->canAccess())
      {
        if ( !u->wasAlive )
          events.push_back(Event::UnitCreate(u));
        if ( !u->wasAccessible )
        {
          discoverUnits.push_back(u);
          events.push_back(Event::UnitDiscover(u));
        }
        if (u->isVisible())
        {
          if ( !u->wasVisible )
            events.push_back(Event::UnitShow(u));
          u->wasVisible = true;
        }
        accessibleUnits.insert(u);
      }
      else
      {
        if (u->wasAccessible)
        {
          if (u->wasVisible)
          {
            u->wasVisible = false;
            events.push_back(Event::UnitHide(u));
          }
          evadeUnits.push_back(u);
          events.push_back(Event::UnitEvade(u));
        }
      }
    }
    foreach(UnitImpl* u, dyingUnits)
    {
      if (u->wasAccessible)
      {
        if (u->wasVisible)
        {
          u->wasVisible = false;
          events.push_back(Event::UnitHide(u));
        }
        evadeUnits.push_back(u);
        events.push_back(Event::UnitEvade(u));
        events.push_back(Event::UnitDestroy(u));
      }
    }
  }
  void GameImpl::extractUnitData()
  {
    //this function extracts all current unit information from Broodwar memory for all the accessible units
    //and also generates the NukeDetect event when needed
    foreach (UnitImpl *i, aliveUnits)
    {
      i->connectedUnits.clear();
      i->loadedUnits.clear();
      int airWeaponCooldown = i->getOriginalRawData->airWeaponCooldown;
      if ( i->getOriginalRawData->subUnit )
        airWeaponCooldown = i->getOriginalRawData->subUnit->airWeaponCooldown;
      int groundWeaponCooldown = i->getOriginalRawData->groundWeaponCooldown;
      if ( i->getOriginalRawData->subUnit )
        groundWeaponCooldown = i->getOriginalRawData->subUnit->groundWeaponCooldown;
      if ( i->getOriginalRawData->unitType == BW::UnitID::Protoss_Reaver )
        groundWeaponCooldown = i->getOriginalRawData->mainOrderTimer;

      i->startingAttack           = airWeaponCooldown > i->lastAirWeaponCooldown || groundWeaponCooldown > i->lastGroundWeaponCooldown;
      i->lastAirWeaponCooldown    = airWeaponCooldown;
      i->lastGroundWeaponCooldown = groundWeaponCooldown;
      if (i->canAccess())
      {
        if (i->getID() == -1)
          i->setID(server.getUnitID(i));
        i->updateData();
      }
      if ( i->getOriginalRawData->unitType == BW::UnitID::Terran_NuclearMissile )
      {
        if ( !i->nukeDetected )
        {
          i->nukeDetected = true;
          Position target(i->getOriginalRawData->orderTargetPos.x, i->getOriginalRawData->orderTargetPos.y);
          if (isFlagEnabled(Flag::CompleteMapInformation) || isVisible(target.x()/32,target.y()/32))
            events.push_back(Event::NukeDetect(target));
          else
            events.push_back(Event::NukeDetect(Positions::Unknown));
        }
      }
    }
  }
  void GameImpl::augmentUnitData()
  {
    //this function modifies the extracted unit data for build unit, loaded units, larva, and interceptors
    foreach(UnitImpl* i, accessibleUnits)
    {
      UnitImpl* orderTargetUnit = UnitImpl::BWUnitToBWAPIUnit(i->getOriginalRawData->orderTargetUnit);
      if ( orderTargetUnit && orderTargetUnit->exists() && i->getOrder() == Orders::ConstructingBuilding )
      {
        UnitImpl* j             = orderTargetUnit;
        i->self->buildUnit      = server.getUnitID((Unit*)j);
        i->self->isConstructing = true;
        i->self->isIdle         = false;
        i->self->buildType      = j->self->type;
        j->self->buildUnit      = server.getUnitID((Unit*)i);
        j->self->isConstructing = true;
        j->self->isIdle         = false;
        j->self->buildType      = j->self->type;
      }
      else if ( i->getAddon() && !i->getAddon()->isCompleted() )
      {
        UnitImpl* j             = (UnitImpl*)i->getAddon();
        i->self->buildUnit      = server.getUnitID((Unit*)j);
        i->self->isConstructing = true;
        i->self->isIdle         = false;
        i->self->buildType      = j->self->type;
        j->self->buildUnit      = server.getUnitID((Unit*)i);
        j->self->isConstructing = true;
        j->self->isIdle         = false;
        j->self->buildType      = j->self->type;
      }
      if ( i->getTransport() )
        ((UnitImpl*)i->getTransport())->loadedUnits.insert((Unit*)i);

      if ( i->getHatchery() )
      {
        UnitImpl* hatchery = (UnitImpl*)i->getHatchery();
        hatchery->connectedUnits.insert((Unit*)i);
        if (hatchery->connectedUnits.size() >= 3)
          hatchery->self->remainingTrainTime = 0;
      }
      if ( i->getCarrier() )
        ((UnitImpl*)i->getCarrier())->connectedUnits.insert((Unit*)i);

    }
  }
  void GameImpl::applyLatencyCompensation()
  {
    //apply latency compensation
    while ((int)(this->commandBuffer.size()) > this->getLatency()+15)
    {
      for (unsigned int i = 0; i < this->commandBuffer[0].size(); i++)
        delete this->commandBuffer[0][i];
      this->commandBuffer.erase(this->commandBuffer.begin());
    }
    this->commandBuffer.push_back(std::vector<Command *>());
    for (unsigned int i = 0; i < this->commandBuffer.size(); i++)
      for (unsigned int j = 0; j < this->commandBuffer[i].size(); j++)
        this->commandBuffer[i][j]->execute(this->commandBuffer.size()-1-i);
  }
  void GameImpl::computeSecondaryUnitSets()
  {
    // This function computes units on tile, player units, neutral units, minerals, geysers, pylons, and static unit sets
    // Also generates the UnitMorph and UnitRenegade callbacks
    for (int y = 0; y < Map::getHeight(); y++)
      for (int x = 0; x < Map::getWidth(); x++)
        this->unitsOnTileData[x][y].clear();

    foreach(UnitImpl* u, discoverUnits)
    {
      ((PlayerImpl*)u->getPlayer())->units.insert(u);
      if (u->getPlayer()->isNeutral())
      {
        neutralUnits.insert(u);
        if (u->getType() == UnitTypes::Resource_Mineral_Field)
          minerals.insert(u);
        else if (u->getType() == UnitTypes::Resource_Vespene_Geyser)
          geysers.insert(u);
      }
      else
      {
        if (u->getPlayer() == Broodwar->self() && u->getType() == UnitTypes::Protoss_Pylon)
          pylons.insert(u);
      }
    }
    foreach(UnitImpl* u, evadeUnits)
    {
      ((PlayerImpl*)u->getPlayer())->units.erase(u);
      if (u->getPlayer()->isNeutral())
      {
        neutralUnits.erase(u);
        if (u->getType() == UnitTypes::Resource_Mineral_Field)
          minerals.erase(u);
        else if (u->getType() == UnitTypes::Resource_Vespene_Geyser)
          geysers.erase(u);
      }
      else if (u->getPlayer() == Broodwar->self() && u->getType() == UnitTypes::Protoss_Pylon)
      {        
        pylons.erase(u);
      }
    }
    foreach(UnitImpl* i, accessibleUnits)
    {
      if ( i->getType().isBuilding() && !i->isLifted() )
      {
        int tx = i->getTilePosition().x();
        int ty = i->getTilePosition().y();
        for(int x = tx; x < tx + i->getType().tileWidth(); ++x)
          for(int y = ty; y < ty + i->getType().tileHeight(); ++y)
            unitsOnTileData[x][y].insert(i);
      }
      else
      {
        int startX = (i->_getPosition.x() - i->_getType.dimensionLeft()) / TILE_SIZE;
        int endX   = (i->_getPosition.x() + i->_getType.dimensionRight() + TILE_SIZE - 1) / TILE_SIZE; // Division - round up
        int startY = (i->_getPosition.y() - i->_getType.dimensionUp())   / TILE_SIZE;
        int endY   = (i->_getPosition.y() + i->_getType.dimensionDown()  + TILE_SIZE - 1) / TILE_SIZE;
        for (int x = startX; x < endX; x++)
          for (int y = startY; y < endY; y++)
            unitsOnTileData[x][y].insert(i);
      }
      if (i->lastType != i->_getType && i->lastType != UnitTypes::Unknown && i->_getType != UnitTypes::Unknown)
      {
        events.push_back(Event::UnitMorph(i));
        if (i->lastType == UnitTypes::Resource_Vespene_Geyser)
        {
          neutralUnits.erase(i);
          geysers.erase(i);
        }
        if (i->_getType == UnitTypes::Resource_Vespene_Geyser)
        {
          neutralUnits.insert(i);
          geysers.insert(i);
        }
      }
      if (i->lastPlayer != i->_getPlayer && i->lastPlayer && i->_getPlayer )
      {
        events.push_back(Event::UnitRenegade(i));
        ((PlayerImpl*)i->lastPlayer)->units.erase(i);
        ((PlayerImpl*)i->_getPlayer)->units.insert(i);
      }
      i->lastPlayer = i->_getPlayer;
      i->lastType   = i->_getType;
    }

    if (this->staticNeutralUnits.empty()) //if we haven't saved the set of static units, save them now
    {
      foreach (UnitImpl* i, accessibleUnits)
      {
        if (i->_getPlayer->isNeutral())
        {
          i->saveInitialInformation();
          this->staticNeutralUnits.insert(i);
          if (i->_getType == UnitTypes::Resource_Mineral_Field)
            this->staticMinerals.insert(i);
          else if (i->_getType == UnitTypes::Resource_Vespene_Geyser)
          {
            this->staticGeysers.insert(i);
          }
        }
      }
    }
  }
  //---------------------------------------------- UPDATE UNITS ----------------------------------------------
  void GameImpl::updateUnits()
  {
    computeUnitExistence();
    computePrimaryUnitSets();
    extractUnitData();
    augmentUnitData();
    applyLatencyCompensation();
    computeSecondaryUnitSets();
  }
  void GameImpl::processEvents()
  {
    //This function translates events into AIModule callbacks
    if ( !client )
      return;
    if (server.isConnected())
      return;
    foreach(Event e, events)
    {
      EventType::Enum et = e.type;
      switch (et)
      {
      case EventType::MatchStart:
        client->onStart();
        break;
      case EventType::MatchEnd:
        client->onEnd(e.isWinner);
        break;
      case EventType::MatchFrame:
        client->onFrame();
        break;
      case EventType::MenuFrame:
        break;
      case EventType::SendText:
        client->onSendText(e.text);
        break;
      case EventType::ReceiveText:
        client->onReceiveText(e.player, e.text);
        break;
      case EventType::PlayerLeft:
        client->onPlayerLeft(e.player);
        break;
      case EventType::NukeDetect:
        client->onNukeDetect(e.position);
        break;
      case EventType::UnitDiscover:
        client->onUnitDiscover(e.unit);
        break;
      case EventType::UnitEvade:
        client->onUnitEvade(e.unit);
        break;
      case EventType::UnitCreate:
        client->onUnitCreate(e.unit);
        break;
      case EventType::UnitDestroy:
        client->onUnitDestroy(e.unit);
        break;
      case EventType::UnitMorph:
        client->onUnitMorph(e.unit);
        break;
      case EventType::UnitShow:
        client->onUnitShow(e.unit);
        break;
      case EventType::UnitHide:
        client->onUnitHide(e.unit);
        break;
      case EventType::UnitRenegade:
        client->onUnitRenegade(e.unit);
        break;
      case EventType::SaveGame:
        client->onSaveGame(e.text);
        break;
      default:
        break;
      }
    }
  }
  //--------------------------------------------- UPDATE BULLETS ---------------------------------------------
  void GameImpl::updateBullets()
  {
    //update bullet information
    for(int i = 0; i < BULLET_ARRAY_MAX_LENGTH; ++i)
      this->bulletArray[i]->setExists(false);
    std::set<Bullet*> lastBullets = bullets;
    bullets.clear();
    for(BW::Bullet* curritem = *BW::BWDATA_BulletNodeTable_FirstElement; curritem; curritem = curritem->nextBullet)
    {
      BulletImpl* b = BulletImpl::BWBulletToBWAPIBullet(curritem);
      b->setExists(true);
      b->updateData();
      if (b->exists())
        this->bullets.insert(b);
      lastBullets.erase(b);
    }
    foreach(BulletImpl* b, lastBullets)
      b->updateData();
    for(int i = 0; i < BULLET_ARRAY_MAX_LENGTH; ++i)
      this->bulletArray[i]->saveExists();
  }
  //--------------------------------------------- SET LAST ERROR ---------------------------------------------
  void GameImpl::setLastError(BWAPI::Error e)
  {
    /* implies that an error has occured */
    this->lastError = e;
  }
  //----------------------------------------------------- DRAW -----------------------------------------------
  bool GameImpl::inScreen(int ctype, int x, int y)
  {
    int screen_x1 = x;
    int screen_y1 = y;
    switch ( ctype )
    {
    case 2: // if we're using map coordinates, subtract the position of the screen to convert the coordinates into screen coordinates
      screen_x1 -= *(BW::BWDATA_ScreenX);
      screen_y1 -= *(BW::BWDATA_ScreenY);
      break;
    case 3: // if we're using mouse coordinates, add the position of the mouse to convert the coordinates into screen coordinates
      screen_x1 += BW::BWDATA_Mouse->x;
      screen_y1 += BW::BWDATA_Mouse->y;
      break;
    }
    if (screen_x1 < 0   || 
        screen_y1 < 0   ||
        screen_x1 > BW::BWDATA_GameScreenBuffer->wid || 
        screen_y1 > BW::BWDATA_GameScreenBuffer->ht)
      return false;
    return true;
  }

  bool GameImpl::inScreen(int ctype, int x1, int y1, int x2, int y2)
  {
    int screen_x1 = x1;
    int screen_y1 = y1;
    int screen_x2 = x2;
    int screen_y2 = y2;
    switch ( ctype )
    {
    case 2: // if we're using map coordinates, subtract the position of the screen to convert the coordinates into screen coordinates
      screen_x1 -= *(BW::BWDATA_ScreenX);
      screen_y1 -= *(BW::BWDATA_ScreenY);
      screen_x2 -= *(BW::BWDATA_ScreenX);
      screen_y2 -= *(BW::BWDATA_ScreenY);
      break;
    case 3: // if we're using mouse coordinates, add the position of the mouse to convert the coordinates into screen coordinates
      screen_x1 += BW::BWDATA_Mouse->x;
      screen_y1 += BW::BWDATA_Mouse->y;
      screen_x2 += BW::BWDATA_Mouse->x;
      screen_y2 += BW::BWDATA_Mouse->y;
      break;
    }
    BW::rect scrLimit = { 0, 0, BW::BWDATA_GameScreenBuffer->wid, BW::BWDATA_GameScreenBuffer->ht };
    if ((screen_x1 < 0 && screen_x2 < 0) ||
        (screen_y1 < 0 && screen_y2 < 0) ||
        (screen_x1 > scrLimit.Xmax  && screen_x2 > scrLimit.Xmax) ||
        (screen_y1 > scrLimit.Ymax && screen_y2 > scrLimit.Ymax))
      return false;
    return true;
  }

  bool GameImpl::inScreen(int ctype, int x1, int y1, int x2, int y2, int x3, int y3)
  {
    int screen_x1 = x1;
    int screen_y1 = y1;
    int screen_x2 = x2;
    int screen_y2 = y2;
    int screen_x3 = x3;
    int screen_y3 = y3;
    switch ( ctype )
    {
    case 2: // if we're using map coordinates, subtract the position of the screen to convert the coordinates into screen coordinates
      screen_x1 -= *(BW::BWDATA_ScreenX);
      screen_y1 -= *(BW::BWDATA_ScreenY);
      screen_x2 -= *(BW::BWDATA_ScreenX);
      screen_y2 -= *(BW::BWDATA_ScreenY);
      screen_x3 -= *(BW::BWDATA_ScreenX);
      screen_y3 -= *(BW::BWDATA_ScreenY);
      break;
    case 3: // if we're using mouse coordinates, add the position of the mouse to convert the coordinates into screen coordinates
      screen_x1 += BW::BWDATA_Mouse->x;
      screen_y1 += BW::BWDATA_Mouse->y;
      screen_x2 += BW::BWDATA_Mouse->x;
      screen_y2 += BW::BWDATA_Mouse->y;
      screen_x3 += BW::BWDATA_Mouse->x;
      screen_y3 += BW::BWDATA_Mouse->y;
      break;
    }
    BW::rect scrLimit = { 0, 0, BW::BWDATA_GameScreenBuffer->wid, BW::BWDATA_GameScreenBuffer->ht };
    if ((screen_x1 < 0 && screen_x2 < 0 && screen_x3 < 0) ||
        (screen_y1 < 0 && screen_y2 < 0 && screen_y3 < 0) ||
        (screen_x1 > scrLimit.Xmax && screen_x2 > scrLimit.Xmax && screen_x3 > scrLimit.Xmax) ||
        (screen_y1 > scrLimit.Ymax && screen_y2 > scrLimit.Ymax && screen_y3 > scrLimit.Ymax))
      return false;
    return true;
  }
//--------------------------------------------------- ON SAVE ------------------------------------------------
  void GameImpl::onSaveGame(char *name)
  {
    /* called when the game is being saved */
    events.push_back(Event::SaveGame(std::string(name)));
  }
//--------------------------------------------------- ISCRIPT ------------------------------------------------
  BWAPI::UnitImpl *GameImpl::spriteToUnit(BW::CSprite *sprite)
  {
    /* Retrieves a sprite's parent unit */
    BWAPI::UnitImpl* unit=NULL;
    for (int i = 0; i < UNIT_ARRAY_MAX_LENGTH; i++) // iterate through every unit
      if (BW::BWDATA_UnitNodeTable->unit[i].sprite == sprite) // compare unit with sprite we're looking for
        unit = unitArray[i];

    return unit;
  }

  void GameImpl::iscriptParser(BW::CSprite *sprite, u8 anim)
  {
    BWAPI::UnitImpl *unit = spriteToUnit(sprite); // get sprite's parent unit
    if ( unit )   // make sure the unit exists
      unit->animState = anim; // associate the animation directly with the unit
  }
  //---------------------------------------------- ON SEND TEXT ----------------------------------------------
  void GameImpl::onSendText(const char* text)
  {
    if ( !parseText(text) && isFlagEnabled(BWAPI::Flag::UserInput) )
    {
      if ( externalModuleConnected )
        events.push_back(Event::SendText(std::string(text)));
      else
        sendText("%s", text);
    }
  }
  //---------------------------------------------- ON RECV TEXT ----------------------------------------------
  void GameImpl::onReceiveText(int playerId, std::string text)
  {
    /* Do onReceiveText */
    int realId = stormIdToPlayerId(playerId);
    if ( realId != -1 && 
         (!this->BWAPIPlayer ||
          realId != this->BWAPIPlayer->getIndex() ) &&
         this->isFlagEnabled(BWAPI::Flag::UserInput) )
      events.push_back(Event::ReceiveText(this->players[realId], text));
  }
  //------------------------------------------- CENTER ON SELECTED -------------------------------------------
  void GameImpl::moveToSelected()
  {
    int count = this->selectedUnitSet.size();
    int x = 0;
    int y = 0;
    foreach(BWAPI::UnitImpl *u, this->selectedUnitSet)
    {
      x += u->getPosition().x();
      y += u->getPosition().y();
    }
    x /= count;
    y /= count;
    x -= BW::BWDATA_GameScreenBuffer->wid / 2;
    y -= BW::BWDATA_GameScreenBuffer->ht  / 2 - 40;
    if ( x < 0 )
      x = 0;
    if ( y < 0 )
      y = 0;
    this->setScreenPosition(x, y);
  }
}