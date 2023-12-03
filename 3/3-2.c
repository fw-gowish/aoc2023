#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *map [140];
const int MAP_SIZE = 140;
const char GEAR = '*';
char* DEFAULT_LINE = "............................................................................................................................................";

int isSymbol(char input) {
  if(input >= '0' && input <= '9') {
    return 0;
  } else if(input == '.') {
    return 0;
  } else {
    return 1;
  }
}

int isNumber(char input) {
  if(input >= '0' && input <= '9') {
    return 1;
  } else {
    return 0;
  }
}

void reverse(char input[]) {
    int size = sizeof(&input) / sizeof(char);
    for(int i = 0; i < size / 2; i++) {
        char temp = input[i];
        input[i] = input[size - i - 1];
        input[size - i - 1] = temp;
    }
}

void cleanupRight(int size, char input[]) {
    for(int i = 0; i < size; i++) {
        if(isNumber(input[i])) continue;
        else {
          for(int j = i; j < size; j++) {
            input[j] = ' ';
          }
          return;
        }
    }
}

void cleanupLeft(int size, char input[]) {
    for(int i = size - 1; i >= 0; i--) {
        if(isNumber(input[i])) continue;
        else {
          for(int j = i; j >= 0; j--) {
            input[j] = '0';
          }
          return;
        }
    }
}

void cleanupMiddle(int size, char input[]) {
  int startIndex = (size - 1) / 2;
  while(isNumber(input[startIndex - 1])) { startIndex --; }
  int endIndex = startIndex - 1;
  while(isNumber(input[endIndex + 1])) { endIndex ++; }

  // Slice string
  int length = endIndex - startIndex + 1;
  char* result = malloc(length * sizeof(char));
  for(int i = 0; i < length; i++) { result[i] = input[startIndex + i]; }

  // Put it into input
  for(int i = 0; i < length; i++) { input[i] = result[i]; }

  // Fill rest of input with empty space
  for(int i = length; i < size; i++) { input[i] = ' '; }

  // Free memory
  free(result);
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
  // Result
  int partNumberSum = 0;

  // Slide window through map
  for(int lineIndex = 0; lineIndex < MAP_SIZE; lineIndex ++) {
    for(int charIndex = 0; charIndex < MAP_SIZE; charIndex ++) {

      char *topLine;
      char *middleLine;
      char *bottomLine;

      if (lineIndex > 0) topLine = map[lineIndex - 1];
      else topLine = DEFAULT_LINE;
      middleLine = map[lineIndex];
      if (lineIndex < MAP_SIZE - 1) bottomLine = map[lineIndex + 1];
      else bottomLine = DEFAULT_LINE;

      // Get surrounding characters
      char topChar = topLine[charIndex];
      char topLeftChar = topLine[charIndex - 1];
      char topRightChar = topLine[charIndex + 1];
      char leftChar = middleLine[charIndex - 1];
      char currentChar = middleLine[charIndex];
      char rightChar = middleLine[charIndex + 1];
      char bottomChar = bottomLine[charIndex];
      char bottomLeftChar = bottomLine[charIndex - 1];
      char bottomRightChar = bottomLine[charIndex + 1];

      // Look for gears
      if(currentChar == GEAR) {
        char topLeftNumber[4] = { '0', '0', '0', '\0' };
        char topNumber[6] = { '0', '0', '0', '0', '0', '\0' };
        char topRightNumber[4] = { '0', '0', '0', '\0' };
        char leftNumber[4] = { '0', '0', '0', '\0' };
        char rightNumber[4] = { '0', '0', '0', '\0' };
        char bottomLeftNumber[4] = { '0', '0', '0', '\0' };
        char bottomNumber[6] = { '0', '0', '0', '0', '0', '\0' };
        char bottomRightNumber[4] = { '0', '0', '0', '\0' };
      
        // Top
        if(isNumber(topChar)) {
          topNumber[0] = topLine[charIndex - 2];
          topNumber[1] = topLine[charIndex - 1];
          topNumber[2] = topLine[charIndex];
          topNumber[3] = topLine[charIndex + 1];
          topNumber[4] = topLine[charIndex + 2];
          cleanupMiddle(5, topNumber);
        } else {
          // Top left
          if(isNumber(topLeftChar)) {
            topLeftNumber[0] = topLine[charIndex - 3];
            topLeftNumber[1] = topLine[charIndex - 2];
            topLeftNumber[2] = topLine[charIndex - 1];

            cleanupLeft(3, topLeftNumber);
          }
          if(isNumber(topRightChar)) {
            topRightNumber[0] = topLine[charIndex + 1];
            topRightNumber[1] = topLine[charIndex + 2];
            topRightNumber[2] = topLine[charIndex + 3];
            cleanupRight(3, topRightNumber);
          }
        }

        // Middle
        if(isNumber(leftChar)) {
          leftNumber[0] = middleLine[charIndex - 3];
          leftNumber[1] = middleLine[charIndex - 2];
          leftNumber[2] = middleLine[charIndex - 1];
          cleanupLeft(3, leftNumber);
        }
        if(isNumber(rightChar)) {
          rightNumber[0] = middleLine[charIndex + 1];
          rightNumber[1] = middleLine[charIndex + 2];
          rightNumber[2] = middleLine[charIndex + 3];
          cleanupRight(3, rightNumber);
        }

        // Bottom
        if(isNumber(bottomChar)) {
          bottomNumber[0] = bottomLine[charIndex - 2];
          bottomNumber[1] = bottomLine[charIndex - 1];
          bottomNumber[2] = bottomLine[charIndex];
          bottomNumber[3] = bottomLine[charIndex + 1];
          bottomNumber[4] = bottomLine[charIndex + 2];
          cleanupMiddle(5, bottomNumber);
        } else {
          if(isNumber(bottomLeftChar)) {
            bottomLeftNumber[0] = bottomLine[charIndex - 3];
            bottomLeftNumber[1] = bottomLine[charIndex - 2];
            bottomLeftNumber[2] = bottomLine[charIndex - 1];
            cleanupLeft(3, bottomLeftNumber);
          }
          if(isNumber(bottomRightChar)) {
            bottomRightNumber[0] = bottomLine[charIndex + 1];
            bottomRightNumber[1] = bottomLine[charIndex + 2];
            bottomRightNumber[2] = bottomLine[charIndex + 3];

            for(int i=0; i<3; i++) {
              printf("%c", bottomRightNumber[i]);
              printf("\n");
            }

            cleanupRight(3, bottomRightNumber);

            for(int i=0; i<3; i++) {
              printf("%c", bottomRightNumber[i]);
              printf("\n");
            }
          }
        }

        // Add null terminators


        // Get number of matches
        int topLeftInt = atoi(topLeftNumber);
        int topInt = atoi(topNumber);
        int topRightInt = atoi(topRightNumber);
        int leftInt = atoi(leftNumber);
        int rightInt = atoi(rightNumber);
        int bottomLeftInt = atoi(bottomLeftNumber);
        int bottomInt = atoi(bottomNumber);
        int bottomRightInt = atoi(bottomRightNumber);


        int numberOfMatches = 0;
        if(topLeftInt > 0) numberOfMatches ++;
        if(topInt > 0) numberOfMatches ++;
        if(topRightInt > 0) numberOfMatches ++;
        if(leftInt > 0) numberOfMatches ++;
        if(rightInt > 0) numberOfMatches ++;
        if(bottomLeftInt > 0) numberOfMatches ++;
        if(bottomInt > 0) numberOfMatches ++;
        if(bottomRightInt > 0) numberOfMatches ++;

        printf("topLeftInt: %d, topInt: %d, topRightInt: %d, leftInt: %d, rightInt: %d, bottomLeftInt: %d, bottomInt: %d, bottomRightInt: %d\n", topLeftInt, topInt, topRightInt, leftInt, rightInt, bottomLeftInt, bottomInt, bottomRightInt);


        // If there are exactly two matches, add it to the result
        if(numberOfMatches == 2) {
          int value = 0;
          if(topLeftInt > 0) {
            if(value == 0) value = topLeftInt;
            else value *= topLeftInt;
          }
          if(topInt > 0) {
            if(value == 0) value = topInt;
            else value *= topInt;
          }
          if(topRightInt > 0) {
            if(value == 0) value = topRightInt;
            else value *= topRightInt;
          }
          if(leftInt > 0) {
            if(value == 0) value = leftInt;
            else value *= leftInt;
          }
          if(rightInt > 0) {
            if(value == 0) value = rightInt;
            else value *= rightInt;
          }
          if(bottomLeftInt > 0) {
            if(value == 0) value = bottomLeftInt;
            else value *= bottomLeftInt;
          }
          if(bottomInt > 0) {
            if(value == 0) value = bottomInt;
            else value *= bottomInt;
          }
          if(bottomRightInt > 0) {
            if(value == 0) value = bottomRightInt;
            else value *= bottomRightInt;
          }
          partNumberSum += value;
        }
      }
    }
  }

  return partNumberSum;
}

int main() {
  readFile();
  int result = sum();
  printf("Result: %d\n", result);
}
