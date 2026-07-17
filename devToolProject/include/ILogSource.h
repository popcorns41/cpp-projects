#pragma once

#include <string>
#include <vector>

class ILogSource{
    public:
        virtual ~ILogSource() = default;

        // Reads all lines from the log source and
        //  returns them as a vector of strings.
        
        virtual std::vector<std::string> readLines() const = 0;
};