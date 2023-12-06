#include <stdio.h>

int distance(int duration_hold, int duration_track) {
  return duration_hold * (duration_track - duration_hold);
}

int main() {
  int result = 0;
  int durations[4] = { 53, 91, 67, 68 };
  int records[4] = { 250, 1330, 1080, 1025 };
  for(int i=0; i<4; i++) {
    int duration = durations[i];
    int waysToBeatTime = 0;
    for(int hold=0; hold<duration; hold++) {
      int testResult = distance(hold, duration);
      if(testResult > records[i]) {
        waysToBeatTime ++;
      }
    }
    if(result == 0) result = waysToBeatTime;
    else result *= waysToBeatTime;
  }
  printf("Result: %d\n", result);
}