
CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -g
LIBS = -lSDL2 -lSDL2_mixer -lGLEW -lGL -lglut 
DEL = rm

all: cryonic_kung_fu

loadshader.o: loadshader.c
	$(CC) -c $(CFLAGS) $< -o $@

libsinternal.o: libsinternal.c
	$(CC) -c $(CFLAGS) $< -o $@

state:o state.c
	$(CC) -c $(FLAGS) $< -o $@

configuration:o configuration.c
	$(CC) -c $(CFLAGS) $< -o $@

ascii_display_dbg.o: ascii_display_dbg.c
	$(CC) -c $(CFLAGS) $< -o $@

sound.o: sound.c
	$(CC) -c $(CFLAGS) $< -o $@

cryonic_kung_fu: loadshader.o libsinternal.o configuration.o state.o ascii_display_dbg.o sound.o
	$(CC) main.c $(CFLAGS) $^ -o $@ $(LIBS)


clean:
	rm *.o main cryonic_kung_fu