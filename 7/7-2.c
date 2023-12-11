#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Enum of cards
enum Card { 
  J = 1, 
  TWO, 
  THREE, 
  FOUR, 
  FIVE, 
  SIX, 
  SEVEN, 
  EIGHT, 
  NINE, 
  T, 
  Q, 
  K, 
  A 
};

enum Card charToCard(char input) {
  switch(input) {
    case '2': return TWO;
    case '3': return THREE;
    case '4': return FOUR;
    case '5': return FIVE;
    case '6': return SIX;
    case '7': return SEVEN;
    case '8': return EIGHT;
    case '9': return NINE;
    case 'T': return T;
    case 'J': return J;
    case 'Q': return Q;
    case 'K': return K;
    case 'A': return A;
  }
}

struct Play {
  enum Card hand[5];
  int bid;
};

int handIsFiveOfKind(enum Card hand[]) {
  for(int i=0; i<5; i++) { if(hand[i] != hand[0]) return 0; }
  return 1;
}

void printHand(enum Card hand[]) {
  // Translate hand to letters
  char handText[6];
  for(int i=0; i<5; i++) {
    switch(hand[i]) {
      case TWO: handText[i] = '2'; break;
      case THREE: handText[i] = '3'; break;
      case FOUR: handText[i] = '4'; break;
      case FIVE: handText[i] = '5'; break;
      case SIX: handText[i] = '6'; break;
      case SEVEN: handText[i] = '7'; break;
      case EIGHT: handText[i] = '8'; break;
      case NINE: handText[i] = '9'; break;
      case T: handText[i] = 'T'; break;
      case J: handText[i] = 'J'; break;
      case Q: handText[i] = 'Q'; break;
      case K: handText[i] = 'K'; break;
      case A: handText[i] = 'A'; break;
    }
  }

  // Print hand
  printf("%s\n", handText);

}

int handIsFourOfKind(enum Card hand[]) {

  // printHand(hand);

  // Check if any of the 5 cards repeats 4 times
  for(int i=0; i<5; i++) {
    int count = 0;
    for(int j=0; j<5; j++) {
      if(hand[i] == hand[j]) {
        // Print the match
        // printf("%d == %d\n", hand[i], hand[j]);
        count++;
      }
    }
    if(count == 4) return 1;
  }
  return 0;
}

int handIsFullHouse(enum Card hand[]) {
  // Check if any of the 5 cards repeats 3 times
  for(int i=0; i<5; i++) {
    int count = 0;
    for(int j=0; j<5; j++) {
      if(hand[i] == hand[j]) count++;
    }
    if(count == 3) {
      // Check if any of the OTHER cards repeats 2 times
      for(int i2=0; i2<5; i2++) {
        int count = 0;
        for(int j2=0; j2<5; j2++) {
          if(hand[i2] == hand[j2]) count++;
        }
        if(count == 2) return 1;
      }
    }
  }

  return 0;
}

int handIsThreeOfKind(enum Card hand[]) {
  // Check if any of the 5 cards repeats 3 times
  for(int i=0; i<5; i++) {
    int count = 0;
    for(int j=0; j<5; j++) {
      if(hand[i] == hand[j]) count++;
    }
    if(count == 3) {
      // Check if any of the OTHER cards repeats 2 times
      for(int i2=0; i2<5; i2++) {
        int count = 0;
        for(int j2=0; j2<5; j2++) {
          if(hand[i2] == hand[j2]) count++;
        }
        if(count == 1) return 1;
      }
    }
  }

  return 0;
}

int handIsTwoPair(enum Card hand[]) {
  enum Card foundPair;
  // Check if any of the 5 cards repeats 2 times
  for(int i=0; i<5; i++) {
    int count = 0;
    for(int j=0; j<5; j++) {
      if(hand[i] == hand[j]) count++;
    }
    if(count == 2) {
      foundPair = hand[i];
      // Check if any of the OTHER cards repeats 2 times
      for(int i2=0; i2<5; i2++) {
        int count = 0;
        for(int j2=0; j2<5; j2++) {
          if(hand[i2] == hand[j2]) count++;
        }
        if(count == 2 && hand[i2] != foundPair) return 1;
      }
    }
  }

  return 0;
}

int handIsOnePair(enum Card hand[]) {
  // Check if any of the 5 cards repeats 2 times
  for(int i=0; i<5; i++) {
    int count = 0;
    for(int j=0; j<5; j++) {
      if(hand[i] == hand[j]) count++;
    }
    if(count == 2) return 1;
  }

  return 0;
}

int handIsHighCard(enum Card hand[]) {
  // Check if any of the 5 cards repeats
  for(int i=0; i<5; i++) {
    int count = 0;
    for(int j=0; j<5; j++) {
      if(hand[i] == hand[j]) count++;
    }
    if(count > 1) return 0;
  }
}

int getStandardHandValue(enum Card hand[]) {
  if(handIsFiveOfKind(hand)) return 70000;
  if(handIsFourOfKind(hand)) return 60000;
  if(handIsFullHouse(hand)) return 50000;
  if(handIsThreeOfKind(hand)) return 40000;
  if(handIsTwoPair(hand)) return 30000;
  if(handIsOnePair(hand)) return 20000;
  if(handIsHighCard(hand)) return 10000;
  return 0;
}

int getHandValue(enum Card hand[]) {

  // Check if hand contains a J
  int numberOfJs = 0;
  for(int i=0; i<5; i++) {
    if(hand[i] == J) numberOfJs ++;
  }

  if(numberOfJs == 0) {
    return getStandardHandValue(hand);
  }

  int bestValue = 0;
  if(numberOfJs == 1) {
    for(int i=1; i<=A; i++) {
      enum Card newHand[5];
      for(int j=0; j<5; j++) {
        if(hand[j] == J) {
          newHand[j] = i;
        } else {
          newHand[j] = hand[j];
        }
      }
      int newValue = getStandardHandValue(newHand);
      if(newValue > bestValue) bestValue = newValue;
    }
  }

  if(numberOfJs == 2) {
    for(int i=1; i<=A; i++) {
      for(int i2=1; i2<=A; i2++) {
        enum Card newHand[5];
        for(int j=0; j<5; j++) {
          if(hand[j] == J) {
            newHand[j] = i;
          } else {
            newHand[j] = hand[j];
          }
        }
        int newValue = getStandardHandValue(newHand);
        if(newValue > bestValue) bestValue = newValue;
      }
    }
  }

  if(numberOfJs == 3) {
    for(int i=1; i<=A; i++) {
      for(int i2=1; i2<=A; i2++) {
        for(int i3=1; i3<=A; i3++) {
          enum Card newHand[5];
          for(int j=0; j<5; j++) {
            if(hand[j] == J) {
              newHand[j] = i;
            } else {
              newHand[j] = hand[j];
            }
          }
          int newValue = getStandardHandValue(newHand);
          if(newValue > bestValue) bestValue = newValue;
        }
      }
    }
  }

  if(numberOfJs == 4) {
    for(int i=1; i<=A; i++) {
      for(int i2=1; i2<=A; i2++) {
        for(int i3=1; i3<=A; i3++) {
          for(int i4=1; i4<=A; i4++) {
            enum Card newHand[5];
            for(int j=0; j<5; j++) {
              if(hand[j] == J) {
                newHand[j] = i;
              } else {
                newHand[j] = hand[j];
              }
            }
            int newValue = getStandardHandValue(newHand);
            if(newValue > bestValue) bestValue = newValue;
          }
        }
      }
    }
  }

  if(numberOfJs == 5) {
    for(int i=1; i<=A; i++) {
      for(int i2=1; i2<=A; i2++) {
        for(int i3=1; i3<=A; i3++) {
          for(int i4=1; i4<=A; i4++) {
            for(int i5=1; i5<=A; i5++) {
              enum Card newHand[5];
              for(int j=0; j<5; j++) {
                if(hand[j] == J) {
                  newHand[j] = i;
                } else {
                  newHand[j] = hand[j];
                }
              }
              int newValue = getStandardHandValue(newHand);
              if(newValue > bestValue) bestValue = newValue;
            }
          }
        }
      }
    }
  }

  return bestValue;

}

int firstHandWins(enum Card firstHand[], enum Card secondHand[]) {
  // Get hand values
  int firstHandValue = getHandValue(firstHand);
  int secondHandValue = getHandValue(secondHand);

  // Compare hand values
  if(firstHandValue > secondHandValue) return 1;
  if(firstHandValue < secondHandValue) return 0;

  // If hand values are equal, compare cards
  for(int i=0; i<5; i++) {
    if(firstHand[i] > secondHand[i]) return 1;
    if(firstHand[i] < secondHand[i]) return 0;
  }
  return 0;
}

int insertPlay(struct Play *plays, struct Play play, int index) {
  for(int i=998; i>= index; i--) {
    plays[i + 1] = plays[i];
  }
  plays[index] = play;
} 

int main() {
  FILE *fp = fopen("7.txt", "r");
  char line[20];
  struct Play *plays = malloc(1000 * sizeof(struct Play));

  int index = 0;
  while(fgets(line, 20, fp) != NULL) {
    // Extract line
    char handText[6] = { line[0], line[1], line[2], line[3], line[4], '\0' };
    char bidText[5] = { line[6], line[7], line[8], line[9], '\0' };
    
    // Parse line
    int bid = atoi(bidText);
    enum Card hand[5];
    for(int i=0; i<5; i++) { hand[i] = charToCard(handText[i]); }
    struct Play play;
    for(int i=0; i<5; i++) { play.hand[i] = hand[i]; }
    play.bid = bid;

    // Print before and after
    /*
      printf("Line: %s", line);
      printf("%d: ", index);
      for(int i=0; i<5; i++) { printf("%d ", play.hand[i]); }
      printf(" - %d\n", play.bid);
      printf("\n");
    */

    if(index == 0) {
      plays[0] = play;
    } else {
      int done = 0;
      for(int i = 0; i < index; i++) {
        if(firstHandWins(play.hand, plays[i].hand)) {
          insertPlay(plays, play, i);
          done = 1;
          break;
        }
      }
      if(!done) {
        plays[index] = play;
      }
    }

    index ++;
  }

  // Print plays and determine result
  long long result = 0L;
  for(int i = 0; i < 1000; i++) {
    result += plays[i].bid * (1000 - i);
    printf("%d: ", i);
    for(int j=0; j<5; j++) { printf("%d ", plays[i].hand[j]); }
    printf(" - handv: %d, bid: %d, result: %d\n", getHandValue(plays[i].hand), plays[i].bid, plays[i].bid * (1000 - i));
  }

  // Print the result
  printf("Result: %lld\n", result);


}