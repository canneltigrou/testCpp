
CXXFLAGS =	-O2 -g -Wall -std=c++0x -fmessage-length=0


OBJS =		Main.o AbstractLogObject.o Robot.o Motor.o Leg.o

LIBS =

TARGET =	simulator

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
