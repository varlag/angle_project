#pragma once
#include <ostream> 

class radians;

class degrees {

private: 
    double value;

public: 
    degrees();
    explicit degrees(double degrees_value);
    

    radians toRadians() const; 
    double getValue() const;

    degrees operator+(const degrees& other) const; 
    degrees operator-(const degrees& other) const;
    degrees operator*(double number) const; 
    degrees operator/(double number) const; 

    degrees& operator+=(const degrees& other);
    degrees& operator-=(const degrees& other);
    degrees& operator*=(double number);      
    degrees& operator/=(double number); 

    bool operator==(const degrees& other) const;
    bool operator!=(const degrees& other) const;
    bool operator<(const degrees& other) const;
    bool operator>(const degrees& other) const;
    bool operator<=(const degrees& other) const;
    bool operator>=(const degrees& other) const;

    degrees operator-() const;
    degrees operator+() const;

    friend std::ostream& operator<<(std::ostream& out, const degrees& angle);
};
 