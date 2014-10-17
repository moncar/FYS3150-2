# pragma once
# ifndef __VEC3_H_INCLUDED__
# define __VEC3_H_INCLUDED__
# include <iostream>

using namespace std;

class vec3 {

    private:
        double m_vec[3];

    public:

        vec3(); // Constructor for empty vector.
        vec3(double x, double y, double z);
        bool operator==(vec3 &rhs);
        vec3 operator+(vec3 &rhs);
        vec3 operator-(vec3 &rhs);
        vec3 operator+(double scalar);
        vec3 operator-(double scalar);
        vec3 operator*(double scalar);
        vec3 operator/(double scalar);
        vec3 cross(vec3 &rhs);
        double dot(vec3 &rhs);
        double norm();
        void set(double x, double y, double z);
        inline double x() const {return m_vec[0];}
        inline double y() const {return m_vec[1];}
        inline double z() const {return m_vec[2];}
        inline double &operator[](int index) {return m_vec[index];}
        inline double operator[](int index) const {return m_vec[index];}

    private:
        friend ostream& operator<<(ostream &stream, vec3 &vec);
};

# endif // VEC3_H
