#pragma once

#include "Game.hpp"
#include "Vec2.hpp"
#include <fstream>
#include <iostream>
#include <random>
#include <chrono>
#include <string>

using std::cout;
using std::endl;

namespace utils {
	void tokenize(std::vector<int>& vector, const std::string& s, const std::string& del = " ")
	{
		int start, end = -1 * del.size();
		do {
			start = end + del.size();
			end = s.find(del, start);
			vector.push_back(stoi(s.substr(start, end - start)));
		} while (end != -1);
	}

	template<typename T>
	T extractValue(const std::string& s, const std::string& del)
	{
		int del_pos = s.find(del);
		return stoi(s.substr(del_pos + del.size(), s.size() - del_pos));
	}

	std::string extractValueStr(const std::string& s, const std::string& del)
	{
		int del_pos = s.find(del);
		return s.substr(del_pos + del.size(), s.size() - del_pos);
	}

	std::vector<int> extractRGB(const std::string& s)
	{
		std::vector<int> result;
		int start = s.find("(") + 1;
		int end = s.find(")") - start;
		std::string values = s.substr(start, end);
		tokenize(result, values, ",");
		return result;
	}

	template<typename T>
	T random(T min, T max) {
		// Use a seed based on current time
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		static std::default_random_engine generator(seed);

		// Create a distribution
		std::uniform_int_distribution<T> distribution(min, max);

		// Generate a random number
		static T previous = distribution(generator);
		T current = distribution(generator);

		// Ensure the new number is different from the previous one
		while (current == previous) {
			current = distribution(generator);
		}
		previous = current;
		return current;
	}
}

Game::Game(const std::string& config)
{
	init(config);
}

void Game::init(const std::string& path)
{
	std::ifstream fin(path);
	std::string temp;

	while (!fin.eof())
	{
		fin >> temp;

		if (temp == "Window")
		{
			fin >> temp;
			int width = utils::extractValue<int>(temp, "=");

			fin >> temp;
			int height = utils::extractValue<int>(temp, "=");

			fin >> temp;
			int frame = utils::extractValue<int>(temp, "=");

			fin >> temp;
			int fullscreen = utils::extractValue<int>(temp, "=");

			if (fullscreen)
			{
				m_window.create(sf::VideoMode(width, height), "Geometry Warefare", sf::Style::Fullscreen);
			}
			else {
				m_window.create(sf::VideoMode(width, height), "Geometry Warfare");
			}
			m_window.setFramerateLimit(frame);
		}

		if (temp == "Font")
		{
			fin >> temp;
			std::string name = utils::extractValueStr(temp, "=");

			fin >> temp;
			int size = utils::extractValue<int>(temp, "=");

			fin >> temp;
			std::vector<int> rgb = utils::extractRGB(temp);
		
			if (!m_font.loadFromFile(name)) {
				std::cout << "Font Error onload!" << std::endl;
			}
			m_text.setFont(m_font);
			m_text.setCharacterSize(size);
			m_text.setFillColor(sf::Color(rgb[0], rgb[1], rgb[2]));
			m_text.setString("0");
		}

		if (temp == "Player")
		{
			fin >> temp;
			int radius = utils::extractValue<int>(temp, "=");
			m_playerConfig.SR = radius;

			fin >> temp;
			int coll_rad = utils::extractValue<int>(temp, "=");
			m_playerConfig.CR = coll_rad;

			fin >> temp;
			int speed = utils::extractValue<int>(temp, "=");
			m_playerConfig.S = speed;

			fin >> temp;
			std::vector<int> fill_rgb = utils::extractRGB(temp);
			m_playerConfig.FR = fill_rgb[0];
			m_playerConfig.FG = fill_rgb[1];
			m_playerConfig.FB = fill_rgb[2];

			fin >> temp;
			std::vector<int> out_rgb = utils::extractRGB(temp);
			m_playerConfig.OR = out_rgb[0];
			m_playerConfig.OG = out_rgb[1];
			m_playerConfig.OB = out_rgb[2];

			fin >> temp;
			int thickness = utils::extractValue<int>(temp, "=");
			m_playerConfig.OT = thickness;

			fin >> temp;
			int vert = utils::extractValue<int>(temp, "=");
			m_playerConfig.V = vert;
		}

		if (temp == "Enemy")
		{
			fin >> temp;
			int radius = utils::extractValue<int>(temp, "=");
			m_enemyConfig.SR = radius;

			fin >> temp;
			int coll_rad = utils::extractValue<int>(temp, "=");
			m_enemyConfig.CR = coll_rad;

			fin >> temp;
			float speed_min = utils::extractValue<float>(temp, "=");
			m_enemyConfig.SMIN = speed_min;

			fin >> temp;
			float speed_max = utils::extractValue<float>(temp, "=");
			m_enemyConfig.SMAX = speed_max;

			fin >> temp;
			std::vector<int> out_rgb = utils::extractRGB(temp);
			m_enemyConfig.OR = out_rgb[0];
			m_enemyConfig.OG = out_rgb[1];
			m_enemyConfig.OB = out_rgb[2];

			fin >> temp;
			int thickness = utils::extractValue<int>(temp, "=");
			m_enemyConfig.OT = thickness;

			fin >> temp;
			int vert_min = utils::extractValue<int>(temp, "=");
			m_enemyConfig.VMIN = vert_min;

			fin >> temp;
			int vert_max = utils::extractValue<int>(temp, "=");
			m_enemyConfig.VMAX = vert_max;

			fin >> temp;
			int lifespan = utils::extractValue<int>(temp, "=");
			m_enemyConfig.L = lifespan;

			fin >> temp;
			int spawn = utils::extractValue<int>(temp, "=");
			m_enemyConfig.SF = spawn;
		}

		if (temp == "Bullet")
		{
			fin >> temp;
			int radius = utils::extractValue<int>(temp, "=");
			m_bulletConfig.SR = radius;

			fin >> temp;
			int coll_rad = utils::extractValue<int>(temp, "=");
			m_bulletConfig.CR = coll_rad;

			fin >> temp;
			float speed = utils::extractValue<float>(temp, "=");
			m_bulletConfig.S = speed;

			fin >> temp;
			std::vector<int> fill_rgb = utils::extractRGB(temp);
			m_bulletConfig.FR = fill_rgb[0];
			m_bulletConfig.FG = fill_rgb[1];
			m_bulletConfig.FB = fill_rgb[2];

			fin >> temp;
			std::vector<int> out_rgb = utils::extractRGB(temp);
			m_bulletConfig.OR = out_rgb[0];
			m_bulletConfig.OG = out_rgb[1];
			m_bulletConfig.OB = out_rgb[2];

			fin >> temp;
			int thickness = utils::extractValue<int>(temp, "=");
			m_bulletConfig.OT = thickness;

			fin >> temp;
			int vert = utils::extractValue<int>(temp, "=");
			m_bulletConfig.V = vert;

			fin >> temp;
			int lifespan = utils::extractValue<int>(temp, "=");
			m_bulletConfig.L = lifespan;
		}
	}

	spawnPlayer();
}

void Game::setPaused(bool paused)
{
	m_paused = paused;
}

void Game::spawnPlayer()
{
	std::shared_ptr<Entity> player = m_entities.addEntity("Player");

	player->cShape = std::make_shared<CShape>
		(
			m_playerConfig.SR, m_playerConfig.V, 
			sf::Color(m_playerConfig.FR, m_playerConfig.FG, m_playerConfig.FB), 
			sf::Color(m_playerConfig.OR, m_playerConfig.OG, m_playerConfig.OB), 
			m_playerConfig.OT
		);
	player->cTransform = std::make_shared<CTransform>
		(
			Vec2(m_window.getSize().x / 2, m_window.getSize().y / 2),
			Vec2(0, 0),
			0.0f
		);
	player->cInput = std::make_shared<CInput>();
	player->cCollision = std::make_shared<CCollision>(m_playerConfig.CR);

	// setting default properties
	player->cShape->circle.setOrigin(m_playerConfig.SR, m_playerConfig.SR);
	player->cShape->circle.setPosition(player->cTransform->pos.x, player->cTransform->pos.y);

	m_player = player;
}

void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vec2& mousePos)
{
	std::shared_ptr<Entity> bullet = m_entities.addEntity("Bullet");

	bullet->cShape = std::make_shared<CShape>
		(
			m_bulletConfig.SR, m_bulletConfig.V,
			sf::Color(m_bulletConfig.FR, m_bulletConfig.FG, m_bulletConfig.FB),
			sf::Color(m_bulletConfig.OR, m_bulletConfig.OG, m_bulletConfig.OB),
			m_bulletConfig.OT
		);

	float diffX = mousePos.x - entity->cTransform->pos.x;
	float diffY = mousePos.y - entity->cTransform->pos.y;
	float dist = sqrt(diffX * diffX + diffY * diffY);
	float angle = acosf(diffX / dist);

	bullet->cTransform = std::make_shared<CTransform>
		(
			Vec2(entity->cShape->circle.getPosition().x, entity->cShape->circle.getPosition().y),
			Vec2(diffX / dist * m_bulletConfig.S, diffY / dist * m_bulletConfig.S),
			angle
		);
	bullet->cLifespan = std::make_shared<CLifespan>(m_bulletConfig.L);
	bullet->cCollision = std::make_shared<CCollision>(m_bulletConfig.CR);

	// setting default properties
	bullet->cShape->circle.setOrigin(m_bulletConfig.SR, m_bulletConfig.SR);
	bullet->cShape->circle.setPosition(bullet->cTransform->pos.x, bullet->cTransform->pos.y);
}

void Game::spawnEnemy()
{
	std::shared_ptr<Entity> enemy = m_entities.addEntity("Enemy");

	enemy->cShape = std::make_shared<CShape>
		(
			m_enemyConfig.SR, utils::random<int>(m_enemyConfig.VMIN, m_enemyConfig.VMAX),
			sf::Color(0, 0, 0, 0), sf::Color(m_enemyConfig.OR, m_enemyConfig.OG, m_enemyConfig.OB),
			m_enemyConfig.OT
		);
	int posX = utils::random<int>(m_enemyConfig.SR, m_window.getSize().x - m_enemyConfig.SR);
	int posY = utils::random<int>(m_enemyConfig.SR, m_window.getSize().y - m_enemyConfig.SR);

	/*float velX = utils::random<int>(m_enemyConfig.SMIN, m_enemyConfig.SMAX) * cos(0);
	float velY = utils::random<int>(m_enemyConfig.SMIN, m_enemyConfig.SMAX) * sin(0);*/

	enemy->cTransform = std::make_shared<CTransform>(Vec2(posX, posY), Vec2(1.0f, 1.0f), 0.0f);
	enemy->cCollision = std::make_shared<CCollision>(m_enemyConfig.CR);

	// setting default properties
	enemy->cShape->circle.setOrigin(m_enemyConfig.SR, m_enemyConfig.SR);

	m_lastEnemySpawnTime = m_currentFrame;
}

void Game::spawnSmallEnemies(std::shared_ptr<Entity> enemy)
{

}

void Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity)
{
	if (m_currentFrame - m_lastUsedSpecialWeapon >= 300)
	{
		m_lastUsedSpecialWeapon = m_currentFrame;
	}
}

void Game::run()
{
	while (m_running)
	{
		m_entities.update();

		if (!m_paused)
		{
			sCollision();
			sMovement();
			sEnemySpawner();
			sLifespan();
			sUserInput();
		}
		else {
			std::cout << "game is paused" << std::endl;
		}
		sRender();
		m_currentFrame++;
	}
}

void Game::sEnemySpawner()
{
	if (m_currentFrame - m_lastEnemySpawnTime >= m_enemyConfig.SF)
	{
		spawnEnemy();
	}
}

void Game::sLifespan()
{
	for (auto& e : m_entities.getEntities("Bullet"))
	{
		if (e->cLifespan->remaining <= 0)
		{
			e->destroy();
		}
		else
		{
			e->cLifespan->remaining -= 1;
		}
	}
}

void Game::sCollision()
{
	for (auto& b : m_entities.getEntities("Bullet"))
	{
		for (auto& e : m_entities.getEntities("Enemy"))
		{
			float diffX = (b->cTransform->pos.x - e->cTransform->pos.x);
			float diffY = (b->cTransform->pos.y - e->cTransform->pos.y);
			float sumRad = (b->cCollision->radius + e->cCollision->radius);

			if (diffX * diffX + diffY * diffY <= sumRad * sumRad)
			{
				e->destroy();
				b->destroy();
				spawnSmallEnemies(e);
			}
		}
	}

	for (auto& e : m_entities.getEntities("Enemy"))
	{
		float diffX = (m_player->cTransform->pos.x - e->cTransform->pos.x);
		float diffY = (m_player->cTransform->pos.y - e->cTransform->pos.y);
		float sumRad = (m_player->cCollision->radius + e->cCollision->radius);

		if (diffX * diffX + diffY * diffY <= sumRad * sumRad)
		{
			e->destroy();
			m_player->cTransform->pos = Vec2(m_window.getSize().x / 2, m_window.getSize().y / 2);
		}
	}
}

void Game::sRender()
{
	m_window.clear();

	for (auto& e : m_entities.getEntities())
	{
		e->cShape->circle.setPosition(e->cTransform->pos.x, e->cTransform->pos.y);
		e->cShape->circle.setRotation(e->cTransform->angle);
		m_window.draw(e->cShape->circle);
	}
	m_window.draw(m_text);

	m_window.display();
}


void Game::sMovement()
{
	for (auto& e : m_entities.getEntities())
	{
		if (e->cShape->circle.getPosition().x - e->cShape->circle.getRadius() <= 0)
		{
			e->cTransform->velocity.x *= -1;
		}
		if (e->cShape->circle.getPosition().y - e->cShape->circle.getRadius() <= 0)
		{
			e->cTransform->velocity.y *= -1;
		}
		if (e->cShape->circle.getPosition().x + e->cShape->circle.getRadius() >= m_window.getSize().x)
		{
			e->cTransform->velocity.x *= -1;
		}
		if (e->cShape->circle.getPosition().y + e->cShape->circle.getRadius() >= m_window.getSize().y)
		{
			e->cTransform->velocity.y *= -1;
		}

		e->cTransform->angle += 1.0f;

		e->cShape->circle.setPosition
		(
			e->cTransform->pos.x += e->cTransform->velocity.x,
			e->cTransform->pos.y += e->cTransform->velocity.y
		);
	}

	// player movement
	if (m_player->cInput->down && m_player->cTransform->pos.y + m_player->cShape->circle.getRadius() + 
		m_player->cShape->circle.getOutlineThickness() <= m_window.getSize().y)
	{
		m_player->cTransform->pos.y += m_playerConfig.S;
	}
	
	if (m_player->cInput->up && m_player->cTransform->pos.y - m_player->cShape->circle.getRadius() -
		m_player->cShape->circle.getOutlineThickness() >= 0)
	{
		m_player->cTransform->pos.y -= m_playerConfig.S;
	}
	
	if (m_player->cInput->right && m_player->cTransform->pos.x + m_player->cShape->circle.getRadius() +
		m_player->cShape->circle.getOutlineThickness() <= m_window.getSize().x)
	{
		m_player->cTransform->pos.x += m_playerConfig.S;
	}
	
	if (m_player->cInput->left && m_player->cTransform->pos.x - m_player->cShape->circle.getRadius() -
		m_player->cShape->circle.getOutlineThickness() >= 0)
	{
		m_player->cTransform->pos.x -= m_playerConfig.S;
	}
}

void Game::sUserInput()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_running = false;
		}

		if (event.type == sf::Event::MouseButtonPressed)
		{
			spawnBullet(m_player, Vec2(sf::Mouse::getPosition(m_window).x, sf::Mouse::getPosition(m_window).y));
		}

		if (event.type == sf::Event::KeyPressed)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			{
				setPaused(true);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				setPaused(false);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				spawnSpecialWeapon(m_player);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				m_player->cInput->left = true;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				m_player->cInput->up = true;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				m_player->cInput->down = true;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				m_player->cInput->right = true;
			}
		}

		if (event.type == sf::Event::KeyReleased)
		{
			if (event.key.code == sf::Keyboard::A)
			{
				m_player->cInput->left = false;
			}
			if (event.key.code == sf::Keyboard::W)
			{
				m_player->cInput->up = false;
			}
			if (event.key.code == sf::Keyboard::S)
			{
				m_player->cInput->down = false;
			}
			if (event.key.code == sf::Keyboard::D)
			{
				m_player->cInput->right = false;
			}
		}
	}
}