#include "kbtick.h"

using namespace std;

// clock 함수는 프로세스 or 스레드의 상태가 Block or Ready 상태로 변경되어 있는 시간은 측정해주지 않는다.
// 그래서 chrono 라이브러리에서 제공하는 함수를 통해 시간을 ms 단위로 측정한다.
// 1초 이상 실행되었다면 입력받은 값을 반환하고 1초 미만으로 실행되었다면 나머지 시간은 TICK을 채우기 위해 usleep 함수를 호출하여 시간을 채운다.
// 반드시 game을 빌드하여 실행할 때는 디버깅용 출력 구문을 전부 주석 처리해야한다.
int custom_getch_tick()
{
   chrono::system_clock::time_point start = chrono::system_clock::now();
   int ch = getch();
   chrono::duration<double> sec = chrono::system_clock::now() - start;
   chrono::milliseconds mic = chrono::duration_cast<chrono::milliseconds>(sec);

   long duration = mic.count();
   string p1 = "getch execution time : " + to_string(duration) + "\n";
   if(duration >= TIME_TICK)
   {
     return ch;
   }
   else
   {
     string p2 = "usleep : " + to_string(TIME_TICK - duration) + "\n";
     usleep((TIME_TICK - duration)*1000);
     return ch;
   }
}
