# PS IN1 320 LAB03
# Maciej Lewicki
# lm34410@zut.edu.pl

CC = gcc

TARGET_LIB = lib.a
OBJ_LIB = lib.o

TARGET = lab03
OBJ = main.o

all: $(TARGET) 

$(TARGET): $(OBJ) $(TARGET_LIB)
	$(CC) -o $(TARGET) $(OBJ) -L. $(TARGET_LIB)

$(TARGET_LIB): $(OBJ_LIB)
	ar rcs $(TARGET_LIB) $(OBJ_LIB)

clean:
	rm -f $(OBJ) $(TARGET) $(TARGET_LIB) $(OBJ_LIB)

