CC:=gcc
CFLAGS:=-Wall

post: postdiscord.o send.o
	$(CC) $(CFLAGS) -o $@ $^ -lcurl

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f *.o post
