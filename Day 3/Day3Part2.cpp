#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {
     if (argc < 2) {
        std::cout << "No input provided." << std::endl;
        return -1;
    }

    std::ifstream ifs(argv[1]);

    long totalJoltage = 0;

    std::string str;
    ifs >> str;
    while (!ifs.fail()) {
        // find highest number, not including final - stop if we find a 9
        char highest;
        int index = -1; // index of most recently found number
        long joltage = 0;
        for (int i = 0; i < 12; i++) {
            joltage = joltage * 10;
            highest = 0;
            for (int j = index + 1; j < str.length() - 11 + i; j++) {
                if (str[j] > highest) {
                    highest = str[j];
                    index = j;
                    if (highest == '9') {
                        break;
                    }
                }
            }
            joltage += highest - 48; // subtract ASCII offset
        }

        std::cout << "Joltage: " << joltage << std::endl;

        totalJoltage += joltage;

        ifs >> str;
    }

    std::cout << "Total Joltage: " << totalJoltage << std::endl;

    return 0;
}