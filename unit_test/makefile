vpath %.cpp ../src
vpath %.h ../include
CC := g++

objects := assert_UT.o
LIBS = -lboost_unit_test_framework

all: test

test: $(objects)
	$(CC) $^ -o $@ $(LIBS)

%.o: %.c
	$(CC) $(CPPFLAGS) -c $<

.PHONY: clean
clean:
	rm test $(objects)
