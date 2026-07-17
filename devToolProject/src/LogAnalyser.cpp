#include "LogAnalyser.h"

std::unordered_map<std::string, int> LogAnalyser::countBySeverity(
    const std::vector<LogEntry>& logs
) const {
    std::unordered_map<std::string, int> counts;

    for (const LogEntry& log : logs) {
        counts[severityToString(log.severity)]++;
    }

    return counts;
}

std::unordered_map<std::string, int> LogAnalyser::countErrorByComponent(
    const std::vector<LogEntry>& logs
) const {
    std::unordered_map<std::string, int> counts;

    for (const LogEntry& log : logs) {
        if (log.severity == Severity::Error) {
            counts[log.component] ++;
        }
    }

    return counts;
}

std::vector<LogEntry> LogAnalyser::filterBySeverity(
    const std::vector<LogEntry>& logs,
    Severity severity
) const {
    std::vector<LogEntry> filtered;

    for (const LogEntry& log : logs) {
        if (log.severity == severity) {
            filtered.push_back(log);
        }
    }

    return filtered;
}

//only works if the timestamps are in a format that allows for lexicographical comparison (e.g., ISO 8601).
std::vector<LogEntry> LogAnalyser::filterByTimestamp(
    const std::vector<LogEntry>& logs,
    const std::string& startTimeStamp,
    const std::string& endTimeStamp
) const {
    std::vector<LogEntry> filtered;

    if (startTimeStamp > endTimeStamp) {
        return filtered;
    }

    for (const LogEntry& log : logs) {
        if (log.timestamp >= startTimeStamp && log.timestamp <= endTimeStamp){
            filtered.push_back(log);
        }
    }

    return filtered;
}

