CC = gcc
CFLAGS = -Wall -std=c11
SRCS = tema3.c f_tbook.c f_ttrie.c f_input.c 
OBJS = $(SRCS:.c=.o)
MAIN = tema3

.PHONY: clean run build

build: $(MAIN)

$(MAIN): $(OBJS)
	$(CC) -o $(MAIN) $(OBJS) $(CFLAGS)

run: build
	./$(MAIN)
	
$(OBS): %.o %.c  
	$(CC) $< $(CFLAGS) -c -o $@
	
clean:
	$(RM) ./*.o *~ $(MAIN)
