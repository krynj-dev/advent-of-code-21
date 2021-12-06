
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <Windows.h>

#define WHITE 15
#define HIGHLIGHT 3

using namespace std;

class Board {
    public:
        bool won = false;
    private:
        vector<vector<int>> board_numbers;
        bool marked[5][5];

    public:
        void set_board(vector<vector<int>> new_board) {
            board_numbers = new_board;
            // Reset marks
            for (int i=0; i < 5; i++) {
                for (int j=0; j < 5; j++) {
                    marked[i][j] = 0;
                }
            }
            return;
        }

        bool mark_pos(int x, int y) {
            marked[x][y] = true;
            return check_win();
        }

        bool mark_num(int n) {
            for (int i=0; i < 5; i++) {
                for (int j=0; j < 5; j++) {
                    if (board_numbers[i][j] == n) {
                        return mark_pos(i, j);
                    }
                }
            }
            return false;
        }

        void print_board() {
            HANDLE hConsole;
            hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

            cout << "Board:\n";
            for(int i=0; i<5; i++) {
                for(int j=0; j<5; j++) {
                    if (marked[i][j]) {
                        SetConsoleTextAttribute(hConsole, HIGHLIGHT);
                        cout <<  board_numbers[i][j] <<  ' ';
                        SetConsoleTextAttribute(hConsole, WHITE);
                    }
                    else {
                        cout << board_numbers[i][j] << ' ';
                    }
                }
                cout << '\n';
            }
        }

        int sum_not_marked() {
            int sum_nm = 0;
            for(int i=0; i < 5; i++) {
                for(int j=0; j < 5; j++) {
                    if (!marked[i][j]) {
                        sum_nm += board_numbers[i][j];
                    }
                }
            }
            return sum_nm;
        }

    private:
        bool check_win() {
            // Check rows
            for (int i=0; i<5; i++) {
                bool winning = true;
                for (int j=0; j<5; j++) {
                    if (!marked[i][j])
                        winning = false;
                }
                if (winning) {
                    won = true;
                    return true;
                }
            }
            // Check columns
            for (int j=0; j<5; j++) {
                bool winning = true;
                for (int i=0; i<5; i++) {
                    if (!marked[i][j])
                        winning = false;
                }
                if (winning) {
                    won = true;
                    return true;
                }
            }
            return false;
        }

};

// Function declarations
int task_one(vector<Board>, vector<int>);
int task_two(vector<Board>, vector<int>);

vector<int> get_draw_order(string, char=',');
vector<Board> get_boards(vector<string>);

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

    vector<int> d_o = get_draw_order(input[0]);

    vector<Board> boards = get_boards(input);

    // boards[0].mark_num(7);
    // boards[0].mark_num(22);
    // boards[0].mark_num(8);

    // for (int i = 0; i < 4; i++) {
    //     boards[i].print_board();
    //     cout << '\n';
    // }

    // for(int i: d_o)
    //     cout << i << " ";
    
    // Task One
    int ans1 = task_one(boards, d_o);
    cout << "1: The answer is " << ans1 << "\n";
    // Task Two
    int ans2 = task_two(boards, d_o);
    cout << "2: The answer is " << ans2 << "\n";

}


int task_one(vector<Board> boards, vector<int> draw_order) {
    // Initialise tracking variable
    int a = 1;
    int b = 1;
    // Iterate through vector
    Board winner;
    bool winner_found = false;
    int i=0;
    while (i < draw_order.size() && !winner_found) {
        cout << "PULLING " << draw_order[i] << endl;
        for (int x=0; x < boards.size(); x++) {
            bool won = boards[x].mark_num(draw_order[i]);
            if (won) {
                cout << "WINNER!" << endl;
                boards[x].print_board();
                winner = boards[x];
                winner_found = true;
                break;
            }
            // boards[x].print_board();
        }
        i++;
    }
    // Calculate Score
    a = draw_order[i-1];
    b = winner.sum_not_marked();
    return a*b;
}


int task_two(vector<Board> boards, vector<int> draw_order) {
    // Initialise tracking variable
    int a = 1;
    int b = 1;
    // Iterate through vector
    Board winner;
    bool remaining_board = true;
    int i=0;
    while (i < draw_order.size() && remaining_board) {
        // cout << "PULLING " << draw_order[i] << endl;
        remaining_board = false;
        for (int x=0; x < boards.size(); x++) {
            if(!boards[x].won) {
                remaining_board = true;
                bool won = boards[x].mark_num(draw_order[i]);
                if (won) {
                    // boards[x].print_board();
                    winner = boards[x];
                }
            }
            // boards[x].print_board();
        }
        i++;
    }
    // Calculate Score
    a = draw_order[i-2]; // -2 since loop happens another time before quitting
    b = winner.sum_not_marked();
    cout << a << " " << b << endl;
    return a*b;
}


vector<int> get_draw_order(string order_string, char delim) {
    vector<int> draw_order;
    int num_size = 1;
    for(int i=0; i < order_string.length(); i++) {
        int j = i+1;
        while(order_string[j] != delim) {
            j++;
            num_size++;
        }
        // cout << i << " " << j << " " << order_string.substr(i, j-i) << "\n";
        draw_order.push_back(stoi(order_string.substr(i, j-i)));
        i = j;
        num_size = 1;
    }
    return draw_order;
}

vector<Board> get_boards(vector<string> input) {
    // Declare return vector
    vector<vector<vector<int>>> boards_base;
    // Iterate through each board
    for(int i=2; i < input.size(); i += 6) {
        // Iterate through each line in the board
        vector<vector<int>> board;
        for(int j=i; j<i+5; j++) {
            vector<int> line = get_draw_order(input[j], ' ');
            // Read line into ints
            board.push_back(line);
        }
        boards_base.push_back(board);
    }

    vector<Board> boards_final;
    for (vector<vector<int>> board: boards_base) {
        Board board_obj;
        board_obj.set_board(board);
        boards_final.push_back(board_obj);
    }

    return boards_final;
}
