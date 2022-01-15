CC = g++

#lxrad automatic generated block start, don't edit below!

FLAGS = -D_VERSION_=\"0.0.1\" -Wall -O2 -ggdb `lxrad-config --cxxflags`

LIBS = `lxrad-config --libs` `wx-config  --libs stc`  

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
	rm -f examples/*.asm examples/*.s examples/*.mc8 examples/*.map examples/*.hex
