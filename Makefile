CC = g++

#lxrad automatic generated block start, don't edit below!

FLAGS = -Wall -O2 `lxrad-config --cxxflags`

LIBS = `lxrad-config --libs`  

OBJS = pscdeeds.o scdeeds1.o  

#lxrad automatic generated block end, don't edit above!


all: $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -oscdeeds $(LIBS)

%.o: %.cc
	$(CC) -c $(FLAGS) $< 

run: all
	./scdeeds

install:

clean:
	rm -f scdeeds *.o core
