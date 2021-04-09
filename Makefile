CC = gcc
#CC = x86_64-w64-mingw32-gcc
CFLAGS = -W -Wall -g
LDFLAGS = -L./ -lftd2xx
#LDFLAGS = 

SRC = $(wildcard *.c)
OBJS = $(SRC:.c=.o)
HEADER = $(SRC:.c=.h)
 
all : projet clean tozip

projet : $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o : %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm *.o

tozip:
	zip -r auto_save2.zip $(SRC) $(HEADER) define.h -x main.c