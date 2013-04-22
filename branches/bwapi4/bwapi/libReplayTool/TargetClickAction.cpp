#include "TargetClickAction.h"
#include "DefaultActions.h"
#include "StrUtil.h"
#include "AbstractReplayReader.h"

using namespace std;
using namespace BWAPI;
using namespace ReplayTool;

TargetClickAction::TargetClickAction(PlayerID player)
  : GameAction(player, ReplayTool::Target_Click)
  ,x(0)
  ,y(0)
  ,targetID(0)
  ,how(0)
{
}

TargetClickAction::TargetClickAction(PlayerID player, short myX, short myY, WORD mytargetID, BWAPI::UnitType myUnitType, BYTE myHow, BWAPI::Order myOrderType)
  : GameAction(player, ReplayTool::Target_Click)
  ,x(myX)
  ,y(myY)
  ,targetID(mytargetID)
  ,unitType(myUnitType)
  ,how(myHow)
  ,orderType(myOrderType)
{

}

void TargetClickAction::read(AbstractReplayReader &reader)
{
  x = reader.readWORD();
  y = reader.readWORD();
  targetID = reader.readWORD();
  unitType = reader.readUnitType();
  orderType = reader.readOrder();
  how = reader.readBYTE();
}

string TargetClickAction::toString() const
{
  string str = GameAction::toString();
  str += StrUtil::format("(%d, %d), %u:%02X, %s, %s%s", x, y, targetID & 0x7FF, targetID >> 12, unitType.c_str(), orderType.c_str(), how ? ", Queued" : "");

  return str;
}