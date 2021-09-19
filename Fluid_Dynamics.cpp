// Fluid_Dynamics.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdio>
#include <array>
#include <cmath>
#include <algorithm>
#include <chrono>
#include <string>
#include <thread>

const size_t kBufferSize = 80;

using namespace std;
using namespace chrono;

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

void accumulateWaveToHeightField(const double x, const double waveLenght, const double maxHeight, array<double, kBufferSize>* heightField)
{
    const double quarterWaveLenght = 0.25 * waveLenght;
    const int start = static_cast<int>((x - quarterWaveLenght) * kBufferSize);
    const int end = static_cast<int>((x + quarterWaveLenght) * kBufferSize);

    for (int i = start; i < end; ++i)
    {
        int iNew = i;
        if (i < 0)
        {
            iNew = -i - 1;
        }
        else if (i >= static_cast<int>(kBufferSize))
        {
            iNew = 2 * kBufferSize - i - 1;
        }
        double distance = fabs((i + 0.5) / kBufferSize - x);
        double height = maxHeight * 0.5 * (cos(min(distance * M_PI / quarterWaveLenght, M_PI)) + 1.0);
        (*heightField)[iNew] += height;
    }
}

void draw(const array<double, kBufferSize>& heightField)
{
    string buffer(kBufferSize, ' ');

    for (size_t i = 0; i < kBufferSize; ++i)
    {
        double height = heightField[i];
        size_t tableIndex = min(static_cast<size_t>(floor(kGrayScaleTableSize * height)), kGrayScaleTableSize - 1);
        buffer[i] = kGrayScaleTable[tableIndex];
    }

    for (size_t i = 0; i < kBufferSize; ++i)
    {
        printf("\b");
    }

    printf("%s", buffer.c_str());
    fflush(stdout);
}

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

        for (double& height : heightField)
        {
            height = 0.0;
        }
        accumulateWaveToHeightField(x, waveLenghtX, maxHeightX, &heightField);
        accumulateWaveToHeightField(y, waveLenghtY, maxHeightY, &heightField);

        draw(heightField);

        this_thread::sleep_for(milliseconds(1000 / fps));
    }
    printf("\n");
    fflush(stdout);

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
