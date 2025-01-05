#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

int main() {
    /* The command buffer */
    string cmdBuff;

    /* The ID of the child process */
    pid_t pid;

    /* Keep running until the user has typed "exit" */
    do {
        /* Prompt the user to enter the command */
        cerr << "cmd> ";
        getline(cin, cmdBuff); // Use getline() to handle spaces in input

        /* If the user wants to exit */
        if (cmdBuff != "exit") {
            /* Create a child */
            pid = fork();

            /* Error check to make sure the child was successfully created */
            if (pid < 0) {
                perror("fork");
                exit(1);
            }

            /* If I am a child, I will do this */
            if (pid == 0) {
                // Tokenize the input to separate the command and its arguments
                stringstream ss(cmdBuff);
                string token;
                vector<string> tokens;
                while (ss >> token) {
                    tokens.push_back(token);
                }

                // Convert the vector to an array of character arrays (C-style strings)
                vector<char*> args;
                for (const auto& t : tokens) {
                    args.push_back(const_cast<char*>(t.c_str()));
                }
                args.push_back(nullptr); // The list of arguments must be null-terminated

                /* Call execlp() to replace my program with that specified at the command line. */
                if (execlp(args[0], args[0], args[1], args[2], nullptr) < 0) {
                    perror("execlp");
                    exit(1);
                }
            }
            /* If I am a parent, I will do the following */
            else {
                int childEventInfo;
                int waitReturn = wait(&childEventInfo);

                // Error check the wait() call
                if (waitReturn < 0) {
                    perror("wait");
                    exit(1);
                }
            }
        }
    } while (cmdBuff != "exit");

    return 0;
}
