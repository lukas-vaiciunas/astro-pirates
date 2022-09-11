#pragma once

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/Music.hpp>
#include <unordered_map>

class AudioData
{
public:
	AudioData(const AudioData &) = delete;
	AudioData &operator=(const AudioData &) = delete;

	static AudioData &getInstance();

	void playSound(uint16_t id);
	void playMusic(uint16_t id);
	void stopMusic();
private:
	AudioData();
	~AudioData() {}

	std::unordered_map<uint16_t, sf::SoundBuffer> soundBuffers_;
	std::unordered_map<uint16_t, std::string> musicPaths_;
	std::vector<sf::Sound> sounds_;
	sf::Music music_;

	uint16_t currentMusicId_;

	void loadSoundBuffers_(const std::string &dataPath);
	void loadMusicPaths_(const std::string &dataPath);
};