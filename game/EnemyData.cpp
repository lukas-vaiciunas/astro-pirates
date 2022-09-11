#include "EnemyData.h"
#include "TextureData.h"
#include "Minion.h"
#include "Boss.h"
#include <fstream>

EnemyData::EnemyData(const std::string &filePath) :
	enemyMap_()
{
	this->load_(filePath);
}

EnemyData::~EnemyData()
{
	for (auto it = enemyMap_.begin(); it != enemyMap_.end(); ++it)
	{
		delete it->second;
	}
}

Enemy *EnemyData::clone(uint16_t id, float x, float y) const
{
	return enemyMap_.at(id)->clone(x, y);
}

void EnemyData::load_(const std::string &filePath)
{
	std::ifstream in(filePath, std::ios_base::in);

	if (!in.is_open())
	{
		printf("Failed to open \"%s\" in EnemyData!\n", filePath.c_str());
		return;
	}

	uint16_t numEnemies;
	in >> numEnemies;

	for (uint16_t i = 0; i < numEnemies; ++i)
	{
		uint16_t id;
		std::string type;
		
		in >> id >> type;

		if (type == "minion")
		{
			float speed;
			float maxHealth;
			float distanceIdle;
			float distanceApproach;
			float distanceStationary;
			float distanceRetreat;
			float shootingCooldownSecs;
			uint16_t textureId;

			in >> speed
				>> maxHealth
				>> distanceIdle
				>> distanceApproach
				>> distanceStationary
				>> distanceRetreat
				>> shootingCooldownSecs
				>> textureId;

			enemyMap_.emplace(
				id,
				new Minion(
					id,
					0.0f, 0.0f,
					speed,
					maxHealth,
					distanceIdle, distanceApproach, distanceStationary, distanceRetreat,
					shootingCooldownSecs,
					TextureData::getInstance().getTexture(textureId)));
		}
		else if (type == "boss")
		{
			float maxHealth;
			float distanceAggro;
			float shootingCooldownSecs;
			float phaseDurationSecs;
			uint16_t textureId;

			in >> maxHealth
				>> distanceAggro
				>> shootingCooldownSecs
				>> phaseDurationSecs
				>> textureId;

			enemyMap_.emplace(
				id,
				new Boss(
					id,
					0.0f, 0.0f,
					maxHealth,
					distanceAggro,
					shootingCooldownSecs,
					phaseDurationSecs,
					TextureData::getInstance().getTexture(textureId)));
		}
	}

	in.close();
}