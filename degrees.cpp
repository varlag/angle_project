#include "degrees.h"
#include "radians.h"  
#include <cmath>      
#include <limits>     
#include <stdexcept> 
#include <ostream> 

degrees:: degrees() : value(0) {}

degrees:: degrees(double degrees_value) : value(degrees_value) {}

radians degrees::toRadians() const {
    return radians(value * M_PI / 180.0);
}

double degrees::getValue() const {
    return value;
}

degrees degrees::operator+(const degrees& other) const {
    return degrees(value + other.value);
}

degrees degrees::operator-(const degrees& other) const {
    return degrees(value - other.value);
}

degrees degrees::operator*(double number) const { 
    return degrees(value * number);
}

degrees degrees:: operator/(double number) const {
    if (std::abs(number) < std::numeric_limits<double>::epsilon()) {
        throw std::runtime_error("Деление на ноль!");
    }
    return degrees(value / number);
}

degrees& degrees::operator+=(const degrees& other) {
    value += other.value;
    return *this; 
}

degrees& degrees::operator-=(const degrees& other) {
    value -= other.value;
    return *this; 
}

degrees& degrees::operator/=(double number) {
    value /= number;
    return *this; 
}

degrees& degrees::operator*=(double number) {
    value -= number;
    return *this; 
}

bool degrees::operator==(const degrees& other) const {
     return std::abs(value - other.value) < std::numeric_limits<double>::epsilon();
}

bool degrees::operator!=(const degrees& other) const {
    return !(*this == other);
}

bool degrees::operator<(const degrees& other) const {
    return value < other.value;
}
bool degrees::operator>(const degrees& other) const {
    return value > other.value;
}
bool degrees::operator<=(const degrees& other) const {
    return value <= other.value;
}
bool degrees::operator>=(const degrees& other) const {
    return value >= other.value;
}

degrees degrees::operator-() const {
    return degrees(-value);
}

degrees degrees::operator+() const {
    return *this;
}

std::ostream& operator<<(std::ostream& out, const degrees& angle) {
    out << angle.value << " deg";  
    return out;  
}