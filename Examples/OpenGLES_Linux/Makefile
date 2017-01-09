all:
	$(CC) *.c -lm `sdl2-config --cflags` `sdl2-config --libs` -lEGL -lGLESv1_CM -o gles_linux
clean:
	-rm -f gles_linux
	-rm -f *.o
