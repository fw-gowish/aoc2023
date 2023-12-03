#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *map [140];
const int MAP_SIZE = 140;
char CHNULL = '.';

int isSymbol(char input) {
  if(input >= '0' && input <= '9') {
    return 0;
  } else if(input == CHNULL) {
    return 0;
  } else {
    return 1;
  }
}

int readFile() {
  FILE *fp = fopen("3.txt", "r");
  int lineNumber = 0;
  char line[142];
  for(int i=0; i<142; i++) {
    fgets(line, 142, fp);
    map[i] = strdup(line);
  }
}

int sum() {
  // Sliding window
  char *top[3];
  char *middle[3];
  char *bottom[3];

  // State
  char numberBuffer[3] = { ' ' };
  int isSymbolNearby = 0;

  // Result
  int partNumberSum = 0;

  // Slide window through map
  for(int lineIndex = 0; lineIndex < MAP_SIZE; lineIndex ++) {
    for(int charIndex = 0; charIndex < MAP_SIZE; charIndex ++) {

      // Update sliding window top
      if(lineIndex - 1 < 0 || charIndex - 1 < 0) top[0] = &CHNULL;
      else top[0] = &map[lineIndex - 1][charIndex - 1];
      if(lineIndex - 1 < 0) top[1] = &CHNULL;
      else top[1] = &map[lineIndex - 1][charIndex];
      if(lineIndex - 1 < 0 || charIndex + 1 >= MAP_SIZE) top[2] = &CHNULL;
      else top[2] = &map[lineIndex - 1][charIndex + 1];

      // Update sliding window middle
      if(charIndex - 1 < 0) middle[0] = &CHNULL;
      else middle[0] = &map[lineIndex][charIndex - 1];
      middle[1] = &map[lineIndex][charIndex];
      if(charIndex + 1 >= MAP_SIZE) middle[2] = &CHNULL;
      else middle[2] = &map[lineIndex][charIndex + 1];

      // Update sliding window bottom
      if(lineIndex + 1 >= MAP_SIZE || charIndex - 1 < 0) bottom[0] = &CHNULL;
      else bottom[0] = &map[lineIndex + 1][charIndex - 1];
      if(lineIndex + 1 >= MAP_SIZE) bottom[1] = &CHNULL;
      else bottom[1] = &map[lineIndex + 1][charIndex];
      if(lineIndex + 1 >= MAP_SIZE || charIndex + 1 >= MAP_SIZE) bottom[2] = &CHNULL;
      else bottom[2] = &map[lineIndex + 1][charIndex + 1];

      // Get the center character in the sliding window
      char *currentChar = middle[1];

      // Check if currentChar is a number
      if(*currentChar >= '0' && *currentChar <= '9') {
        // If currentChar is a number, append it to the numberBuffer
        numberBuffer[0] = numberBuffer[1];
        numberBuffer[1] = numberBuffer[2];
        numberBuffer[2] = *currentChar;
        
        // Check for symbols around
        if(isSymbol(*top[0]) || isSymbol(*top[1]) || isSymbol(*top[2]) || isSymbol(*middle[0]) || isSymbol(*middle[2]) || isSymbol(*bottom[0]) || isSymbol(*bottom[1]) || isSymbol(*bottom[2])) {
          isSymbolNearby = 1;
        }
      } else {
        // Add number to total, if it is a machine part
        if(isSymbolNearby) {

          // Remove spaces from numberBuffer
          if(numberBuffer[0] == ' ') numberBuffer[0] = '0';
          if(numberBuffer[1] == ' ') numberBuffer[1] = '0';
          if(numberBuffer[2] == ' ') numberBuffer[2] = '0';

          // Create a null-terminated numberBuffer
          char nullTerminatedNumberBuffer[4] = { numberBuffer[0], numberBuffer[1], numberBuffer[2], '\0' };
          int value = atoi(nullTerminatedNumberBuffer);
          partNumberSum += value;
        }

        // Reset the numberBuffer
        numberBuffer[0] = ' ';
        numberBuffer[1] = ' ';
        numberBuffer[2] = ' ';
        isSymbolNearby = 0;
      }
    }

    // Add number to total, if it is a machine part
    if(isSymbolNearby) {

      // Remove spaces from numberBuffer
      if(numberBuffer[0] == ' ') numberBuffer[0] = '0';
      if(numberBuffer[1] == ' ') numberBuffer[1] = '0';
      if(numberBuffer[2] == ' ') numberBuffer[2] = '0';

      // Create a null-terminated numberBuffer
      char nullTerminatedNumberBuffer[4] = { numberBuffer[0], numberBuffer[1], numberBuffer[2], '\0' };
      int value = atoi(nullTerminatedNumberBuffer);
      partNumberSum += value;
    }

    // Reset the numberBuffer
    numberBuffer[0] = ' ';
    numberBuffer[1] = ' ';
    numberBuffer[2] = ' ';
    isSymbolNearby = 0;
  }

  return partNumberSum;
}

int main() {
  readFile();
  int result = sum();
  printf("Result: %d\n", result);
}
