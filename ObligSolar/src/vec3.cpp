# include <cmath>
# include "vec3.h"

using namespace std;

// Constructor creating vector containing zeros.
vec3::vec3() {

    set(0, 0, 0);

}

// Constructor creating vector from desired parameters.
vec3::vec3(double x, double y, double z) {

    set(x, y, z);

}

bool vec3::operator==(vec3 &rhs) {

    return (m_vec[0] == rhs.x() && m_vec[1] == rhs.y() && m_vec[2] == rhs.z());

}

vec3 vec3::operator+(vec3 &rhs) {

    return vec3(m_vec[0] + rhs.x(),
                m_vec[1] + rhs.y(),
                m_vec[2] + rhs.z());

}

vec3 vec3::operator-(vec3 &rhs) {

    return vec3(m_vec[0] - rhs.x(),
                m_vec[1] - rhs.y(),
                m_vec[2] - rhs.z());

}

vec3 vec3::operator+(double scalar) {

    return vec3(m_vec[0] + scalar,
                m_vec[1] + scalar,
                m_vec[2] + scalar);

}

vec3 vec3::operator-(double scalar) {

    return vec3(m_vec[0] - scalar,
                m_vec[1] - scalar,
                m_vec[2] - scalar);

}

vec3 vec3::operator*(double scalar) {

    return vec3(m_vec[0] * scalar,
                m_vec[1] * scalar,
                m_vec[2] * scalar);

}

vec3 vec3::operator/(double scalar) {

    return vec3(m_vec[0] / scalar,
                m_vec[1] / scalar,
                m_vec[2] / scalar);

}

vec3 vec3::cross(vec3 &rhs) {

    return vec3(m_vec[1] * rhs.z() - m_vec[2] * rhs.y(),
                - (m_vec[0] * rhs.z() - m_vec[2] * rhs.x()),
                m_vec[0]*rhs.y() - m_vec[1]*rhs.x());

}

double vec3::dot(vec3 &rhs) {

    return m_vec[0] * rhs.x() + m_vec[1] * rhs.y() + m_vec[2] * rhs.z();

}

double vec3::norm() {

    return sqrt(m_vec[0] * m_vec[0] + m_vec[1] * m_vec[1] + m_vec[2] * m_vec[2]);

}

void vec3::set(double x, double y, double z) {

    m_vec[0] = x;
    m_vec[1] = y;
    m_vec[2] = z;

}

ostream& operator<<(ostream &stream, vec3 &vec) {

    return stream << "[" << vec.x() << ", " << vec.y() << ", " << vec.z() << "]";

}
