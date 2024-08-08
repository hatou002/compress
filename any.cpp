#include <iostream>
#include <bitset>
#include <fstream>
using namespace std;

int main() {
    // Define the input binary string
    std::string s = "10100";
    // Define the size of the bitset based on the length of the input string
    const size_t size = s.length();

    // Create a bitset with the correct size and initialize it with the binary string
    std::bitset<16> binarySet(s); // Use a larger size to accommodate various lengths

    // Open a file in write mode
    std::ofstream outputFile("binary_output.txt");

    // Check if the file is opened successfully
    if (outputFile.is_open()) {
        // Write only the binary representation to the file
        outputFile << binarySet.to_string().substr(16 - size) << std::endl;

        // Close the file
        outputFile.close();
        std::cout << "Binary representation written to binary_output.txt" << std::endl;
    } else {
        std::cerr << "Unable to open file" << std::endl;
    }

    return 0;
}