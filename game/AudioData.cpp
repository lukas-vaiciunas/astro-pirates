#include "AudioData.h"
#include <fstream>

AudioData::AudioData() :
	soundBuffers_(),
	musicPaths_(),
	sounds_(8, sf::Sound()),
	music_(),
	currentMusicId_(0)
{
	this->loadSoundBuffers_("data/sound-effects.txt");
	this->loadMusicPaths_("data/music.txt");
}

AudioData &AudioData::getInstance()
{
	static AudioData instance;
	return instance;
}

void AudioData::playSound(uint16_t id)
{
	for (sf::Sound &sound : sounds_)
	{
		if (sound.getStatus() == sf::SoundSource::Status::Stopped)
		{
			sound.setBuffer(soundBuffers_[id]);
			sound.play();
			break;
		}
	}
}

void AudioData::playMusic(uint16_t id)
{
	if (currentMusicId_ == id) return;

	this->stopMusic();
	music_.openFromFile(musicPaths_[id]);
	music_.setLoop(true);
	music_.setVolume(25);
	music_.play();

	currentMusicId_ = id;
}

void AudioData::stopMusic()
{
	music_.stop();
}

void AudioData::loadSoundBuffers_(const std::string &dataPath)
{
	std::ifstream in(dataPath, std::ios_base::in);

	if (!in.is_open())
	{
		printf("Failed to open %s in SoundData!", dataPath.c_str());
		return;
	}

	uint16_t numSoundBuffers;
	uint16_t id;
	std::string path;

	in >> numSoundBuffers;

	while (numSoundBuffers--)
	{
		in >> id >> path;

		sf::SoundBuffer soundBuffer;

		soundBuffer.loadFromFile(path);

		soundBuffers_.emplace(static_cast<uint16_t>(id), std::move(soundBuffer));
	}

	in.close();
}

void AudioData::loadMusicPaths_(const std::string &dataPath)
{
	std::ifstream in(dataPath, std::ios_base::in);

	if (!in.is_open())
	{
		printf("Failed to open %s in SoundData!", dataPath.c_str());
		return;
	}

	uint16_t numMusicTracks;
	uint16_t id;
	std::string path;

	in >> numMusicTracks;

	while (numMusicTracks--)
	{
		in >> id >> path;

		musicPaths_.emplace(static_cast<uint16_t>(id), path);
	}

	in.close();
}