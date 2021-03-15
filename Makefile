.PHONY build:
build:
		clang++ -D PLATFORM_WINDOWS -Wall -I./include -march=x86-64 -fexceptions -std=c++17 src/*.cpp -o bin/pathtracer

.PHONY rebuild:
rebuild:
		clang++ -D PLATFORM_WINDOWS -Wall -I./include -march=x86-64 -fexceptions -std=c++17 src/*.cpp -o bin/pathtracer
		./bin/pathtracer

.PHONE clean:
clean:
		rm -rfv ./bin/*
