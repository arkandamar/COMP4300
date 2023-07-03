#pragma once

#include "Game.hpp"
#include "Vec2.hpp"
#include <fstream>
#include <iostream>
#include <random>
#include <chrono>
#include <math.h>

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

	float rad(float deg)
	{
		return deg * (std::_Pi / 180);
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

			m_cd.setFont(m_font);
			m_cd.setCharacterSize(size);
			m_cd.setFillColor(sf::Color(rgb[0], rgb[1], rgb[2]));
			m_cd.setString("0");
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

			fin >> temp;
			int cooldown = utils::extractValue<int>(temp, "=");
			m_playerConfig.SP = cooldown;
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
	player->cScore = std::make_shared<CScore>(0);
	player->cCooldown = std::make_shared<CCooldown>(m_playerConfig.SP);

	// setting default properties
	player->cShape->circle.setOrigin(m_playerConfig.SR, m_playerConfig.SR);
	player->cShape->circle.setPosition(player->cTransform->pos.x, player->cTransform->pos.y);
	m_cd.setPosition(sf::Vector2f(m_window.getSize().x - m_window.getSize().x / 2, 0));

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

	float velX = utils::random<int>(m_enemyConfig.SMIN, m_enemyConfig.SMAX) * 1;
	float velY = utils::random<int>(m_enemyConfig.SMIN, m_enemyConfig.SMAX) * 1;

	enemy->cTransform = std::make_shared<CTransform>(Vec2(posX, posY), Vec2(velX, velY), 0.0f);
	enemy->cCollision = std::make_shared<CCollision>(m_enemyConfig.CR);

	// setting default properties
	enemy->cShape->circle.setOrigin(m_enemyConfig.SR, m_enemyConfig.SR);

	m_lastEnemySpawnTime = m_currentFrame;
}

void Game::spawnSmallEnemies(std::shared_ptr<Entity> enemy)
{
	// seperating angle between small enemies
	float sepAngle = (float) 360 / enemy->cShape->circle.getPointCount();
	for (int i = 1; i <= enemy->cShape->circle.getPointCount(); ++i)
	{
		std::shared_ptr<Entity> sEnemy =  m_entities.addEntity("Small Enemy");
		sEnemy->cShape = std::make_shared<CShape>
			(
				enemy->cShape->circle.getRadius() / 2,
				enemy->cShape->circle.getPointCount(),
				enemy->cShape->circle.getFillColor(),
				enemy->cShape->circle.getOutlineColor(),
				enemy->cShape->circle.getOutlineThickness()
			);

		float velX = cos(utils::rad(enemy->cTransform->angle + (sepAngle * i))) * 1;
		float velY = sin(utils::rad(enemy->cTransform->angle + (sepAngle * i))) * 1;
	
		sEnemy->cTransform = std::make_shared<CTransform>
			(
				enemy->cTransform->pos,
				Vec2(velX, velY),
				0.0f
			);
		sEnemy->cLifespan = std::make_shared<CLifespan>(m_enemyConfig.L);
		sEnemy->cCollision = std::make_shared<CCollision>(enemy->cShape->circle.getRadius() / 2);
	}
}

void Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity, const Vec2& mousePos)
{
	if (m_player->cCooldown->remaining <= 0)
	{
		std::shared_ptr<Entity> weapon = m_entities.addEntity("Special Bullet");

		weapon->cShape = std::make_shared<CShape>
			(
				m_bulletConfig.CR * 5, m_bulletConfig.V,
				sf::Color(100, 50, 90),
				sf::Color(125, 200, 110),
				m_bulletConfig.OT
			);

		float diffX = mousePos.x - entity->cTransform->pos.x;
		float diffY = mousePos.y - entity->cTransform->pos.y;
		float dist = sqrt(diffX * diffX + diffY * diffY);
		float angle = acosf(diffX / dist);

		weapon->cTransform = std::make_shared<CTransform>
			(
				Vec2(entity->cShape->circle.getPosition().x, entity->cShape->circle.getPosition().y),
				Vec2(diffX / dist * m_bulletConfig.S, diffY / dist * m_bulletConfig.S),
				angle
			);
		weapon->cCollision = std::make_shared<CCollision>(m_bulletConfig.CR * 5);
		weapon->cLifespan = std::make_shared<CLifespan>(m_bulletConfig.L * 5);

		// setting default properties
		weapon->cShape->circle.setOrigin(m_bulletConfig.SR, m_bulletConfig.SR);
		weapon->cShape->circle.setPosition(weapon->cTransform->pos.x, weapon->cTransform->pos.y);

		// set cooldown when fired
		m_player->cCooldown->remaining = m_player->cCooldown->total;
	}
}

void Game::run()
{
	while (m_running)
	{
		m_entities.update();

		if (!m_paused)
		{
			sCooldown();
			sCollision();
			sMovement();
			sEnemySpawner();
			sLifespan();
		}
		
		sUserInput();
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

void Game::sCooldown()
{
	float time = m_player->cCooldown->remaining / (float) 60;

	if (m_player->cCooldown->remaining >= 0)
	{
		m_player->cCooldown->remaining--;
	}

	if (time <= 0)
	{
		m_cd.setString("Special Weapon Ready");
	}
	else
	{
		m_cd.setString(std::to_string(time));
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
			e->cLifespan->remaining--;
		}
	}

	for (auto& e : m_entities.getEntities("Small Enemy"))
	{
		if (e->cLifespan->remaining <= 0)
		{
			e->destroy();
		}
		else
		{
			e->cLifespan->remaining--;
		}
	}

	for (auto& e : m_entities.getEntities("Special Bullet"))
	{
		if (e->cLifespan->remaining <= 0)
		{
			e->destroy();
		}
		else
		{
			e->cLifespan->remaining--;
		}
	}
}

void Game::sCollision()
{
	// if enemy collide with bullet
	for (auto& b : m_entities.getEntities("Bullet"))
	{
		for (auto& e : m_entities.getEntities("Enemy"))
		{
			float diffX = (b->cTransform->pos.x - e->cTransform->pos.x);
			float diffY = (b->cTransform->pos.y - e->cTransform->pos.y);
			float sumRad = (b->cCollision->radius + e->cCollision->radius);

			if (diffX * diffX + diffY * diffY <= sumRad * sumRad)
			{
				spawnSmallEnemies(e);
				e->destroy();
				b->destroy();
				m_player->cScore->score += 100;
			}
		}
	}

	// if enemy collide with player
	for (auto& e : m_entities.getEntities("Enemy"))
	{
		float diffX = (m_player->cTransform->pos.x - e->cTransform->pos.x);
		float diffY = (m_player->cTransform->pos.y - e->cTransform->pos.y);
		float sumRad = (m_player->cCollision->radius + e->cCollision->radius);

		if (diffX * diffX + diffY * diffY <= sumRad * sumRad)
		{
			e->destroy();
			m_player->cTransform->pos = Vec2(m_window.getSize().x / 2, m_window.getSize().y / 2);
			m_player->cScore->score = 0;
		}
	}

	// if small enemy collide with bullet
	for (auto& b : m_entities.getEntities("Bullet"))
	{
		for (auto& e : m_entities.getEntities("Small Enemy"))
		{
			float diffX = (b->cTransform->pos.x - e->cTransform->pos.x);
			float diffY = (b->cTransform->pos.y - e->cTransform->pos.y);
			float sumRad = (b->cCollision->radius + e->cCollision->radius);

			if (diffX * diffX + diffY * diffY <= sumRad * sumRad)
			{
				e->destroy();
				b->destroy();
				m_player->cScore->score += 200;
			}
		}
	}

	// if small enemy collide with player
	for (auto& e : m_entities.getEntities("Small Enemy"))
	{
		float diffX = (m_player->cTransform->pos.x - e->cTransform->pos.x);
		float diffY = (m_player->cTransform->pos.y - e->cTransform->pos.y);
		float sumRad = (m_player->cCollision->radius + e->cCollision->radius);

		if (diffX * diffX + diffY * diffY <= sumRad * sumRad)
		{
			e->destroy();
			m_player->cTransform->pos = Vec2(m_window.getSize().x / 2, m_window.getSize().y / 2);
			m_player->cScore->score = 0;
		}
	}

	// if special enemy collide with player
	for (auto& s : m_entities.getEntities("Special Bullet"))
	{
		for (auto& e : m_entities.getEntities("Small Enemy"))
		{
			float diffX = (s->cTransform->pos.x - e->cTransform->pos.x);
			float diffY = (s->cTransform->pos.y - e->cTransform->pos.y);
			float sumRad = (s->cCollision->radius + e->cCollision->radius);

			if (diffX * diffX + diffY * diffY <= sumRad * sumRad)
			{
				e->destroy();
				m_player->cScore->score += 200;
			}
		}

		for (auto& e : m_entities.getEntities("Enemy"))
		{
			float diffX = (s->cTransform->pos.x - e->cTransform->pos.x);
			float diffY = (s->cTransform->pos.y - e->cTransform->pos.y);
			float sumRad = (s->cCollision->radius + e->cCollision->radius);

			if (diffX * diffX + diffY * diffY <= sumRad * sumRad)
			{
				spawnSmallEnemies(e);
				e->destroy();
				m_player->cScore->score += 100;
			}
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
	m_text.setString(std::to_string(m_player->cScore->score));
	m_window.draw(m_cd);
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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			setPaused(false);
		}

		if (event.type == sf::Event::Closed)
		{
			m_running = false;
		}


		if (!m_paused) 
		{	
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (m_specialWeaponMode)
				{
					spawnSpecialWeapon(m_player, Vec2(sf::Mouse::getPosition(m_window).x, sf::Mouse::getPosition(m_window).y));
				}
				else
				{
					spawnBullet(m_player, Vec2(sf::Mouse::getPosition(m_window).x, sf::Mouse::getPosition(m_window).y));
				}
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
				{
					setPaused(true);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					m_specialWeaponMode ? m_specialWeaponMode = false : m_specialWeaponMode = true;
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
}