CC = gcc
CFLAGS = -lncursesw
TARGET = calc
SRC = calculator.c

$(TARGET): $(SRC)
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS)

clean:
	rm -f $(TARGET)
