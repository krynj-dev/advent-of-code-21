#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Function declarations
int task_one(vector<string>);
int task_two(vector<string>);
vector<int> count_zeros(vector<string>);

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
    int pc = task_one(input);
    cout << "1: Your power consumption is " << pc << "\n";
    // Task Two
    int ls = task_two(input);
    cout << "2: Your life support rating is " << ls << "\n";

}

int task_one(vector<string> input) {
    // Initialise tracking variables
    vector<int> zeros = count_zeros(input);
    // Calculate rates
    int gamma = 0;
    int epsilon = 0;
    for(int i=0; i < zeros.size(); i++) {
        int val = zeros[zeros.size()-1-i] < input.size() / 2;
        gamma += val << i;
        epsilon += !val << i;
    }
    // cout << gamma << "\n";
    // cout << epsilon << "\n";
    return gamma*epsilon;
}


int task_two(vector<string> input) {
    // Initialise tracking variables
    vector<string> o2_pool = input, co2_pool = input;
    vector<int> o2_zeros = count_zeros(o2_pool), co2_zeros = count_zeros(co2_pool);
    bool o2_found = false, co2_found = false;
    // for(int i: o2_zeros)
    //     cout << i << " ";
    //     cout << "\n";
    int bit;
    // Iterate for each column
    for (int x=0; x < o2_zeros.size(); x++) { // x is the current column being examined
        // cout << "x=" << x << "\n";
        vector<string> o2_temp, co2_temp;
        int o2_val = o2_zeros[x] <= o2_pool.size() / 2;
        int co2_val = co2_zeros[x] <= co2_pool.size() / 2;
        // Check o2 pool
        for(const string num: o2_pool) {
            bit = num[x]-'0';
            if(bit == o2_val) {
                o2_temp.push_back(num);
                // cout << "keeping " << num << "\n";
            }
        }
        // Check co2 pool
        for(const string num: co2_pool) {
            bit = num[x]-'0';
            if(bit != co2_val) {
                co2_temp.push_back(num);
                // cout << "keeping " << num << "\n";
            }
        }
        // Check if found
        if(o2_pool.size() == 1){
            o2_found = true;
        }
        if(co2_pool.size() == 1){
            co2_found = true;
        }
        // prune pool
        if (!o2_found){
            o2_pool = o2_temp;
            o2_zeros = count_zeros(o2_pool);
        }
        if (!co2_found){
            co2_pool = co2_temp;
            co2_zeros = count_zeros(co2_pool);
        }
    }
    // cout << o2_pool[0] << "\n";
    // cout << co2_pool[0] << "\n";
    // Convert to decimal
    int o2_rating = 0;
    int co2_rating = 0;
    for(int i=0; i < o2_pool[0].length(); i++) {
        int o2_val = o2_pool[0][o2_pool[0].length()-1-i]-'0';
        int co2_val = co2_pool[0][co2_pool[0].length()-1-i]-'0';
        o2_rating += o2_val << i;
        co2_rating += co2_val << i;
    }

    return o2_rating*co2_rating;
}

vector<int> count_zeros(vector<string> input) {
    vector<int> zeros(input[0].length());
    // Iterate through vector
    for(int i=0; i < input.size(); i++) {
        for (int j=0; j < input[i].length(); j++) {
            int val = input[i][j]-'0';
            if ( !val ) {
                zeros[j] += 1;
            }
        }
    }
    return zeros;
}
