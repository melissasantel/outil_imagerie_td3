CPPFLAGS=-I/opt/opencv/include
CXXFLAGS=-Wall -Wextra -Werror
LDFLAGS=-Wl,-R/opt/opencv/lib -L/opt/opencv/lib
LDLIBS=\
	-lopencv_core\
	-lopencv_imgproc\
	-lopencv_highgui
BIN=\
	median-filter\
	bilateral\
	nl-means

.PHONY: all
all: $(BIN)

.PHONY: test
test:
	./median-filter 1 ../data/barbara-i.png res-1.png; pvisu res-1.png
	./median-filter 3 ../data/barbara-i.png res-3.png; pvisu res-3.png
	./bilateral 10 30 ../data/barbara.png res-1.png; pvisu res-1.png
	./bilateral 10 30 ../data/barbara-g-10.png res-1.png; pvisu res-1.png
	./nl-means 5 ../data/barbara.png res-5.png; pvisu res-5.png
	./nl-means 15 ../data/barbara.png res-15.png; pvisu res-15.png
	./nl-means 10 ../data/barbara-g-10.png res-10.png; pvisu res-10.png


.PHONY: clean
clean:
	$(RM) *~ *.png

.PHONY: cleanall
cleanall: clean
	$(RM) $(BIN) *.o *.pdf
