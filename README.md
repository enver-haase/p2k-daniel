
From Daniel, as quoted by Jeremy Melton:
"
Below is the source code for the power-driver-board-part of my Sparks Pinball 2000 project. It is written in C as a Linux kernel module utilizing the real time extensions RTAI from https://www.rtai.org/. The sound and graphics part (not published here) is written in C++ as a Linux user space program. The communication between the two part are made using FIFO:s. The code must only be considered as test software. It is very poorly commented and may not be easy to read. If you make any modifications to it, please send me a copy...

Maybe there are someone out there who are interested in continue to build on the code and maybe write a Pinball 2000 Open Source Toolkit, that can be used by anyone interested in making their own Pinball 2000 game. If so, the code must be rewritten. It isn’t a good way to place everything that has to do with the power-driver-board (including the rules) in a kernel module. One idéa is to simpify the kernel module and let it only deal with functions that has directly to do with the power driver board like fire solenoids, flash lamps, running lamp patterns etc, and sending switch event up to a user space program where all the game code is written. Another way is to write everything in user space using RTAI-LXRT and skip the kernel module part...
Here is the code: ***. Disclaimer: The code is “as is”. Use it at your own risk. I will not be responsible for any hardware malfunction.
I included a definition file for SWEP1 for anyone interested in writing new software to their own game...
"

From:
http://www.jeremymelton.com/blog/2009/03/controlling-pinball-2000/

See also:
http://www.pinrepair.com/pin2000/
