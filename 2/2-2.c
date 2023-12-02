#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int lineGetGameIdValue(const char* line_raw) {
  int red = 0;
  int green = 0;
  int blue = 0;
  int min_red = 0;
  int min_green = 0;
  int min_blue = 0;

  // Remove everything before colon in line
  char* line_weird = strchr(line_raw, ':');
  
  // Remove first two characters from line
  char* line = malloc(strlen(line_weird) - 2);
  strncpy(line, line_weird + 2, strlen(line_weird) - 2);

  // Split lines by grabs
  char* grab = strtok(line, " ");


  // Go through each grab
  while (grab != NULL) {
    if (grab[0] >= '0' && grab[0] <= '9') {
      int value = atoi(grab);
      const char* label = strtok(NULL, " ");

      // Apply value in appropriate color
      if(label[0] == 'r') {
        red += value;
        if(red > min_red) min_red = red;
      }
      else if(label[0] == 'g') {
        green += value;
        if(green > min_green) min_green = green;
      }
      else if(label[0] == 'b') {
        blue += value;
        if(blue > min_blue) min_blue = blue;
      }

      // If grab is terninated, determine possibility of game
      char lastChar = label[strlen(label) - 1];
      if (lastChar == ';' || lastChar == '\n') {
        if(red > min_red) min_red = red;
        if(green > min_green) min_green = green;
        if(blue > min_blue) min_blue = blue;
        red = 0;
        green = 0;
        blue = 0;
      }
    }

    grab = strtok(NULL, " ");
  }

  // Free memory
  free(line);

  printf("Min Red: %d, Min Green: %d, Min Blue: %d\n", min_red, min_green, min_blue);
  return min_red * min_green * min_blue;
}

int main() {
  FILE *fp = fopen("2.txt", "r");
  char line[200];
  int summedPossibleGameIds = 0;
  int i = 0;

  while (fgets(line, 200, fp) != NULL) {
    ++i;
    printf("---- %i ----\n", i);
    int gameValue = lineGetGameIdValue(line);
    printf("Game Value: %d\n\n", gameValue);
    summedPossibleGameIds += gameValue;
  }

  printf("Result: %d\n", summedPossibleGameIds);
}