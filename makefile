vpath %.cpp src
vpath %.h include
CC := g++

CPPFLAGS = -I include -MD
objects := pvector.o graphics.o agent.o flowField.o main.o \
           point.o path.o color.o steeringBehavior.o random.o \
		   obstacle.o scenario.o mouseFollower.o prison.o \
		   windy.o wander.o pursuit.o flee.o evade.o flock.o \
           pathFollower.o obstacleAvoidance.o entity.o \
		   leaderFollower.o DNA.o rocket.o
LIBS = -lglut -lGLU -lGL

all: exec

%.o: %.cpp
	$(CC) $(CPPFLAGS) -c $<

exec: $(objects)
	$(CC) $^ -o $@ $(LIBS)

.PHONY: clean help
clean:
	rm exec 
	rm *.o
	rm *.d

help:
	@echo "make"
	@echo "make clean"

-include $(objects:.o=.d)