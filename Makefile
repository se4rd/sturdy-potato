CC = g++

CFLAGS = -g

LDFLAGS = -lSDL2 -lSDL2_ttf

SRCS = main.cpp

TARGET = main

all: $(TARGET)

$(TARGET): $(SRCS)
	clear
	$(CC) $(SRCS) $(CFLAGS) $(LDFLAGS) -o $(TARGET)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	gf2 $(TARGET)