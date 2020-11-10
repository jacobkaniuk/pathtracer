.PHONY build:
build:
		g++ -I./include	src/pathtracer.cpp -o bin/raytracer

.PHONE clean:
clean:
		rm -rfv ./bin/*
