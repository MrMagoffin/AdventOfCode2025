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
    // merge ranges
    for (int i = 0; i < ranges.size() - 1; i++) {
        int j = i + 1;
        while (j < ranges.size()) {
            if (ranges[i].min < ranges[j].min) {
                if (ranges[i].max >= ranges[j].min && ranges[i].max <= ranges[j].max) {
                    // range i overlaps below range j
                    std::cout << "Combining (" << ranges[i].min << "," << ranges[i].max << ") and (" << ranges[j].min << "," << ranges[j].max << ") into (";
                    ranges[i].max = ranges[j].max;
                    ranges.erase(ranges.begin() + j);
                    j = i + 1;
                    std::cout << ranges[i].min << "," << ranges[i].max << ")" << std::endl;
                    continue;
                }
                else if (ranges[i].max > ranges[j].max) {
                    // range i encompasses range j
                    std::cout << "Combining (" << ranges[i].min << "," << ranges[i].max << ") and (" << ranges[j].min << "," << ranges[j].max << ") into (";
                    ranges.erase(ranges.begin() + j);
                    j = i + 1;
                    std::cout << ranges[i].min << "," << ranges[i].max << ")" << std::endl;
                    continue;
                }
            }
            if (ranges[i].min >= ranges[j].min && ranges[i].min <= ranges[j].max) {
                if (ranges[i].max >= ranges[j].min && ranges[i].max <= ranges[j].max) {
                    // range i is encompassed by range j
                    std::cout << "Combining (" << ranges[i].min << "," << ranges[i].max << ") and (" << ranges[j].min << "," << ranges[j].max << ") into (";
                    ranges[i].min = ranges[j].min;
                    ranges[i].max = ranges[j].max;
                    ranges.erase(ranges.begin() + j);
                    j = i + 1;
                    std::cout << ranges[i].min << "," << ranges[i].max << ")" << std::endl;
                    continue;
                }
                else if (ranges[i].max > ranges[j].max) {
                    // range i overlaps above range j
                    std::cout << "Combining (" << ranges[i].min << "," << ranges[i].max << ") and (" << ranges[j].min << "," << ranges[j].max << ") into (";
                    ranges[i].min = ranges[j].min;
                    ranges.erase(ranges.begin() + j);
                    j = i + 1;
                    std::cout << ranges[i].min << "," << ranges[i].max << ")" << std::endl;
                    continue;
                }
            }
            j++;
        }
    }

    long freshItems = 0;
    std::cout << "Finalized ranges:" << std::endl;
    for (auto it = ranges.cbegin(); it != ranges.cend(); it++) {
        std::cout << "(" << it->min << "," << it->max << ")" << std::endl;
        freshItems += it->max - it->min + 1;
    }

    std::cout << "Found " << freshItems << " fresh items" << std::endl;

    return 0;
}