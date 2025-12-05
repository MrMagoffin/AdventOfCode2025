#include <fstream>
#include <iostream>

bool checkID(long ID) {
    if (ID >= 10 && ID < 100) {
        // 2 digits
        return (ID % 11 == 0);
    }
    else if (ID >= 1000 && ID < 10000) {
        // 4 digits
        return (ID % 101 == 0);
    }
    else if (ID >= 100000 && ID < 1000000) {
        // 6 digits
        return (ID % 1001 == 0);
    }
    else if (ID >= 10000000 && ID < 100000000) {
        // 8 digits
        return (ID % 10001 == 0);
    }
    else if (ID >= 1000000000 && ID < 10000000000) {
        // 10 digits
        return (ID % 100001 == 0);
    }
    else {
        return false;
    }
}

bool checkID2(long ID) {
    if (ID < 10) {
        // 1 digit
        return false;
    }
    else if (ID < 100) {
        // 2 digits
        return (ID % 11 == 0);
    }
    else if (ID < 1000) {
        // 3 digits
        return (ID % 111 == 0);
    }
    else if (ID < 10000) {
        // 4 digits
        return (ID % 101 == 0 || ID % 1111 == 0);
    }
    else if (ID < 100000) {
        // 5 digits
        return (ID % 11111 == 0);
    }
    else if (ID < 1000000) {
        // 6 digits
        return (ID % 1001 == 0 || ID % 10101 == 0 || ID % 111111 == 0);
    }
    else if (ID < 10000000) {
        // 7 digits
        return (ID % 1111111 == 0);
    }
    else if (ID < 100000000) {
        // 8 digits
        return (ID % 10001 == 0 || ID % 1010101 == 0 || ID % 11111111 == 0);
    }
    else if (ID < 1000000000) {
        // 9 digits
        return (ID % 1001001 == 0 || ID % 111111111 == 0);
    }
    else if (ID < 10000000000) {
        // 10 digits
        return (ID % 100001 == 0 || ID % 101010101 == 0 || ID % 1111111111 == 0);
    }
    else {
        return false;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "No input provided." << std::endl;
        return -1;
    }

    std::ifstream ifs(argv[1]);

    char tmp;
    long long val[2] = {0, 0}; // inclusive range
    long long sum[2] = {0, 0}; // for part 1 and part 2
    ifs >> val[0];
    while (!ifs.fail()) {
        ifs >> tmp;
        ifs >> val[1];

        std::cout << "Checking range " << val[0] << " to " << val[1] << "..." << std::endl;

        for (long i = val[0]; i <= val[1]; i++) {
            if (checkID(i)) {
                std::cout << "Found part 1 bad ID " << i << std::endl;
                sum[0] += i;
                sum[1] += i;
            }
            else if (checkID2(i)) {
                std::cout << "Found part 2 bad ID " << i << std::endl;
                sum[1] += i;
            }
        }


        ifs >> tmp;
        ifs >> val[0];
    }

    std::cout << "Final sum (part 1): " << sum[0] << std::endl;
    std::cout << "Final sum (part 2): " << sum[1] << std::endl;

    return 0;
}