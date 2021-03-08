.PHONY build:
build:
		g++ -I./include	-std=c++17 src/pathtracer.cpp -o bin/pathtracer

.PHONE clean:
clean:
		rm -rfv ./bin/*
