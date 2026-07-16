#include <fstream>
#include <iostream>
#include <string>
#include <string>
#include <vector>

int main() {
    std::ifstream file("../data/sample_logs.txt");

    if (!file.is_open()){
        std::cerr << "Failed to open log file.\n";
        return 1;
    }

    std::vector<std::string> lines;
    std::string line;

    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    std::cout << "Loaded " << lines.size() << " log lines.\n\n";

    for (const std::string& logLine : lines) {
        std::cout << logLine << "\n";
    }

    return 0;
}