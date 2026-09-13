myShell - Programming Assignment 1

1. Student/Group Information
Course: CPSC 351
Section: 3
Assignment: Programming Assignment 1
Group: 5

Isaac Parada - CWID: 885065110
James Le - CWID: 884746165
Eugene Kim - CWID: 886836733
Luke Nguyen - CWID: 84179630

Names and IDs are preserved from the group's README. The source also credits
Hoang Nguyen; confirm how this contributor should be listed before submission.

2. Files Included
myShell.cpp - Source for the Windows command-line shell.
README.txt - Group information, build/run instructions, design, and test results.
README.md - GitHub overview with a link to this README.
screenshots/README.txt - Screenshot descriptions and instructions for refreshing evidence.
screenshots/dir.png - Directory listing and return to the shell prompt.
screenshots/ping.png - Ping to 192.168.86.1 with four successful replies.
screenshots/echo_color.png - Consecutive echo and color commands.
screenshots/invalid.png - Unsupported-command handling from an earlier build.
screenshots/exit.png - Exit command and closing message.

3. How to Compile
Target environment: Windows with a C++17 compiler and Windows development headers.
The exact compiler/version used to create the supplied screenshots was not
recorded in the repository. The member who built it must supply that detail
before submission. The following are supported build instructions, not a claim
about which compiler produced those screenshots.

Visual Studio Developer Command Prompt, opened in the source folder:
    cl /EHsc /W4 /std:c++17 /D_CRT_SECURE_NO_WARNINGS myShell.cpp /Fe:myShell.exe

Alternatively, a Windows terminal with MinGW-w64 g++ on PATH:
    g++ -std=c++17 -Wall -Wextra -pedantic myShell.cpp -o myShell.exe

To identify the compiler used, run cl in the Developer Command Prompt or
g++ --version for MinGW-w64. Record the actual compiler and version here.

4. How to Run
Open a Windows terminal in the folder containing myShell.exe and run:
    .\myShell.exe
The program prints a welcome message and the ==> prompt. Enter commands one at
a time. Type exit or quit to close the shell.

5. Supported Commands
dir [path]                 List files and folders.
help [command]             Show Windows command help.
vol [drive:]               Show the volume label and serial number.
path                       Show the current executable search path.
tasklist                   Show running processes.
notepad [filename]         Open Notepad, optionally with a file.
echo [text ...]            Print text.
color [attribute]          Set console colors, for example: color 0A.
ping address [-n count]    Ping an address, for example: ping 192.168.86.1.

Command names are case-insensitive. A line may contain up to four tokens total:
the command and up to three arguments. exit and quit close the shell without
creating a worker thread.

6. Threading Design
main() reads input with fgets(), parses it with parseCommand(), and checks the
command against the supported list. Each valid executable command is passed to
commandThread() through CreateThread(). The worker joins the parsed tokens into
a command line and calls system(). The parent waits with WaitForSingleObject()
before reusing the input buffer and command data, then releases the thread handle
with CloseHandle(). Invalid commands and exit/quit do not create a thread.

7. Testing
The results below describe the group's supplied Windows screenshots. They show
a working earlier build. The latest source adds a supported-command list after
invalid input, which is not present in invalid.png. Rebuild the final source and
refresh the evidence before treating these screenshots as tests of the final build.

Test 1 - Command with no arguments
Input: dir
Observed: A directory listing for the Group5_PA1 folder appears, including
myShell.cpp and myShell.exe. The ==> prompt returns afterward.
Evidence: screenshots/dir.png
Refresh needed: Include .\myShell.exe, the welcome message, dir, and the resulting
output together so the program being tested is clearly identified.

Test 2 - Command with one argument
Input: ping 192.168.86.1
Observed: Four replies are received. Statistics show 4 packets sent, 4 received,
0 lost (0% loss), and round-trip times of 10 ms minimum, 11 ms maximum, and
10 ms average. The ==> prompt returns after ping finishes.
Evidence: screenshots/ping.png
The address is the target used in this test; its ownership is not assumed.

Test 3 - Multiple arguments and consecutive valid commands
Input 1: echo Hello World
Input 2: color 0A
Observed: Hello World is printed. Both commands are followed by another ==>
prompt, and the captured console text is green on a black background.
Evidence: screenshots/echo_color.png

Test 4 - Unsupported commands
Input 1: hello123
Input 2: invalidCommand
Observed: Each command produces an unsupported-command error and the prompt
returns. The second command is shown in lowercase in the error message because
command names are normalized before validation.
Evidence: screenshots/invalid.png
Refresh needed: The current source also prints the supported commands after
each error. Recompile and replace this screenshot to show that complete output.

Test 5 - Clean termination
Input: exit
Observed: Thanks for using myShell! appears after the exit command.
Evidence: screenshots/exit.png
The screenshot documents exit. quit is implemented but is not shown in the
supplied evidence; the assignment permits exit or quit for the required test.

8. Known Limitations
- Requires Windows and its command processor for normal execution.
- Supports only the nine listed OS commands, plus exit and quit.
- Accepts at most 511 input characters and four tokens per command line.
- Does not support arguments containing quoted spaces.
- Rejects &, |, <, >, ^, and % in arguments. Piping, redirection, and environment
  variable expansion are not supported.
- Environment changes inside the command processor do not update the parent
  shell's environment.
- Ping results depend on the target and network configuration.
- The compiler/version and final-build screenshot refresh remain to be completed.

9. Team Contributions
The following summary is based on repository commits. Members should confirm
the name/account associations and add any work not represented in Git history.

Isaac Parada (Mr1saac): Added the initial project files and set up the shared
repository for the group.

James Le (lejames11367): Added the directory, ping, invalid-command, and exit
screenshots, then added the echo/color screenshot.

Eugene Kim (Kimchyboy): Revised parseCommand(), including the token assignment
and count statements and formatting; updated group information and corrected typos.

Luke Nguyen (lukeng-29): Corrected the input parameter type in parseCommand()
and updated the group information in the README.

Additional contributor credited in source and commits:
Hoang Nguyen (Hoang842): Added the shared command whitelist, refactored command
validation, and added the supported-command list after invalid input. Confirm
this contributor's relationship to the group roster before submission.
