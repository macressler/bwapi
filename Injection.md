

# General Information #

> ## When BWAPI can be injected ##
> BWAPI can be injected at any time, though you **can NOT inject BWAPI during a game**. Some locations that BWAPI can be injected include:
    * Main Menu
    * Game Lobby
    * Mission Briefing
    * Battle.net

> ## Injection Side-Effects ##
> When injecting BWAPI, animated graphics (Main Menu and Campaign) will temporarily disappear. This is not expected behaviour, however this does not seem to have an impact on the stability of Starcraft or BWAPI.

# Loaders #

> ## [Chaoslauncher](http://winner.cspsx.de/Starcraft/) ##
> Chaoslauncher is the preferred loading tool because of the ability to use its [APM Alert](http://wiki.teamliquid.net/starcraft/APMAlert) and [W-MODE](http://wiki.teamliquid.net/starcraft/W-Mode) plugins.

> How to:
    * Download and install BWAPI
    * Navigate to the `BWAPI/ChaosLauncher/` directory
    * Run ChaosLauncher
    * Enable the BWAPI injector and click _Start_

> ## [MPQDraft](http://sourceforge.net/projects/mpqdraft/) ##
> MPQDraft may be preferred by some users, but is the least used among AI and BWAPI developers.

> How to:
    * Download and install BWAPI
    * Navigate to the `BWAPI/MPQDraft/` directory
    * Run MPQDraft
    * Follow one of the two processes listed below:

> Create a self-executing loader:
    * Select _CREATE SELF EXECUTING MPQ_
    * (Step 1 of 3) Set the paths for the input archive and output executable, then click _Next_
    * (Step 2 of 3) Select Starcraft, specify any command line parameters, and click _Next_
    * (Step 3 of 3) Select the BWAPI injector with any other plugins and click _Finish_
    * Run the newly created executable

> Immediately load BWAPI:
    * Select _LOAD MPQ PATCH_
    * (Step 1 of 3) Select Starcraft, specify any command line parameters, and click _Next_
    * (Step 2 of 3) Select any MPQ archives you want to load and click _Next_
    * (Step 3 of 3) Select the BWAPI injector with any other plugins and click _Finish_

> ## [DLL Injector](http://www.google.com/search?q=DLL+injector) ##
> A DLL injector may be preferred to load other hacks such as [McBanes's Resolution Hack](http://www.starcraftresolutionhack.kilu.de/).

> How to:
    * Follow the instructions provided by the DLL Injector using BWAPI.dll 