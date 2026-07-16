#pragma once

#include "ILogSource.h"

#include <string>
#include <vector>

// Represents a log source that reads log entries from a file.
class FileLogSource : public ILogSource {
    public:
        explicit FileLogSource(std::string filePath);

        std::vector<std::string> readLines() const override;

    private:
        std::string filePath_;
};