// CPSC 351 - Programming Assignment 1: myShell

#include <windows.h>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

constexpr int MAX_TOKENS = 4;
constexpr int INPUT_SIZE = 512;

struct CommandData {
    int argc;
    char* argv[MAX_TOKENS];
};

// Split the input into a command and up to three arguments.
int parseCommand(char input[], char *argv[])
{
    int argc = 0;
    char *token = strtok(input, " \t\r\n");

    while (token != nullptr)
    {
        if (argc == MAX_TOKENS) { // If there are more than 4 tokens, return -1
            return -1;
        }
        argv[argc] = token;
        argc++;
        token = strtok(nullptr, " \t\r\n");
    }

    return argc;
}

bool isSupportedCommand(const char* command) {
    const char* supported[] = {
        "dir", "help", "vol", "path", "tasklist",
        "notepad", "echo", "color", "ping"
    };

    for (const char* name : supported) {
        if (std::strcmp(command, name) == 0) {
            return true;
        }
    }
    return false;
}

bool containsShellOperators(const CommandData& command) {
    for (int i = 1; i < command.argc; ++i) {
        if (std::strpbrk(command.argv[i], "&|<>^%") != nullptr) {
            return true;
        }
    }
    return false;
}

// Rebuild the parsed command and execute it in the worker thread.
DWORD WINAPI commandThread(LPVOID parameter) {
    const CommandData* command = static_cast<const CommandData*>(parameter);
    std::string commandLine;

    for (int i = 0; i < command->argc; ++i) {
        if (i > 0) {
            commandLine += ' ';
        }
        commandLine += command->argv[i];
    }

    int result = std::system(commandLine.c_str());
    if (result == -1) {
        std::fprintf(stderr, "Error: could not execute the command.\n");
        return 1;
    }
    return static_cast<DWORD>(result);
}

int main() {
    char input[INPUT_SIZE];

    std::puts("Welcome to myShell!");
    std::puts("Type a command, or enter exit/quit to close the shell.");

    // Read and process commands until exit, quit, or end of input.
    while (1) {
        std::printf("==> ");
        std::fflush(stdout);

        if (std::fgets(input, sizeof(input), stdin) == nullptr) {
            std::putchar('\n');
            break;
        }

        // Discard excess input so it does not become the next command.
        if (std::strchr(input, '\n') == nullptr) {
            int ch = std::getchar();
            if (ch != '\n' && ch != EOF) {
                while ((ch = std::getchar()) != '\n' && ch != EOF) {
                }
                std::fprintf(stderr, "Error: command line is too long.\n");
                continue;
            }
        }

        CommandData command = {};
        command.argc = parseCommand(input, command.argv);

        if (command.argc == 0) {
            continue;
        }
        if (command.argc == -1) {
            std::fprintf(stderr, "Error: use a command and at most three arguments.\n");
            continue;
        }

        for (char* ch = command.argv[0]; *ch != '\0'; ++ch) {
            *ch = static_cast<char>(std::tolower(static_cast<unsigned char>(*ch)));
        }

        if (std::strcmp(command.argv[0], "exit") == 0 ||
            std::strcmp(command.argv[0], "quit") == 0) {
            break;
        }
        if (!isSupportedCommand(command.argv[0])) {
            std::fprintf(stderr, "Error: '%s' is not a supported command.\n",
                         command.argv[0]);
            continue;
        }
        if (containsShellOperators(command)) {
            std::fprintf(stderr, "Error: shell-control characters are not supported.\n");
            continue;
        }

        // Each valid command gets its own worker thread.
        HANDLE thread = CreateThread(nullptr, 0, commandThread, &command, 0, nullptr);
        if (thread == nullptr) {
            std::fprintf(stderr, "Error: CreateThread failed (%lu).\n", GetLastError());
            continue;
        }

        // Wait before reusing the input buffer and command data.
        if (WaitForSingleObject(thread, INFINITE) == WAIT_FAILED) {
            std::fprintf(stderr, "Error: WaitForSingleObject failed (%lu).\n",
                         GetLastError());
            std::exit(EXIT_FAILURE);
        }
        if (!CloseHandle(thread)) {
            std::fprintf(stderr, "Error: CloseHandle failed (%lu).\n", GetLastError());
            return 1;
        }
    }

    std::puts("Thanks for using myShell!");
    return 0;
}
