CFLAGS = -W -Wall -g 
LDFLAGS =

SRC = $(wildcard *.c)
OBJS = $(SRC:.c=.o)
HEADER = $(SRC:.c=.h)
 
all : projet
 
remake: clean projet

projet : $(OBJS)
	gcc $(LDFLAGS) -o $@ $^

%.o : %.c
	gcc $(CFLAGS) -o $@ -c $<

clean:
	rm *.o

cleaner : clean
	rm projet test_auto.zip

tozip:
	zip -r test_auto.zip $(SRC) $(HEADER) define.h -x main.c