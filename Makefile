CC = g++

# CFLAGS = -Wall

LDFLAGS = -lSDL2 -lSDL2_ttf

SRCS = main.cpp

TARGET = main

all: $(TARGET)

$(TARGET): $(SRCS)
	clear
	$(CC) $(SRCS) $(LDFLAGS) -o $(TARGET)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)