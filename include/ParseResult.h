#pragma once

#include "LogEntry.h"

#include <optional>
#include <string>

struct ParseResult {
    std::optional<LogEntry> entry;
    std::string errorMessage;
};