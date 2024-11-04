#include <httplib.h>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

#include "ContentManager.hpp"


int main(void)
{
  using namespace httplib;

  Server svr;
  ContentManager content_manager;
  content_manager.setContentRoot("./ui");

  svr.Get("/", [&content_manager](const Request& req, Response& res) {
    std::string content = content_manager.getMainPage();
    res.set_content(content, "text/html");
  });

  svr.Get(R"(/.*\.css)", [&content_manager](const Request& req, Response& res) {
    std::string content = content_manager.getStylesheet(req.matches[0].str());
    res.set_content(content, "text/css");
  });

  svr.listen("localhost", 1234);
}