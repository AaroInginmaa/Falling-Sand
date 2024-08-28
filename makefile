CC = gcc
CFLAGS = 
ODIR = bin
SDIR = src
OBJS = main.o
INC = -I./include
LDIR = -L./lib
LINKS = -lSDL2main -lSDL2

all: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(ODIR)/fallingsand.exe $(INC) $(LDIR) $(LINKS)

main.o: $(SDIR)/main.c
	$(CC) $(CFLAGS) -c $(SDIR)/main.c $(INC) $(LDIR) $(LINKS)

clean:
	rm *.o
	rm bin/*.exe
