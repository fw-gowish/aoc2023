#include <stdio.h>

long long distance(long long duration_hold, long long duration_track) {
  return duration_hold * (duration_track - duration_hold);
}

int main() {
  long long duration = 53916768L;
  long long record = 250133010801025L;
  long long waysToBeatTime = 0;
  for(long long hold=0; hold<duration; hold++) {
    long long testResult = distance(hold, duration);
    
    if(testResult > record) {
      waysToBeatTime ++;
    }
  }
  printf("Result: %d\n", waysToBeatTime);
}