To program AIs using BWAPI you will need to have the following installed:
  * [Starcraft: Broodwar](http://us.blizzard.com/en-us/games/sc/) (1.16.1)
  * [Visual C++ 2010 Express Edition](http://www.microsoft.com/visualstudio/eng/downloads#d-2010-express) _(Note: See tutorial on using other compilers)_

Once you have those, download and install the latest version of BWAPI from http://code.google.com/p/bwapi/downloads/list. It will come packed with a hack loader (Chaoslauncher) and example projects.

Navigate to the installation directory, then open and compile the example projects. Copy the compiled `ExampleAIModule.dll` to your `Starcraft/bwapi-data/AI` directory and set the `bwapi.ini` configuration file accordingly.

Now, start the Chaoslauncher program that comes packaged with BWAPI. Check off the appropriate version of BWAPI to be loaded (`DEBUG|RELEASE`) and click Start.

Start a game and you should now see the `ExampleAIModule` playing the game.