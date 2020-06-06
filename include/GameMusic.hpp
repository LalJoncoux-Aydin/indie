#ifndef GAMEMUSIC_HH_
#define GAMEMUSIC_HH_

#include <SFML/Audio.hpp>
#include <iostream>

class GameMusic {
    public:
    GameMusic();
    ~GameMusic();
    void setSound(const std::string &file);
    void setMusic(const std::string &file);
    void playMusic();
    void pauseMusic();
    void stopMusic();
    void musicsetVolume(const unsigned int &volume);
    void musicsetLoop(const bool isloop);
    void soundsetVolume(const unsigned int &volume);
    void soundsetLoop(const bool isloop);

    protected:
    sf::Music _music;
    sf::Sound _sound;
    sf::SoundBuffer _buffer;
};

#endif
