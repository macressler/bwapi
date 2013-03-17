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

template <int TYPE>
struct CanMake
{
  bool operator ()(Unit *u) const
  { return Broodwar->canMake(TYPE, u); }
};

std::function<void(Unit*)> BuildAction(UnitType type)
{
  return [=](Unit *u){ u->build(type, Broodwar->getBuildLocation(type, TilePosition(u->getPosition()))); Broodwar << Broodwar->getLastError() << endl; };
}

CompareFilter<Unit*> CompletedUnitCount(UnitType type)
{
  return [=](Unit*){ return self->completedUnitCount(type); };
}

void addTestCase(Unit *pUnit, const std::function<void(Unit*)> &action, const UnitFilter &completion, int timeout)
{
  if ( !pUnit )
    return;
  
  int endTime = Broodwar->getFrameCount() + timeout;
  pUnit->registerEvent(action, IsCompleted && IsIdle, 1);
  //pUnit->registerEvent([&](Unit *u){ Broodwar << ((!completion.isValid() || completion(u)) ? "PASS" : "FAIL") << endl; }, [endTime](Unit*){return endTime < Broodwar->getFrameCount();}, 1);
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
    UnitType toBuild = unit->getType().getRace().getCenter();
    //addTestCase(unit, BuildAction(toBuild), CompletedUnitCount(toBuild) > 0, 200);
    unit->registerEvent(BuildAction(toBuild), IsIdle && IsCompleted, 1, 6);
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

