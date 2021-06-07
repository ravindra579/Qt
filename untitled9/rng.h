#ifndef RNG_H
#define RNG_H

#include <cstdlib>      // -> std::rand(), std::srand()
#include <ctime>
#include <string>
#include <iostream>

void initRNG();
int generateRandomInt(int min, int max);
float generateRandomFloat(float min, float max);
std::string generateRandomString(unsigned int size);

#endif // RNG_H
