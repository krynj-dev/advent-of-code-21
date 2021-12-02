#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Function declarations
int task_one(vector<int>);
int task_two(vector<int>);

int main(int argc, char *argv[])
{
    // Read inputs from file
    ifstream inputFile;
    inputFile.open(argv[1]);
    // Read lines into vector
    vector<int> input;
    string line;
    while ( getline (inputFile, line) ) {
        input.push_back(stoi(line));
    }
    
    // Task One
    int drops1 = task_one(input);
    cout << "1: The count is " << drops1 << "\n";
    // Task Two
    int drops2 = task_two(input);
    cout << "2: Your count is " << drops2 << "\n";

}


int task_one(vector<int> input) {
    // Initialise tracking variable
    int count = 0;
    // Iterate through vector
    for (int i = 1; i < input.size(); i++) {
        if (input[i] > input[i-1]) {
            count += 1;
        }
    }
    return count;
}


int task_two(vector<int> input) {
    // Initialise tracking variable
    int count = 0;
    // Cheat: Each triple shares two elements, so dont bother adding/comparing them
    // Iterate through vector
    for (int i = 3; i < input.size(); i++) {
        if (input[i] > input[i-3]) {
            count += 1;
        }
    }
    return count;
}