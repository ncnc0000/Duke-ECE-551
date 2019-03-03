SOURCES=command.cpp command.h shell_operating.h shell_operating.cpp main.cpp
OBJS=$(patsubst %.cpp, %.o, $(SOURCES))
CPPFLAGS=-ggdb3 -std=gnu++98 -Wall -Werror -pedantic

myShell: $(OBJS)
	g++ $(CPPFLAGS) -o myShell $(SOURCES)

clean:
	rm compress *~ *.o
