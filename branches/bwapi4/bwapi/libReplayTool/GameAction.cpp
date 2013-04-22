#include "GameAction.h"
#include <cstdio>
#include "DefaultActions.h"

using namespace std;
using namespace BWAPI;
using namespace ReplayTool;

void GameAction::Factory::add(GameAction* prototype)
{
  if (prototype != nullptr)
  {
    if (actions.find(prototype->getAction()) == actions.end())
      actions.insert(make_pair(prototype->getAction(), prototype));
  }
}

GameAction* GameAction::Factory::create(PlayerID player, ActionID action)
{
  ActionMap::iterator itr = actions.find(action);

  if (itr != actions.end())
    return (*itr).second->from(player);
  else
    return nullptr;
}

GameAction::Factory& GameAction::Factory::instance()
{
  static Factory instance;
  return instance;
}

GameAction::GameAction(PlayerID _player, ActionID _action)
  :player(_player)
  ,action(_action)
{
}

string GameAction::toString() const
{
  const size_t BUFF_SIZE = 128;
  char buffer[BUFF_SIZE];
  const char* actionName = action < ReplayTool::Max ? ReplayTool::pszActionNames[action] : "INVALID";

  sprintf_s(buffer, BUFF_SIZE, "(P%d) %s: ", player, actionName);

  return buffer;
}