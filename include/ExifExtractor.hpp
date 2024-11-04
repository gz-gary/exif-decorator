#include <libraw/libraw.h>
#include <nlohmann/json.hpp>
#include <string>

class ExifExtractor {
public:
    nlohmann::json extractFromPath(const std::string& path);

private:
    std::string parseISO(float iso) const;
    std::string parseAperture(float aperture) const;
    std::string parseShutterSpeed(float shutter) const;
    std::string parseFocalLength(float focal) const;

    LibRaw iProcessor;
};