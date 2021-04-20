CC = gcc
CFLAGS = -W -Wall -g
LDFLAGS = -L./lib -lftd2xx

SRC = $(wildcard src/*.c)
OBJS = $(SRC:.c=.o)
HEADER = $(SRC:.c=.h)
 
all : projet clean

projet : $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o : %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm src/*.o

tozip:
	zip -r auto_save2.zip $(SRC) $(HEADER) define.h -x main.c