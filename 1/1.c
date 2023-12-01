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
      if (c >= '0' && c <= '9') {
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