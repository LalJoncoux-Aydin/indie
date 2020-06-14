#ifndef ICHARACTER_HPP_
#define ICHARACTER_HPP_

// Standard libs
#include <iostream>
#include <cstring>
#include <vector>
#include <memory>
// Local libs
#include "Vector.hpp"
#include "cell.hpp"
#include "Bomb.hpp"
// Define

// Functions
class ICharacter
{
    public:
        virtual void die() = 0;
        virtual bool getIsIa() = 0;
        virtual bool isDead() = 0;
        virtual void powerUp(PowerUp power) = 0;
        virtual void move(std::vector<std::vector<cell_t>> map) = 0;
        virtual void move(orientation face) = 0;
        virtual Vector<unsigned int> getPos() = 0;
        virtual orientation getOrientation() = 0;
        virtual void goToPrevPos() = 0;
        virtual std::shared_ptr<Bomb> getBombs() = 0;
        virtual unsigned int getBombRadius() = 0;
        virtual unsigned int getSpeed() = 0;
        virtual void setIsIa(bool status) = 0;
        virtual void setPos(Vector<unsigned int> new_pos) = 0;
        virtual void setIsDead(bool status) = 0;
        virtual void setBombRadius(unsigned int value) = 0;
        virtual void setSpeed(unsigned int value) = 0;
};

// ENFANT
class Perso: public ICharacter
{
    public:
        Perso(Vector<unsigned int> pos, bool isIA) {
            _pos = pos;
            _isIa = isIA;
            _currentBombs = std::make_shared<Bomb>(_bombRadius);
        };

        // Getters
        bool getIsIa() {return _isIa;};
        bool isDead() {return _isDead;}
        unsigned int getBombRadius() { return _bombRadius; };
        unsigned int getSpeed() { return _speed; };
        Vector<unsigned int> getPos() { return _pos; };
        orientation getOrientation() { return _orientation; };
        std::shared_ptr<Bomb> getBombs() { return _currentBombs; };

        // Setters
        void die() {
            _isDead = true;
        };
        void goToPrevPos() {
            _pos = _prevPos;
        };
        void setIsIa(bool status) {
            _isIa = status;
        };
        void setPos(Vector<unsigned int> new_pos) {
            _pos = new_pos;
            _prevPos = new_pos;
        };
        void setIsDead(bool status) {
            _isDead = status;
        };
        void setBombRadius(unsigned int value) {
            _bombRadius = value;
        };
        void setSpeed(unsigned int value) {
            _speed = value;
        };

        void powerUp(PowerUp power){};
        void move(std::vector<std::vector<cell_t>> map){};
        void move(orientation face){};

        ~Perso() {};

        bool _isIa;
        Vector<unsigned int> _pos;
        bool _isDead = false;
        Vector<unsigned int> _prevPos;
        std::shared_ptr<Bomb> _currentBombs;
        orientation _orientation;
        unsigned int _bombRadius = 3;
        unsigned int _speed;
};

class Player: public Perso
{
  public:
    Player(Vector<unsigned int> pos, bool isIA);

    // getters
    unsigned int getSpeed() { return _speed; };
 //   void powerUp(PowerUp power);

    void move(orientation face);

    // setters

    ~Player() {};

    private:
        orientation _orientation;
        unsigned int _speed;
};

class IA: public Perso
 {
  public:
    IA(Vector<unsigned int> pos, bool isIA);

    // getters
    unsigned int getSpeed() { return _speed; };
    //  virtual void powerUp(PowerUp power);

    void move(std::vector<std::vector<cell_t>> map);
    ~IA(){}
  private:
        orientation _orientation;
        unsigned int _speed;
        int last_direction = 0;

};

#endif /* !ICHARACTER_HPP_ */
