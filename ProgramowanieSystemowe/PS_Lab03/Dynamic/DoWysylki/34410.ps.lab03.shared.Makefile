# PS IN1 320 LAB03
# Maciej Lewicki
# lm34410@zut.edu.pl

CC = gcc
LIBS = -ldl -Wl,-rpath,.

TARGET_LIB = libGroups.so
OBJ_LIB = lib.o

TARGET = lab03
OBJ = main.o

all: $(TARGET) 

$(TARGET): $(OBJ) $(TARGET_LIB)
	$(CC) -o $(TARGET) $(OBJ) $(LIBS) -L.$(TARGET_LIB)

$(TARGET_LIB): $(OBJ_LIB)
	$(CC) -shared -fPIC -o $@ $^

$(OBJ_LIB): lib.c
	$(CC) -c -fPIC lib.c
	

clean:
	rm -f $(OBJ) $(TARGET) $(TARGET_LIB) $(OBJ_LIB)
