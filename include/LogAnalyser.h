#pragma once

#include "LogEntry.h"

#include <string>
#include <unordered_map>
#include <vector>

class LogAnalyser {
    public:
    std::unordered_map<std::string, int> countBySeverity(
        const std::vector<LogEntry>& logs
    ) const;

    std::unordered_map<std::string, int> countErrorByComponent(
        const std::vector<LogEntry>& logs
    ) const;

    std::vector<LogEntry> filterBySeverity(
        const std::vector<LogEntry>& logs,
        Severity severity
    ) const;
};