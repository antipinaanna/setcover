all: main.o 
	g++ -o SC main.o 
main.o: main.cpp 
	g++ -c -g main.cpp

clean: cleanobj cleanmain 

cleanobj:
	rm -f *.o

cleanmain:
	rm SC

.PHONY: clean cleanobj cleanmain