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

    // load into memory first
    std::ifstream ifs(argv[1]);

    std::string line;
    std::vector<std::string> lines;
    int width = 0;
    while (getline(ifs, line)) {
        if (line.length() > width) width = line.length();
        lines.emplace_back(line);
    }

    // now iterate right-to-left
    long val = -1;
    long bigSum = 0;
    bool didOperation = false;
    std::vector<long> vals;
    for (int i = width - 1; i >= 0; i--) {
        // iterate through rows
        for (auto it = lines.cbegin(); it != lines.cend(); it++) {
            char chr = it->at(i);
            if (chr == ' ') {
                continue;
            }
            else if (chr == '*') {
                // multiply current value and stored values and clear
                for (auto jt = vals.cbegin(); jt != vals.cend(); jt++) {
                    val *= (*jt);
                }
                std::cout << "Got multiply result " << val << " at column " << i << std::endl;
                didOperation = true;
            }
            else if (chr == '+') {
                // add current value and stored values and clear
                for (auto jt = vals.cbegin(); jt != vals.cend(); jt++) {
                    val += (*jt);
                }
                std::cout << "Got add result " << val << " at column " << i << std::endl;
                didOperation = true;
            }
            else if (chr >= '0' && chr <= '9') {
                // accumulate current value
                if (val == -1) val = chr - '0';
                else val = 10*val + chr - '0';
            }
            else {
                std::cout << "Unrecognized character " << chr << std::endl;
                return -1;
            }
        }
        // column complete, did we do an operation?
        if (didOperation) {
            // add to sum and clear stored values
            bigSum += val;
            vals.clear();
            val = -1;
            didOperation = false;
        }
        else if (val != -1) {
            // store current value
            std::cout << "Storing value " << val << " at column " << i << std::endl;
            vals.push_back(val);
            val = -1;
        }
    }

    std::cout << "Got big sum of " << bigSum << std::endl;

    return 0;
}