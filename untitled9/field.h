#ifndef FIELD_H
#define FIELD_H

#include <string>
#include <vector>
#include <array>
#include <iostream>
#include <limits>
#include <algorithm>

#include "rng.h"


class Field
{
private:
    // number of elements of the field
    unsigned int m_size;
    // name of the field
    std::string m_name;
    // data of the field
    std::vector<float> m_data;

public:
    Field();

    // get private members and infos
    unsigned int getSize();
    const std::string& getName();
    const std::vector<float>* getData();
    void print(int number=0);
    std::array<float, 2> getRange();

    // set private members
    void setSize(unsigned int size);
    void setName(std::string name);
    void setData(std::vector<float>* data);
    void setValue(float value, unsigned int index);

    // utils
    void randomize(float min, float max);
    std::vector<unsigned int> getOrderedIndices();
};

#endif // FIELD_H
