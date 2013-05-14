#include "DevAIModule.h"

#include <BWAPI/Filters.h>
#include <algorithm>

using namespace BWAPI;
using namespace Filter;

bool enabled;
int mapH, mapW;

DWORD dwCount = 0;

Player *self;

////////////////////////////////
void DevAIModule::onStart()
{
  // enable stuff
  bw->enableFlag(Flag::UserInput);

  // save player info
  self = bw->self();

  // save map info
  mapH = bw->mapHeight();
  mapW = bw->mapWidth();

  // make things go fast
  //bw->setLocalSpeed(0);
  //bw->setFrameSkip(16);

  // set command optimization
  bw->setCommandOptimizationLevel(3);
}

void DevAIModule::onEnd(bool isWinner)
{
}

void DevAIModule::onFrame()
{
  if ( bw->isReplay() ) // ignore everything if in a replay
    return;

  // Log and display the best logical FPS seen in the game
  static int bestFPS = 0;
  bestFPS = std::max(bestFPS, Broodwar->getFPS());
  Broodwar->drawTextScreen(Positions::Origin, "%cBest: %d FPS\nCurrent: %d FPS", Text::White, bestFPS, Broodwar->getFPS() );
  
  // Limit logical frames processed to prevent stacking commands
  if ( Broodwar->getFrameCount() % Broodwar->getLatencyFrames() != 0 )
    return;

  // Iterate our own units
  Unitset myUnits = self->getUnits();
  for ( auto u = myUnits.begin(); u != myUnits.end(); ++u )
  {
    if ( u->getType().isWorker() && u->isIdle() )
      u->gather( u->getClosestUnit( Filter::IsMineralField) );

  }

}

void DevAIModule::onSendText(std::string text)
{
  if ( text == "/wiki" )
  {
    writeUnitWiki();
    writeWeaponWiki();
    Broodwar->printf("Generated wiki pages!");
  }
  else
  {
    Broodwar->sendText("%s", text.c_str());
  }
}

void DevAIModule::onReceiveText(BWAPI::Player* player, std::string text)
{
}

void DevAIModule::onPlayerLeft(BWAPI::Player* player)
{
}

void DevAIModule::onNukeDetect(BWAPI::Position target)
{
}

void DevAIModule::onUnitDiscover(BWAPI::Unit* unit)
{
}

void DevAIModule::onUnitEvade(BWAPI::Unit* unit)
{
}

void DevAIModule::onUnitShow(BWAPI::Unit* unit)
{
}

void DevAIModule::onUnitHide(BWAPI::Unit* unit)
{
}

void newOnUnitComplete(BWAPI::Unit *unit);

void DevAIModule::onUnitCreate(BWAPI::Unit* unit)
{
  //unit->registerEvent(newOnUnitComplete, IsCompleted, 1);
  //Broodwar << __FUNCTION__ " -- " << unit->getPlayer()->getName() << ": " << unit->getType() << std::endl;
}

void DevAIModule::onUnitDestroy(BWAPI::Unit* unit)
{
}

void DevAIModule::onUnitMorph(BWAPI::Unit* unit)
{
}

void DevAIModule::onUnitRenegade(BWAPI::Unit* unit)
{
}

void DevAIModule::onSaveGame(std::string gameName)
{
}

void DevAIModule::onUnitComplete(BWAPI::Unit *unit)
{
  //Broodwar << __FUNCTION__ << " -- " << unit->getType() << std::endl;
}

void newOnUnitComplete(BWAPI::Unit *unit)
{
  //Broodwar << __FUNCTION__ " -- " << unit->getType() << std::endl;
}
