#include <bits/stdc++.h>
namespace std {

struct ProcessInfo {
    int pid;
    string user;
};

}  // namespace std

int main() {
    std::string topOutputFilePath = "work.txt";  //Here tou can add your file path

    std::ifstream topOutputFile(topOutputFilePath);
    if (!topOutputFile.is_open()) {
        std::cerr << "Failed to open file: " << topOutputFilePath << std::endl;
        return 1;
    }

    std::string line;
    std::vector<std::ProcessInfo> processList;

    while (std::getline(topOutputFile, line)) {
        std::istringstream iss(line);
        int pid;
        std::string user;

        if (iss >> pid >> user) {
            processList.push_back({pid, user});
        }
    }

    topOutputFile.close();

    // Print the list of running PIDs and users
    std::cout << "Running PIDs and Users:" << std::endl;
    for (const auto& process : processList) {
        std::cout << "PID: " << process.pid << ", User: " << process.user << std::endl;
    }

    return 0;
}
