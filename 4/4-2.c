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

int getNumberOfMatches(int board[], int winningNumbers[]) {
  int matches = 0;
  for(int i = 0; i < 25; i++) {
    if(numberIsInBoard(winningNumbers[i], board)) {
      matches ++;
    }
  }
  return matches;
}


int main() {
  int scoreboardCopies[193];
  int result = 193;

  // Populate scoreboardCopies
  for(int i=0; i<193; i++) {
    scoreboardCopies[i] = 1;
  }

  // Parse the input 
  FILE *fp = fopen("4.txt", "r");
  char line[118];
  int cardIndex = 0;
  while(fgets(line, 118, fp) != NULL) {
    // Read the board and the winning numbers
    int board[10];
    int winningNumbers[25];
    readBoard((char *)line, board);
    readWinningNumbers((char *)line, winningNumbers);
    
    // Determine number of matches
    int numberOfMatches = getNumberOfMatches(board, winningNumbers);
    int scoreboards = numberOfMatches * scoreboardCopies[cardIndex];
    result += scoreboards;
    printf("%d - %d matches, %d copies, %d scoreboards\n", cardIndex, numberOfMatches, scoreboardCopies[cardIndex], scoreboards);
    for(int i = 1; i <= numberOfMatches; i++) {
      if(cardIndex + i > 193) continue;
      scoreboardCopies[cardIndex + i] += scoreboardCopies[cardIndex];
    }
    
    cardIndex ++;
  }

  // Print the result
  printf("Result: %d\n", result);
}