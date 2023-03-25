all: linux

linux:
	gcc -Wall -pedantic -O2 sdl_fire_doom_demo.c -o sdl_fire_doom_demo `sdl-config --cflags --libs`
	strip -s sdl_fire_doom_demo

windows:
	gcc -Wall -pedantic -O2 sdl_fire_doom_demo.c -o sdl_fire_doom_demo.exe `sdl-config --cflags --libs`
	strip -s sdl_fire_doom_demo.exe

clean:
	rm -f sdl_fire_doom_demo
	rm -f sdl_fire_doom_demo.exe
