


# Chaos Launcher #

After installing BWAPI, navigate to the _`BWAPI/Chaoslauncher`_ directory and run _`Chaoslauncher - MultiInstance.exe`_.

> ![http://bwapi.googlecode.com/svn/wiki/multi_tut_01.gif](http://bwapi.googlecode.com/svn/wiki/multi_tut_01.gif)

Select _`BWAPI Injector`_ and any other plugins you wish to use.

> ![http://bwapi.googlecode.com/svn/wiki/multi_tut_03.gif](http://bwapi.googlecode.com/svn/wiki/multi_tut_03.gif)


# BWAPI #

To set up BWAPI for multiple instances, you must configure the AI path for each instance. Browse to _`Starcraft/bwapi-data/`_ and open _`bwapi.ini`_.

> ![http://bwapi.googlecode.com/svn/wiki/multi_tut_05.gif](http://bwapi.googlecode.com/svn/wiki/multi_tut_05.gif)

Now change the _`ai`_ entry to contain comma-separated paths to the AI modules you wish to use.

> ![http://bwapi.googlecode.com/svn/wiki/multi_tut_06.gif](http://bwapi.googlecode.com/svn/wiki/multi_tut_06.gif)

Each comma-separated entry will be loaded for their respective instance (first instance loads the first entry, etc). If there are more instances than entries, then the last entry is used for all subsequent instances.


# Networking #

After installing BWAPI, a new network mode called **Local PC** should now be available after choosing Multiplayer.

> ![http://bwapi.googlecode.com/svn/wiki/multi_tut_07.gif](http://bwapi.googlecode.com/svn/wiki/multi_tut_07.gif)

> _**Note**: **This network mode will only appear when BWAPI has been [injected](Injection.md)** and will allow you to play matches between multiple instances._


# Conclusion #

If you run into problems, please don't hesitate to do one of the following:

  * Visit the [IRC channel](http://webchat.quakenet.org/?channels=BWAPI)
  * Post on the [BroodwarAi forum](http://www.broodwarai.com/forums/index.php?showforum=46)
  * Create an [issue](http://code.google.com/p/bwapi/issues/list)