CC = g++

CFLAGS = -c

TARGET = SolveSquare.exe

all: setup

setup: main.o SolveSquare.o Tests.o TrollMode.o UI.o
	$(CC) main.o SolveSquare.o Tests.o TrollMode.o UI.o -o $(TARGET)

main.o: main.cpp AllSolveSquare.h SolveSquare.h Tests.h TrollMode.h UI.h
	$(CC) $(CFLAGS) main.cpp

SolveSquare.o: SolveSquare.cpp SolveSquare.h Colors.h
	$(CC) $(CFLAGS) SolveSquare.cpp

Tests.o: Tests.cpp Tests.h SolveSquare.h Colors.h
	$(CC) $(CFLAGS) Tests.cpp

Troll.o: TrollMode.cpp TrollMode.h SolveSquare.h Colors.h
	$(CC) $(CFLAGS) TrollMode.cpp

UI.o: UI.cpp AllSolveSquare.h SolveSquare.h Tests.h TrollMode.h UI.h Colors.h
	$(CC) $(CFLAGS) UI.cpp

run:
	$(TARGET)

clean:
	rm -f *.o $(TARGET)

.PHONY: clean all setup