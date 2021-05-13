#include <iostream>
#include "catch.hpp"
#include "pixel.h"
#include "blend_ops.hpp"
#include "constants.h"


TEST_CASE("Replace100%"){
    Pixel p1(constants::layer::pixel::colors::RGBA::BLUE, BitDepth::R8G8B8A8);
	Pixel p2(constants::layer::pixel::colors::RGBA::RED, BitDepth::R8G8B8A8);
	Pixel output(p2);
	image::operations::BlendNormal(&p1, &p2, &output, 1.f);
    REQUIRE(output == Pixel(constants::layer::pixel::colors::RGBA::BLUE));
}

TEST_CASE("Replace50%"){
    Pixel p1(constants::layer::pixel::colors::RGBA::BLUE, BitDepth::R8G8B8A8);
	Pixel p2(constants::layer::pixel::colors::RGBA::RED, BitDepth::R8G8B8A8);
	Pixel output(p2);
	image::operations::BlendNormal(&p1, &p2, &output, 0.5f);
    REQUIRE(output == Pixel(color::ColorRGBA(0.5f, 0.f, 0.5f, 1.f)));
}

TEST_CASE("Multiply100%"){
    Pixel pm1(color::ColorRGBA(0.5f, 0.5f, 1.f, 1.f), BitDepth::R8G8B8A8);
	Pixel pm2(color::ColorRGBA(1.f, 1.f, 1.f, 1.f), BitDepth::R8G8B8A8);
    Pixel output(pm2);
    image::operations::BlendMultiply(&pm1, &pm2, &output, 1.f);
	std::cout << "R: " << output[0] << " G: " << output[1] << " B: "<< output[2] << " A: " << output[3] << std::endl;
    REQUIRE(output == Pixel(color::ColorRGBA(0.5f, 0.5f, 0.5f, 1.f)));
}

TEST_CASE("Multiply75%"){
	Pixel pm1(color::ColorRGBA(0.5f, 0.5f, 1.f, 1.f), BitDepth::R8G8B8A8);
	Pixel pm2(color::ColorRGBA(1.f, 1.f, 1.f, 1.f), BitDepth::R8G8B8A8);
    Pixel output(pm2);
	image::operations::BlendMultiply(&pm1, &pm2, &output, .75f);
	std::cout << "R: " << output[0] << " G: " << output[1] << " B: "<< output[2] << " A: " << output[3] << std::endl;
    REQUIRE(output == Pixel(color::ColorRGBA(0.75f, 0.75f, 0.75f, 1.f)));
}

TEST_CASE("Darken100%"){
    	// Darken Test
	Pixel pd1(color::ColorRGBA(0.5f, 0.5f, 0.5f, 1.f), BitDepth::R8G8B8A8);
	Pixel pd2(color::ColorRGBA(1.f, 1.f, 1.f, 1.f), BitDepth::R8G8B8A8);
    Pixel output(pd2);
	image::operations::BlendDarken(&pd1, &pd2, &output, 1.f);
    REQUIRE(output == Pixel(color::ColorRGBA(0.5f, 0.5f, 0.5f, 1.f)));
}