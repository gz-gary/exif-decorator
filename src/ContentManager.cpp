#include "ContentManager.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <cassert>
#include <iostream>

ContentManager::ContentManager(LoadMode loadMode)
    : load_mode(loadMode)
{
}

void ContentManager::setContentRoot(const std::string &path)
{
    content_root = path;
}

std::string ContentManager::getStylesheet(const std::string &fileName) const
{
    std::string path = content_root + "/stylesheets" + fileName;
    return readContent(path);
}

std::string ContentManager::getScript(const std::string &fileName) const
{
    std::string path = content_root + "/scripts" + fileName;
    return readContent(path);
}

std::string ContentManager::getMainPage() const
{
    std::string path = content_root + "/html/main.html";
    return readContent(path);
}

std::string ContentManager::readContent(const std::string &path) const
{
    std::ifstream file_stream{path};
    if (!file_stream.is_open()) throw -1;

    std::stringstream string_stream{};
    string_stream << file_stream.rdbuf();
    return string_stream.str();
}
