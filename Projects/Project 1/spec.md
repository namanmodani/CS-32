CS 32 Project 1, Winter 2022

Winter 2022 CS 32

Programming Assignment 1  
Gone with the Wind
---------------------------------------------

**Time due: 11:00 PM Wednesday, January 12**

The appendix to this document is the specification of the last CS 31 project from a previous quarter. We will provide you with a correct[1](#endnote1) solution to that project. Your assignment is to (1) organize the code for the solution in appropriate header and implementation files, and (2) implement a new feature.

You should read [the appendix](cs31p7spec.html) now. It describes a game in which a player has to survive atop a mesa teeming with fierce creatures. You will be working with [this code that implements the game](cs31p7soln.cpp). Notice that it is a single file. (Just so you know, [the way we tested its correctness](cs31p7testing.html) is similar to how we'll test the correctness of the programs you write in CS 32.)

### Organize the code

Take the single source file, and divide it into appropriate header files and implementation files, one pair of files for each class. Place the main routine in its own file named `main.cpp`. Make sure each file `#include`s the headers it needs. Each header file must have include guards.

Now what about the global constants? Place them in their own header file named `globals.h`. And what about utility functions like `randInt` or `clearScreen` that are used by more than one class implementation? Place them in their own implementation file named `utilities.cpp`, and place their prototype declarations in `globals.h`. (Note that for utility functions like `decodeDirection` that are used by only one class implementation, it would be better to declare and implement them in that class's implementation file, not in `globals.h`. Also, note that in addition to Mesa, the implementation of the History class described below will use `clearScreen`.)

The [Visual C++](../../visualcpp.html) and the [Xcode](../../xcode.html) writeups demonstrate how to create a multi-file project. From the collection of the eleven files produced as a result of this part of the project, make sure you can build an executable file that behaves exactly the same way as the original single-file program. Make sure you can also do this with [g++ with Linux](../../linux.html).

### Add a feature

If you try running the updated programs (the [Windows version](newgarks.exe), the [Mac version](newgarksmac.zip), or the [Linux version](newgarks.linux) of the full game, and the [Windows version](newminigarks.exe), the [Mac version](newminigarksmac.zip), or the [Linux version](newminigarks.linux) of the smaller version of the game), you'll see they have one new command you can type: `h` for history. This command shows you for each grid point how many times during the course of the game the player was at that point when the player attacked a gark: dot means 0 times, a letter character A through Y means 1 through 25 times (A means 1, B means 2, etc.) and Z means 26 or more times.

Your task is to implement this functionality. You will need to do the following:

*   Define a class named `History` with the following public interface:
    
    	class History
    	{
    	  public:
    	    History(int nRows, int nCols);
    	    bool record(int r, int c);
    	    void display() const;
    	};
    
    *   The constructor initializes a History object that corresponds to a Mesa with `nRows` rows and `nCols` columns. You may assume (i.e., you do not have to check) that it will be called with a first argument that does not exceed `MAXROWS` and a second that does not exceed `MAXCOLS`, and that neither argument will be less than 1.
    *   The `record` function is to be called to notify the History object that the player was at row `r`, column `c` when the player attacked a neighboring gark. The function returns false if row `r`, column `c` is not within the Mesa; otherwise, it returns true after recording what it needs to. This function expects its parameters to be expressed in the same coordinate system as the Mesa (e.g., row 1, column 1 is the upper-left-most position).
    *   The `display` function clears the screen and displays the history grid as the posted programs do. This function _does_ clear the screen, display the history grid, and write an empty line after the history grid; it does _not_ print the `Press enter to continue.` after the display. (Note to Xcode users: It is acceptable that clearScreen() just writes a newline instead of clearing the screen if you launch your program from within Xcode, since the Xcode output window doesn't have the capability of being cleared.)
    
    The class declaration (with any private members you choose to add to support your implementation) must be in a file named `History.h`, and the implementation of the History class's member functions must be in `History.cpp`. If you wish, you may add a public destructor to the History class. You must _not_ add any other _public_ members to the class. (This implies, for example, that you must _not_ add a public default constructor.) The only member function of the History class that may write to `cout` is `History::display`.
    
*   Add a data member of type History (_not_ of type pointer-to-History) to the Mesa class, and provide this public function to access it; it must return a _reference_ to the Mesa's History object.
    
    	class Mesa
    	{
    	  …
    	  History& history();
    	  …
    	};
    
*   When the player attacks a neighboring gark, its Mesa's history object must be notified about the position of the player when the gark was attacked.
    
*   Have the Game recognize the new `h` command, tell its Mesa's history object to display the history grid, and then print the `Press enter to continue.` prompt and wait for the user to respond. (`cin.ignore(10000,'\n');` does that nicely.) Typing the `h` command does not count as the player's turn.
    

### Turn it in

By Tuesday, January 11, there will be a link on the class webpage that will enable you to turn in your source files. You do not have to turn in a report or other documentation for this project. What you will turn in for this project will be one zip file containing _only_ the thirteen files you produced, no more and no less. The files must have these names _exactly_:

Gark.h

Player.h

History.h

Mesa.h

Game.h

globals.h

 

Gark.cpp

Player.cpp

History.cpp

Mesa.cpp

Game.cpp

utilities.cpp

main.cpp

The zip file itself may be named whatever you like.

If we take these thirteen source files, we must be able to successfully build an executable using g32[2](#endnote2) and one using either Visual C++ or clang++ — you must not introduce compilation or link errors.

If you do not follow the requirements in the above paragraphs, your score on this project will be zero. "Do you mean that if I do everything right except misspell a file name or include an extra file or leave off one semicolon, I'll get no points whatsoever?" Yes. That seems harsh, but attention to detail is an important skill in this field. A draconian grading policy certainly encourages you to develop this skill.

The only exception to the requirement that the zip file contain exactly thirteen files of the indicated names is that if you create the zip file under macOS, it is acceptable if it contains the additional files that the macOS zip utility sometimes introduces: `__MACOSX`, `.DS_Store`, and names starting with `._` that contain your file names.

To not get a zero on this project, your program must meet these requirements as well:

*   Except to add the member function `Mesa::history`, you must not make any additions or changes to the public interface of any of the classes. (You are free to make changes to the private members and to the implementations of the member functions.) The word `friend` and the word sequence `pragma once` must not appear in any of the files you submit.
    
*   Your program must not use any global variables whose values may change during execution. Global _constants_ (e.g. `MAXROWS`) are all right.
    
*   Except in `Game::play` (or a function it calls) and `History::display`, your program must write no output to `cout` beyond what is already in the program or is required by this spec. If you want to print things out for debugging purposes, write to `cerr` instead of `cout`. When we test your program, we will cause everything written to `cerr` to be discarded instead — we will never see that output, so you may leave those debugging output statements in your program if you wish.
    
*   If we replace your `main.cpp` file with the following, the program must build successfully under both g32 and either Visual C++ or clang++:
    
    	#include "Gark.h"
    	int main()
    	{}
    
    Furthermore, if `Gark.h` contains the line `#include "_XXXXX_.h"`, where _XXXX_ represents any of `Game`, `Mesa`, `History`, `Player`, `Gark`, or `globals`, and if removing that `#include "_XXXX_.h"` line from `Gark.h` still allows the above program to build successfully, then `Gark.h` must not contain that `#include "_XXXX_.h"` line. For example, if `Gark.h` contained `#include "Game.h"`, but removing `#include "Game.h"` from it still allowed the little three-line program above to build successfully, then `Gark.h` must not contain `#include "Game.h"`.
    
*   If, in the text and little program of the requirement above, you replace all occurrences of `Gark.h` with `Player.h`, you must meet the resulting requirement. Similarly, if you replace all occurrences of `Gark.h` with `History.h`, you must meet the resulting requirement. The same also holds if you replace with `Game.h` and with `globals.h`. The requirement must also be met if you replace with `Mesa.h` with one exception: `Mesa.h` should include `globals.h`. (Even if `History.h` includes `globals.h` and `Mesa.h` includes `History.h`, good practice says that the author of `Mesa.h` who wants to use `MAXGARKS` and knows that it's declared in `globals.h` shouldn't have to wonder whether some other header already includes `globals.h`.)
    
*   If we replace your `main.cpp` file with the following, the program must build successfully under both g32 and either Visual C++ or clang++:
    
    	#include "Game.h"
    	#include "Game.h"
    	#include "Mesa.h"
    	#include "Mesa.h"
    	#include "History.h"
    	#include "History.h"
    	#include "Player.h"
    	#include "Player.h"
    	#include "Gark.h"
    	#include "Gark.h"
    	#include "globals.h"
    	#include "globals.h"
    	int main()
    	{}
    
*   If we replace your `main.cpp` file with the following, the program must build successfully under both g32 and either Visual C++ or clang++:
    
    	#include "History.h"
    	int main()
    	{
    	    History h(2, 2);
    	    h.record(1, 1);
    	    h.display();
    	}
    
*   If we replace your `main.cpp` file with the following, the program must build successfully under both g32 and either Visual C++ or clang++:
    
    	#include "Gark.h"
    	int main()
    	{
    	    Gark g(nullptr, 1, 1);
    	}
    
*   If we replace your `main.cpp` file with the following, the program must build successfully under both g32 and either Visual C++ or clang++:
    
    	#include "Player.h"
    	int main()
    	{
    	    Player p(nullptr, 1, 1);
    	}
    
*   If we replace your `main.cpp` file with the following, the program must build successfully under both g32 and either Visual C++ or clang++:
    
    	#include "Mesa.h"
    	int main()
    	{
    	    Mesa m(10, 20);
    	    m.addPlayer(2, 2);
    	}
    
*   If we replace your `main.cpp` file with the following, the program must build successfully under both g32 and either Visual C++ or clang++:
    
    	#include "globals.h"
    	#include "Player.h"
    	#include "Mesa.h"
    	int main()
    	{
    	    Mesa m(10, 20);
    	    Player p(&m, 2, 3);
    	}
    
*   If we replace your `main.cpp` file with the following, the program must build successfully under both g32 and either Visual C++ or clang++:
    
    	#include "Mesa.h"
    	#include "Player.h"
    	int main()
    	{
    	    Mesa m(10, 20);
    	    Player p(&m, 2, 3);
    	}
    
*   If we replace your `main.cpp` file with the following, the program must build successfully under both g32 and either Visual C++ or clang++:
    
    	#include "Player.h"
    	#include "Mesa.h"
    	int main()
    	{
    	    Mesa m(10, 20);
    	    Player p(&m, 2, 3);
    	}
    
*   If we replace your `main.cpp` file with the following, the program must build successfully under both g32 and either Visual C++ or clang++:
    
    	#include "History.h"
    	#include "Mesa.h"
    	#include <iostream>
    	using namespace std;
    
    	int main()
    	{
    	    Mesa m(1, 3);
    	    m.history().record(1, 2);
    	    Mesa m2(1, 2);
    	    m2.history().record(1, 1);
    	    m.history().display();
    	    cout << "===" << endl;
    	}
    
    When executed, it must clear the screen (_à la_ `Mesa::display`), and write the following three lines and no others:
    
    	.A.   _<== This is the first line that must be written._
    	      _<== This empty line is the second line that must be written._
    	===   _<== This is the third line that must be written._
    
    (In an Xcode output window, it would write a newline instead of clearing the screen.)
    
*   If we replace your `main.cpp` file with the following, the program must build successfully under both g32 and either Visual C++ or clang++:
    
    	#include "Mesa.h"
    	#include "Player.h"
    	#include "History.h"
    	#include "globals.h"
    	#include <iostream>
    	using namespace std;
    
    	int main()
    	{
    	    Mesa m(3, 4);
    	    m.addPlayer(2, 4);
    	    m.addGark(2, 3);
    	    m.addGark(3, 4);
    	    m.player()->moveOrAttack(LEFT);
    	    m.player()->moveOrAttack(DOWN);
    	    m.player()->moveOrAttack(LEFT);
    	    m.player()->moveOrAttack(UP);
    	    m.player()->moveOrAttack(LEFT);
    	    m.player()->moveOrAttack(DOWN);
    	    m.history().display();
    	    cout << "====" << endl;
    	}
    
    When executed, it must clear the screen (_à la_ `Mesa::display`), and write the following four lines and no others:
    
    	.A..   _<== This is the first line that must be written._
    	...B   _<== This is the second line that must be written._
    	....   _<== This is the third line that must be written._
    	       _<== This empty line is the fourth line that must be written._
    	====   _<== This is the fifth line that must be written._
    
    (In an Xcode output window, it would write a newline instead of clearing the screen.)
    
*   If we replace your `main.cpp` file with the following, the program must _not_ build successfully; attempting to compile it should produce an error message like `'p' uses undefined class 'Player'` or `variable has incomplete type 'Player'` or `variable 'Player p' has initializer but incomplete type` (and perhaps other error messages):
    
    	#include "Gark.h"
    	#include "Mesa.h"
    	int main()
    	{
    	    Mesa m(10, 20);
    	    Player p(&m, 2, 3);
    	    Gark g(&m, 1, 1);
    	}
    
*   If we replace your `main.cpp` file with the following, the program must _not_ build successfully; attempting to compile it should produce an error message like `'g' uses undefined class 'Gark'` or `variable has incomplete type 'Gark'` or `variable 'Gark g' has initializer but incomplete type` (and perhaps other error messages):
    
    	#include "Player.h"
    	#include "Mesa.h"
    	int main()
    	{
    	    Mesa m(10, 20);
    	    Player p(&m, 2, 3);
    	    Gark g(&m, 1, 1);
    	}
    
*   If we replace your `main.cpp` file with the following, the program must _not_ build successfully; attempting to compile it should produce an error message like `'m' uses undefined class 'Mesa'` or `variable has incomplete type 'Mesa'` or `variable 'Mesa m' has initializer but incomplete type` (and perhaps other error messages):
    
    	#include "globals.h"
    	#include "Gark.h"
    	#include "Player.h"
    	int main()
    	{
    	    Mesa m(10, 10);
    	}
    
*   If we replace your `main.cpp` file with the following, the program must _not_ build successfully; attempting to compile it should produce an error message like `'History' : no appropriate default constructor available` or `no matching constructor for initialization of 'History'` or `no matching function for call to 'History::History()'` (and perhaps other error messages):
    
    	#include "History.h"
    	int main()
    	{
    	    History h;
    	}
    
*   If a .cpp file uses a class or function declared in a particular header file, then it should #include that header. The idea is that someone writing a .cpp file should not worry about which header files include other header files. For example, a .cpp file using an A object and a B object should include both A.h (where presumably the class A is declared) and B.h (where B is declared), without considering whether or not A.h includes B.h or vice versa.
    

To create a zip file on a SEASnet machine, you can select the thirteen files you want to turn in, right click, and select "Send To / Compressed (zipped) Folder". Under macOS, copy the files into a new folder, select the folder in Finder, and select File / Compress "_folderName_"; make sure you _copied_ the files into the folder instead of creating aliases to the files.

### Advice

Developing your solution incrementally will make your work easier. Start by making sure you can build and run the original program successfully with the one source file having the name `main.cpp`. Then, starting with Gark, say, produce `Gark.h`, removing the code declaring the Gark class from `main.cpp`, but leaving in `main.cpp` the implementation of the Gark member functions. Get that two-file solution to work. Also, make sure you meet those of the requirements above that involve only the `Gark.h` header.

Next, split off `Player.h`, testing the now three-file solution and also making sure you meet those of the requirements above that involve only the `Gark.h` and `Player.h` headers. Continue in this manner until you've produced all the required headers (except `History.h`, since you're not yet adding the history feature), the whole program still works, and you meet all the applicable requirements.

Now split off the member function implementations of, say, Gark, putting them in `Gark.cpp`. Test everything again. You see where this is going. The basic principle is to _not_ try to produce all the files at once, because many misconceptions you have will affect many files. This will make it difficult to fix all those problems, since many of them will interfere with each other. By tackling one file at a time, and importantly, not proceeding to another until you've got everything so far working, you'll keep the job manageable, increasing the likelihood of completing the project successfully and, as a nice bonus, reducing the amount of time you spend working on it.

### Help

While we will provide you assistance in clarifying what this assignment is asking for and in using g32 and either Visual C++ or clang++, we will otherwise offer minimal help with this assignment. This is to give you a chance to honestly evaluate your own current programming ability. If you find that you're having trouble with the C++ program itself (not simply the Visual C++, Xcode, or g++ environment, which may be new to you), then you may want to reconsider your decision to take this class this quarter. Perhaps you've let your C++ programming skills get rusty, or maybe you didn't learn the material in CS 31 or its equivalent very well. If you decide to take the course later, what you should do between now and then is program, program, program! Solve some old or current CS 31 or PIC 10A or early PIC 10B projects, and read and do the exercises in a good introductory programming text using C++. You'll have to be self-motivated to make time for that, but the payoff will be a greater likelihood for success in CS 32.

* * *

#### Endnotes

[1](#ref1) "Correct" in terms of what a CS 31 student would know. For example, a CS 31 student wouldn't know that sometimes you need to write a copy constructor, so the posted solution ignores that issue. (You don't have to worry about that issue for this project, either.)

[2](#ref2) As the [Project Requirements](../../requirements.html) document tells you, "build using g32" is shorthand for "build using g32 on cs32.seas.ucla.edu" — that specific command (g32, not g++) on a SEASnet machine reached via that specific name.