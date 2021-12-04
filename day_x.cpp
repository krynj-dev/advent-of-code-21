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
    int ans1 = task_one(input);
    cout << "1: The answer is " << ans1 << "\n";
    // Task Two
    int ans2 = task_two(input);
    cout << "2: Your answer is " << ans2 << "\n";

}


int task_one(vector<string> input) {
    // Initialise tracking variable
    int a = 0;
    // Iterate through vector
    for (int i=0; i < input.size(); i++) {
        
    }
    return a;
}


int task_two(vector<string> input) {
    // Initialise tracking variable
    int b = 0;
    // Iterate through vector
    for (int i=0; i < input.size(); i++) {
        
    }
    return b;
}