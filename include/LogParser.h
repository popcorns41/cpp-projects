#pragma once

#include "ParseResult.h"
#include <string>

class LogParser {
    public:
        ParseResult parseLine(const std::string& line) const;
};