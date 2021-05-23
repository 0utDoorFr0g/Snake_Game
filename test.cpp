#include <iostream>
#include "kbhit.h"
#include <ncurses.h>

using namespace std;

int main(int argc, char *argv[])
{
  halfdelay(100);
  int ch = 0;
  while(ch != KB_X)
  {
    ch = kbhit();
    cout << "get : " << ch << endl;
  }
  return 0;
}
