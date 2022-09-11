#pragma once

class Enemy;

#include <unordered_map>
#include <string>

class EnemyData
{
public:
	EnemyData(const std::string &filePath);
	~EnemyData();

	Enemy *clone(uint16_t id, float x, float y) const;
private:
	std::unordered_map<uint16_t, Enemy *> enemyMap_;

	void load_(const std::string &filePath);
};