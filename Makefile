CC = g++

game.o : Position.cpp gameMap.cpp gameScoreMission.cpp kbtick.cpp snake.cpp gameWindow.cpp item.cpp gate.cpp
   $(CC) -o game.o Position.cpp gameMap.cpp gameScoreMission.cpp kbtick.cpp snake.cpp gameWindow.cpp item.cpp gate.cpp -lncursesw