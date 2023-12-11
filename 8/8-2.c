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
      break;
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

  long long result = 0;

  char buffer1[4] = "VSA";
  //char buffer2[4] = "GTA";
  //char buffer3[4] = "VDA";
  //char buffer4[4] = "BBA";
  //char buffer5[4] = "AAA";
  //char buffer6[4] = "VSA";

  long long instructionNumber = 0;

  while(
    buffer1[2] != 'Z' 
    //buffer2[2] != 'Z' ||
    //buffer3[2] != 'Z' ||
    //buffer4[2] != 'Z' ||
    //buffer5[2] != 'Z' ||
    //buffer6[2] != 'Z'
  ) {
    char instruction = instructions[instructionNumber % (NUMBER_Of_INSTRUCTIONS - 3)];
    find(buffer1, buffer1, instruction);
    //find(buffer2, buffer2, instruction);
    //find(buffer3, buffer3, instruction);
    //find(buffer4, buffer4, instruction);
    //find(buffer5, buffer5, instruction);
    //find(buffer6, buffer6, instruction);
    instructionNumber ++;
    result ++;
  }

  // Print result
  printf("Result: %d\n", result);

  return 0;
}

// I used this as a playground to find the starts that started with A, find out how many steps they individually had
// to reach a Z-ending & put the numbers in an online LCM calculator
// A bit of a manual solution, but it worked. 

/*
  PS C:\Users\PC\files\Homebrew\aoc2023\8> gcc 8-2.c -o 8-2.exe
  PS C:\Users\PC\files\Homebrew\aoc2023\8> .\8-2.exe
  Result: 13771
  PS C:\Users\PC\files\Homebrew\aoc2023\8> gcc 8-2.c -o 8-2.exe
  PS C:\Users\PC\files\Homebrew\aoc2023\8> .\8-2.exe
  Result: 20803
  PS C:\Users\PC\files\Homebrew\aoc2023\8> gcc 8-2.c -o 8-2.exe
  PS C:\Users\PC\files\Homebrew\aoc2023\8> .\8-2.exe
  Result: 23147
  PS C:\Users\PC\files\Homebrew\aoc2023\8> gcc 8-2.c -o 8-2.exe
  PS C:\Users\PC\files\Homebrew\aoc2023\8> .\8-2.exe
  Result: 19631
  PS C:\Users\PC\files\Homebrew\aoc2023\8> gcc 8-2.c -o 8-2.exe
  PS C:\Users\PC\files\Homebrew\aoc2023\8> .\8-2.exe
  Result: 17287
  PS C:\Users\PC\files\Homebrew\aoc2023\8> gcc 8-2.c -o 8-2.exe
  PS C:\Users\PC\files\Homebrew\aoc2023\8> .\8-2.exe
  Result: 17873
*/

// Final result: 18625484023687