#include "RessourceManager.h"

void RessourceManager::ClearRessources()
{
	for (auto& texture : m_textureMap)
		texture.second.Destroy();

	for (auto& shader : m_shaderMap)
		shader.second.Destroy();
}

void RessourceManager::LoadShader(const char * vxPath, const char * fxPath, const char* key)
{
	Shader shader;
	shader.Init(vxPath, fxPath);

	m_shaderMap[key] = std::move(shader);
}

void RessourceManager::LoadTexture(const char * texturePath, const bool bUseAlpha, const char* key)
{
	Texture texture;
	texture.Init(texturePath, bUseAlpha);

	m_textureMap[key] = std::move(texture);
}