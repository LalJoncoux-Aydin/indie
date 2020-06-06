/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Vector
*/

#ifndef VECTOR_HPP_
#define VECTOR_HPP_

template <typename T>
class Vector {
    public:
        Vector() { x = 0; y = 0; }
        Vector(T a, T b) : x(a), y(b) {}
        Vector(const Vector<T> &v) : x(v.x), y(v.y) {}
        ~Vector() {}

        Vector<T> operator+(Vector<T> a) {
            return Vector(x + a.x, y + a.y);
        };
        Vector<T> operator=(Vector<T> b) {
            x = b.x;
            y = b.y;
            return Vector(x, y);
        };

        T x;
        T y;
    private:
};

#endif /* !VECTOR_HPP_ */
