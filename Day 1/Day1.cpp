#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "No input provided." << std::endl;
        return -1;
    }

    std::ifstream ifs(argv[1]);
    int dial = 50;
    int zero_count[2] = {0, 0};
    bool at_zero;
    char dir;
    int count;
    ifs >> dir;
    while (!ifs.fail()) {
        at_zero = (dial == 0);

        if (dir == 'L') {
            ifs >> count;
            dial -= count;
        }
        else if (dir == 'R') {
            ifs >> count;
            dial += count;
        }
        else {
            std::cout << "Unknown direction " << dir << std::endl;
            return -1;
        }

        if (dial < 0) {
            // passed zero at least once going left, if we started above zero
            zero_count[1] -= (dial / 100) - (at_zero ? 0 : 1);
            dial = ((dial % 100) + 100) % 100;
            if (dial == 0) {
                zero_count[0]++;
            }
        }
        else if (dial > 99) {
            // passed zero at least once going right
            zero_count[1] += dial / 100;
            dial = dial % 100;
            if (dial == 0) {
                zero_count[0]++;
            }
        }
        else if (dial == 0) {
            // ended right at 0
            zero_count[0]++;
            zero_count[1]++;
        }

        ifs >> dir;
    }

    std::cout << "Final count (Part 1): " << zero_count[0] << std::endl;
    std::cout << "Final count (Part 2): " << zero_count[1] << std::endl;

    return 0;
}