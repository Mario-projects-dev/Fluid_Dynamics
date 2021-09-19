// Fluid_Dynamics.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdio>
#include <array>
#include <cmath>

const size_t kBufferSize = 80;

using namespace std;

void updateWave(const double timeInterval, double* x, double* speed)
{
    (*x) += timeInterval * (*speed);


if ((*x) > 1.0)
{
    (*speed) *= -1.0;
    (*x) = 1.0 + timeInterval * (*speed);
} 
else if ((*x) < 0.0) 
{
    (*speed) *= -1.0;
    (*x) = timeInterval * (*speed);
}
};


int main()
{
    const waveLenghtX = 0.8;
    const waveLenghtY = 1.2;

    const maxHeightX = 0.5;
    const maxHeightY = 0.4;

    double x = 0.0;
    double y = 1.0;
    double speedX = 1.0;
    double speedY = -0.5;

    const int fps = 100;
    const double timeInterval = 1.0 / fps;

    array<double, kBufferSize> heightField;

    for (int i = 0; i < 1000; ++i)
    {
        updateWave(timeInterval, &x, &speedX);
        updateWave(timeInterval, &y, &speedY);
    }

    return 0;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
