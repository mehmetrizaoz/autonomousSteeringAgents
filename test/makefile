vpath %.h ../include
CC := g++

CPPFLAGS = -I ../include
objects := test_suites.o
LIBS = -lboost_unit_test_framework

all: test_suites

test_suites: $(objects) ../pvector.o ../point.o
	$(CC) $^ -o $@ $(LIBS)

%.o: %.cpp
	$(CC) $(CPPFLAGS) -c $<

.PHONY: clean help
clean:
	rm test_suites $(objects)