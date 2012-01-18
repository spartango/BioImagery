CC=g++
CFLAGS= -Wall
LDFLAGS = -lcurl

SRC = 
OBJECT = 
ALL = 

all: $(ALL)

test: $(OBJECT)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

$(OBJECT): $(SRC)
	$(CC) $(CFLAGS) $(LDFLAGS) -c $<

clean:
	rm -rf *.o core* $(ALL)