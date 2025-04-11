do():
	g++ main.cpp -w -ISDL/include/SDL2 -LSDL/lib -lSDL2 -lSDL2main -lSDL2_mixer -lSDL2_ttf -lSDL2_image -o tank_trouble.exe
	./tank_trouble.exe
	# rm -r tank_trouble.exe