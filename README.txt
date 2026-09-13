myShell - Programming Assignment 1

1. Student/Group Information
Course: CPSC 351, Section 3
Assignment: Programming Assignment 1
Group: 5

Isaac Parada - 885065110
James Le - 884746165
Eugene Kim - 886836733
Luke Nguyen - 84179630
Hoang Nguyen - 885020313

The code also credits Hoang Nguyen. Check whether he needs to be added to this
group list before submitting.

2. Files Included
myShell.cpp - Contains the shell program.
README.txt - Explains how to build, run, and test the program.
README.md - Gives a short overview on GitHub.
screenshots/README.txt - Lists the screenshots and which ones need updating.
screenshots/dir.png - Shows a directory listing.
screenshots/ping.png - Shows ping replies from 192.168.86.1.
screenshots/echo_color.png - Shows echo and color running one after another.
screenshots/invalid.png - Shows errors for unsupported commands.
screenshots/exit.png - Shows the shell closing.

3. How to Compile
The program needs Windows and a C++17 compiler.

Open a Visual Studio Developer Command Prompt in the source folder and run:
    cl /EHsc /W4 /std:c++17 /D_CRT_SECURE_NO_WARNINGS myShell.cpp /Fe:myShell.exe

Or, if using MinGW-w64 g++, run:
    g++ -std=c++17 -Wall -Wextra -pedantic myShell.cpp -o myShell.exe

Compiler/version used for the screenshots: still needs to be recorded.
Run cl or g++ --version on the Windows computer used for testing to check it.

4. How to Run
In a Windows terminal, open the folder containing myShell.exe and enter:
    .\myShell.exe

Enter commands at the ==> prompt. Type exit or quit to stop.

5. Supported Commands
dir [path]                 Lists files and folders.
help [command]             Shows help for Windows commands.
vol [drive:]               Shows the volume label and serial number.
path                       Shows the executable search path.
tasklist                   Lists running processes.
notepad [filename]         Opens Notepad.
echo [text ...]            Prints text.
color [attribute]          Changes console colors, such as color 0A.
ping address [-n count]    Pings an address, such as ping 192.168.86.1.

Command names are case-insensitive. Each line can have a command and up to three
arguments, for a total of four tokens.

6. Threading Design
main() reads the input with fgets(). parseCommand() splits it into tokens using
strtok(). After checking the command, main() calls CreateThread() to start a
worker. The worker puts the tokens back into a command line and calls system().

The main thread uses WaitForSingleObject() to wait for the worker to finish.
This keeps the input buffer valid until the command is done. It then calls
CloseHandle() and shows the next prompt. Invalid commands, exit, and quit do not
start a worker thread.

7. Testing
These results come from the included Windows screenshots. They were taken before
the latest change to invalid-command output. Rerun the final build and update
the screenshots before submitting.

Test 1: dir
Result: The files in Group5_PA1 were listed, and the ==> prompt returned.
Screenshot: screenshots/dir.png
To update: Include the program launch and welcome message in the screenshot.

Test 2: ping 192.168.86.1
Result: Four packets were sent and four replies were received, with 0% loss.
The minimum time was 10 ms, maximum was 11 ms, and average was 10 ms.
The prompt returned after ping finished.
Screenshot: screenshots/ping.png

Test 3: echo Hello World, followed by color 0A
Result: Hello World was printed. The screenshot shows green text on a black
background and a prompt after each command. This covers multiple arguments
and two valid commands in a row.
Screenshot: screenshots/echo_color.png

Test 4: hello123, followed by invalidCommand
Result: Both commands showed an unsupported-command error and returned to the
prompt. The error displays invalidcommand in lowercase.
Screenshot: screenshots/invalid.png
To update: The latest code also prints the supported-command list after each
error. Rebuild the program and capture that output.

Test 5: exit
Result: The shell printed Thanks for using myShell!
Screenshot: screenshots/exit.png
This screenshot covers exit. There is no screenshot for quit.

8. Known Limitations
- The program uses Windows functions and cannot run directly on macOS or Linux.
- Input is limited to 511 characters and four tokens. Quoted spaces are not supported.
- Only the listed commands are accepted. The characters &, |, <, >, ^, and %
  are blocked in arguments, so pipes, redirection, and variable expansion are
  not supported.
- Changes to environment variables inside system() do not change the main
  shell's environment.
- Ping results depend on the address and network connection.

9. Team Contributions
This summary follows the Git commits. Each member should check their name,
account, and work before submitting.

Isaac Parada (Mr1saac): Added the initial project files and set up the group repo.
James Le (lejames11367): Added the test screenshots, including echo and color.
Eugene Kim (Kimchyboy): Updated parseCommand(), formatting, and group information.
Luke Nguyen (lukeng-29): Fixed the input parameter type in parseCommand() and
updated the group information.

Hoang Nguyen (Hoang842): Added the shared command list, updated command
validation, and added the list of supported commands after an invalid command.
His name is credited in the code but is not in the group list above; confirm
how he should be listed.
