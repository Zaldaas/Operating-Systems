#include <iostream>
#include <fstream>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

std::vector<std::string> loadData(const std::string& filename) {
    std::ifstream file(filename);
    std::string word;
    std::vector<std::string> data;

    // Read word by word
    while (file >> word) {
        data.push_back(word);
    }
    return data;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: ./multi-search <FILE NAME> <KEY> <NUMBER OF PROCESSES>" << std::endl;
        return -1;
    }

    std::string filename = argv[1];
    std::string key = argv[2];
    int numProcesses = std::stoi(argv[3]);

    std::vector<std::string> data = loadData(filename);
    size_t length = data.size();

    // If more processes than lines, adjust to number of lines
    numProcesses = std::min(numProcesses, static_cast<int>(length));

    size_t chunkSize = length / numProcesses;
    std::vector<pid_t> childPIDs;

    for (int i = 0; i < numProcesses; i++) {
        size_t start = i * chunkSize;
        size_t end = (i == numProcesses - 1) ? length : start + chunkSize;

        pid_t pid = fork();

        if (pid == 0) { // child process
            for (size_t j = start; j < end; j++) {
                if (data[j] == key) {
                    exit(j); // found the key, return the index as exit code
                }
            }
            exit(255); // didn't find the key, use a unique code to signify not found
        } else if (pid < 0) {
            perror("fork");
            return -1;
        } else {
            childPIDs.push_back(pid); // parent process
        }
    }

    int exitStatus;
    int foundIndex = -1;

    for (int i = 0; i < numProcesses; i++) {
        if (wait(&exitStatus) < 0) {
            perror("wait");
            exit(-1);
        }

        int status = WEXITSTATUS(exitStatus);
        if (status != 255) {
            foundIndex = status;
            break;
        }
    }

    // Kill the remaining child processes
    for (pid_t pid : childPIDs) {
        kill(pid, SIGKILL);
    }

    if (foundIndex != -1) {
        std::cout << "String found at index: " << foundIndex << std::endl;
    } else {
        std::cout << "No string found" << std::endl;
    }

    return 0;
}
