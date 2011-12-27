CC=g++
CFLAGS= -Wall
LDFLAGS = -I/usr/local/include/opencv2 -lm -lopencv_core -lopencv_highgui -lopencv_video -lopencv_imgproc -lopencv_gpu -lopencv_calib3d -lopencv_legacy -lopencv_objdetect -lopencv_ml
SRC = letter_recog.cpp
OBJECT = letter_recog.o
ALL = letter_recog

all: $(ALL)

test: $(OBJECT)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

$(OBJECT): $(SRC)
	$(CC) $(CFLAGS) $(LDFLAGS) -c $<

.PHONY: clean

clean:
	rm -rf *.o core* $(ALL)



