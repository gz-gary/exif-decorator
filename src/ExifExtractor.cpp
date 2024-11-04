#include "ExifExtractor.hpp"
#include <libraw/libraw.h>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip> // Include the iomanip header for setprecision
using nlohmann::json;

json ExifExtractor::extractFromPath(const std::string &path) const
{
    json result{};

    LibRaw iProcessor;
    iProcessor.open_file(path.c_str());
    libraw_iparams_t iparam = iProcessor.imgdata.idata;
    libraw_imgother_t iother = iProcessor.imgdata.other;

    result["make"] = std::string(iparam.make);
    result["model"] = std::string(iparam.model);
    result["ISO sensivity"] = parseISO(iother.iso_speed);
    result["aperture"] = parseAperture(iother.aperture);
    result["shutter speed"] = parseShutterSpeed(iother.shutter);
    result["focal length"] = parseFocalLength(iother.focal_len);

    return result;
}

std::string ExifExtractor::parseISO(float iso) const
{
    std::stringstream parser{};
    parser << int(iso);
    return parser.str();
}

std::string ExifExtractor::parseAperture(float aperture) const
{
    std::stringstream parser{};
    parser << std::fixed << std::setprecision(1); // Set precision for floating-point numbers
    parser << aperture;
    return parser.str();
}

std::string ExifExtractor::parseShutterSpeed(float shutter) const
{
    std::stringstream parser{};
    if (shutter < 1.0) {
        int factor = 1.0 / shutter;
        parser << "1/" << factor;
    } else {
        parser << std::fixed << std::setprecision(1);
        parser << shutter;
    }
    return parser.str();
}

std::string ExifExtractor::parseFocalLength(float focal) const
{
    std::stringstream parser{};
    parser << int(focal);
    return parser.str();
}
