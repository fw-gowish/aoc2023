#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int RED_MAX = 12;
const int GREEN_MAX = 13;
const int BLUE_MAX = 14;
const char* COLOR_RED = "red";
const char* COLOR_GREEN = "green";
const char* COLOR_BLUE = "blue";

int lineGetGameIdValue(const char* line_raw) {
  // Remove everything before colon in line
  char* line_weird = strchr(line_raw, ':');
  
  // Remove first two characters from line
  char* line = malloc(strlen(line_weird) - 2);
  strncpy(line, line_weird + 2, strlen(line_weird) - 2);

  // Split lines by grabs
  char* grab = strtok(line, " ");

  int red = 0;
  int green = 0;
  int blue = 0;

  // Go through each grab
  while (grab != NULL) {
    if (grab[0] >= '0' && grab[0] <= '9') {
      int value = atoi(grab);
      const char* label = strtok(NULL, " ");

      // Apply value in appropriate color
      if(label[0] == 'r') red += value;
      else if(label[0] == 'g') green += value;
      else if(label[0] == 'b') blue += value;

      // If grab is terninated, determine possibility of game
      char lastChar = label[strlen(label) - 1];
      if (lastChar == ';' || lastChar == '\n') {
        if(red > RED_MAX || green > GREEN_MAX || blue > BLUE_MAX) return 0;
        red = green = blue = 0;
      }
    }

    grab = strtok(NULL, " ");
  }

  return atoi(&line_raw[5]);
}

int main() {
  FILE *fp = fopen("2.txt", "r");
  char line[200];
  int summedPossibleGameIds = 0;

  // Read every line
  while (fgets(line, 200, fp) != NULL) {
    int gameValue = lineGetGameIdValue(line);
    summedPossibleGameIds += gameValue;
  }

  // Print summedPossibleGameIds
  printf("Result: %d\n", summedPossibleGameIds);
}