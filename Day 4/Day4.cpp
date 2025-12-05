#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int main(int argc, char* argv[]) {
     if (argc < 2) {
        std::cout << "No input provided." << std::endl;
        return -1;
    }

    std::ifstream ifs(argv[1]);

    std::vector<std::string> map;
    std::string str;
    ifs >> str;
    while (!ifs.fail()) {
        map.push_back(str);
        ifs >> str;
    }


    int goodRolls = 0;
    int badRolls = 0;

    // iterate over rows
    for (auto y = 0; y < map.size(); y++) {
        // iterate over columns
        for (int x = 0; x < map[0].length(); x++) {
            if (map[y][x] == '@') {
                int adjacentCount = 0;

                // NW
                if (x > 0 && y > 0 && map[y-1][x-1] == '@') adjacentCount++;
                // N
                if (y > 0 && map[y-1][x] == '@') adjacentCount++;
                // NE
                if (x < map[0].length() - 1 && y > 0 && map[y-1][x+1] == '@') adjacentCount++;
                // W
                if (x > 0 && map[y][x-1] == '@') adjacentCount++;
                // E
                if (x < map[0].length() - 1 && map[y][x+1] == '@') adjacentCount++;
                // SW
                if (x > 0 && y < map.size() - 1 && map[y+1][x-1] == '@') adjacentCount++;
                // S
                if (y < map.size() - 1 && map[y+1][x] == '@') adjacentCount++;
                // SE
                if (x < map[0].length() - 1 && y < map.size() - 1 && map[y+1][x+1] == '@') adjacentCount++;

                if (adjacentCount < 4) {
                    std::cout << "Found accessible roll with " << adjacentCount << " neighbors @ (" << x << "," << y << ")" << std::endl;
                    goodRolls++;
                }
                else {
                    std::cout << "Found inaccessible roll with " << adjacentCount << " neighbors @ (" << x << "," << y << ")" << std::endl;
                    badRolls++;
                }
            }
        }    
    }

    std::cout << "Total good rolls: " << goodRolls << std::endl;
    std::cout << "Total bad rolls: " << badRolls << std::endl;

    return 0;
}