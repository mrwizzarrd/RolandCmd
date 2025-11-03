#Project Variables

TARGET = RolandCmd
SRC_DIR = src
INC_DIR = include
CC = gcc
CFLAGS = -Iinclude -std=c11 -D_POSIX_C_SOURCE=199309L #-Wall -Wextra

#find all .c files in src/
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:.c=.o)

#rules
all: $(TARGET)

#Links object files
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

#after compilation
clean:
	rm -f $(SRC_DIR)/*.o $(TARGET)

rebuild: clean all

