#include "ImplementationUtils.h"

std::string ImplementationUtils::getWorkingDirectory(const std::string &argvZero) {
    std::string directory(argvZero);
    std::string execName("editor");

    // Remove the executable name from the directory
    directory.erase(directory.size() - execName.size(), execName.size());

    return directory;
}