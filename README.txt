myShell - Programming Assignment 1

1. Student/Group Information
Name: Isaac Parada , James Le , Eugene Kim , 
CWID: 885065110 , 884746165 , 886836733 , 
Course: CPSC 351
Section: 3
Assignment: Programming Assignment 1
Group: 5

2. Files Included
myShell.cpp - Source code for the Windows command-line shell.
README.txt - Build instructions, program design, and test information.
screenshots/README.txt - Instructions for capturing the required test screenshots.
Add each screenshot filename to this list after capturing it.

3. How to Compile
On Windows, open a Visual Studio Developer Command Prompt in the source folder:
    cl /EHsc /W4 /std:c++17 /D_CRT_SECURE_NO_WARNINGS myShell.cpp /Fe:myShell.exe

Alternatively, with MinGW-w64 g++ installed:
    g++ -std=c++17 -Wall -Wextra -pedantic myShell.cpp -o myShell.exe

These are the Windows build commands. Record the compiler/version actually used
after building on Windows: [Enter compiler/version]

4. How to Run
In Command Prompt or PowerShell, open the folder containing myShell.exe and run:
    .\myShell.exe
Enter commands at the ==> prompt. Type exit or quit to stop.

5. Supported Commands
dir [path]                 List files and folders.
help [command]             Show Windows command help.
vol [drive:]               Show the volume label and serial number.
path                       Show the current executable search path.
tasklist                   Show running processes.
notepad [filename]         Open Notepad, optionally with a file.
echo [text ...]            Print text.
color [attribute]          Set console colors, for example: color 0A.
ping address [-n count]    Ping an address, for example: ping 127.0.0.1 -n 2.

Command names are case-insensitive. A line can contain four tokens total:
the command plus up to three arguments.

6. Threading Design
main() reads input, parses it, checks for exit/quit, and validates the command.
For each valid command, CreateThread() starts commandThread(), which joins the
tokens and calls system(). The parent waits with WaitForSingleObject() before
reusing the input buffer, then closes the thread handle with CloseHandle().
Invalid commands and exit/quit do not create a thread.

7. Testing
Local checks passed for parsing, input handling, dispatch, and waiting, using a
test substitute for the Windows API. Native Windows command output is unverified.
Run the following tests on Windows, record the actual results, and add screenshots.

Test 1: dir
Expected: A directory listing appears, followed by another prompt.
Observed: [Enter Windows result]
Screenshot 1: screenshots/Screenshot1_dir.png

Test 2: ping 127.0.0.1
Expected: Ping output and statistics appear, followed by another prompt.
Observed: [Enter Windows result]
Screenshot 2: screenshots/Screenshot2_ping.png

Test 3: echo Hello World, then color 0A (on separate lines)
Expected: Hello World prints, then the text changes to green on black.
A prompt returns after each command. This covers multiple arguments and two
consecutive valid commands.
Observed: [Enter Windows result]
Screenshot 3: screenshots/Screenshot3_echo_color.png

Test 4: invalidCommand
Expected: An unsupported-command error appears, followed by another prompt.
Observed: [Enter Windows result]
Screenshot 4: screenshots/Screenshot4_invalid.png

Test 5: exit (repeat with quit in a new run)
Expected: Thanks for using myShell! appears and the shell closes.
Observed: [Enter Windows result]
Screenshot 5: screenshots/Screenshot5_exit.png

8. Known Limitations
- Requires Windows and its command processor for normal execution.
- Supports only the nine commands listed above, plus exit and quit.
- Accepts at most 511 input characters and four tokens per line.
- Does not support arguments containing quoted spaces.
- Rejects &, |, <, >, ^, and % in arguments; piping, redirection, and environment
  variable expansion are not supported.
- Commands execute through system(); environment changes inside the command
  processor do not update the parent shell's environment.
- Network command results depend on the target and network connection.

9. Team Contributions
Isaac Parada: [Enter actual contributions]
Add any other group members and their contributions before submission.