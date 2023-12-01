#include "stdio.h"
#include "string.h"
#include "stdlib.h"

int main()
{
  // Read the input file main.c 
  FILE *fp = fopen("1.txt", "r");
  
  // Read the file line by line
  char line[100];
  int total = 0;
  while (fgets(line, 100, fp) != NULL) {
    int line_length = strlen(line);
    char first_number_char = NULL;
    char last_number_char = NULL;
    for(int i=0; i<line_length; i++) {
      char c = line[i];

      // Replace 'one' with '1', 'two' with '2', etc.
      if (strncmp(&line[i], "one", 3) == 0) {
        c = '1';
      } else if (strncmp(&line[i], "two", 3) == 0) {
        c = '2';
      } else if (strncmp(&line[i], "three", 5) == 0) {
        c = '3';
      } else if (strncmp(&line[i], "four", 4) == 0) {
        c = '4';
      } else if (strncmp(&line[i], "five", 4) == 0) {
        c = '5';
      } else if (strncmp(&line[i], "six", 3) == 0) {
        c = '6';
      } else if (strncmp(&line[i], "seven", 5) == 0) {
        c = '7';
      } else if (strncmp(&line[i], "eight", 5) == 0) {
        c = '8';
      } else if (strncmp(&line[i], "nine", 4) == 0) {
        c = '9';
      }

      if (c >= '1' && c <= '9') {
        if (first_number_char == NULL) {
          first_number_char = c;
        } else {
          last_number_char = c;
        }
      }
    }
    if(first_number_char == NULL) {
      first_number_char = '0';
    }
    if(last_number_char == NULL) {
      last_number_char = first_number_char;
    }
    char total_number_char[2] = {first_number_char, last_number_char};
    int total_number = atoi(total_number_char);
    total += total_number;
  }

  // Print the total
  printf("Total: %d\n", total);
  fclose(fp);
  return 0;
}