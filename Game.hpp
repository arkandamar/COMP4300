#pragma once

#include "EntityManager.hpp"
#include "Entity.hpp"

#include <SFML/Graphics.hpp>

struct PlayerConfig { int SR, CR, FR, FG, FB, OR, OG, OB, OT, V, SP; float S; };
struct EnemyConfig { int SR, CR, OR, OG, OB, OT, VMIN, VMAX, L, SF; float SMIN, SMAX; };
struct BulletConfig { int SR, CR, FR, FG, FB, OR, OG, OB, OT, V, L; float S; };

class Game
{
	sf::RenderWindow m_window;
	EntityManager m_entities;
	sf::Font m_font;
	sf::Text m_text;
	sf::Text m_cd;
	PlayerConfig m_playerConfig;
	EnemyConfig m_enemyConfig;
	BulletConfig m_bulletConfig;
	int m_score = 0;
	int m_currentFrame = 0;
	int m_lastEnemySpawnTime = 0;
	int m_lastUsedSpecialWeapon = 0;
	bool m_specialWeaponMode = false;
	bool m_paused = false; // whether game logic is updated
	bool m_running = true; // whether game is running
	
	std::shared_ptr<Entity> m_player;

	Game(std::string& filename);
	void init(const std::string& config); //initialize the game state
	void setPaused(bool paused);

	// system
	void sMovement();
	void sUserInput();
	void sLifespan();
	void sRender();
	void sEnemySpawner();
	void sCollision();
	void sCooldown();

	// spawner
	void spawnPlayer();
	void spawnEnemy();
	void spawnSmallEnemies(std::shared_ptr<Entity> entity);
	void spawnBullet(std::shared_ptr<Entity> entity, const Vec2& mousePos);
	void spawnSpecialWeapon(std::shared_ptr<Entity> entity, const Vec2& mousePos);

public:

	Game(const std::string& config);
	void run();
};