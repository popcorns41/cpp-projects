#include "LogParser.h"

#include <sstream>

std::string severityToString(Severity severity){
    switch (severity){
        case Severity::Info:
            return "INFO";
        case Severity::Warning:
            return "WARN";
        case Severity::Error:
            return "ERROR";
        default:
            return "UNKNOWN";
    }
}

Severity severityFromString(const std::string& text){
    if (text == "INFO") {
        return Severity::Info;
    }

    if (text == "WARN") {
        return Severity::Warning;
    }

    if (text == "ERROR") {
        return Severity::Error;
    }

    return Severity::Unknown;
}

ParseResult LogParser::parseLine(const std::string& line) const {
    std::istringstream stream(line);

    std::string timestamp;
    std::string severityText;
    std::string component;

    if (!(stream >> timestamp >> severityText >> component)){
        return ParseResult{
            std::nullopt,
            "Malformed line: expected timestamp, severity, and component"
        };
    }

    std::string message;
    std::getline(stream, message);

    if (!message.empty() && message.front() == ' ') {
        message.erase(0,1);
    }

    Severity severity = severityFromString(severityText);

    if (severity == Severity::Unknown){
        return ParseResult{
            std::nullopt,
            "Unknown severity: " + severityText
        };
    }

    return ParseResult{
        LogEntry{
            timestamp,
            severity,
            component,
            message
        },
        ""
    };
}