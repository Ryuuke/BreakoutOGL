#include "GameLevel.h"

#include <fstream>
#include <string>
#include <sstream>

#include "RessourceManager.h"

void GameLevel::Load(RessourceManager& ressourceManager, const char* levelFile, const int& levelWidth, const int& levelHeight)
{
	m_briks.clear();

	std::ifstream fileReader(levelFile);

	std::vector<std::vector<int>> tileNumbers;
	int number = 0;

	std::string line;

	while (std::getline(fileReader, line))
	{
		std::stringstream lineStream(line);
		std::vector<int> tileLine;

		while (lineStream >> number)
			tileLine.push_back(number);

		tileNumbers.push_back(tileLine);
	}

	if (tileNumbers.size() > 0)
		Init(ressourceManager, tileNumbers, levelWidth, levelHeight);
}

void GameLevel::Init(RessourceManager& ressourceManager, const std::vector<std::vector<int>>& tileData, const int& levelWidth, const int& levelHeight)
{
	int maxWidth = tileData[0].size();
	int maxHeight = tileData.size();

	float unitWidth = levelWidth / static_cast<float>(maxWidth);
	float unitHeight = levelHeight / static_cast<float>(maxHeight);

	for (auto i = 0; i < tileData.size(); i++)
	{
		for (auto j = 0; j < tileData[i].size(); j++)
		{
			glm::vec2 position(unitWidth * j, unitHeight * i);
			glm::vec2 size(unitWidth, unitHeight);

			if (tileData[i][j] == 1)
			{
				auto block = GameObject(ressourceManager.GetTexture("solidBrick"), position, size);
				block.m_bIsBlock = true;
				m_briks.emplace_back(std::move(block));
				continue;
			}

			glm::vec3 color;

			switch (tileData[i][j])
			{
			case 2:
				color = glm::vec3(.2f, .6f, 1.f);
				break;
			case 3:
				color = glm::vec3(.0f, .7f, .0f);
				break;
			case 4:
				color = glm::vec3(.8f, .8f, .4f);
				break;
			case 5:
				color = glm::vec3(1.f, .5f, .0f);
				break;
			default:
				continue;
				break;
			}

			m_briks.emplace_back(ressourceManager.GetTexture("brick"), position, size, color);
		}
	}
}

bool GameLevel::IsCompleted()
{
	return false;
}

void GameLevel::Draw(SpriteRenderer& spriteRenderer)
{
	for (auto& brick : m_briks)
	{
		brick.VDraw(spriteRenderer);
	}
}
