#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

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

    // iterate over grid
    gridPtr = grid;
    int splitCount = 0;
    for (int y = 0; y < height-1; y++) {
        for (int x = 0; x < width; x++) {
            if (*gridPtr == 'S') {
                // spawn first beam
                grid[(y+1)*width + x] = '|';
            }
            else if (*gridPtr == '|') {
                // will it be split?
                if (grid[(y+1)*width + x] == '^') {
                    // yes
                    splitCount++;
                    if (grid[(y+1)*width + x - 1] != '|') {
                        grid[(y+1)*width + x - 1] = '|';
                    }
                    if (grid[(y+1)*width + x + 1] != '|') {
                        grid[(y+1)*width + x + 1] = '|';
                    }
                }
                else {
                    // no
                    grid[(y+1)*width + x] = '|';
                }
            }
            // splitters can be ignored, already handled
            gridPtr++;
        }
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            std::cout << grid[y*width + x];
        }
        std::cout << std::endl;
    }
    std::cout << "Total splits: " << splitCount << std::endl;

    delete[] grid;

    return 0;
}