#pragma once

class GameState;

#include "DriverState.h"
#include "Listener.h"
#include "Player.h"
#include "EnemyPool.h"
#include "BulletPool.h"
#include "ParticlePool.h"
#include "Camera.h"
#include "Background.h"
#include "Satellite.h"
#include "Level.h"
#include "HealthUi.h"
#include "TargetArrowUi.h"
#include "InfoTextUi.h"

class Game :
	public DriverState,
	public Listener
{
public:
	Game();
	~Game();

	void onEvent(const Event &ev) override;

	void updateOnKeyPress(sf::Keyboard::Key key) override;
	void updateOnKeyRelease(sf::Keyboard::Key key) override;
	void updateOnMouseMove(int mouseX, int mouseY) override;
	void updateOnMousePress(sf::Mouse::Button button) override;
	void updateOnMouseRelease(sf::Mouse::Button button) override;
	void update(float deltaTime) override;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
	friend class PlayGameState;
	friend class PausedGameState;
	friend class DeathGameState;

	enum class StateType : uint8_t
	{
		None,
		Play,
		Paused,
		Death
	};

	StateType stateType_;

	GameState *state_;

	Player player_;
	EnemyPool enemyPool_;
	BulletPool bulletPool_;
	ParticlePool particlePool_;
	Camera camera_;
	Background background_;

	Satellite station_;

	Level level_;

	HealthUi healthUi_;
	TargetArrowUi targetArrowUi_;
	InfoTextUi infoTextUi_;

	void updateCameraPosition_();
	void changeState_(const StateType &stateType);
};