#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

struct Range{
    long min;
    long max;
    Range(long _min, long _max) : min(_min), max(_max) {}
};

int main(int argc, char* argv[]) {
     if (argc < 2) {
        std::cout << "No input provided." << std::endl;
        return -1;
    }

    std::ifstream ifs(argv[1]);

    long val[2];
    char chr;
    std::string line;
    std::vector<Range> ranges;
    // get ranges
    while (std::getline(ifs, line)) {
        if (line.length() == 0) {
            break;
        }
        std::istringstream iss(line);
        iss >> val[0];
        iss >> chr;
        iss >> val[1];
        ranges.emplace_back(val[0], val[1]);
    }
    // process IDs
    int freshItems = 0;
    while (std::getline(ifs, line)) {
        std::istringstream iss(line);
        iss >> val[0];
        for (auto it = ranges.cbegin(); it != ranges.cend(); it++) {
            if (val[0] >= it->min && val[0] <= it->max) {
                std::cout << "Found fresh item " << val[0] << " between " << it->min << " and " << it->max << std::endl;
                freshItems++;
                break;
            }
        }
    }
    std::cout << "Found " << freshItems << " fresh items" << std::endl;

    return 0;
}