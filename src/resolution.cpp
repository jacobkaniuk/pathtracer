#include "resolution.h"

std::pair<int, int> display::get_resolution_values(const display::resolution& resolution) {
    std::unordered_map<display::resolution, std::pair<int, int>> resolutions_to_values = {
        // common 16:9 resolutions
		{display::resolution::res_360,    std::make_pair(640, 360)},
		{display::resolution::res_540,    std::make_pair(960, 540)},
        {display::resolution::res_720,    std::make_pair(1280, 720)},
        {display::resolution::res_1080,   std::make_pair(1920, 1080)},
        {display::resolution::res_4k,     std::make_pair(3840, 2160)},
        {display::resolution::res_8k,     std::make_pair(7680, 4320)},
	};

    return resolutions_to_values[resolution];
};