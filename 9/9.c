#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long getNextNumber(long numbers[], int size) {
  long nextNumber = numbers[size - 1];
  long *oldDifferences = malloc(sizeof(long) * (size - 1));
  long *differences = malloc(sizeof(long) * (size - 1));

  long sum = 0;
  for(int i = 0; i < size - 1; i++) {
    differences[i] = numbers[i + 1] - numbers[i];
    sum += differences[i];
  }

  int iteration = 1;
  nextNumber += differences[size - 1 - iteration];
  while(sum != 0) {
    // Copy differences to oldDifferences
    memcpy(oldDifferences, differences, sizeof(long) * (size - 1));

    // Clear differences
    memset(differences, 0, sizeof(long) * (size - 1));

    // Calculate new differences
    long lastOutput = 0;
    for(int i = 0; i < size - 1 - iteration; i++) {
      differences[i] = oldDifferences[i + 1] - oldDifferences[i];
      lastOutput = differences[i];
    }

    // Calculate new sum
    sum = 0;
    for(int i = 0; i < size - 1 - iteration; i++) {
      sum += differences[i];
    }

    // Calculate next number
    nextNumber += lastOutput;
    iteration ++;
  }

  // Free memory
  free(oldDifferences);
  free(differences);

  return nextNumber;
}

int main() {

  FILE *fp = fopen("9.txt", "r");
  char line[300];
  long result = 0;
  int lineNumber = 1;
  while(fgets(line, 300, fp) != NULL) {
    long numbers[21];
    // explode line by space
    char *token = strtok(line, " ");
    int i = 0;
    while(token != NULL) {
      numbers[i] = atol(token);
      token = strtok(NULL, " ");
      i++;
    }

    // find next number
    int nextNumber = getNextNumber(numbers, 21);
    printf("%d - Next number: %ld\n", lineNumber, nextNumber);
    // add to result
    result += nextNumber;
    lineNumber ++;
  }

  // print result
  printf("Result: %ld\n", result);


  return 0;
}