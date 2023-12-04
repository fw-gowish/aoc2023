#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isNumber(char c) {
  return c >= '0' && c <= '9';
}

int readNumberAt(char* text, int index) {
  char c1 = text[index];
  char c2 = text[index + 1];
  if(!isNumber(c1)) c1 = '0';
  if(!isNumber(c2)) c2 = ' ';
  char total[3] = {c1, c2, '\0'};
  int output = atoi(total);
  return output;
}

void readBoard(char* line, int board[]) {
  for(int i=0; i<10; i+=1) {
    board[i] = readNumberAt(line, 10 + i * 3);
  }
}

void readWinningNumbers(char* line, int winningNumbers[]) {
  for(int i=0; i<25; i+=1) {
    winningNumbers[i] = readNumberAt(line, 42 + i * 3);
  }
}

int numberIsInBoard(int number, int board[]) {
  for(int i=0; i<10; i++) {
    if(board[i] == number) return 1;
  }
  return 0;
}

int getPoints(int board[], int winningNumbers[]) {
  int matches = 0;
  for(int i = 0; i < 25; i++) {
    if(numberIsInBoard(winningNumbers[i], board)) {
      matches ++;
    }
  }
  int points = 0;
  while(matches > 0) {
    matches --;
    if(points == 0) points = 1;
    else points *= 2;
  }

  return points;
}

int main() {
  int result = 0;

  // Parse the input 
  FILE *fp = fopen("4.txt", "r");
  char line[118];
  while(fgets(line, 118, fp) != NULL) {
    // Read the board and the winning numbers
    int board[10];
    int winningNumbers[25];
    readBoard((char *)line, board);
    readWinningNumbers((char *)line, winningNumbers);
    
    // Determine points
    int points = getPoints(board, winningNumbers);
    result += points;
  }

  // Print the result
  printf("Result: %d\n", result);
}