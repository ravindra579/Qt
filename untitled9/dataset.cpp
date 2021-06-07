#include "dataset.h"

Dataset::Dataset()
{
    m_nbFields = 0;
    m_size = 0;
    m_names = {};
    m_fields = {};
    m_title = "";
}


void Dataset::setSize(unsigned int size)
{
    m_size = size;
}


void Dataset::addField(Field &field)
{
    // check that the new field has the same size as the dataset
    if (field.getSize() == m_size)
    {
        m_fields.push_back(field);
        m_nbFields += 1;
        m_names.push_back(field.getName());
    }
    else
    {
        std::cout << "addField: size mismatch" << std::endl;
    }
}


void Dataset::setValue(std::string name, float value, unsigned int index)
{
    // error: index too high
    if (index >= m_size)
    {
        std::cout << "setValue: index exceeds data size" << std::endl;
        return;
    }

    // find field
    unsigned int fieldIndex = 0;
    bool found = false;
    for (unsigned int i=0; i<m_names.size(); ++i)
    {
        // return corresponding field
        if (name==m_names[i])
        {
            found = true;
            fieldIndex = i;
        }
    }

    // error: field name not found
    if (!found)
    {
        std::cout << "setValue: field name not found" << std::endl;
        return;
    }

    // assign value
    m_fields[fieldIndex].setValue(value, index);
    return;
}


void Dataset::setTitle(std::string title)
{
    m_title = title;
}


unsigned int Dataset::getSize()
{
    return m_size;
}


unsigned int Dataset::getNumberOfFields()
{
    return m_nbFields;
}


std::vector<std::string> Dataset::getNames()
{
    return m_names;
}


Field Dataset::getField(std::string name)
{
    unsigned int index = 0;
    for (std::string fieldName : m_names)
    {
        // return corresponding field
        if (name==fieldName)
        {
            return m_fields[index];
        }

        index ++;
    }

    // return empty field if the requested field is not found
    std::cout << "getField: requested field not found" << std::endl;
    return Field();
}


void Dataset::printInfo()
{
    std::cout << "---- info ----" << "\n";
    std::cout << "  size:             " << this->getSize() << "\n";
    std::cout << "  number of fields: " << this->getNumberOfFields() << "\n";
    std::cout << "---- fields ----" << "\n";
    for (std::string name : this->getNames())
    {
        std::array<float, 2> range = this->getField(name).getRange();
        std::cout << "  " << name << ": [" << range[0] << ", " << range[1] << "]" << "\n";
    }
    std::cout << std::endl;

}


std::string Dataset::getTitle()
{
    return m_title;
}


bool Dataset::hasFieldNammed(std::string name)
{
    if (std::find(m_names.begin(), m_names.end(), name) != m_names.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}
