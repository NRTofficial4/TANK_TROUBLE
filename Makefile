do():
	g++ main.cpp -w -ISDL/include/SDL2 -LSDL/lib -lSDL2 -lSDL2main -lSDL2_mixer -lSDL2_ttf -lSDL2_image -o main.exe
	./main.exe
	rm -r main.exe