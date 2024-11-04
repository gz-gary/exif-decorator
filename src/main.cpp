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

  svr.Get(R"(/exif-information.json?.*)", [&exif_extractor](const Request& req, Response& res) {
    std::cerr << "request for json" << std::endl;
    std::optional<std::string> path{};
    for (auto param : req.params) {
      if (param.first == "raw-url") {
        path = param.second;
        std::cerr << param.second << std::endl;
        break;
      }
    }
    if (path.has_value()) {
      std::string content{};
      try {
        content = nlohmann::to_string(exif_extractor.extractFromPath(path.value()));
      } catch (int status) {
        if (status == -1) { // file does not exist or is not local
          res.status = 404;
          res.set_content("{}", "text/plain");
        } else {
          res.set_content(content, "application/json");
        }
      }
    } else {
      res.status = 404;
      res.set_content("{}", "text/plain");
    }
  });

  svr.listen("localhost", 1234);
}