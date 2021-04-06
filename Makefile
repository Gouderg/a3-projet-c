CC = gcc
CFLAGS = -W -Wall -g
LDFLAGS = 
 
SRC = $(wildcard *.c)
OBJS = $(SRC:.c=.o)
HEADER = $(SRC:.c=.h)
AOUT = projet
 
all : $(AOUT) 
 
projet : $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean :
	@rm *.o

cleaner : clean
	@rm $(AOUT) test_auto.zip


tozip:
	zip -r test_auto.zip $(SRC) $(HEADER) define.h -x main.c