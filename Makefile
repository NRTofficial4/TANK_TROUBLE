do():
	g++ main.cpp -w -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -o main
	./main
	rm -r main