#include <iostream>
#include <thread>
#include <filesystem>
#include <mutex>

namespace fs = std::filesystem;

std::mutex mtx;
int totalFileCnt = 0, totalDirCnt = 0;

void countFilesAndDirs(const fs::path& dir) {
    int fileCnt = 0, dirCnt = 0;

    for (const auto& entry : fs::directory_iterator(dir)) {
        if (entry.is_regular_file()) {
            ++fileCnt;
        } else if (entry.is_directory()) {
            ++dirCnt;
            countFilesAndDirs(entry);
        }
    }

    mtx.lock();
    totalFileCnt += fileCnt;
    totalDirCnt += dirCnt;
    mtx.unlock();
}

int main() {
    fs::path rootDirectory = "";  // Put your actual root directory path

    std::thread countingThread(countFilesAndDirs, rootDirectory);

    countingThread.join();

    std::cout << "Total files in the directory tree: " << totalFileCnt << std::endl;
    std::cout << "Total directories in the directory tree: " << totalDirCnt << std::endl;

    return 0;
}
