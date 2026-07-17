#pragma once

#include <string>

enum class Severity {
    Info,
    Warning,
    Error,
    Unknown
};

struct LogEntry {
    std::string timestamp;
    Severity severity;
    std::string component;
    std::string message;
};

std::string severityToString(Severity severity);
Severity severityFromString(const std::string& text);