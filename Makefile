pathtracer: image_buffer.o pathtracer.o pixel.o serializers.o
	clang++ *.o -D PLATFORM_WINDOWS -Wall -I./include -march=x86-64 -fexceptions -std=c++17 -o bin/pathtracer
	bin/pathtracer

image_buffer.o: src/image_buffer.cpp
	clang++ -c -D PLATFORM_WINDOWS -I./include -march=x86-64 -fexceptions -std=c++17 src/image_buffer.cpp

pathtracer.o: src/pathtracer.cpp
	clang++ -c -D PLATFORM_WINDOWS -I./include -march=x86-64 -fexceptions -std=c++17 src/pathtracer.cpp

pixel.o: src/pixel.cpp
	clang++ -c -D PLATFORM_WINDOWS -I./include -march=x86-64 -fexceptions -std=c++17 src/pixel.cpp

serializers.o: src/serializers.cpp
	clang++ -c -D PLATFORM_WINDOWS -I./include -march=x86-64 -fexceptions -std=c++17 src/serializers.cpp

.PHONY clean:
clean:
	rm -rfv bin/*
	rm -rfv *.s
	rm -rfv *.o
