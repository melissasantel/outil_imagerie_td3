CPPFLAGS=-I/opt/opencv/include
CXXFLAGS=-Wall -Wextra -Werror
LDFLAGS=-Wl,-R/opt/opencv/lib -L/opt/opencv/lib
LDLIBS=\
	-lopencv_core\
	-lopencv_imgproc\
	-lopencv_highgui
BIN=\
	median-filter\
	bilateral
	# nl-means

.PHONY: all
all: $(BIN)

.PHONY: test
test:
	./median-filter 1 ../data/barbara-i.png res-1.png; pvisu res-1.png
	./median-filter 3 ../data/barbara-i.png res-3.png; pvisu res-3.png
	# ./bilateral 10 30 ../data/barbara.png res-1.png; pvisu res-1.png
	# ./bilateral 10 30 ../data/barbara-g-10.png res-1.png; pvisu res-1.png
	# ./hsv-modification 100 0 0 ../data/horse.png horse-hsv.png; pvisu horse-hsv.png
	# ./eq-histogram ../data/eq-ex.png; pvisu ../data/eq-ex.png; pvisu eq.png; pvisu eq-ocv.png; pvisu diff.png


.PHONY: clean
clean:
	$(RM) *~ *.png

.PHONY: cleanall
cleanall: clean
	$(RM) $(BIN) *.o *.pdf
