#pragma once

#include <unordered_map>

#include "Shader.h"
#include "Texture.h"

class RessourceManager
{
private:
	using TextureMap = std::unordered_map<const char* , Texture>;
	using ShaderMap = std::unordered_map<const char*, Shader>;

	TextureMap m_textureMap;
	ShaderMap m_shaderMap;
public:
	RessourceManager() = default;
	~RessourceManager() = default;
	void ClearRessources();

	void LoadShader(const char* vxPath, const char* fxPath, const char* key);
	void LoadTexture(const char* texturePath, const bool bUseAlpha, const char* key);

	inline Shader* GetShader(const char* shaderName) { return &m_shaderMap[shaderName]; }
	inline Texture* GetTexture(const char* textureName) { return &m_textureMap[textureName]; }
};

