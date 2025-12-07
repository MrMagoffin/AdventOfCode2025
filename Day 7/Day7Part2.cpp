#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <iomanip>

#define START -2
#define SPLIT -1

int main(int argc, char* argv[]) {
     if (argc < 2) {
        std::cout << "No input provided." << std::endl;
        return -1;
    }

    std::ifstream ifs(argv[1]);

    // get dimensions
    std::string str;
    getline(ifs, str);
    int width = str.length();
    int height = 0;
    while (!ifs.fail()) {
        height++;
        getline(ifs, str);
    }
    ifs.clear();
    ifs.seekg(0);

    char* grid = new char[width*height];
    char* gridPtr = grid;
    getline(ifs, str);
    while (!ifs.fail()) {
        memcpy(gridPtr, str.c_str(), width*sizeof(char));
        gridPtr += width;
        getline(ifs, str);
    }

    // make a new grid of longs
    long* longGrid = new long[width*height];
    long* longGridPtr = longGrid;
    gridPtr = grid;
    for (int i = 0; i < width*height; i++) {
        if (*gridPtr == 'S') {
            *longGridPtr = START;
        }
        else if (*gridPtr == '^') {
            *longGridPtr = SPLIT;
        }
        else {
            *longGridPtr = 0;
        }
        longGridPtr++;
        gridPtr++;
    }

    // iterate over long grid
    longGridPtr = longGrid;
    for (int y = 0; y < height-1; y++) {
        for (int x = 0; x < width; x++) {
            if (*longGridPtr == START) {
                // spawn first beam
                longGrid[(y+1)*width + x] = 1;
            }
            else if (*longGridPtr > 0) {
                // will it be split?
                if (longGrid[(y+1)*width + x] == SPLIT) {
                    // yes
                    longGrid[(y+1)*width + x - 1] += *longGridPtr;
                    longGrid[(y+1)*width + x + 1] += *longGridPtr;
                }
                else {
                    // no
                    longGrid[(y+1)*width + x] += *longGridPtr;
                }
            }
            // splitters can be ignored, already handled
            longGridPtr++;
        }
    }

    // sum values on last line
    long totalPaths = 0;
    for (int x = 0; x < width; x++) {
        totalPaths += *longGridPtr;
        longGridPtr++;
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            std::cout << std::setw(2) << longGrid[y*width + x] << ",";
        }
        std::cout << std::endl;
    }
    std::cout << "Total paths: " << totalPaths << std::endl;

    delete[] grid;
    delete[] longGrid;

    return 0;
}