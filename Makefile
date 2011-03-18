CC = /usr/bin/g++
OBJS = rng.o random.o samplestat.o
SRCS = rng.cc random.cc samplestat.cc
HDRS = rng.h random.h samplestat.cc
CFLAGS = -Wall -g
EXECS = windowTest randomTest transientFaker
LFLAGS = -lm

# use a hash mark to start a comment line
#

all: $(EXECS)

windowTest: $(OBJS) windowTest.cc
	$(CC) $(CFLAGS) windowTest.cc $(OBJS) -o windowTest $(LFLAGS)

randomTest: $(OBJS) randomTest.cc
	$(CC) $(CFLAGS) randomTest.cc $(OBJS) -o randomTest $(LFLAGS)

transientFaker: $(OBJS) transientFaker.cc
	$(CC) $(CFLAGS) transientFaker.cc random.o rng.o samplestat.o -o transientFaker $(LFLAGS)

rng.o: rng.cc rng.h

random.o: random.cc random.h
 
samplestat.o: samplestat.h samplestat.cc

clean:
	/bin/rm -f $(OBJS) $(EXECS) *~ core*
