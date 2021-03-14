.PHONY build:
build:
		g++ -W -I./include -mcmodel=medium	-fexceptions -std=c++17 src/pathtracer.cpp -o bin/pathtracer

.PHONE clean:
clean:
		rm -rfv ./bin/*
