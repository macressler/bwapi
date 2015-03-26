BWAPI can automate most of the menus in the Starcraft GUI. The following options in the [bwapi.ini](http://code.google.com/p/bwapi/source/browse/trunk/Release_Binary/Starcraft/bwapi-data/bwapi.ini) file specify how BWAPI automates the in-game menu system:



# auto\_menu #
This specifies what mode the menu system is in. It can have one of the following values:
  * `OFF - does no menu automation`
  * `SINGLE_PLAYER - goes to single player screen (also used for replays)`
  * `LAN - goes to one of the specified local area networks`
  * `BATTLE_NET - goes to Battle Net login screen`

If auto\_menu is set to OFF, menu automation is disabled and none of the other options have any effect.

# lan\_mode #
This specifies the network mode that is to be used. It should be the same name as the network mode being used. Examples:
  * `Local Area Network (IPX)`
  * `Direct Cable Connection`
  * `Local Area Network (UDP)`
  * `Local PC`
  * `Direct IP`

# auto\_restart #

This specifies what to do at the end of a match or replay. It can have one of the following values:
  * `OFF - Does not automate the Victory/Defeat screen that appears after the end of the match. This lets you see the result of the match and also save the replay before starting the next match.`
  * `ON - Automates the Victory/Defeat screen, so BWAPI will proceed to the next match with no manual user input.`

# map #
Specifies which map to play on, or which replays to watch. The path is relative to the Starcraft folder. If you wish to automate the process of joining a LAN UDP game, set auto\_menu to LAN\_UDP and set map to nothing (i.e. "map = ").
Maps can contain wildcard characters `?` (one character) and `*` (any number of characters). If a wildcard is used, then the map choice depends on the `mapiteration` option.

Examples:
  * `map = maps/(2)Boxer.scm`
  * `map = maps/BroodWar/WebMaps/(?)*.sc?`
  * `map = maps/replays/LastReplay.rep`
  * `map = `

# save\_replay #
This specifies where to save the replay to.

Example:

  * `save_replay = maps\replays\BWAPI_LastReplay.rep`

You can also use environment variables as "`%VARIABLE%`".

Example:

  * `save_replay = maps\replays\%OS%_%USERNAME%.rep`

Will become "`WINDOWS_NT_SYSTEM.rep`" or whatever your configuration is.

We have also added our own variables, they are as follows:
| Variable | Description | Sample |
|:---------|:------------|:-------|
| `%BOTNAME%` | The full name of the BWAPI Player. | Undermind |
| `%BOTNAME6%` | The name of the BWAPI Player truncated to 6 characters. | MimicB |
| `%BOTRACE%` | The race of the BWAPI Player represented as a single character. | P |
| `%MAP%` | The name of the map truncated to 16 characters. | Challenger |
| `%ALLYNAMES%` | The names of all allied players, each truncated to 6 characters. | krasi0Overmi |
| `%ALLYRACES%` | The races of all allied players, each race being represented as a single character. | TZ |
| `%ENEMYNAMES%` | The names of all enemy players, each truncated to 6 characters. | UAlberSkynet |
| `%ENEMYRACES%` | The races of all enemy players, each race being represented as a single character. | ZP |

Additionally, flexible time-formatting expansions can also be added. The time formatting extensions use the same rules as [this function](http://en.cppreference.com/w/cpp/chrono/c/strftime), but with a dollar sign ($) as the formatting character.

Example:

  * `save_replay = maps/replays/%BOTNAME6%/$Y $b $d/%MAP%_%BOTRACE%%ALLYRACES%vs%ENEMYRACES%_$H$M$S.rep`

# race #
Specifies which race to select for the player. Can have one of the following values:
  * `Terran`
  * `Protoss`
  * `Zerg`
  * `Random`
  * `RandomTP`
  * `RandomTZ`
  * `RandomPZ`

# enemy\_race #
Specifies which race to select for the computer opponents. This option is only used in single player games - currently no computer opponents are automatically added to LAN UDP games. Can have one of the following values:
  * `Terran`
  * `Protoss`
  * `Zerg`
  * `Random`
  * `RandomTP`
  * `RandomTZ`
  * `RandomPZ`

You can also specify enemy races individually using the following keys:
  * `enemy_race_1`
  * `enemy_race_2`
  * `enemy_race_3`
  * `enemy_race_4`
  * `enemy_race_5`
  * `enemy_race_6`
  * `enemy_race_7`

Set the race to "Default" and the race specified in [enemy\_race](#enemy_race.md) will be used.

# enemy\_count #
Specifies the number of computer opponents to add to the game. This option is only used in single player games - currently no computer opponents are automatically added to LAN UDP games. Must be a value between 0 and 7. If the map does not have enough slots for the given number of computer opponents, then BWAPI uses the maximum number possible. For example, if you try to specify 7 computer opponents on a 3 player map, only 2 opponents will be in the game.

# game\_type #
Specifies the GameType. Sub-type selection is not implemented at this time (add an issue if you want to see it added), so there is limited support for Team Melee, and several other game types which use game sub-type options. Can have one of the following values:

  * `TOP_VS_BOTTOM`
  * `MELEE`
  * `FREE_FOR_ALL`
  * `ONE_ON_ONE`
  * `USE_MAP_SETTINGS`
  * `CAPTURE_THE_FLAG`
  * `GREED`
  * `SLAUGHTER`
  * `SUDDEN_DEATH`
  * `TEAM_MELEE`
  * `TEAM_FREE_FOR_ALL`
  * `TEAM_CAPTURE_THE_FLAG`

# sound #
Specifies whether or not Starcraft should run the sound engine. Disabling the sound engine can give Starcraft a slight speed boost(see [this tutorial](speed.md)). It can have one of the following values:
  * `OFF - disable sound`
  * `ON - run normally`