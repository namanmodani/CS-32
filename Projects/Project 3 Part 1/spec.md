CS 32 Project 3, Winter 2022

Winter 2022 CS 32

Programming Assignment 3  
Super Peach Sisters
----------------------------------------------

**Part 1 due 11:00 PM Sunday, February 20**  
**Part 2 due 11:00 PM Sunday, February 27**  

The [Project 3 specification document](spec.pdf) is posted.

**Updates**

*   If your program is built with these new versions of [GameController.h](GameController.h) and [GameController.cpp](GameController.cpp), at the end of execution, it will write to `cerr` information about memory leaks of objects derived from GraphObject. (It writes nothing if there are no such leaks.) If you currently have no leaks, you can see what it reports by temporarily commenting out a delete expression in a StudentWorld member function.
*   Mac users: If you quit the game prematurely by typing `q`, any sound being played is cut off. Originally, if you quit by closing the window, the sound would keep on going; if it was the 82-second opening theme music, for example, it could get pretty annoying. The new version of GameController.cpp fixes that, so closing the window also ends the sound being played. (Of course, if you find and comment out the call to playSound that plays the theme, you won't ever hear the opening theme.)

To see what the game looks like in action:

*   Windows: Open [the Windows sample executable zip file](SuperPeachSisters-sample-windows.zip) and drag the folder named SuperPeachSisters in it to your desktop. In that desktop folder, double-click on the SuperPeachSisters application. On the SEASnet Windows server, you may have to move the folder to C:\\Users\\_yourusername_ instead of the desktop.
*   macOS: You'll need to have XQuartz and freeGLUT installed to run the program.
    1.  Install [XQuartz](http://xquartz.org):
        1.  Click the download link, open the downloaded .dmg file, double-click on XQuartz.pkg, and follow the installation instructions.
        2.  Log out and log back in again.
        3.  To verify the installation, open a Terminal window and run the command `echo $DISPLAY`. That should produce one line of output that ends with `org.xquartz:0`.
    2.  Install freeGLUT:
        
        1.  Install the [homebrew](http://brew.sh/) package manager.
        2.  Open a Terminal window and run the command `brew install freeglut`.
        
        Some Homebrew installation problems seem to be fixed by running the command  
        
        	git -C $(brew --repository homebrew/core) checkout master
        
        or by running the commands
        
        	rm -rf /usr/local/Homebrew/Library/Taps/homebrew/homebrew-core
        	brew update
        
    3.  Unzip [the Mac sample executable zip file](SuperPeachSisters-sample-mac.zip). In that zip file is a file named README.txt that tells you how to launch the program.
*   Linux:
    1.  Install OpenGL and freeGLUT (already installed on the SEASnet Linux servers cs32.seas.ucla.edu, lnxsrv06.seas.ucla.edu, lnxsrv07.seas.ucla.edu, and lnxsrv09.seas.ucla.edu):
        *   Ubuntu: `sudo apt-get install freeglut3 freeglut3-dev`
        *   Fedora: `sudo yum install freeglut freeglut-devel`
    2.  Unzip [the Linux sample executable zip file](SuperPeachSisters-sample-linux.zip). Change into the SuperPeachSisters directory. In that directory there is a file named README that tells you how to launch the program. You won't hear any sound effects. The Linux version builds and tries to connect to an X11 server, so it should work if your DISPLAY environment variable is set correctly. In a few days, we may have a way to get sound effects working.

You can also download the project skeletons with the code we've written, for [Windows](SuperPeachSisters-skeleton-windows.zip), [macOS with Xcode](SuperPeachSisters-skeleton-mac.zip), [macOS on the command line](SuperPeachSisters-skeleton-cmdmac.zip), or [Linux](linux.html), and make sure you can build and run them. All they'll do is have you lose a life each time you hit Enter, but at least you can verify that the graphics library works for you.

The **only** files you will modify are Actor.h, Actor.cpp, StudentWorld.h, and StudentWorld.cpp. Indeed, those will be the only code files you'll turn in, so in implementing your solution, you must **not** depend on any changes you make to code files other than those four.

At some point in Project 3, you may find the [Stringstreams](../../stringstreams.html) writeup helpful.

As a simple example of how a StudentWorld object and an actor object can interact, this [demo zip file](demo.zip) has the StudentWorld and Actor files for a simple demo that has one object appear that plays a sound whenever you hit the space bar. That object never dies, so type `q` to end the demo. (Our framework intercepts the `q` to end the game.)

Notes for Visual C++ users:

*   If the Windows skeleton doesn't build for you, you probably need to ensure that your project is using Windows SDK Version 10.0.17763.0 or 10.0.16299.0 (or possibly 10.0.18362.0). To do this:
    1.  Launch the Visual Studio Installer, find your version of Visual Studio, and select Modify. In the list on the right side of optional packages, make sure SDK 10.0.17763.0 or 10.0.16299.0 (or possibly 10.0.18362.0) is selected.
    2.  After modifying your Visual Studio installation, open the project in Visual Studio and right-click on Solution 'SuperPeachSisters' above the list of source files. Select Retarget Solution and choose the newly installed version of the SDK.
    3.  Build the project.
*   Also, if the skeleton crashes after 1 to 30 seconds with a dialog box showing an error code 0xc0000022, try disabling your antivirus software and building the executable. Unfortunately, we can't tell the SEASnet Windows Server to accept that there's no virus, so it may be impossible to run SuperPeachSisters on that server.

Notes for Xcode users:

*   You might get a message at startup relating to the Assets directory. If you want to fix the issue just for this project, select File / Project Settings... and for Derived Data Location, select Project-relative Location. If instead you want to fix it for every project you create with Xcode, select Xcode / Preferences... and for the Derived Data, select Relative. Alternatively, you could simply change the assetDirectory string literal in main.cpp to be a full path name to wherever you choose to put the Assets directory.