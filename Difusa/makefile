CC = g++
CFLAGS = -I.

MAIN = test

NOMBRE= dif

CLS= difusa.o Clasificacion.o Pertenencia.o

OBJ = $(MAIN).o $(CLS)

_: main

#-------------------------------------------------

COFLAGS = -I.

%.o: %.cpp $(DEPS)
	$(CC) -c -o $(DEPS) $@ $< $(COFLAGS)

#--------------------------------------------------

main: $(OBJ) 
	$(CC) -o $(NOMBRE) $(MAIN).o $(CFLAGS)


.PHONY: clean

clean: 
	rm $(NOMBRE) \
	$(OBJ)


OBJT = talker.o formato.o
OBJC = chatter.o formato.o


talker:  talker.o formato.o 
	$(CC) -o talker talker.o formato.o $(CFLAGS)

chatter: chatter.o formato.o 
	$(CC) -o chatter chatter.o formato.o $(CFLAGS)

