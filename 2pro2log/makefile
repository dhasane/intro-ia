CC = g++
CFLAGS = -I.

NOM = 2p2l.exe
OBJ = 2pro2log.o


_: compile run

%.o: %.cpp 
	$(CC) -c -o $(DEPS) $@ $< $(CFLAGS)

compile: $(OBJ)
	$(CC) -o $(NOM) $(OBJ) $(CFLAGS)

#de esta forma no dejo todo lleno de archivos innecesarios
run:
	./$(NOM)
	rm $(OBJ)
	rm $(NOM)



