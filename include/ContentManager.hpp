#include <string>

class ContentManager {
public:
    enum class LoadMode {
        LOADMODE_EMBEDDED,
        LOADMODE_EXTERNAL
    };

    explicit ContentManager(LoadMode loadMode = LoadMode::LOADMODE_EXTERNAL);
    void setContentRoot(const std::string& path);
    std::string getStylesheet(const std::string& fileName) const;
    std::string getScript(const std::string& fileName) const;
    std::string getMainPage() const;

private:
    std::string readContent(const std::string &path) const;

    LoadMode load_mode;
    std::string content_root;
    

};