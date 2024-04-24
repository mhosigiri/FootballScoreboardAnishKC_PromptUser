#include <iostream>
#include "Scoreboard.h"
using namespace std;
int main() {
  Scoreboard s1;
  s1.getT1().setName("Dallas Cowboys");
  s1.getT1().setCoachName("Mike McCarthy");
  s1.getT1().setHomeCity("Dallas");
  s1.getT1().setScore(10);
  s1.getT1().setTimeoutCount(3);
  s1.getT2().setName("New York Giants");
  s1.getT2().setCoachName("Mike McCarthy");
  s1.getT2().setHomeCity("New York");
  s1.getT2().setScore(10);
  s1.getT2().setTimeoutCount(3);

  s1.setScoreboard();

  s1.stopClock();
  s1.resetClock();
  s1.setClock(12,0);
  s1.setScoreboard();
  
  
  return 0;
}