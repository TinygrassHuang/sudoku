void load_board(const char* filename, char board[9][9]);
void display_board(const char board[9][9]);
bool is_complete(char const board[9][9]);
bool make_move(char position[2],char digit,char board[9][9]);
bool check_digit(int row, int column, char const board[9][9], char digit);
bool save_board(char* const filename, char const board[9][9]);
bool solve_board(char board[9][9]);
