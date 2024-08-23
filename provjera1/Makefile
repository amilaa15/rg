CC = g++
CFLAGS = -I/usr/include/GL
LIBS = -lGL -lGLU -lglut
APPS = test

all: $(APPS)

%: %.cpp
	$(CC) -o $@ $(CFLAGS) $< $(LIBS)

.PHONY: clean
clean:
	rm -rf *.o $(APPS)
