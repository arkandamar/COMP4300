#pragma once

#include "Game.hpp"
#include "Vec2.hpp"
#include <fstream>
#include <iostream>
#include <random>
#include <chrono>

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
			m_bulletConfig.SR;

			fin >> temp;
			int coll_rad = utils::extractValue<int>(temp, "=");
			m_bulletConfig.CR;

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
			Vec2(m_playerConfig.S * cos(0), m_playerConfig.S * sin(0)),
			0.0f
		);

	player->cShape->circle.setPosition(player->cTransform->pos.x, player->cTransform->pos.y);

	player->cInput = std::make_shared<CInput>();

	m_player = player;
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
	enemy->cShape->circle.setOrigin(m_enemyConfig.SR, m_enemyConfig.SR);

	int posX = utils::random<int>(m_enemyConfig.SR, m_window.getSize().x - m_enemyConfig.SR);
	int posY = utils::random<int>(m_enemyConfig.SR, m_window.getSize().y - m_enemyConfig.SR);

	enemy->cTransform = std::make_shared<CTransform>
		(
			Vec2(posX, posY),
			Vec2(1, 1),
			0.0f
		);

	m_lastEnemySpawnTime = m_currentFrame;
}

void Game::run()
{
	while (m_running)
	{
		m_entities.update();

		if (!m_paused)
		{
			if (m_currentFrame - m_lastEnemySpawnTime >= m_enemyConfig.SF)
			{
				spawnEnemy();
			}

			sUserInput();
		}
		else {
			std::cout << "game is paused" << std::endl;
		}

		sRender();

		m_currentFrame++;
	}
}

void Game::sRender()
{
	m_window.clear();

	for (auto& e : m_entities.getEntities())
	{
		e->cShape->circle.setPosition(e->cTransform->pos.x, e->cTransform->pos.y);
		e->cTransform->angle += 1.0f;
		e->cShape->circle.setRotation(e->cTransform->angle);
		m_window.draw(e->cShape->circle);
	}
	m_window.draw(m_text);

	m_window.display();
}

void Game::sUserInput()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_running = false;
			m_window.close();
		}

		if (event.type == sf::Event::MouseButtonPressed)
		{
			std::cout << sf::Mouse::getPosition(m_window).x << " " << sf::Mouse::getPosition(m_window).y << std::endl;
		}

		if (event.type == sf::Event::KeyPressed)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			{
				setPaused(true);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				std::cout << "game return" << std::endl;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				std::cout << "using special ability" << std::endl;
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
	}
}