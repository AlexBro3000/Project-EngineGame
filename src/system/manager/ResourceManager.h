#pragma once

#include <string>
#include <map>
#include <memory>

class Directory;
class ShaderProgram;

class ResourceManager
{
private:
    typedef std::map<const std::string, std::shared_ptr<::Directory>> DirectoryMap;
    static DirectoryMap directories;

    typedef std::map<const std::string, std::shared_ptr<::ShaderProgram>> ShaderProgramMap;
    static ShaderProgramMap shader_programs;

public:
    /*
    ResourceManager() = delete;
    ResourceManager(const ResourceManager&) = delete;
    ResourceManager(ResourceManager&&) = delete;
    ~ResourceManager() = delete;

    ResourceManager& operator=(const ResourceManager&) = delete;
    ResourceManager& operator=(ResourceManager&&) = delete;
    */

    static void Init(int argc, char** argv);
    static void Terminate();

    class Directory
    {
    public:
        static ::Directory& load(const std::string& name, const std::string& parent_name, const std::string& path, bool is_create);
        static ::Directory& load(const std::string& name, const std::string& path, bool is_create);
        static void         unload(const std::string& name);

        static ::Directory& get(const std::string& name);

    private:
    };

    class ShaderProgram
    {
    public:
        static ::ShaderProgram& load(const std::string& name, const std::string& path_vert, const std::string& path_frag);
        static void             unload(const std::string& name);

        static ::ShaderProgram& get(const std::string& name);

    private:
    };

private:
    static std::string getLaunchDirectory(const std::string& path);

};

//    static std::shared_ptr<RenderEngine::Texture2D> loadTexture(const std::string& textureName, const std::string& texturePath);
//    static std::shared_ptr<RenderEngine::Texture2D> getTexture(const std::string& textureName);
//
//    static std::shared_ptr<RenderEngine::Sprite> loadSprite(const std::string& spriteName,
//        const std::string& textureName,
//        const std::string& shaderName,
//        const std::string& subTextureName = "default");
//    static std::shared_ptr<RenderEngine::Sprite> getSprite(const std::string& spriteName);
//
//    static std::shared_ptr<RenderEngine::Texture2D> loatTextureAtlas(std::string textureName,
//        std::string texturePath,
//        std::vector<std::string> subTextures,
//        const unsigned int subTextureWidth,
//        const unsigned int subTextureHeight);
//
//    static bool loadJSONResources(const std::string& JSONPath);
//
//    static const std::vector<std::vector<std::string>>& getLevels() { return m_levels; }
//    static const std::vector<std::string>& getStartScreen() { return m_startScreen; }
