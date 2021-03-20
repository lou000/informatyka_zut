# PS IN1 320 LAB02
# Maciej Lewicki
# lm34410@zut.edu.pl

CC = gcc
OBJFILES = 34410.ps.lab02.second.lib.o 34410.ps.lab02.second.main.o
TARGET = lab02

all: $(TARGET)
$(TARGET): $(OBJFILES)
	$(CC) -o $(TARGET) $(OBJFILES)
clean:
	rm -f $(OBJFILES) $(TARGET) 

