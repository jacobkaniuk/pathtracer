#ifndef RESOLUTION_H
#define RESOLUTION_H

#include <utility>
#include <unordered_map>

namespace display {
    enum resolution{
            res_360,
            res_540,
            res_720,
            res_1080,
            res_4k,
            res_8k,
            res_HD = res_720,
            res_FHD = res_1080,
            res_UDH = res_4k,
        };


std::pair<int, int> get_resolution_values(const resolution& resolution);

} // namespace display

#endif // RESOLUTION_H