#ifndef ICHARACTER_HPP_
#define ICHARACTER_HPP_

// Standard libs
#include <iostream>
#include <cstring>
#include <vector>
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
        virtual bool dropBomb() = 0;
        virtual Vector<unsigned int> getPos() = 0;
        virtual orientation getOrientation() = 0;
        virtual void goToPrevPos() = 0;
        virtual std::vector<Bomb*> getBombs() = 0;

        virtual void deleteBomb(int index) = 0;
};

// ENFANT
class Perso: public ICharacter
{
    public:
        Perso(Vector<unsigned int> pos, bool isIA) {
            _pos = pos;
            _isIa = isIA;
        };

        void die() {
            _isDead = true;
        };
        // Getters
        bool getIsIa() {return _isIa;};
        bool isDead() {return _isDead;}
        void powerUp(PowerUp power){};
        void move(orientation face){};
        bool dropBomb(){
            if (_maxBombs > _currentBombs.size()) {
                std::cout << "yea" << std::endl;
        //      Bomb &new_bomb(_bombRadius, _pos);
                _currentBombs.push_back(new Bomb(_bombRadius, _pos));
                std::cout << _currentBombs[0]->getTimeBeforeExplosion() << std::endl;
                return (true);
            }
            return (false);
        };
        unsigned int getMaxBombs() { return _maxBombs; };
        Vector<unsigned int> getPos() { return _pos; };
        orientation getOrientation() {
            return _orientation;
        };
        void goToPrevPos() {
            _pos = _prevPos;
        };
        std::vector<Bomb*> getBombs() {
            return _currentBombs;
        };
        void deleteBomb(int index) {};

        ~Perso() {};


        unsigned int _maxBombs;


        bool _isIa;
         Vector<unsigned int> _pos;
        bool _isDead = false;
//        Vector<unsigned int> _pos;
        Vector<unsigned int> _prevPos;
        std::vector<Bomb*> _currentBombs;
        orientation _orientation;
        unsigned int _bombRadius;



    protected:
       // bool _isIa;
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
    bool dropBomb();

    // setters

    ~Player() {};

    private:
        //std::vector<Bomb*> _currentBombs;
        orientation _orientation;
        unsigned int _maxBombs;
        //unsigned int _bombRadius;
        unsigned int _speed;
};

class IA: public Perso
 {
  public:
    IA(Vector<unsigned int> pos, bool isIA);
    //  virtual void powerUp(PowerUp power) = 0;
    void move(orientation face);
    bool dropBomb() ;
    ~IA(){}
    private:
    orientation _orientation;
    //unsigned int _bombRadius;

};

#endif /* !ICHARACTER_HPP_ */
