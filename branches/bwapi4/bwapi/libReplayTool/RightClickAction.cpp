#include "RightClickAction.h"
#include "DefaultActions.h"
#include "StrUtil.h"
#include "AbstractReplayReader.h"

using namespace std;
using namespace BWAPI;
using namespace ReplayTool;

RightClickAction::RightClickAction(PlayerID player)
  : GameAction(player, ReplayTool::Right_Click)
  ,x(0)
  ,y(0)
  ,targetID(0)
  ,how(0)
{
}

RightClickAction::RightClickAction(PlayerID player, short myX, short myY, WORD mytargetID, BWAPI::UnitType myUnitType, BYTE myHow)
  : GameAction(player, ReplayTool::Right_Click)
  ,x(myX)
  ,y(myY)
  ,targetID(mytargetID)
  ,unitType(myUnitType)
  ,how(myHow)
{

}

void RightClickAction::read(AbstractReplayReader &reader)
{
  x = reader.readWORD();
  y = reader.readWORD();
  targetID = reader.readWORD();
  unitType = reader.readUnitType();
  how = reader.readBYTE();
}

string RightClickAction::toString() const
{
  string str = GameAction::toString();
  str += StrUtil::format("(%d, %d), %u:%02X, %s%s", x, y, targetID & 0x7FF, targetID >> 12, unitType.c_str(), how ? ", Queued" : "");

  return str;
}