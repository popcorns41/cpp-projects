#include "FileLogSource.h"

#include <fstream>
#include <stdexcept>
#include <utility>

FileLogSource::FileLogSource(std::string filePath)
    : filePath_(std::move(filePath)) {} 

std::vector<std::string> FileLogSource::readLines() const {
    std::ifstream file(filePath_);

    if(!file.is_open()){
        throw std::runtime_error("Failed to open log file: " + filePath_);
    }

    std::vector<std::string> lines;
    std::string line;

    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    return lines;
}