#include "field.h"

Field::Field()
{
    m_size = 0;
    m_name = "";
    m_data = {};
}


unsigned int Field::getSize()
{
    return m_size;
}


const std::string& Field::getName()
{
    return m_name;
}


const std::vector<float>* Field::getData()
{
    return &m_data;
}


void Field::print(int number)
{
    std::cout << "---- info ----" << std::endl;
    std::cout << "name: " << m_name << std::endl;
    std::cout << "size: " << m_size << std::endl;

    std::cout << "---- data ----" << std::endl;

    if (m_size ==0)
    {
        std::cout << "  empty " << std::endl;
    }
    else if (number == 0)
    {
        for (unsigned int i=0; i<m_size; i++)
        {
            std::cout << "  " << i << ": " << m_data[i] << std::endl;
        }
    }
    else if (number > 0)
    {
        for (unsigned int i=0; i<static_cast<unsigned int>(number); i++)
        {
            std::cout << "  " << i << ": " << m_data[i] << std::endl;
        }
    }
    else
    {
        for (unsigned int i=0; i<static_cast<unsigned int>(number); i++)
        {
            std::cout << "  " << i << ": " << m_data[m_size-i-1] << std::endl;
        }
    }

    std::cout << std::endl;
}


std::array<float, 2> Field::getRange()
{
    float max = std::numeric_limits<float>::min();;
    float min = std::numeric_limits<float>::max();;

    for (float value : *this->getData())
    {
        if (value > max)
        {
            max = value;
        }

        if (value < min)
        {
            min = value;
        }
    }

    return {min, max};
}


void Field::setSize(unsigned int size)
{
    // note: we reset m_data to avoid size mismatch
    m_size = size;
    m_data.resize( size );
}


void Field::setName(std::string name)
{
    m_name = name;
}


void Field::setData(std::vector<float> *data)
{
    // check input array size matches m_size
    if (m_size == data->size())
    {
        m_data = *data;
    }
    else
    {
        std::cout << "setData: size mismatch -> use setSize first" << std::endl;
    }
}


void Field::setValue(float value, unsigned int index)
{
    if (index < m_size)
    {
        m_data[index] = value;
    }
    else
    {
        std::cout << "setValue: index exceeds data size" << std::endl;
    }
}


void Field::randomize(float min, float max)
{
    // size
    unsigned int size = this->getSize();

    // random name
    unsigned int stringSize = static_cast<unsigned int>(generateRandomInt(4, 12));
    this->setName(generateRandomString(stringSize));

    // field values
    for (unsigned int i=0; i<size; i++)
    {
        this->setValue(generateRandomFloat(min, max), i);
    }
}


std::vector<unsigned int> Field::getOrderedIndices()
{
    std::vector<float> sortedData = m_data;
    std::vector<unsigned int> sortedIndex;
    sortedIndex.resize(m_size);
    for (unsigned int i=0; i<m_size; ++i)
        sortedIndex[i] = i;

    unsigned int minIndex;
    for (unsigned int i=0; i<m_size; ++i)
    {
        minIndex = i;

        // find index of min value in [index, ...]
        for (unsigned int index=i; index<m_size; ++index)
        {
            if (sortedData[index]<sortedData[minIndex])
            {
                minIndex = index;
            }
        }

        // swap values at pos. i and minIndex for sortedData and sortedIndex
        std::swap(sortedData[i], sortedData[minIndex]);
        std::swap(sortedIndex[i], sortedIndex[minIndex]);
    }

    return sortedIndex;
}
