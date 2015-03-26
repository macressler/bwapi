# Developing BWAPI #

While we have made a lot of progress on BWAPI, there is still plenty of things which need to be properly tested and improved. If you are interested in developing the BWAPI framework, please don't hesitate to [contact us](contact.md).


We are using [Visual Studio 2010 Express Edition](http://www.microsoft.com/visualstudio/eng/downloads#d-2010-express) to develop BWAPI. It is completely free software.

## You don't need to know how to code to get involved! ##
Aside from writing code, participation can include any of the following:
  * Accumulating valuable knowledge about the Starcraft game engine
  * Providing feedback about commits, bugs, and anything else by testing the HEAD revision.
  * Organizing the code, making it easier to read, and adding comments.
  * Fixing some small bugs or including small patches/fixes to the code.
  * Improving, expanding, and/or clarifying the user documentation found in header files and creating code samples.
  * Manage issues, recruit project members, and spread the word.

## How to Start Working on BWAPI ##

  1. Obtain an SVN Program. Google has its own instructions for getting an SVN program, but we use [TortoiseSVN](http://tortoisesvn.tigris.org/)
  1. Follow the instructions on the [Source](http://code.google.com/p/bwapi/source/checkout) tab for retrieving the source code
  1. Move the contents of `starcraft-folder` from the `Release_Binary` directory to your Starcraft directory, so that BWAPI.dll is copied automatically when the project is built.
  1. Download [Doxygen](http://www.stack.nl/~dimitri/doxygen/download.html#srcbin) in order to compile the BWAPI documentation. The software is freeware.
  1. Download [Inno Setup](http://www.jrsoftware.org/isdl.php) and [Inno Script Studio](https://www.kymoto.org/products/inno-script-studio/downloads) in order to compile the BWAPI installer. These are freeware.

Try to follow the [coding standard](BWAPI4CodingStandard.md) and make sure BWAPI still compiles and runs before you submit any changes. Also check to make sure the TestAIModule passes all test cases.

## Useful Tools for finding new offsets/hooks ##
  * [Ollydbg](http://www.ollydbg.de/)
  * [IDA Pro](http://www.hex-rays.com/idapro/)
  * [ArtMoney](http://www.artmoney.ru/)

## How To Create a New Release of BWAPI ##
  1. Check out BWAPI
  1. Update the `ChangeLog` file with info from the [Changes](Changes.md) page.
  1. Update the `README` file so it has the name of the new release at the top of the file.
  1. Compile BWAPI as Release mode and Debug mode.
  1. Run Doxygen with `Doxyfile` found in the `/bwapi/include` directory
  1. Compile the installer with Inno Script Studio
  1. Rename and upload the compiled executable found in `trunk/Installer/Output` to the downloads tab
  1. Mark the new release as featured and tell everyone!