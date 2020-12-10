myExec: plannerTester.o bigEnvironment.o pathPlanner.o display.o
		gcc -o myExec1 plannerTester.o pathPlanner.o display.o -lX11
		gcc -o myExec2 bigEnvironment.o pathPlanner.o display.o -lX11
		
plannerTester.o: obstacles.h plannerTester.c display.h
		gcc -c plannerTester.c

bigEnvironment.o: obstacles.h bigEnvironment.c display.h
		gcc -c bigEnvironment.c

pathPlanner.o: obstacles.h pathPlanner.c display.h
		gcc -c pathPlanner.c

display.o: display.h display.c
		gcc -c display.c

clean:
		rm -f *.o
