#pragma once

class Objective;
class Player;
class EnemyPool;

#include "EnemyData.h"
#include "Listener.h"

class Level : public Listener
{
public:
	Level(Player &player, EnemyPool &enemyPool);
	~Level();

	void onEvent(const Event &ev) override;

	bool existsObjective() const;
	float getObjectiveX() const;
	float getObjectiveY() const;
private:
	Objective *currentObjective_;

	Player &player_;
	EnemyPool &enemyPool_;

	EnemyData enemyData_;

	float objectiveX_;
	float objectiveY_;

	uint16_t stage_;

	void init_();
	void generateNewObjective_();
	void generateMinionObjective_();
	void generateBossObjective_();
};