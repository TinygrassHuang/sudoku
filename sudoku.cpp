#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "sudoku.h"

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* pre-supplied function to load a Sudoku board from a file */
void load_board(const char* filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in) {
    cout << "Failed!\n";
  }
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << '\n';
  assert(row == 9);
}

/* internal helper function */
void print_frame(int row) {
  if (!(row % 3)) {
    cout << "  +===========+===========+===========+\n";
  } else {
    cout << "  +---+---+---+---+---+---+---+---+---+\n";
  }
}

/* internal helper function */
void print_row(const char* data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|\n";
}

/* pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++) {
    cout << (char) ('1'+r) << "   ";
  }
  cout << '\n';
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}

/* add your functions here */

// blank is represented by '.', retur false if there's a blank found
bool is_complete(char const board[9][9]){
  for (int row = 0 ; row<9 ; row++){
    for (int column = 0 ; column<9 ; column++){
      if (board[row][column] < '1' || board[row][column] > '9'){
	return false;
      }
    }
  }
  return true;
}

// check if the move is legal, if legal then put the number in sudoku board.
bool make_move(char position[2] ,char digit,char board[9][9]){
  
  // get the position index
  int position_row = position[0] - 'A';
  int position_column = position[1] - '1';

  // check if the index is out of bound
  if (position_row < 0 || position_row > 8 || position_column < 0 || position_column > 8)
    return false;
  // check if the digit is legal
  if (digit < '1' || digit > '9')
    return false;
  // check if the position is empty
  if (board[position_row][position_column] != '.')
    return false;
  // check if digit has been used in row, column or 3x3 subgrid.
  if (!check_digit(position_row, position_column, board, digit))
    return false;
  
  board[position_row][position_column] = digit;// place digit
  return true;
}


// check if the digit has been used in row, column or 3x3 subgrid
bool check_digit(int row, int column, char const board[9][9], char digit){
  
  // check if the digit has been used in this column
  for (int n=0; n<9; n++){
    if (board[row][n] == digit)
      return false;
  }

  // check if the digit has been used in this row
  for (int n=0; n<9; n++){
    if (board[n][column] == digit)
      return false;
  }

  // check if the digit has been used in 3x3 subgrid
  for (int n = (row/3)*3; n < (row/3)*3 + 3; n++){
    for (int m = (column/3)*3; m < (column/3)*3 + 3; m++){
      if (board[n][m] == digit)
	return false;
    }
    }
  return true;
}

// save the board to a file
bool save_board(char* const filename, char const board[9][9]){
  ofstream out;
  out.open(filename);

  if (out.fail())//return false if the file can't be opened
    return false;
  
  for ( int row=0 ; row<9 ; row++){
    for ( int column=0 ; column<9 ; column++){
      out.put(board[row][column]);
      if (column == 8)
	out.put('\n');
      if (out.bad())//return false if the character can't be written
	return false;
    }
  }
  
  out.close();
  
  if (out.fail())//return false if the file can't be closed
    return false;
  
  return true;
}


// solve the sudoku board using recursion, return true if there is an answer
bool solve_board(char board[9][9]){
  
  // iterate all position on the board
  for (int row=0; row<9 ; row++){
    for (int column=0; column<9 ; column++){
      // check if the position is empty
      if (board[row][column] == '.'){
	// try every digit from 1 to 9, return false if all the digits have been tried
	for (char n='1'; n<='9' ; n++){
	  // place the digit if it is legal,
	  if (check_digit(row, column, board, n)){
	    board[row][column] = n;
	    // call this function again (RECURSION), if no answer delete previous digit placed
	    if (solve_board(board))
	      return true;
	    else
	      board[row][column] = '.';
	  }
	}
	return false;
      }
    }
  }
  return true;
}
