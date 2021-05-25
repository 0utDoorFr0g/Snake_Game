# 공지

#### 협의 사항
- terminal 크기는 (가로, 세로) 크기는 (87, 21)이다.
- gameScreen의 (가로, 세로) 크기는 (42,21)이다.
- missionScreen, scoreScreen의 (가로, 세로) 크기는 (42, 10) 이다.
- **gameWindow.cpp 파일에서 Snake_game을 진행 내용을 표시하는 Window를 생성하고 키보드 입력을 받아서 gameMap 객체에서 currentMap 데이터를 받아서 게임의 진행 상황을 보여준다.**
- **gameMap 객체는 현재 플레이에 사용되는 맵을 저장하는 currentMap 배열을 가지고 있고 멤버 변수인 snake, item, gate 객체가 gameMap 객체와 상호작용하며 currentMap 배열을 수정한다.**
- **gameWindow.cpp 파일에서 gameMap 객체의 gameTimeFlow 함수를 반복적으로 호출하여 1틱씩 시간이 흐르는 현상을 구현한다. **

#### 상수별 의미
- **의미 : 맵에서 사용하는 상수, 출력에서 사용하는 상수**
- Void : 0, 0x20
- Wall : 1, 0x25A1
- Immunity Wall : 2, 0x25A2
- Snake Head : 3, 0x25CC
- Snake Body : 4, 0x25CB
- Poision Item : 5, 0x2B14
- Grow Item : 6, 0x2B15

#### 해결된 문제

- 유니코드 문제 해결 - 단순히 맵을 프린트할 때, 가로 공간에 X2를 해줌으로써 문제를 해결했다.
- 윈도우 객체를 리턴하는 것이 가능할까? - 굳이 구현할 필요가 없다고 생각한다.  반복하여 currentMap을 출력하는 코드가 시간복잡도가 그리 높지 않으므로 빠른 처리가 가능하다.

#### 의문점
.
#### 문서

.

| 클래스 : gameMap | 게임에서 사용되는 데이터를 관리하는 클래스  |
|-|-|
|- int map[4][21][21] |4개의 map의 데이터를 저장한 배열|
|- const int MAP_WIDTH|맵의 폭을 표현한 상수|
|- const int MAP_HEIGHT|맵의 높이를 표현한 상수|
|-  int mapVariaty|맵의 개수를 표현한 변수|
|-  int currentMap[21][21] | 현재 게임에서 사용하는 맵의 데이터를 저장한 배열|
|-  snake snakeOnMap | Snake 객체|
| - item itemOnMap[3] |item 객체 배열|
| +   gameMap() | gameMap 클래스의 생성자 |
| +  int getCurrentMapPosition(int x, int y)| 특정 좌표의 현재 게임에서 사용하는 맵 데이터를 반환하는 함수 |
| + void setCurrentMap(int num)| 특정 map의 데이터를 currentMap으로 복사하는 함수|
| +  void snakeInitialize() | Snake 객체를 currentMap에 표시하는 함수 |
| +  void itemInitialize() | item 객체를 초기화하고 currentMap에 표시하는 함수 |
| + void gameTimeFlow() | item 객체가 Map에 있던 시간을 증가시키고 5 tick이 지난 item을 삭제하고 currentMap에 새로 item을 생성하고 Snake를 전진시키고 이를 CurrentMap에 적용시키는 함수 |
| +  void snakeChangeDirection(int dir) | snake의 진행 방향을 바꾸는 함수 |

.

| 클래스 : item | Poision Item, Grow Item의 위치, 속성, 맵에 출현한 시간을 관리하는 클래스  |
|-|-|
| - Position itemPosition | 아이템의 위치, 종류를 표현한 변수 |
| - int age | 아이템이 맵에 출현한 후, 지난 시간을 표현한 변수 |
| + getter & setter | age, itemPosition 멤버 변수 접근자 |
| + item(int y, int x, int type) | 주어진진 값으로 멤버 변수를 초기화하는 생성자 |
| +  item() | 멤버 변수를 0으로 초기화하는 생성자 |

.

| kbtick 파일 | 1초동안 입력을 받는 함수를 구현한 파일 |
| - | - |
| + int custom_getch_tick() | 1초동안 입력을 한 번 받고 1초 안에 입력이 왔다면 남은 시간동안 sleep하고 1초 이상 입력이 없다면 오류를 표현한 값을 반환한 함수 |

.

| 클래스 : Position |                                                              |
| ----------------- | ------------------------------------------------------------ |
| - int x, int y    | 해당하는 위치의 좌표에 대한 정보                             |
| - type            | 해당하는 위치가 snake의 head인지 아니면 body인지를 3, 4로 저장 |
| + Position()      | 생성자                                                       |
| + getter & setter | x,y,type 멤버 변수 접근자                                                             |


.

| class Snake                        |                                                              |
| ---------------------------------- | ------------------------------------------------------------ |
| - vector`<Position>` snakePosition | head 부터 body 까지 snake의 정보를 담고 있는<br />Position 객체들을 저장하는 vector 컨테이너 |
| - int snakeLength                  | 뱀 길이                                                      |
| - int direction                    | 뱀의 방향, 1은 동쪽, 2는 서쪽, 3은 남쪽, 4는 북쪽으로<br />그 안에 헤더파일 주석문에 적힌 내용은 잘못된... 거... |
| + snake                            | 생성자                                                       |
| + changeDirection                  | 방향을 바꿈                                                  |
| + snakeGo                          | 주어진 방향으로 snake 구성 Position의 위치를 전부 바꿈       |
| + snakeGrow()                      | 아직 미구현                                                  |
| + getSnakePosX / PosY              | 특정 인덱스의 snake 위치를 리턴.                             |
| + getSnakeLength()                 | snake 길이 리턴                                              |
| + getDirection                     | snake의 방향을 리턴.                                         |
