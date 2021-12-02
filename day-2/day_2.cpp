#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Function declarations
int task_one(vector<string>);
int task_two(vector<string>);

int main(int argc, char *argv[])
{
    // Print out the system arguments
    // for (int i=1; i < argc; i++) {
    //     cout << argv[i] << " ";
    // }
    // Read inputs from file
    ifstream inputFile;
    inputFile.open(argv[1]);
    // Read lines into vector
    vector<string> input;
    string line;
    while ( getline (inputFile, line) ) {
        input.push_back(line);
    }
    
    // Task One
    int dpp1 = task_one(input);
    cout << "1: Your position-depth product is " << dpp1 << "\n";
    // Task Two
    int dpp2 = task_two(input);
    cout << "2: Your position-depth product is " << dpp2 << "\n";

}

int task_one(vector<string> input) {
    // Initialise tracking variables
    int position = 0;
    int depth = 0;
    // Iterate through vector
    for (const string command : input) {
        // Find value
        int value = atoi(&command.at(command.length()-1));
        // Find command
        string direction = command.substr(0, command.length()-2);
        // cout << value << "\t" << command.compare("forward") << "\n";
        // Command logic
        if (direction.compare("forward") == 0) {
            // cout << direction << "\n";
            position += value;
        }
        else {
            // cout << "\t" << direction << "\n";
            if (direction.compare("up") == 0) {
                depth -= value;
            }
            else {
                depth += value;
            }
        }
    }
    return depth*position;
}


int task_two(vector<string> input) {
    // Initialise tracking variables
    int position = 0;
    int depth = 0;
    int aim = 0;
    // Iterate through vector
    for (const string command : input) {
        // Find value
        int value = atoi(&command.at(command.length()-1));
        // Find command
        string direction = command.substr(0, command.length()-2);
        // cout << value << "\t" << command.compare("forward") << "\n";
        // Command logic
        if (direction.compare("forward") == 0) {
            // cout << direction << "\n";
            position += value;
            depth += aim*value;
        }
        else {
            // cout << "\t" << direction << "\n";
            if (direction.compare("up") == 0) {
                aim -= value;
            }
            else {
                aim += value;
            }
        }
    }
    return depth*position;
}