#include "rng.h"

void initRNG()
{
    // initialize RNG seed using current time
    // -> must be called once

    // NB: seed creation needs improvements
    std::srand(static_cast<unsigned int>(std::time(0)));
}


int generateRandomInt(int min, int max)
{
    // initial range: [0, RAND_MAX]
    double denominator = 1.0 / (RAND_MAX - 0.0);
    return static_cast<int>( (max - min)*std::rand()*denominator) + min;
}


float generateRandomFloat(float min, float max)
{
    // initial range: [0, RAND_MAX]
    float denominator = static_cast<float>( 1.0 / (RAND_MAX - 0.0) );
    return static_cast<float>( (max - min)*std::rand()*denominator + min);
}


std::string generateRandomString(unsigned int size)
{
    std::string output(size, ' ');

    int charNumber = 0;
    for (unsigned int i=0; i<size; i++)
    {
        charNumber = generateRandomInt(97, 122);
        output[i] = static_cast<char>(charNumber);
    }

    return output;
}
