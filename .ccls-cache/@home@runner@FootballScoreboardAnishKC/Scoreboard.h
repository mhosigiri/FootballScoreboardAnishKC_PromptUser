#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <atomic>
#include <mutex>
using namespace std;

//This is Scoreboard.h file complementing the Football Scoreboard

class Team
{
private:
  string name;
  string coach_name;
  string home_city;
  bool home_status;
  int score;
  int timeout_count;
public:
  Team()
{
  name = "default_name"; 
  coach_name = "deafault_coach_name"; 
  home_city = "defaultHomeCity";
  home_status = true;
  score = 0; 
  timeout_count = 0;
}
  void setName(string n) {name = n;}
  void setCoachName(string cn) {coach_name = cn;}
  void setHomeCity(string hc) {home_city = hc;}
  void setScore(int s) {score = s;}
  void setTimeoutCount(int tc) {timeout_count = tc;}
  string getName() const {return name;}
  string getCoachName() const {return coach_name;}
  string getHomeCity() const {return home_city;}
  bool getHomeStatus() const {return home_status;}
  int getScore() const {return score;}
  int getTimeoutCount() const {return timeout_count;}
};

class Scoreboard
{
private:
  int quarter;
  int down;
  int toGo;
  int min;
  int sec;
  Team T1;
  Team T2;
  atomic<bool> active;
  thread clockThread;
  mutex lock;
  void runClock()
{
  while(active.load())
    {
      this_thread::sleep_for(chrono::seconds(1));
      lock.lock();
      sec++;
      if(sec>= 60) {
        sec = 0;
        min++;
      } lock.unlock();
    }
}
public:
  Scoreboard()
{
  quarter = 1;
  down = 1;
  toGo = 10;
  min = 0;
  sec = 0;
  active = false;
  T1 = Team();
  T2 = Team();
}
void startClock()
{
  active.store(true);
  clockThread = thread(&Scoreboard::runClock, this);
}
void stopClock()
{
  active.store(false);
  if(clockThread.joinable())
  {
    clockThread.join();
  }
}
void resetClock()
{
  lock.lock();
  min = 0;
  sec = 0;
  lock.unlock();
}
void setClock(int m, int s){
  lock.lock();
  min = m;
  sec = s;
  lock.unlock();
}
  void setQuarter(int q) {quarter = q;}
  void setDown(int d) {down = d;}
  void settoGo(int tg) {toGo = tg;}
  void setMin(int m) {min = m;}
  void setSec(int se) {sec = se;}
  int getQuarter() const {return quarter;}
  int getDown() const {return down;}
  int gettoGo() const {return toGo;}
  int getMin() const {return min;}
  int getSec() const {return sec;}
  Team& getT1() {return T1;}
  Team& getT2() {return T2;}
  void setScoreboard() {
    cout << T1.getName() << "\t" << min << ":" << sec << "\t" << T2.getName() << endl;
    cout << "\t" << T1.getScore() << "\t\t\t\t\t" << T2.getScore() << endl;
    cout << T1.getCoachName() << "\t\t" << T2.getCoachName() << endl;
    cout << T1.getHomeCity() << "\t\t\t\t" << T2.getHomeCity() << endl;
    cout << down << "  DOWN" << "\t\t\t\t" << "TO GO  " << toGo << endl;
  }
};
