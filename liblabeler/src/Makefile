CC=g++
CFLAGS= -g -Wall -02

# Linker flags
LIB_FLAGS = -lcurl -lm -lopencv_core -lopencv_highgui -lopencv_video -lopencv_imgproc -lopencv_gpu -lopencv_calib3d -lopencv_legacy -lopencv_objdetect -lopencv_ml -lopencv_features2d -lopencv_calib3d -lopencv_flann
LDFLAGS = -I/usr/local/include/opencv2 $(LIB_FLAGS)

# Source files in the library
SRC = Roi.cpp util/CurlUtils.cpp LabeledImage.cpp ImageSequence.cpp
OBJECT = $(SRC:.cpp=.o)

UNAME := $(shell uname)

all: liblabeler

# Builds tests for the library, dependent on its install
test_liblabeler: test/labeledImageFunctionality.o
	$(CC) $(CFLAGS) $(LDFLAGS) -llabeler test/labeledImageFunctionality.cpp -o test_liblabeler

# Builds the shared library object
liblabeler: $(OBJECT)
	$(CC) $(CFLAGS) -shared -soname,liblabeler.so.1 -o liblabeler.so $(OBJECT) $(LDFLAGS)

# Installs the shared library and headers, may require root perms
install:
	cp *.h /usr/include
	cp liblabeler.so* /usr/lib

# Compiles cpp files to objects, position independent and ready for shared use
.cpp.o:
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ -fpic -g -c $<

# Cleans binaries
clean:
	rm -rf *.o core* liblabeler.so.* test_liblabeler
