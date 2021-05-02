This will eventually be a progressive, multithreaded pathtracer which will be able to load in scene data and render out to a few different file formats. CUDA support for simd ops to come later.

Dependencies:
- **catch2** https://github.com/catchorg/Catch2 (copied as single header file **test/include/catch.hpp**)
- **fmt** https://github.com/fmtlib/fmt

**How To**
- build and the application with command `make`
- run all unit tests with command `make test`
- clean build files with command `make clean`
