lependu:	lependu.c
	g++ -Wall  -o "lependu" "lependu.c" `sdl-config --cflags --libs` -lSDL -lSDL_ttf -lSDL -lSDL_image -lfreetype

clean:
	rm lependu
