#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int NUMBER_OF_LOCATIONS = 776;
const int NUMBER_Of_INSTRUCTIONS = 296;
struct Location *locations;

struct Location {
  char name[4];
  char left[4];
  char right[4];
};

void find(char* buffer, char* name, char instruction) {
  for(int i=0; i<NUMBER_OF_LOCATIONS; i++) {
    if (
      locations[i].name[0] == name[0] && 
      locations[i].name[1] == name[1] && 
      locations[i].name[2] == name[2]
    ) {
      if(instruction == 'L') {
        strcpy(buffer, locations[i].left);
      } else {
        strcpy(buffer, locations[i].right);
      }
      return;
    }
  }
}

int main() {
  locations = malloc(sizeof(struct Location) * NUMBER_OF_LOCATIONS);
  char instructions[NUMBER_Of_INSTRUCTIONS];

  // Read the file
  FILE *fp = fopen("8.txt", "r");
  char line[NUMBER_Of_INSTRUCTIONS];
  int lineNumber = 0;
  int locationNumber = 0;
  while(fgets(line, NUMBER_Of_INSTRUCTIONS, fp) != NULL) {
    if(lineNumber == 0) {
      strcpy(instructions, line);
    } else if(lineNumber > 1) {
      struct Location location;
      strncpy(location.name, line, 3);
      location.left[0] = line[7];
      location.left[1] = line[8];
      location.left[2] = line[9];
      location.right[0] = line[12];
      location.right[1] = line[13];
      location.right[2] = line[14];
      location.left[3] = '\0';
      location.name[3] = '\0';
      location.right[3] = '\0';
      locations[locationNumber] = location;
      locationNumber ++;
    }
    lineNumber ++;
  }


  char buffer[3];
  int instructionNumber = 0;
  char instruction = instructions[instructionNumber];
  find(buffer, "AAA", instruction);
  int result = 1;
  while(buffer[0] != 'Z' || buffer[1] != 'Z' || buffer[2] != 'Z') {
    result ++;
    instructionNumber ++;
    char instruction = instructions[instructionNumber % (NUMBER_Of_INSTRUCTIONS - 3)];
    find(buffer, buffer, instruction);
  }
  
  // Print the result
  printf("Result: %d\n", result);

  return 0;
}