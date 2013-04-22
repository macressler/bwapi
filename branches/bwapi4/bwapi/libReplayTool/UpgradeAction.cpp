#include "UpgradeAction.h"
#include "DefaultActions.h"
#include "AbstractReplayReader.h"

using namespace std;
using namespace BWAPI;
using namespace ReplayTool;

UpgradeAction::UpgradeAction(PlayerID player)
  : GameAction(player, ReplayTool::Upgrade)
  , upgradeType(BWAPI::UpgradeTypes::Carrier_Capacity)

{
}

UpgradeAction::UpgradeAction(PlayerID player, BWAPI::UpgradeType myTech)
  : GameAction(player, ReplayTool::Upgrade)
  , upgradeType(myTech)

{
}

void UpgradeAction::read(AbstractReplayReader &reader)
{
  upgradeType = reader.readUpgradeType();
}

string UpgradeAction::toString() const
{
  const size_t BUFF_SIZE = 128;
  char buffer[BUFF_SIZE];
  string str = GameAction::toString();

  sprintf_s(buffer, BUFF_SIZE, "%s", upgradeType.c_str());
  str += buffer;

  return str;
}