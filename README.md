### 개발 노트

#### 오브젝트 별 대응값

- Immune Wall : 2
- Wall : 1
- Snake : 3
- Head : 4

#### 타임 틱

 - 1초
 - 0.n초는 디버깅하기 힘들고 컨트롤하기 힘듬.

#### getch 함수

 - W,A,S,D 같은 아스키코드에 포함된 문자들은 잘 받아들임.
 - 근데 방향키 같은 문자들은 [ESCAPE] 문자로 인식함.

#### ncureses 라이브러리 설치

- sudo apt-get update
- sudo apt-get install libncurses5-dev libncursesw5-dev

#### 의문점

- 프로그램 구현에서 반드시 유니코드를 고려해야하는가? (확인 요망, 실제 프로그래밍 시 제대로 동작 안 함.)
- ...

#### To-Do List

- 기말 프로젝트 설명 자료에서 나온 예제들 따라해보기.(O)
- 2단계 작업 진행하기.(진행중)
- GameWindow 클래스를 어떻게 구현할지 생각해보기.
- kbtick과 Moon-branch의 파일을 합칠 때 발생하는 문제점을 어떻게 해결할지 토의해보기.
