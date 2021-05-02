CC = clang++
PREPROCESSORS = -D PLATFORM_WINDOWS
FLAGS = -I./include -I./tests/include -I./vendor/fmt/include -I./vendor/googletest/googletest/include \
		-I./vendor/googletest/googlemock/include -march=x86-64 -fexceptions -std=c++17 -O3
SRC = src
INCLUDE = include
BINDIR = bin
TESTDIR = tests
TESTOBJ = $(TESTDIR)/obj
OUTPUT = $(BINDIR)/pathtracer
TEST_OUTPUT = $(TESTDIR)/bin/test_all

pathtracer: catch.o image_buffer.o pathtracer.o pixel.o serializers.o blend_ops.o\
			image_layer.o transform.o image_layer_stack.o resolution.o
	$(CC) $(FLAGS) *.o -o $(OUTPUT)
	./$(OUTPUT)

catch.o: $(TESTDIR)/include/catch.hpp
	$(CC) -c $(PREPROCESSORS) $(FLAGS) $(TESTDIR)/include/catch.hpp

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

$(TESTOBJ)/test_main.o: $(TESTDIR)/test_main.cpp
	$(CC) -c $(FLAGS) $(TESTDIR)/test_main.cpp -o $(TESTOBJ)/test_main.o

$(TESTOBJ)/test_vector3.o: $(TESTDIR)/test_vector3.cpp
	$(CC) -c $(FLAGS) $(TESTDIR)/test_vector3.cpp -o $(TESTOBJ)/test_vector3.o

$(TESTOBJ)/test_matrix4.o: $(TESTDIR)/test_matrix4.cpp
	$(CC) -c $(FLAGS) $(TESTDIR)/test_matrix4.cpp -o $(TESTOBJ)/test_matrix4.o

$(TESTOBJ)/test_ray.o: $(TESTDIR)/test_ray.cpp
	$(CC) -c $(FLAGS) $(TESTDIR)/test_ray.cpp -o $(TESTOBJ)/test_ray.o

$(TESTOBJ)/test_blend_ops.o: $(TESTDIR)/test_blend_ops.cpp
	$(CC) -c $(FLAGS) $(SRC)/pixel.cpp -o $(TESTOBJ)/test_pixel.o
	$(CC) -c $(FLAGS) $(TESTDIR)/test_blend_ops.cpp -o $(TESTOBJ)/test_blend_ops.o

.PHONY test:
test: $(TESTOBJ)/test_main.o $(TESTOBJ)/test_vector3.o $(TESTOBJ)/test_matrix4.o $(TESTOBJ)/test_blend_ops.o
	$(CC) $(FLAGS) $(TESTOBJ)/*.o -o $(TEST_OUTPUT)
	./$(TEST_OUTPUT) -s


.PHONY clean:
clean:
	rm -rfv $(BINDIR)/*
	rm -rfv *.s
	rm -rfv *.o
