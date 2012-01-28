CC=g++
CFLAGS= -Wall -02
LIB_FLAGS = -lcurl -lm -lopencv_core -lopencv_highgui -lopencv_video -lopencv_imgproc -lopencv_gpu -lopencv_calib3d -lopencv_legacy -lopencv_objdetect -lopencv_ml -lopencv_features2d -lopencv_calib3d -lopencv_flann -llabeler

LDFLAGS = -I/usr/local/include/opencv2 $(LIB_FLAGS)

# Source files in the pipeline
SRC =
OBJECT = $(SRC:.cpp=.o)

UNAME := $(shell uname)

all: processor

# Tests for the processor module
test_processor: test/labeledImageFunctionality.o
	$(CC) $(CFLAGS) $(LDFLAGS) -llabeler test/labeledImageFunctionality.cpp -o test_liblabeler

# This is the executable processing pipeline
processor: $(OBJECT)
	$(CC) $(CFLAGS) -o liblabeler.so $(OBJECT) $(LDFLAGS)

# Compiles cpp to object files
.cpp.o:
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ -c $<

# Cleans targets
clean:
	rm -rf *.o core* liblabeler.so.* test_liblabeler