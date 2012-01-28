CC=g++
CFLAGS= -Wall -02
LDFLAGS = -I/usr/local/include/opencv2 -lcurl -lm -lopencv_core -lopencv_highgui -lopencv_video -lopencv_imgproc -lopencv_gpu -lopencv_calib3d -lopencv_legacy -lopencv_objdetect -lopencv_ml -lopencv_features2d -lopencv_calib3d -lopencv_flann

SRC = Roi.cpp util/CurlUtils.cpp LabeledImage.cpp labeledImageFunctionality.cpp
OBJECT = $(SRC:.cpp=.o)
EXECUTABLE = labeledImageFunctionality

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECT)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJECT) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ -c $<

clean:
	rm -rf *.o core* $(EXECUTABLE)