CC=g++
CFLAGS =-g -c -Wall
LDFLAGS=
SOURCES=src/main/c++/main.cpp src/main/c++/neuro.cpp src/main/c++/layer.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=neuro.exe

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(EXECUTABLE)
	rm $(OBJECTS)
