Group 5 - Screenshot Evidence

Existing files and observed behavior:
dir.png - Directory listing, followed by the myShell prompt.
ping.png - ping 192.168.86.1, four replies, 0% packet loss, and the next prompt.
echo_color.png - echo Hello World and color 0A, with a prompt after each command.
invalid.png - Two unsupported-command errors and continued prompting.
exit.png - exit and the closing message.

Refresh these screenshots after compiling the latest myShell.cpp:
1. dir.png: Show the program launch (.\myShell.exe), welcome message, dir output,
   and the next ==> prompt in one readable image.
2. invalid.png: Show hello123 and invalidCommand. The current version also prints
   Supported commands: dir help vol path tasklist notepad echo color ping
   after each unsupported-command error. Include that output and the next prompt.

Run the other tests again against the final build and replace any outdated
images. Capture actual Windows output; preserve readable commands and prompts.
After refreshing evidence, update README.txt to remove resolved refresh notes
and record the compiler/version actually used. Zip the folder as Group5_PA1.zip.
