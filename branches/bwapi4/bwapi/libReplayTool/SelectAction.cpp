#include "SelectAction.h"
#include "DefaultActions.h"
#include "AbstractReplayReader.h"
#include "StrUtil.h"
#include <cassert>

using namespace std;
using namespace BWAPI;
using namespace ReplayTool;

ActionID deduceSelectActionFrom(SelectAction::SelectType type)
{
  switch (type)
  {
  case SelectAction::SELECT_DeltaAdd:
    return ReplayTool::Select_Delta_Add;
  case SelectAction::SELECT_DeltaDel:
    return ReplayTool::Select_Delta_Del;
  case SelectAction::SELECT_Units:
    return ReplayTool::Select_Units;
  default:
    assert(0);
    return 0;
  }
}

SelectAction::SelectAction(PlayerID player, SelectType myType)
  :GameAction(player, deduceSelectActionFrom(myType))
  ,unitsCount(0)
  ,type(myType)
{
}

SelectAction::SelectAction(PlayerID player, SelectType myType, const SelectUnitData mySelectedUnits[], unsigned myUnitsCount)
  :GameAction(player, deduceSelectActionFrom(myType))
  ,unitsCount(myUnitsCount)
  ,type(myType)
{
  for (unsigned i = 0; i < unitsCount; ++i)
    selectedUnits[i] = mySelectedUnits[i];
}

void SelectAction::read(AbstractReplayReader &reader)
{
  unitsCount = (unsigned)reader.readBYTE();

  if (unitsCount > MAX_UNITS)
    unitsCount = MAX_UNITS;

  WORD selectData;

  for (unsigned i = 0; i < unitsCount; ++i)
  {
    selectData =  reader.readWORD();
    selectedUnits[i].unitID = EXTRACT_SELECT_DATA_UNITID(selectData);
    selectedUnits[i].data = EXTRACT_SELECT_DATA_DATA(selectData);
  }
}

string SelectAction::toString() const
{
  const size_t BUFF_SIZE = 128;
  char buffer[BUFF_SIZE];
  string str = GameAction::toString();

  sprintf_s(buffer, BUFF_SIZE, "%u", unitsCount);
  str += buffer;

  for (unsigned i = 0; i < unitsCount; ++i)
  {
    sprintf_s(buffer, BUFF_SIZE, ", %u:%02X", selectedUnits[i].unitID, selectedUnits[i].data);
    str += buffer;
  }

  return str;
}