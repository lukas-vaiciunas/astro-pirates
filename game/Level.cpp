#include "Level.h"
#include "Event.h"
#include "Player.h"
#include "EnemyPool.h"
#include "Objective.h"
#include "Rng.h"
#include "EventQueue.h"
#include "AudioData.h"
#include "Config.h"

Level::Level(Player &player, EnemyPool &enemyPool) :
	Listener({ EventType::TargetDestroyed }),
	currentObjective_(nullptr),
	player_(player),
	enemyPool_(enemyPool),
	enemyData_("data/enemies.txt"),
	objectiveX_(0.0f),
	objectiveY_(0.0f),
	stage_(1)
{
	this->init_();
}

Level::~Level()
{
	delete currentObjective_;
}

void Level::onEvent(const Event &ev)
{
	if (ev.getType() == EventType::TargetDestroyed)
	{
		currentObjective_->update(static_cast<const EventTargetDestroyed &>(ev).getId());

		if (currentObjective_->isDone())
		{
			AudioData::getInstance().playSound(2);
			++stage_;

			this->init_();
		}
	}
}

bool Level::existsObjective() const
{
	return currentObjective_ != nullptr;
}

float Level::getObjectiveX() const
{
	return objectiveX_;
}

float Level::getObjectiveY() const
{
	return objectiveY_;
}

void Level::init_()
{
	this->generateNewObjective_();

	EventQueue::getInstance().send(new EventUpdateObjectiveUi());
}

void Level::generateNewObjective_()
{
	delete currentObjective_;

	if (stage_ % 3 == 0)
	{
		this->generateBossObjective_();
	}
	else
	{
		this->generateMinionObjective_();
	}
}

void Level::generateMinionObjective_()
{
	const float spawnOffset = 240.0f;
	const float enemyOffset = (Config::windowWidth / Config::worldScale + Config::windowHeight / Config::worldScale) * 0.2f;
	const float playerX = player_.getX();
	const float playerY = player_.getY();

	std::vector<std::pair<float, float>> possibleLocations = {
		{	playerX - spawnOffset,	playerY - spawnOffset	},
		{	playerX,				playerY - spawnOffset,	},
		{	playerX + spawnOffset,	playerY - spawnOffset	},
		{	playerX + spawnOffset,	playerY					},
		{	playerX + spawnOffset,	playerY + spawnOffset	},
		{	playerX,				playerY + spawnOffset	},
		{	playerX - spawnOffset,	playerY + spawnOffset	},
		{	playerX - spawnOffset,	playerY					}
	};

	std::mt19937 &eng = Rng::getInstance().getEng();
	std::uniform_int_distribution<size_t> possibleLocationsIndexDis(0, possibleLocations.size() - 1);

	std::pair<float, float> &selectedLocation = possibleLocations[possibleLocationsIndexDis(eng)];

	objectiveX_ = selectedLocation.first;
	objectiveY_ = selectedLocation.second;

	uint16_t minNumEnemies = 3 + stage_;
	uint16_t maxNumEnemies = minNumEnemies + stage_;

	std::uniform_int_distribution<uint16_t> numEnemiesDis(minNumEnemies, maxNumEnemies);
	std::uniform_real_distribution<float> enemyOffsetDis(-enemyOffset, enemyOffset);

	uint16_t numEnemies = numEnemiesDis(eng);

	for (uint16_t i = 0; i < numEnemies; ++i)
	{
		enemyPool_.add(enemyData_.clone(1, objectiveX_ + enemyOffsetDis(eng), objectiveY_ + enemyOffsetDis(eng)));
	}

	currentObjective_ = new Objective(
		{
			{ 1, numEnemies }
		});
}

void Level::generateBossObjective_()
{
	const float spawnOffset = 240.0f;
	const float bossOffset = (Config::windowWidth / Config::worldScale + Config::windowHeight / Config::worldScale) * 0.2f;
	const float playerX = player_.getX();
	const float playerY = player_.getY();

	std::vector<std::pair<float, float>> possibleLocations = {
		{	playerX - spawnOffset,	playerY - spawnOffset	},
		{	playerX,				playerY - spawnOffset,	},
		{	playerX + spawnOffset,	playerY - spawnOffset	},
		{	playerX + spawnOffset,	playerY					},
		{	playerX + spawnOffset,	playerY + spawnOffset	},
		{	playerX,				playerY + spawnOffset	},
		{	playerX - spawnOffset,	playerY + spawnOffset	},
		{	playerX - spawnOffset,	playerY					}
	};

	std::mt19937 &eng = Rng::getInstance().getEng();
	std::uniform_int_distribution<size_t> possibleLocationsIndexDis(0, possibleLocations.size() - 1);

	std::pair<float, float> &selectedLocation = possibleLocations[possibleLocationsIndexDis(eng)];

	objectiveX_ = selectedLocation.first;
	objectiveY_ = selectedLocation.second;

	std::uniform_real_distribution<float> bossOffsetDis(-bossOffset, bossOffset);

	uint16_t numBosses = static_cast<uint16_t>(stage_ / 3.0f);

	for (uint16_t i = 0; i < numBosses; ++i)
	{
		enemyPool_.add(enemyData_.clone(2, objectiveX_ + bossOffsetDis(eng), objectiveY_ + bossOffsetDis(eng)));
	}

	currentObjective_ = new Objective(
		{
			{ 2, numBosses }
		}
	);
}