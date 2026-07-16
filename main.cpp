#include "FileLogSource.h"
#include "LogAnalyser.h"
#include "LogParser.h"

#include <iostream>
#include <memory>
#include <string>
#include <vector>

int main (int argc, char* argv[]) {

    if (argc != 2){
        std::cerr << "Usage: log_inspector <log_file_path\n";
        return 1;
    }

    std::string filePath = argv[1];


    try {
        std::unique_ptr<ILogSource> source = 
            std::make_unique<FileLogSource>(filePath);

        LogParser parser;
        LogAnalyser analyser;

        std::vector<std::string> lines = source -> readLines();
        std::vector<LogEntry> logs;

        int malformedCount = 0;

        for (const std::string& line : lines) {
            ParseResult result = parser.parseLine(line);

            if (result.entry.has_value()) {
                logs.push_back(result.entry.value());
            } else {
                malformedCount++;
                std::cerr << "Skipped line: " << result.errorMessage << "\n";
                std::cerr << "Line content: " << line << "\n\n";
            }
        }

        std::cout << "Loaded " << logs.size() << " valid log entries.\n";
        std::cout << "Ignored " << malformedCount << " malformed log lines.\n\n";

        std::cout << "Log count by severity:\n";
        auto severityCounts = analyser.countBySeverity(logs);

        for (const auto& [severity, count]: severityCounts) {
            std::cout << severity << ": " << count << "\n";
        }

        std::cout << "\nErrors by component:\n";
        auto errorCounts = analyser.countErrorByComponent(logs);

        for (const auto& [component, count] : errorCounts){
            std::cout << component << ": " << count << "\n";
        }

        std::cout << "\nError logs:\n";
        std::vector<LogEntry> errors = analyser.filterBySeverity(logs, Severity::Error);

        for (const LogEntry& error : errors) {
            std::cout
                << error.timestamp << " "
                << severityToString(error.severity) << " "
                << error.component << " "
                << error.message << "\n";
        }

        std::cout << "\nLogs between timestamps:\n";

        std::string startTimestamp = "2026-07-18T14:22:03";
        std::string endTimestamp = "2026-07-18T14:22:06";

        std::vector<LogEntry> logsInRange = analyser.filterByTimestamp(logs, startTimestamp, endTimestamp);

        for (const LogEntry& log : logsInRange) {
            std::cout
                << log.timestamp << " "
                << severityToString(log.severity) << " "
                << log.component << " "
                << log.message << "\n";
        }

        return 0;
    } catch (const std::exception& e){
        std::cerr << "Application error: " << e.what() << "\n";
        return 1;
    }
}