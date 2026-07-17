#pragma once

#include "LogEntry.h"

#include <string>
#include <unordered_map>
#include <vector>

// Analyzes log entries and provides various statistics and filtering capabilities.
class LogAnalyser {
    public:
    // Counts the number of log entries for each severity level.
    std::unordered_map<std::string, int> countBySeverity(
        const std::vector<LogEntry>& logs
    ) const;

    // Counts the number of error log entries for each component.
    std::unordered_map<std::string, int> countErrorByComponent(
        const std::vector<LogEntry>& logs
    ) const;

    // Filters log entries by the specified severity level.
    std::vector<LogEntry> filterBySeverity(
        const std::vector<LogEntry>& logs,
        Severity severity
    ) const;

    std::vector<LogEntry> filterByTimestamp(
        const std::vector<LogEntry>& logs,
        const std::string& startTimeStamp,
        const std::string& endTimeStamp
    ) const;
};