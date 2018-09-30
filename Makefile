build: src/*.cpp
	g++ -o bin/gameoflife src/*.cpp -lsfml-window -lsfml-system -lsfml-graphics