do():
	g++ main.cpp -Iinclude -Llib -lSDL2 -lSDL2main -o main.exe
	./main.exe
	rm -r main.exe