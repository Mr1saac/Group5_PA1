// CPSC 351, Section 3 - Programming Assignment 1: myShell
// Group 5: Isaac Parada, James Le, Eugene Kim, Luke Nguyen

#include <windows.h>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

const int MAX_TOKENS = 4;
const int INPUT_SIZE = 512;

// Hoang Nguyen: list of commands our shell supports
const char* supportedCommands[] = {
    "dir", "help", "vol", "path", "tasklist",
    "notepad", "echo", "color", "ping"
};

const int commandCount = sizeof(supportedCommands) / sizeof(supportedCommands[0]);

struct CommandData {
    int argc;
    char* argv[MAX_TOKENS];
};

// splits what the user typed into separate parts
int parseCommand(char* input, char* argv[]) {
    int argc = 0;
    char* token = strtok(input, " \t\r\n");

    while (token != nullptr) {
        if (argc >= MAX_TOKENS) {
            return -1;
        }

        argv[argc] = token;
        argc++;
        token = strtok(nullptr, " \t\r\n");
    }

    return argc;
}

// Hoang Nguyen: checks if the command is allowed
bool isSupportedCommand(const char* command) {
    for (int i = 0; i < commandCount; i++) {
        if (strcmp(command, supportedCommands[i]) == 0) {
            return true;
        }
    }
    return false;
}

// Hoang Nguyen: prints all supported commands
void printSupportedCommands() {
    printf("Supported commands:");

    for (int i = 0; i < commandCount; i++) {
        printf(" %s", supportedCommands[i]);
    }

    printf("\n");
}

// checks for characters we do not want passed to the Windows shell
bool hasShellCharacters(CommandData& command) {
    for (int i = 1; i < command.argc; i++) {
        if (strpbrk(command.argv[i], "&|<>^%") != nullptr) {
            return true;
        }
    }
    return false;
}

// function that the thread runs
DWORD WINAPI runCommand(LPVOID parameter) {
    CommandData* command = (CommandData*)parameter;
    std::string commandLine = "";

    for (int i = 0; i < command->argc; i++) {
        if (i != 0) {
            commandLine += " ";
        }
        commandLine += command->argv[i];
    }

    int result = system(commandLine.c_str());

    if (result == -1) {
        fprintf(stderr, "Error: could not execute the command.\n");
        return 1;
    }

    return (DWORD)result;
}

int main() {
    char input[INPUT_SIZE];

    printf("Welcome to myShell!\n");
    printf("Type a command, or enter exit/quit to close the shell.\n");

    while (true) {
        printf("==> ");
        fflush(stdout);

        if (fgets(input, sizeof(input), stdin) == nullptr) {
            printf("\n");
            break;
        }

        // if the line was too long, clear the rest of it
        if (strchr(input, '\n') == nullptr) {
            int ch = getchar();

            if (ch != '\n' && ch != EOF) {
                while ((ch = getchar()) != '\n' && ch != EOF) {
                    // just clearing the input buffer
                }

                fprintf(stderr, "Error: command line is too long.\n");
                continue;
            }
        }

        CommandData command = {};
        command.argc = parseCommand(input, command.argv);

        if (command.argc == 0) {
            continue;
        }

        if (command.argc == -1) {
            fprintf(stderr, "Error: use a command and at most three arguments.\n");
            continue;
        }

        // make the command lowercase so DIR and dir both work
        for (char* ch = command.argv[0]; *ch != '\0'; ch++) {
            *ch = (char)tolower((unsigned char)*ch);
        }

        if (strcmp(command.argv[0], "exit") == 0 ||
            strcmp(command.argv[0], "quit") == 0) {
            break;
        }

        if (!isSupportedCommand(command.argv[0])) {
            printf("Error: '%s' is not a supported command.\n", command.argv[0]);
            printSupportedCommands();
            continue;
        }

        if (hasShellCharacters(command)) {
            fprintf(stderr, "Error: shell-control characters are not supported.\n");
            continue;
        }

        // run the command using a Windows thread
        HANDLE thread = CreateThread(nullptr, 0, runCommand, &command, 0, nullptr);

        if (thread == nullptr) {
            fprintf(stderr, "Error: CreateThread failed (%lu).\n", GetLastError());
            continue;
        }

        // wait until the command is done before asking for another one
        if (WaitForSingleObject(thread, INFINITE) == WAIT_FAILED) {
            fprintf(stderr, "Error: WaitForSingleObject failed (%lu).\n", GetLastError());
            CloseHandle(thread);
            return 1;
        }

        if (!CloseHandle(thread)) {
            fprintf(stderr, "Error: CloseHandle failed (%lu).\n", GetLastError());
            return 1;
        }
    }

    printf("Thanks for using myShell!\n");
    return 0;
}
