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
        virtual void move(orientation face) = 0;
        virtual Vector<unsigned int> getPos() = 0;
        virtual orientation getOrientation() = 0;
        virtual void goToPrevPos() = 0;
        virtual std::shared_ptr<Bomb> getBombs() = 0;
};

// ENFANT
class Perso: public ICharacter
{
    public:
        Perso(Vector<unsigned int> pos, bool isIA) {
            _pos = pos;
            _isIa = isIA;
            _currentBombs = std::make_shared<Bomb>();
        };

        // Getters
        bool getIsIa() {return _isIa;};
        bool isDead() {return _isDead;}
        void powerUp(PowerUp power){};
        void move(orientation face){};
        unsigned int getMaxBombs() { return _maxBombs; };
        Vector<unsigned int> getPos() { return _pos; };
        orientation getOrientation() {
            return _orientation;
        };
        void goToPrevPos() {
            _pos = _prevPos;
        };
        std::shared_ptr<Bomb> getBombs() {
            return _currentBombs;
        };

        // Setters
        void die() {
            _isDead = true;
        };

        ~Perso() {};


        unsigned int _maxBombs;
        bool _isIa;
         Vector<unsigned int> _pos;
        bool _isDead = false;
        Vector<unsigned int> _prevPos;
        std::shared_ptr<Bomb> _currentBombs;
        orientation _orientation;
        unsigned int _bombRadius;
};

class Player: public Perso
{
  public:
    Player(Vector<unsigned int> pos, bool isIA);

    // getters
    unsigned int getMaxBombs() { return _maxBombs; };
    unsigned int getBombRadius() { return _bombRadius; };
    unsigned int getSpeed() { return _speed; };
    void powerUp(PowerUp power);

    void move(orientation face);

    // setters

    ~Player() {};

    private:
        orientation _orientation;
        unsigned int _maxBombs;
        unsigned int _speed;
};

class IA: public Perso
 {
  public:
    IA(Vector<unsigned int> pos, bool isIA);
    //  virtual void powerUp(PowerUp power) = 0;
    void move(orientation face);
    ~IA(){}
  private:
    orientation _orientation;

};

#endif /* !ICHARACTER_HPP_ */
