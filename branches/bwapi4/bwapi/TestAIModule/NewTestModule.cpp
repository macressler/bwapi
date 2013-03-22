#include "NewTestModule.h"
#include <queue>
#include <functional>

using namespace BWAPI;
using namespace std;

Player *self;

void DebugUnit(Unit *pUnit, const char * const fxn)
{
  Broodwar << fxn << ": " << pUnit->getType() << " owned by " << (pUnit->getPlayer() ? pUnit->getPlayer()->getName() : "unknown") << endl;
}

struct DrawBoxEvt
{
  int left, top, right, bottom;
  DrawBoxEvt(int l, int t, int r, int b) 
    : left(l), top(t), right(r), bottom(b)
  {}
  void operator() ( Game*) 
  {
    Broodwar->drawBoxMap(left, top, right, bottom, Colors::Green);
  }
};

struct BuildAction
{
  UnitType type;
  BuildAction(UnitType t) : type(t) {}
  void operator()(Unit *u)
  {
    TilePosition targPos = Broodwar->getBuildLocation(type, TilePosition(u->getPosition()) );
    if ( Broodwar->getLastError() != Errors::None )
      Broodwar << Broodwar->getLastError() << endl;
    
    u->build(type, targPos );
    if ( Broodwar->getLastError() != Errors::None )
      Broodwar << Broodwar->getLastError() << endl;
    
    Broodwar->registerEvent( DrawBoxEvt(targPos.x*32, targPos.y*32, targPos.x*32 + 4*32, targPos.y*32 + 3*32), nullptr, 100000 );
  }
};
/*
std::function<void(Unit*)> BuildAction(UnitType type)
{
  return [=](Unit *u){ u->build(type, Broodwar->getBuildLocation(type, TilePosition(u->getPosition()))); Broodwar << Broodwar->getLastError() << endl; };
}*/

struct CompletedUnitCount
{
  UnitType type;
  CompletedUnitCount(UnitType t) : type(t) {}
  bool operator()(Unit *)
  {
    return self->completedUnitCount(type) > 0;
  }
};
/*
CompareFilter<Unit*> CompletedUnitCount(UnitType type)
{
  return [=](Unit*){ return self->completedUnitCount(type); };
}*/

struct TimeTest
{
  int endTime;

  TimeTest(int t) : endTime(t) {}
  bool operator() (Unit *)
  {
    return endTime < Broodwar->getFrameCount();
  }
};

struct CompleteAction
{
  UnitFilter completionCmp;
  CompleteAction(const UnitFilter &c) : completionCmp(c) {}
  void operator()(Unit *u)
  {
    Broodwar << ((!completionCmp.isValid() || completionCmp(u)) ? "PASS" : "FAIL") << endl;
  }
};

void addTestCase(Unit *pUnit, const std::function<void(Unit*)> &action, const UnitFilter &completion, int timeout)
{
  if ( !pUnit )
    return;
  
  int endTime = Broodwar->getFrameCount() + timeout;
  pUnit->registerEvent(action, IsCompleted && IsIdle, 1, 6);
  pUnit->registerEvent(CompleteAction(completion), TimeTest(endTime), 1, 6);
}

void NewTestModule::onStart()
{
  Broodwar->enableFlag(Flag::UserInput);
  self = Broodwar->self();
}
void NewTestModule::onEnd(bool isWinner)
{
}
void NewTestModule::onFrame()
{
}
void NewTestModule::onSendText(std::string text)
{
}
void NewTestModule::onReceiveText(BWAPI::Player* player, std::string text)
{
}
void NewTestModule::onPlayerLeft(BWAPI::Player* player)
{
}
void NewTestModule::onNukeDetect(BWAPI::Position target)
{
}
void NewTestModule::onUnitDiscover(BWAPI::Unit* unit)
{
  //DebugUnit(unit, __FUNCTION__);
}
void NewTestModule::onUnitEvade(BWAPI::Unit* unit)
{
  //DebugUnit(unit, __FUNCTION__);
}
void NewTestModule::onUnitShow(BWAPI::Unit* unit)
{
  //DebugUnit(unit, __FUNCTION__);
}
void NewTestModule::onUnitHide(BWAPI::Unit* unit)
{
  //DebugUnit(unit, __FUNCTION__);
}
void NewTestModule::onUnitCreate(BWAPI::Unit* unit)
{
  DebugUnit(unit, __FUNCTION__);
  if ( unit->getPlayer() == self && unit->getType().isWorker() )
  {
    Broodwar << unit->getType() << endl;
    UnitType toBuild = unit->getType().getRace().getCenter();
    addTestCase(unit, BuildAction(toBuild), CompletedUnitCount(toBuild), 250);
    //unit->registerEvent(BuildAction(toBuild), IsIdle && IsCompleted, 1, 6);
  }
}
void NewTestModule::onUnitDestroy(BWAPI::Unit* unit)
{
  //DebugUnit(unit, __FUNCTION__);
}
void NewTestModule::onUnitMorph(BWAPI::Unit* unit)
{
  //DebugUnit(unit, __FUNCTION__);
}
void NewTestModule::onUnitRenegade(BWAPI::Unit* unit)
{
  //DebugUnit(unit, __FUNCTION__);
}
void NewTestModule::onSaveGame(std::string gameName)
{
}
void NewTestModule::onUnitComplete(BWAPI::Unit *unit)
{
  //DebugUnit(unit, __FUNCTION__);
}

