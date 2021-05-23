#include "kbtick.h"
#include <string>

using namespace std;

int main(int argc, char * argv[])
{
  setlocale(LC_ALL,"");
  initscr(); // ncurses init
  halfdelay(10); // delay set 1 second
  string p1 = "result : ";
  string p2 = "total time : ";

  chrono::system_clock::time_point start = chrono::system_clock::now(); // time check start
  int ch = custom_getch_tick(); // get character in 1 second
  p1 += to_string(ch) + "\n";
  chrono::duration<double> sec = chrono::system_clock::now() - start; // time check end
  chrono::milliseconds mic = chrono::duration_cast<chrono::milliseconds>(sec);
  long duration = mic.count();
  p2 += to_string(duration) + "\n";
  printw(p1.c_str());
  printw(p2.c_str());
  refresh();
  getch();
  endwin();
  return 0;
}
