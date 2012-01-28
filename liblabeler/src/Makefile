CC=g++
CFLAGS= -Wall -02
LIB_FLAGS = -lcurl -lm -lopencv_core -lopencv_highgui -lopencv_video -lopencv_imgproc -lopencv_gpu -lopencv_calib3d -lopencv_legacy -lopencv_objdetect -lopencv_ml -lopencv_features2d -lopencv_calib3d -lopencv_flann
LDFLAGS = -I/usr/local/include/opencv2 $(LIB_FLAGS)

SRC = Roi.cpp util/CurlUtils.cpp LabeledImage.cpp
OBJECT = $(SRC:.cpp=.o)

UNAME := $(shell uname)

all: liblabeler

test_liblabeler: test/labeledImageFunctionality.o
	$(CC) $(CFLAGS) $(LDFLAGS) -llabeler test/labeledImageFunctionality.cpp -o test_liblabeler

liblabeler: $(OBJECT)
	$(CC) $(CFLAGS) -shared -soname,liblabeler.so.1 -o liblabeler.so $(OBJECT) $(LDFLAGS)

install:
	cp Roi.h /usr/include
	cp LabeledImage.h /usr/include
	cp liblabeler.so* /usr/lib

.cpp.o:
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ -fpic -g -c $<

clean:
	rm -rf *.o core* liblabeler.so.* test_liblabeler