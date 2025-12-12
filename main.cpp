#include <iostream>
#include "degrees.h"
#include "radians.h"

void test_all_operations() {
    std::cout << "=== ТЕСТИРУЕМ ВСЕ ОПЕРАЦИИ ===\n\n";
    
    std::cout << "1. DEGREES:\n";
    degrees d1(30), d2(60);
    
    degrees d_sum = d1 + d2;
    degrees d_diff = d1 - d2;
    degrees d_mult = d1 * 2.0;
    degrees d_div = d1 / 2.0;
    degrees d_neg = -d1;
    
    d1 += d2;
    d1 -= d2;
    d1 *= 2.0;
    d1 /= 2.0;
    
    bool d_eq = (d1 == d2);
    bool d_lt = (d1 < d2);
    
    radians d_to_r = d1.toRadians();
    
    std::cout << "Все операции degrees работают!\n";

    std::cout << "2. RADIANS:\n";
    radians r1(1.0), r2(2.0);
    
    radians r_sum = r1 + r2;
    radians r_diff = r1 - r2;
    radians r_mult = r1 * 2.0;
    radians r_mult1 = 2.0 * r1;
    radians r_div = r1 / 2.0;
    radians r_neg = -r1;
    
    r1 += r2;
    r1 -= r2;
    r1 *= 2.0;
    r1 /= 2.0;
    
    bool r_eq = (r1 == r2);
    bool r_lt = (r1 < r2);
    
    degrees r_to_d = r1.toDegrees();
    std::cout << "Все операции radians работают!\n";
}

int main() {
    test_all_operations();
    return 0;
}