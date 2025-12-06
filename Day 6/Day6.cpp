#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

int main(int argc, char* argv[]) {
     if (argc < 2) {
        std::cout << "No input provided." << std::endl;
        return -1;
    }

    std::ifstream ifs(argv[1]);

    std::string line;
    std::vector<std::vector<long>> values;
    long bigSum = 0;
    while (getline(ifs, line)) {
        std::istringstream iss(line);
        if (line[0] == 0x20 || line[0] >= 0x30) {
            // numbers
            values.emplace_back();
            long val;
            iss >> val;
            while (!iss.fail()) {
                values.back().push_back(val);
                iss >> val;
            }
        }
        else {
            // operations
            char op;
            for (int i = 0; i < values.cbegin()->size(); i++) {
                iss >> op;
                if (op == '*') {
                    long result = 1;
                    for (auto it = values.cbegin(); it != values.cend(); it++) {
                        result *= it->at(i);
                    }
                    std::cout << "Got result " << result << " for column " << i << std::endl;
                    bigSum += result;
                }
                else if (op == '+') {
                    long result = 0;
                    for (auto it = values.cbegin(); it != values.cend(); it++) {
                        result += it->at(i);
                    }
                    std::cout << "Got result " << result << " for column " << i << std::endl;
                    bigSum += result;
                }
                else {
                    std::cout << "Unknown operation " << op << std::endl;
                    return -1;
                }
            }
        }
    }

    std::cout << "Got big sum of " << bigSum << std::endl;

    return 0;
}