vpath %.h ../include
CC := g++

CPPFLAGS = -I ../include
objects := test_suite_pvector.o
LIBS = -lboost_unit_test_framework

all: test_suite_pvector

test_suite_pvector: $(objects) ../pvector.o ../point.o
	$(CC) $^ -o $@ $(LIBS)

%.o: %.cpp
	$(CC) $(CPPFLAGS) -c $<

.PHONY: clean help
clean:
	rm test_suite_pvector $(objects)