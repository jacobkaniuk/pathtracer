CC = clang++
PREPROCESSORS = -D PLATFORM_WINDOWS
FLAGS = -I./include -march=x86-64 -fexceptions -std=c++17 
SRC = src
BIN = bin
OUTPUT = $(BIN)/pathtracer

pathtracer: image_buffer.o pathtracer.o pixel.o serializers.o
	clang++ *.o -o $(OUTPUT)
	./$(OUTPUT)
	
image_buffer.o: $(SRC)/image_buffer.cpp
	$(CC) -c $(PREPROCESSORS) $(FLAGS) $(SRC)/image_buffer.cpp

pathtracer.o: $(SRC)/pathtracer.cpp
	$(CC) -c $(PREPROCESSORS) $(FLAGS) $(SRC)/pathtracer.cpp

pixel.o: $(SRC)/pixel.cpp
	$(CC) -c $(PREPROCESSORS) $(FLAGS) $(SRC)/pixel.cpp

serializers.o: $(SRC)/serializers.cpp
	$(CC) -c $(PREPROCESSORS) $(FLAGS) $(SRC)/serializers.cpp

.PHONY clean:
clean:
	rm -rfv $(BIN)/*
	rm -rfv *.s
	rm -rfv *.o
