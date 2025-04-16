CC = g++

CFLAGS = -Iinclude -g

LDFLAGS = -lSDL2 -lSDL2_ttf

SRCS = src/*

TARGET = main

all: $(TARGET)

$(TARGET): $(SRCS)
	clear
	$(CC) $(SRCS) $(CFLAGS) $(LDFLAGS) -o $(TARGET)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

gf2: $(TARGET)
	gf2 $(TARGET)