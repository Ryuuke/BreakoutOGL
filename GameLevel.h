#pragma once

#include <vector>
#include "GameObject.h"

class RessourceManager;
class SpriteRenderer;

class GameLevel
{
public:
	std::vector<GameObject> m_briks;

	GameLevel() = default;
	~GameLevel() = default;
	 
	void Load(RessourceManager& ressourceManager, const char* levelFile, 
		const int& levelWidth, const int& levelHeight);

	bool IsCompleted();
	void Draw(SpriteRenderer& spriteRenderer);

private:
	void Init(RessourceManager& ressourceManager, const std::vector<std::vector<int>>& tileData, 
		const int& levelWidth, const int& levelHeight);
};
