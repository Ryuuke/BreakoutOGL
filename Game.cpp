#include "Game.h"

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include "DrawableComponent.h"
#include "Transform2DComponent.h"
#include "SquareShape.h"

Game::~Game()
{
	m_pSpriteRenderer->Destroy();
	m_ressourceManager.ClearRessources();
}

void Game::Init()
{
	glm::mat4 projection = glm::ortho(0.f, static_cast<float>(m_width), static_cast<float>(m_height),
									  0.f, -1.f, 1.f);

	LoadAssets();
	
	Shader* shader = m_ressourceManager.GetShader("defaultShader");

	shader->Use();

	shader->SetMatrix4("projection", projection);
	shader->SetInt("image", 0);

	m_pSpriteRenderer = std::make_unique<SpriteRenderer>(shader);

	m_pSpriteRenderer->Init();

	m_pPlayer = std::make_unique<GameObject>(m_ressourceManager.GetTexture("brick"),
		glm::vec2(m_width / 2 - PLAYER_SIZE.x / 2, m_height - PLAYER_SIZE.y), PLAYER_SIZE);

	m_pBall = std::make_unique<BallObject>(m_ressourceManager.GetTexture("face"), 
		glm::vec2(m_pPlayer->m_position.x + m_pPlayer->m_size.x / 2 - BALL_RADIUS, 
			m_pPlayer->m_position.y - BALL_RADIUS * 2), BALL_RADIUS);
}

void Game::ResetLevel()
{
	for (auto& brick : m_levels[m_currentLevelIndex - 1].m_briks)
	{
		brick.m_bIsDead = false;
	}
	
	m_pPlayer->m_position = glm::vec2(m_width / 2 - PLAYER_SIZE.x / 2, m_height - PLAYER_SIZE.y);
	m_pBall->m_position = glm::vec2(m_pPlayer->m_position.x + m_pPlayer->m_size.x / 2 - BALL_RADIUS,
									m_pPlayer->m_position.y - BALL_RADIUS * 2);
	m_pBall->m_bIsStuck = true;
}

void Game::LoadAssets()
{
	m_ressourceManager.LoadShader("default_vx.glsl", "default_fx.glsl", "defaultShader");

	std::string texturesPath(TEXTURES_PATH);
	std::string levelsPath(LEVELS_PATH);

	m_ressourceManager.LoadTexture(std::string(texturesPath + "awesomeface.png").data(), true, "face");
	m_ressourceManager.LoadTexture(std::string(texturesPath + "block.png").data(), false, "brick");
	m_ressourceManager.LoadTexture(std::string(texturesPath + "block_solid.png").data(), false, "solidBrick");
	m_ressourceManager.LoadTexture(std::string(texturesPath + "background.jpg").data(), false, "background");
	m_ressourceManager.LoadTexture(std::string(texturesPath + "paddle.png").data(), true, "paddle");

	GameLevel levelOne;
	levelOne.Load(m_ressourceManager, std::string(levelsPath + "one.txt").data(), m_width, m_height / 2);

	GameLevel levelTwo;
	levelTwo.Load(m_ressourceManager, std::string(levelsPath + "two.txt").data(), m_width, m_height / 2);

	GameLevel levelThree;
	levelThree.Load(m_ressourceManager, std::string(levelsPath + "three.txt").data(), m_width, m_height / 2);

	GameLevel levelFour;
	levelFour.Load(m_ressourceManager, std::string(levelsPath + "four.txt").data(), m_width, m_height / 2);

	m_levels.push_back(levelOne);
	m_levels.push_back(levelTwo);
	m_levels.push_back(levelThree);
	m_levels.push_back(levelFour);
}

void Game::ProcessInput(const float& deltaTime)
{
	if (m_state != Game::GAME_ACTIVE)
		return;
	
	float velocity = PLAYER_SPEED * deltaTime;

	if (m_keys[GLFW_KEY_D])
	{
		float nextPosition = m_pPlayer->m_position.x + velocity;

		if (nextPosition > m_width - PLAYER_SIZE.x)
			return;

		m_pPlayer->m_position.x = nextPosition;
	}

	if (m_keys[GLFW_KEY_A])
	{
		float nextPosition = m_pPlayer->m_position.x - velocity;

		if (nextPosition < 0)
			return;

		m_pPlayer->m_position.x = nextPosition;
	}

	if (m_pBall->m_bIsStuck)
	{
		m_pBall->m_position.x = m_pPlayer->m_position.x + m_pPlayer->m_size.x / 2 - BALL_RADIUS;
		m_pBall->m_position.y = m_pPlayer->m_position.y - BALL_RADIUS * 2;
	}

	if (m_keys[GLFW_KEY_SPACE])
		m_pBall->m_bIsStuck = false;
	
	if (m_keys[GLFW_KEY_U])
	{
		m_keys[GLFW_KEY_U] = false;
		
		for (auto& brick : m_levels[m_currentLevelIndex - 1].m_briks)
		{
			brick.m_bIsDead = true;
		}
	}
}

void Game::Update(const float& deltaTime)
{
	m_pBall->Move(deltaTime, m_width, m_height);

	for (auto& brick : m_levels[m_currentLevelIndex - 1].m_briks)
	{
		if (brick.m_bIsDead)
			continue;
		
		if (!CheckCollision(*m_pBall.get(), brick))
			continue;

		if (brick.m_bIsBlock)
			continue;

		brick.m_bIsDead = true;
	}
	
	/* check for win */
	{
		int counter = 0;
		
		for (auto& brick : m_levels[m_currentLevelIndex-1].m_briks)
		{
			if (!brick.m_bIsDead)
				break;
			
			counter++;
		}
		
		if (counter == m_levels[m_currentLevelIndex - 1].m_briks.size())
		{
			m_currentLevelIndex = (m_currentLevelIndex % 4) + 1;
			ResetLevel();
			return;
		}
	}

	/* check for loss */
	if (m_pBall->m_position.y > m_height)
	{
		ResetLevel();
	}

	CheckCollision(*m_pBall.get(), *m_pPlayer.get());
}

bool Game::CheckCollision(const BallObject& ball, const GameObject& box)
{
	auto ballCenter = ball.m_position + ball.m_radius;

	auto halfBox = glm::vec2(box.m_size.x / 2, box.m_size.y / 2);

	auto boxCenter = glm::vec2(box.m_position.x + halfBox.x, box.m_position.y + halfBox.y);

	auto difference = ballCenter - boxCenter;

	auto clamped = glm::clamp(difference, -halfBox, halfBox);

	auto closestPoint = boxCenter + clamped;

	difference = closestPoint - ballCenter;

	if (glm::length(difference) < ball.m_radius)
	{
		auto directionCollision = GetDirectionCollision(difference);
	
		if (directionCollision == UP || directionCollision == DOWN)
		{
			m_pBall->m_velocity.y = -m_pBall->m_velocity.y;

			float penetration = m_pBall->m_radius - std::abs(difference.y);

			if (directionCollision == UP)
				m_pBall->m_position.y -= penetration-1; // Move ball back up
			else
				m_pBall->m_position.y += penetration+1; // Move ball back down
		}
		else
		{
			m_pBall->m_velocity.x = -m_pBall->m_velocity.x;

			float penetration = m_pBall->m_radius - std::abs(difference.x);

			if (directionCollision == LEFT)
				m_pBall->m_position.x -= penetration-1; // Move ball back up
			else
				m_pBall->m_position.x += penetration+1; // Move ball back down
		}
	}

	return glm::length(difference) < ball.m_radius;
}

Game::Direction Game::GetDirectionCollision(glm::vec2 difference)
{
	glm::vec2 normals[] = {
		glm::vec2(0.0f, 1.0f),	// up
		glm::vec2(1.0f, 0.0f),	// right
		glm::vec2(0.0f, -1.0f),	// down
		glm::vec2(-1.0f, 0.0f)	// left
	};

	float maxAngle = 0;
	int direction = 0;

	for (int i = 0; i < 4; i++)
	{
		float angle = glm::dot(normals[i], difference);

		if (angle < maxAngle)
			continue;

		maxAngle = angle;
		direction = i;
	}

	return (Direction)direction;
}

void Game::Render()
{
	if (m_state != Game::GAME_ACTIVE)
		return;

	auto& spriteRendererRef = *m_pSpriteRenderer.get();

	spriteRendererRef.VDraw(m_ressourceManager.GetTexture("background"),
		glm::vec2(0, 0), glm::vec2(m_width, m_height));

	m_levels[m_currentLevelIndex - 1].Draw(spriteRendererRef);

	m_pPlayer->VDraw(spriteRendererRef);
	m_pBall->VDraw(spriteRendererRef);
}
