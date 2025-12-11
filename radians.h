#pragma once

#include <ostream>

class degrees;

class radians {
private:
    double value;
    
public:
    radians();
    explicit radians(double radians_value);
    
    degrees toDegrees() const;
    double getValue() const;
    
    radians operator+(const radians& other) const;
    radians operator-(const radians& other) const;
    radians operator*(double number) const;
    radians operator/(double number) const;
    
    radians& operator+=(const radians& other);
    radians& operator-=(const radians& other);
    radians& operator*=(double number);
    radians& operator/=(double number);
    
    bool operator==(const radians& other) const;
    bool operator!=(const radians& other) const;
    bool operator<(const radians& other) const;
    bool operator>(const radians& other) const;
    bool operator<=(const radians& other) const;
    bool operator>=(const radians& other) const;
    
    radians operator-() const;
    radians operator+() const;
    
    friend std::ostream& operator<<(std::ostream& out, const radians& angle);
};