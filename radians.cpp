#include "radians.h"
#include "degrees.h"
#include <cmath>
#include <limits>
#include <stdexcept>

radians::radians() : value(0) {}

radians::radians(double radians_value) : value(radians_value) {}

degrees radians::toDegrees() const {
    return degrees(value * 180.0 / M_PI);
}

double radians::getValue() const {
    return value;
}

radians radians::operator+(const radians& other) const {
    return radians(value + other.value);
}

radians radians::operator-(const radians& other) const {
    return radians(value - other.value);
}

radians radians::operator*(double number) const {
    return radians(value * number);
}

radians radians::operator/(double number) const {
    if (std::abs(number) < std::numeric_limits<double>::epsilon()) {
        throw std::runtime_error("Деление на ноль!");
    }
    return radians(value / number);
}

radians& radians::operator+=(const radians& other) {
    value += other.value;
    return *this;
}

radians& radians::operator-=(const radians& other) {
    value -= other.value;
    return *this;
}

radians& radians::operator*=(double number) {
    value *= number;
    return *this;
}

radians& radians::operator/=(double number) {
    if (std::abs(number) < std::numeric_limits<double>::epsilon()) {
        throw std::runtime_error("Деление на ноль!");
    }
    value /= number;
    return *this;
}

bool radians::operator==(const radians& other) const {
    return std::abs(value - other.value) < 
           std::numeric_limits<double>::epsilon();
}

bool radians::operator!=(const radians& other) const {
    return !(*this == other);
}

bool radians::operator<(const radians& other) const {
    return value < other.value;
}

bool radians::operator>(const radians& other) const {
    return value > other.value;
}

bool radians::operator<=(const radians& other) const {
    return value <= other.value;
}

bool radians::operator>=(const radians& other) const {
    return value >= other.value;
}

radians radians::operator-() const {
    return radians(-value);
}

radians radians::operator+() const {
    return *this;
}

std::ostream& operator<<(std::ostream& out, const radians& angle) {
    out << angle.value << " rad";
    return out;
}
