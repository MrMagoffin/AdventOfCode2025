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
        char highest[2] = {0, 0};
        int index = -1;
        for (int i = 0; i < str.length() - 1; i++) {
            if (str[i] > highest[0]) {
                highest[0] = str[i];
                index = i;
                if (highest[0] == '9') {
                    break;
                }
            }
        }

        // now find highest number to the right of the previous one
        for (int i = index + 1; i < str.length(); i++) {
            if (str[i] > highest[1]) {
                highest[1] = str[i];
                if (highest[1] == '9') {
                    break;
                }
            }
        }

        int joltage = 10*highest[0] + highest[1] - 528; // subtract ascii offset for both

        std::cout << "Joltage: " << joltage << std::endl;

        totalJoltage += joltage;

        ifs >> str;
    }

    std::cout << "Total Joltage: " << totalJoltage << std::endl;

    return 0;
}