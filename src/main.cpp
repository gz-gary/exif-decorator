#include <base64.h>
#include <httplib.h>

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <optional>

#include "ContentManager.hpp"
#include "ExifExtractor.hpp"

int main(void)
{
  using namespace httplib;

  Server svr{};
  ContentManager content_manager{};
  content_manager.setContentRoot("./ui");
  
  ExifExtractor exif_extractor{};

  svr.Get("/", [&content_manager](const Request& req, Response& res) {
    std::string content = content_manager.getMainPage();
    res.set_content(content, "text/html");
  });

  svr.Get(R"(/.*\.css)", [&content_manager](const Request& req, Response& res) {
    std::string content = content_manager.getStylesheet(req.matches[0].str());
    res.set_content(content, "text/css");
  });

  svr.Get(R"(/.*\.js)", [&content_manager](const Request& req, Response& res) {
    std::string content = content_manager.getScript(req.matches[0].str());
    res.set_content(content, "text/javascript");
  });

  svr.Post(R"(/upload-raw)", [&exif_extractor](const Request& req, Response& res) {
    try {
        nlohmann::json json_req = nlohmann::json::parse(req.body),
                       json_res;
        std::string base64data = json_req["file"].get<std::string>(); // Get the raw string value
        std::string str_buffer = base64_decode(base64data);

        json_res = exif_extractor.extractFromBuffer(
          str_buffer.data(),
          str_buffer.size()
        );

        std::string content{json_res.dump()};
        res.set_content(content, "application/json");
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        // Handle the exception and set an appropriate response
        res.set_content("{\"error\": \"Internal Server Error\"}", "application/json");
    }
  });

  svr.listen("localhost", 1234);
}