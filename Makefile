CC = g++

CFLAGS = -c

TARGET_FILE = SolveSquare.exe

TARGET_DIR = ./build/

all: setup

setup: main.o SolveSquare.o Tests.o TrollMode.o UI.o
	$(CC) $(TARGET_DIR)main.o $(TARGET_DIR)SolveSquare.o $(TARGET_DIR)Tests.o $(TARGET_DIR)TrollMode.o $(TARGET_DIR)UI.o -o $(TARGET_FILE)
	mv $(TARGET_FILE) $(TARGET_DIR)

main.o: main.cpp AllSolveSquare.h SolveSquare.h Tests.h TrollMode.h UI.h
	mkdir -p $(TARGET_DIR)
	$(CC) $(CFLAGS) main.cpp
	mv main.o $(TARGET_DIR)

SolveSquare.o: SolveSquare.cpp SolveSquare.h Colors.h
	mkdir -p $(TARGET_DIR)
	$(CC) $(CFLAGS) SolveSquare.cpp
	mv SolveSquare.o $(TARGET_DIR)

Tests.o: Tests.cpp Tests.h SolveSquare.h Colors.h
	mkdir -p $(TARGET_DIR)
	$(CC) $(CFLAGS) Tests.cpp
	mv Tests.o $(TARGET_DIR)

TrollMode.o: TrollMode.cpp TrollMode.h SolveSquare.h Colors.h
	mkdir -p $(TARGET_DIR)
	$(CC) $(CFLAGS) TrollMode.cpp
	mv TrollMode.o $(TARGET_DIR)

UI.o: UI.cpp AllSolveSquare.h SolveSquare.h Tests.h TrollMode.h UI.h Colors.h
	mkdir -p $(TARGET_DIR)
	$(CC) $(CFLAGS) UI.cpp
	mv UI.o $(TARGET_DIR)

run:
	$(TARGET_DIR)$(TARGET_FILE)

clean:
	rm -f $(TARGET_DIR)*.o $(TARGET_DIR)$(TARGET_FILE)

.PHONY: clean all setup