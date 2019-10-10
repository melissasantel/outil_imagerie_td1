CPPFLAGS=-I/opt/opencv/include 
CXXFLAGS=-Wall -Wextra -Werror
LDFLAGS=-Wl,-R/opt/opencv/lib -L/opt/opencv/lib
LDLIBS=\
	-lopencv_core\
	-lopencv_imgproc\
	-lopencv_highgui
BIN=\
	readwriteshow\
	crop\
	pixels-loops\
	video-player

.PHONY: all 
all: $(BIN)

.PHONY: test
test:
	./readwriteshow ../data/lena_color.png a.png; pvisu a.png
	./crop ../data/lena_color.png 10 200 300 100; pvisu crop.png; pvisu crop-cv.png
	./pixels-loops ../data/lena_color.png
	./video-player ../data/video-tribot.mp4
	./video-player ../data/video-seq4.mp4

.PHONY: clean
clean:
	$(RM) *~ *.png

.PHONY: cleanall
cleanall: clean
	$(RM) $(BIN) *.o *.pdf
