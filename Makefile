export COLOR_NC='\e[0m' # No Color
export COLOR_BLACK='\e[0;30m'
export COLOR_GRAY='\e[1;30m'
export COLOR_RED='\e[0;31m'
export COLOR_LIGHT_RED='\e[1;31m'
export COLOR_GREEN='\e[0;32m'
export COLOR_LIGHT_GREEN='\e[1;32m'
export COLOR_BROWN='\e[0;33m'
export COLOR_YELLOW='\e[1;33m'
export COLOR_BLUE='\e[0;34m'
export COLOR_LIGHT_BLUE='\e[1;34m'
export COLOR_PURPLE='\e[0;35m'
export COLOR_LIGHT_PURPLE='\e[1;35m'
export COLOR_CYAN='\e[0;36m'
export COLOR_LIGHT_CYAN='\e[1;36m'
export COLOR_LIGHT_GRAY='\e[0;37m'
export COLOR_WHITE='\e[1;37m'


CC = clang++
PREPROCESSORS = -D PLATFORM_WINDOWS
FLAGS = $(INCLUDE_DIRS) -march=x86-64 -fexceptions -std=c++17 -O3
TEST_FLAGS = $(INCLUDE_TEST_DIRS) -march=x86-64 -fexceptions -std=c++17 -O3
SRC = src
INCLUDE_DIRS = -I./include -I./vendor/fmt/include
INCLUDE_TEST_DIRS = -I./tests/include -I./include
BINDIR = bin
TESTDIR = tests
TESTOBJ = $(TESTDIR)/obj
OUTPUT = $(BINDIR)/pathtracer
TEST_OUTPUT = $(TESTDIR)/bin/test_all

# MAIN

pathtracer: image_buffer.o pathtracer.o pixel.o serializers.o blend_ops.o \
			image_layer.o transform.o image_layer_stack.o resolution.o
	$(build_pathtracer)
	./$(OUTPUT)

image_buffer.o: $(SRC)/image_buffer.cpp
	$(CC) -c $(PREPROCESSORS) $(FLAGS) $(SRC)/image_buffer.cpp

pathtracer.o: $(SRC)/pathtracer.cpp
	$(CC) -c $(PREPROCESSORS) $(FLAGS) $(SRC)/pathtracer.cpp

pixel.o: $(SRC)/pixel.cpp
	$(CC) -c $(PREPROCESSORS) $(FLAGS) $(SRC)/pixel.cpp

serializers.o: $(SRC)/serializers.cpp
	$(CC) -c $(PREPROCESSORS) $(FLAGS) $(SRC)/serializers.cpp

image_layer.o : $(SRC)/image_layer.cpp
	$(CC) -c $(PREPROCESSORS) $(FLAGS) $(SRC)/image_layer.cpp

transform.o : $(SRC)/transform.cpp
	$(CC) -c $(PREPROCESSORS) $(FLAGS) $(SRC)/transform.cpp

image_layer_stack.o: $(SRC)/image_layer_stack.cpp
	$(CC) -c $(PREPROCESSORS) $(FLAGS) $(SRC)/image_layer_stack.cpp

resolution.o: $(SRC)/resolution.cpp
	$(CC) -c $(PREPROCESSORS) $(FLAGS) $(SRC)/resolution.cpp

blend_ops.o: $(SRC)/blend_ops.cpp ./include/blend_ops.hpp
	$(CC) -c $(PREPROCESSORS) $(FLAGS) $(SRC)/blend_ops.cpp


# TESTING 

$(TESTOBJ)/test_main.o: $(TESTDIR)/test_main.cpp
	$(CC) -c $(TEST_FLAGS) $(TESTDIR)/test_main.cpp -o $(TESTOBJ)/test_main.o

$(TESTOBJ)/test_vector3.o: $(TESTDIR)/test_vector3.cpp
	$(CC) -c $(TEST_FLAGS) $(TESTDIR)/test_vector3.cpp -o $(TESTOBJ)/test_vector3.o

$(TESTOBJ)/test_matrix4.o: $(TESTDIR)/test_matrix4.cpp
	$(CC) -c $(TEST_FLAGS) $(TESTDIR)/test_matrix4.cpp -o $(TESTOBJ)/test_matrix4.o

$(TESTOBJ)/test_ray.o: $(TESTDIR)/test_ray.cpp
	$(CC) -c $(TEST_FLAGS) $(TESTDIR)/test_ray.cpp -o $(TESTOBJ)/test_ray.o

$(TESTOBJ)/test_blend_ops.o: $(TESTDIR)/test_blend_ops.cpp
	$(CC) -c $(TEST_FLAGS) $(SRC)/pixel.cpp -o $(TESTOBJ)/test_pixel.o
	$(CC) -c $(TEST_FLAGS) $(TESTDIR)/test_blend_ops.cpp -o $(TESTOBJ)/test_blend_ops.o

.PHONY run:
run: pathtracer

.PHONY build:
build: build_fmt build_test build_pathtracer

.PHONY build_pathtracer: 
build_pathtracer: image_buffer.o pathtracer.o pixel.o serializers.o blend_ops.o \
			image_layer.o transform.o image_layer_stack.o resolution.o
	@printf "\n$(COLOR_CYAN) === Pathtracer Built ===\n\n$(COLOR_NC)"
	$(CC) $(FLAGS) *.o -o $(OUTPUT)

.PHONY build_fmt:
build_fmt:
	@printf "\n$(COLOR_CYAN) === Building fmt Library ===\n\n$(COLOR_NC)" && \
	cd vendor/fmt && \
	cmake . && \
	make fmt/fast && \
	cd ../.. && \
	cp -v vendor/fmt/CMakeFiles/fmt.dir/src/format.cc.o format.cc.o && \
	cp -v vendor/fmt/CMakeFiles/fmt.dir/src/os.cc.o os.cc.o

.PHONY build_test:
build_test: $(TESTOBJ)/test_main.o $(TESTOBJ)/test_vector3.o $(TESTOBJ)/test_matrix4.o $(TESTOBJ)/test_blend_ops.o
	@printf "\n$(COLOR_CYAN) === Unit Tests Built ===\n\n$(COLOR_NC)"
	$(CC) $(FLAGS) $(TESTOBJ)/*.o -o $(TEST_OUTPUT)

.PHONY test:
test: $(TESTOBJ)/test_main.o $(TESTOBJ)/test_vector3.o $(TESTOBJ)/test_matrix4.o $(TESTOBJ)/test_blend_ops.o
	$(build_test)
	@printf "\n $(COLOR_LIGHT_GREEN)=== Running Unit Tests ===\n\n"
	./$(TEST_OUTPUT)

.PHONY clean:
clean:
	@printf $(COLOR_LIGHT_RED)"Cleaning all binary and intermediate files\n\n"
	rm -rfv $(BINDIR)/*
	rm -rfv *.s
	rm -rfv *.o
	rm -rfv $(TESTOBJ)/*.s
	rm -rfv $(TESTOBJ)/*.o
