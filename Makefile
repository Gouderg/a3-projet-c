CC = gcc
#CC = x86_64-w64-mingw32-gcc
CFLAGS = -W -Wall -g
#LDFLAGS = -L./ -lftd2xx
LDFLAGS =

SRC = $(wildcard *.c)
OBJS = $(SRC:.c=.o)
HEADER = $(SRC:.c=.h)
 
all : projet
 
remake: clean projet

projet : $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm *.o

cleaner : clean
	rm projet test_auto.zip

tozip:
	zip -r test_auto.zip $(SRC) $(HEADER) define.h -x main.c