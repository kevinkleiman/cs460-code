CC      =  gcc
CFLAGS  = -pedantic -std=c11 -ggdb #-save-temps
LDFLAGS =
SRCS    = $(wildcard *.c)
OBJS    = $(SRCS:.c=.o)
DEPS    = $(wildcard *.h)
TARGET  = album

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

run: 
	./$(TARGET) ./photos/*.jpg

.PHONY: clean
clean:
	rm -rf $(OBJS) $(TARGET) *~
	rm -rf *.jpg
	rm -rf *.html
