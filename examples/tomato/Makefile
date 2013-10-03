###################################
# Makefile
# Pomodoro Project
# CS542 - OO - Spring 2013
# Jim Counts
###################################
CC = g++
CFLAGS = -Wall -g 
TI = -I ../../igloo -I pomodoro -I ../../
LI = -Lpomodoro/lib

CHECK = cppcheck -v --inline-suppr --enable=all
STYLE = astyle -YfDHUbps4yj -k3
DIRS = pomodoro/obj pomodoro/lib pomodoro/bin tests/bin
OBJS = pomodoro/obj/Menus.o pomodoro/obj/Timer.o \
       pomodoro/obj/LogManager.o pomodoro/obj/LogListener.o \
       pomodoro/obj/Tomato.o pomodoro/obj/FileListener.o \
       pomodoro/obj/MessageCache.o pomodoro/obj/PomodoroState.o 

LIBS = pomodoro/lib/libtomato.a
TESTS = tests/bin/menu_tests tests/bin/timer_tests \
		tests/bin/logmanager_tests tests/bin/tomato_tests \
		tests/bin/messagecache_tests

PROG = pomodoro/bin/pomodoro

all: $(DIRS) $(PROG) test

clean:
	rm -f $(LIBS) $(TESTS) $(OBJS) $(PROG)

$(PROG): $(LIBS) pomodoro/pomodoro.cpp 
	$(CHECK) pomodoro/pomodoro.cpp
	$(STYLE) pomodoro/pomodoro.cpp
	chmod 666 pomodoro/pomodoro.cpp
	$(CC) $(LI) pomodoro/pomodoro.cpp -ltomato -o pomodoro/bin/pomodoro $(CFLAGS)

test: $(TESTS)
	tests/bin/menu_tests
	tests/bin/timer_tests
	tests/bin/logmanager_tests
	tests/bin/tomato_tests
	tests/bin/messagecache_tests

tests/bin/messagecache_tests: $(LIBS) tests/messagecache_tests.cpp
	$(CHECK) tests/messagecache_tests.cpp
	$(STYLE) tests/messagecache_tests.cpp
	chmod 666 tests/messagecache_tests.cpp
	$(CC) $(TI) $(LI) tests/messagecache_tests.cpp -ltomato -o tests/bin/messagecache_tests $(CFLAGS)

tests/bin/tomato_tests: $(LIBS) tests/tomato_tests.cpp 
	$(CHECK) tests/tomato_tests.cpp
	$(STYLE) tests/tomato_tests.cpp
	chmod 666 tests/tomato_tests.cpp
	$(CC) $(TI) $(LI) tests/tomato_tests.cpp -ltomato -o tests/bin/tomato_tests $(CFLAGS)

tests/bin/logmanager_tests: $(LIBS) tests/logmanager_tests.cpp 
	$(CHECK) tests/logmanager_tests.cpp
	$(STYLE) tests/logmanager_tests.cpp
	chmod 666 tests/logmanager_tests.cpp
	$(CC) $(TI) $(LI) tests/logmanager_tests.cpp -ltomato -o tests/bin/logmanager_tests $(CFLAGS)

tests/bin/timer_tests: $(LIBS) tests/timer_tests.cpp 
	$(CHECK) tests/timer_tests.cpp
	$(STYLE) tests/timer_tests.cpp
	chmod 666 tests/timer_tests.cpp
	$(CC) $(TI) $(LI) tests/timer_tests.cpp -ltomato -o tests/bin/timer_tests $(CFLAGS)

tests/bin/menu_tests: $(LIBS) tests/menu_tests.cpp
	$(CHECK) tests/menu_tests.cpp
	$(STYLE) tests/menu_tests.cpp
	chmod 666 tests/menu_tests.cpp
	$(CC) $(TI) $(LI) tests/menu_tests.cpp -ltomato -o tests/bin/menu_tests $(CFLAGS)

pomodoro/lib/libtomato.a: $(OBJS)
	rm -f pomodoro/lib/libtomato.a
	ar rcs pomodoro/lib/libtomato.a $(OBJS)

pomodoro/obj/PomodoroState.o: pomodoro/PomodoroState.h pomodoro/PomodoroState.cpp
	$(CHECK) pomodoro/PomodoroState.h  pomodoro/PomodoroState.cpp
	$(STYLE) pomodoro/PomodoroState.h  pomodoro/PomodoroState.cpp
	chmod 666 pomodoro/PomodoroState.h  pomodoro/PomodoroState.cpp
	$(CC) -c pomodoro/PomodoroState.cpp -o pomodoro/obj/PomodoroState.o $(CFLAGS)

pomodoro/obj/MessageCache.o: pomodoro/MessageCache.h pomodoro/MessageCache.cpp pomodoro/LogListener.h
	$(CHECK) pomodoro/MessageCache.h pomodoro/MessageCache.cpp
	$(STYLE) pomodoro/MessageCache.h pomodoro/MessageCache.cpp
	chmod 666 pomodoro/MessageCache.h pomodoro/MessageCache.cpp
	$(CC) -c pomodoro/MessageCache.cpp -o pomodoro/obj/MessageCache.o $(CFLAGS)

pomodoro/obj/FileListener.o: pomodoro/FileListener.h pomodoro/FileListener.cpp pomodoro/LogListener.h
	$(CHECK) pomodoro/FileListener.h pomodoro/FileListener.cpp
	$(STYLE) pomodoro/FileListener.h pomodoro/FileListener.cpp
	chmod 666 pomodoro/FileListener.h pomodoro/FileListener.cpp
	$(CC) -c pomodoro/FileListener.cpp -o pomodoro/obj/FileListener.o $(CFLAGS)

pomodoro/obj/Tomato.o: pomodoro/Tomato.h pomodoro/Tomato.cpp 
	$(CHECK) pomodoro/Tomato.h pomodoro/Tomato.cpp
	$(STYLE) pomodoro/Tomato.h pomodoro/Tomato.cpp
	chmod 666 pomodoro/Tomato.h pomodoro/Tomato.cpp
	$(CC) -c pomodoro/Tomato.cpp -o pomodoro/obj/Tomato.o $(CFLAGS)
 
pomodoro/obj/LogListener.o: pomodoro/LogListener.h 
	$(CHECK) pomodoro/LogListener.h 
	$(STYLE) pomodoro/LogListener.h 
	chmod 666 pomodoro/LogListener.h 
	$(CC) -c pomodoro/LogListener.h -o pomodoro/obj/LogListener.o $(CFLAGS)

pomodoro/obj/LogManager.o: pomodoro/LogManager.h pomodoro/LogManager.cpp
	$(CHECK) pomodoro/LogManager.h pomodoro/LogManager.cpp
	$(STYLE) pomodoro/LogManager.h pomodoro/LogManager.cpp
	chmod 666 pomodoro/LogManager.h pomodoro/LogManager.cpp
	$(CC) -c pomodoro/LogManager.cpp -o pomodoro/obj/LogManager.o $(CFLAGS)

pomodoro/obj/Timer.o: pomodoro/Timer.h pomodoro/Timer.cpp
	$(CHECK) pomodoro/Timer.h pomodoro/Timer.cpp
	$(STYLE) pomodoro/Timer.h pomodoro/Timer.cpp
	chmod 666 pomodoro/Timer.h pomodoro/Timer.cpp
	$(CC) -c pomodoro/Timer.cpp -o pomodoro/obj/Timer.o $(CFLAGS)

pomodoro/obj/Menus.o: pomodoro/Menus.h pomodoro/Menus.cpp
	$(CHECK) pomodoro/Menus.h pomodoro/Menus.cpp
	$(STYLE) pomodoro/Menus.h pomodoro/Menus.cpp
	chmod 666 pomodoro/Menus.h pomodoro/Menus.cpp
	$(CC) -c pomodoro/Menus.cpp -o pomodoro/obj/Menus.o $(CFLAGS)

pomodoro/obj:
	mkdir pomodoro/obj

pomodoro/lib:
	mkdir pomodoro/lib

pomodoro/bin:
	mkdir pomodoro/bin

tests/bin: 
	mkdir tests/bin

# DO NOT DELETE