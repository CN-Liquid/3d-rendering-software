all:
	g++ -I src/include -L src/lib -o main main.cpp -m64 -lmingw32 -lSDL2main -lSDL2
