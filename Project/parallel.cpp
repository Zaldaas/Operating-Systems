#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string>
#include <vector>

using namespace std;

int main() {
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "Error: Unable to open input.txt" << endl;
        return 1;
    }

    string url = "https://api.open-meteo.com/v1/forecast?latitude=";
    string currentWeather = "&current_weather=True";
    int index = 1;
    float latitude, longitude;
    vector<pid_t> children;

    while (inputFile >> latitude >> longitude) {
        string filename = "file" + to_string(index) + ".json";
        string finalURL = url + to_string(latitude) + "&longitude=" + to_string(longitude) + currentWeather;

        pid_t pid = fork();
        if (pid < 0) {
            cerr << "Fork failed." << endl;
            return 1;
        }

        if (pid == 0) { // Child process
            cout << "Child process ID: " << getpid() << endl;
            cout << "Parent process ID: " << getppid() << endl;
            cout << "UID: " << getuid() << " GID: " << getgid() << endl;

            execlp("/usr/bin/curl", "curl", "-o", filename.c_str(), finalURL.c_str(), (char *)NULL);
            exit(0);
        } else { // Parent process
            children.push_back(pid);
        }
        index++;
    }

    for (pid_t childPid : children) {
        waitpid(childPid, NULL, 0);
    }

    inputFile.close();
    return 0;
}
