#include "GameMusic.hpp"
#include <SFML/Audio.hpp>

GameMusic::GameMusic()
{
}

GameMusic::~GameMusic()
{
}

void GameMusic::setSound(const std::string &file)
{
    if (_sound.getBuffer())
        _sound.resetBuffer();
    if(!_buffer.loadFromFile(file)) {
        std::cerr << "Sound not found !" << file << std::endl;
        exit(84);
    }
    _sound.setBuffer(_buffer);
    _sound.play();
}

void GameMusic::setMusic(const std::string &file)
{
    if (!_music.openFromFile(file)) {
        std::cerr << "Music not found !" << file << std::endl;
        exit (84);
    }
    _music.play();
}

void GameMusic::playMusic()
{
    _music.play();
}

void GameMusic::pauseMusic()
{
    _music.pause();
}

void GameMusic::stopMusic()
{
    _music.stop();
}

void GameMusic::musicsetVolume(const unsigned int &volume)
{
    _music.setVolume(volume);
}

void GameMusic::musicsetLoop(const bool isloop)
{
    _music.setLoop(isloop);
}

void GameMusic::soundsetVolume(const unsigned int &volume)
{
    _sound.setVolume(volume);
}

void GameMusic::soundsetLoop(const bool isloop)
{
    _sound.setLoop(isloop);
}
