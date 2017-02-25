#pragma once

#include <memory>

#include "RessourceManager.h"
#include "SpriteRenderer.h"
#include "GameLevel.h"
#include "BallObject.h"
#include "Actor.h"
#include "SquareShape.h"

#define TEXTURES_PATH "Assets/Textures/"
#define LEVELS_PATH "Assets/Levels/"


constexpr float PLAYER_SPEED = 280.f;
constexpr float BALL_RADIUS = 15.f;

class Game
{
public:
	const glm::vec2 PLAYER_SIZE = glm::vec2(60.f, 10.f);
	
	enum GameState
	{
		GAME_ACTIVE,
		GAME_MENU,
		GAME_WIN
	};

	enum Direction
	{
		UP,
		RIGHT,
		DOWN,
		LEFT
	};

	bool m_keys[1024];
	GameState m_state;
	int m_width = 0;
	int m_height = 0;

private:
	std::vector<GameLevel> m_levels;
	int m_currentLevelIndex = 1;

	RessourceManager m_ressourceManager;
	
	std::unique_ptr<GameObject> m_pPlayer = nullptr;
	std::unique_ptr<BallObject> m_pBall = nullptr;
	std::unique_ptr<SpriteRenderer> m_pSpriteRenderer = nullptr;

public:
	Game(const int& width, const int& height): m_width(width), m_height(height)
	{ }
	
	~Game();

	void Init();
	void ResetLevel();
	void ProcessInput(const float& deltaTime);
	void Update(const float& deltaTime);
	void Render();
private:
	void LoadAssets();
	bool CheckCollision(const BallObject& ball, const GameObject& box);
	Direction GetDirectionCollision(glm::vec2 difference);
};

