#include <iostream>
#include <spline/Function.h>

int main()
{
    auto splines = Function::fromFile("splines.json");

    for (auto entry : splines) {
        std::cout << entry.first << ":" << std::endl;

        for (float k=-0.5; k<=1.5; k+=0.1) {
            std::cout << k << ": " << entry.second.get(k) << std::endl;
        }
    }
}
