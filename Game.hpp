#include <SFML/Graphics.hpp>
#include "EntityManager.hpp"

#pragma once
class Game
{
	sf::RenderWindow m_window;
	EntityManager m_entities;
	Entity m_player;
	bool m_pause;
	bool m_running;

public:
	void init();
	void update();

	// system
	void sMovement(std::vector<Entity>& entities);
	void sUserInput();
	void sRender(std::vector<Entity>& entities());
	void sEnemySpawner();
	void sCollision();
};