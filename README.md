# 공지

#### 필수 공지

- snakeMap은 전체 21, 87로 구성되어 있음. 
- snakeGame이 실행되는 gameScreen가 가로 42칸을 차지함.
- missionScreen과 scoreScreen이 각각 세로 10칸 가로 42칸을 차지함.
- **gameWindow.cpp 위에서 gameMap을 호출하여 currentMap을 가져오는 구조**
- **gameMap은 게임이 플레이되는 맵을 저장하는 currentMap 배열을 가지고 있으며 그 맵을 snake 객체, item 객체, gate 객체가 건드리면서 수정하는 형식**
- 따라서 매 시간 틱마다 gameTimeFlow() 메소드를 통해 시간이 1틱 흘렀다는 것을 전해주면 currnetMap의 부수적인 객체들이 currentMap을 수정하고, 그 수정된 맵을 gameWindow가 최종적으로 받아서 출력하는 구조로 생각중임.



#### 해결된 것들

- 유니코드 문제 해결 - 단순히 맵을 프린트할 때, 가로 공간에 X2를 해줌으로써 문제를 해결함.
- 윈도우 객체를 리턴하는 것이 가능한가? - 굳이 그거를 구현할 필요가 없어보임.  매번 새로 currentMap을 출력하도록 하는게 그다지 시간복잡도가 높지 않아 빠르게 처리 가능함



#### 의문점

- 







| 클래스 : Position |                                                              |
| ----------------- | ------------------------------------------------------------ |
| - int x, int y    | 해당하는 위치의 좌표에 대한 정보                             |
| - type            | 해당하는 위치가 snake의 head인지 아니면 body인지를 3, 4로 저장 |
| + Position()      | 생성자                                                       |
| + getter & setter |                                                              |











| 클래스 gameMap                  |                                                              |
| ------------------------------- | ------------------------------------------------------------ |
| - int map`[4][21][21]`          | 21 * 21로 이루어진 맵을 총 4개 저장                          |
| - const int MAP_WIDTH           | 맵의 가로 길이를 상수로 저장                                 |
| - const int MAP_HEIGHT          | 맵의 세로 길이를 상수로 저장                                 |
| - int mapVariaty                | 맵의 총 개수 저장                                            |
| - int currentMap`[21][21]`      | 현재 게임이 플레이되고 있는 map을 저장하는 배열 변수<br />gameMap 클래스 안에서 생성되는 snake 객체와 gate 객체, <br />그리고 item 객체가 이 배열과 직접 상호작용 하면서 <br />current Map을 바꿀 예정. |
| - snake snakeOnMap              | snake를 관리하고 로직이 담겨있는 객체                        |
| + gameMap()                     | 생성자.<br />기본적으로 setCurrentMap 메소드를 통해 currentMap을<br />0번째 map 으로 저장하고,<br />snakeInitialize 메소드를 통해 currentMap 위에 snake를 그림. |
| + getCurrentMapPosition()       | 주어진 좌표에 내용을 currentMap에서 가져옴.                  |
| + setCurrentMap()               | 인자로 주어지는 Map number 에 따라 currentMap 변수를 map[num]의 내용으로 깊은 복사함. |
| + snakeInitialize()             | snakeOnMap의 snake의 위치가 담겨 있는 정보를 얻어서 <br />currentMap에 snake 머리를 그린 후에 반복문을 통해 <br />body까지 그림 |
| + gameTimeFlow()                | snakeOnMap에 저장된 방향 그대로 snake를 전진시키고<br />그것을 currentMap에 반영함. |
| + snakeChangeDirection(int dir) | snakeOnMap 안에 내부구현 메소드를 호출하여<br />snake 객체의 방향을 바꿈. |





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

