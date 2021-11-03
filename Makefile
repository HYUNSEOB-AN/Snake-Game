CC = g++
CCFLAGS = -g

Main : Snake.o Main.o CreateTerm.o
		$(CC) $(CCFLAGS) -o Main Main.o CreateTerm.o Snake.o -lncursesw
%.o : %.cpp %.h
		$(CC) $(CCFLAGS) -c $< -lncursesw
%.o : %.cpp
		$(CC) $(CCFLAGS) -c $< -lncursesw
% : %.cpp
		$(CC) $(CCFLAGS) -o $@ $< -lncursesw
clean :
		rm *.o
