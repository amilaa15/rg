CC = g++
CFLAGS = -I/usr/include/GL
LIBS = -lGL -lGLU -lglut
APPS = zavrsniprojekt

all: $(APPS)

%: %.cpp
	$(CC) -o $@ $(CFLAGS) $< $(LIBS)

.PHONY: clean
clean:
	rm -rf *.o $(APPS)
