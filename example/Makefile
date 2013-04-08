###################################
# Makefile
###################################
CC = g++
INCLUDE = -I ../igloo -I ../approvals
CFLAGS = -Wall 

all: runtest 

runtest: sampletest
	./bin/sampletest

sampletest: sampletest.cpp
	$(CC) $(INCLUDE) sampletest.cpp -o ./bin/sampletest $(CFLAGS)

clean: 
	rm -f bin/sampletest