#include "stringlib.h"

vector<size_t> findAll(string inputStr, char target)
{
    vector<size_t> result;

    for (size_t i=0; i<inputStr.length(); ++i)
    {
        if (inputStr[i]==target)
            result.push_back(i);
    }

    return result;
}


vector<size_t> findAll(string inputStr, string target)
{
    vector<size_t> result;
    size_t targetLen = target.size();

    for (size_t i=0; i<inputStr.length(); ++i)
    {
        if (inputStr.substr(i, targetLen)==target)
            result.push_back(i);
    }

    return result;
}


vector<string> split(string inputStr, char separator)
{
    // vector containing the positions of the separator in the string
    vector<size_t> pos = findAll(inputStr, separator);

    if (pos.empty())
    {
        // return the input string in a container
        return {inputStr};
    }

    else
    {
        // return a vector of sub-strings

        string tmpStr;

        // output vector
        vector<string> outputStr;

        // first position
        tmpStr = inputStr.substr(0, pos[0]);
        if (!tmpStr.empty())
            outputStr.push_back(tmpStr);

        // intermediate positions
        for (size_t i=0; i<pos.size()-1; ++i)
        {
            tmpStr = inputStr.substr(pos[i]+1, pos[i+1]-pos[i]-1);
            if (!tmpStr.empty())
                outputStr.push_back(tmpStr);
        }

        // last position
        tmpStr = inputStr.substr(pos.back()+1, inputStr.size()-1);
        if (!tmpStr.empty())
            outputStr.push_back(tmpStr);

        return outputStr;
    }

}


vector<string> split(string inputStr, string separator)
{
    // vector containing the positions of the separator in the string
    vector<size_t> pos = findAll(inputStr, separator);
    size_t length = separator.size();

    if (pos.empty())
    {
        // return the input string in a container
        return {inputStr};
    }

    else
    {
        // return a vector of sub-strings

        string tmpStr;

        // output vector
        vector<string> outputStr;

        // first position
        tmpStr = inputStr.substr(0, pos[0]+length-1);
        if (!tmpStr.empty())
            outputStr.push_back(tmpStr);

        // intermediate positions
        for (size_t i=0; i<pos.size()-1; ++i)
        {
            tmpStr = inputStr.substr(pos[i]+length, pos[i+1]-pos[i]+length-2);
            if (!tmpStr.empty())
                outputStr.push_back(tmpStr);
        }

        // last position
        tmpStr = inputStr.substr(pos.back()+length, inputStr.size()+length-2);
        if (!tmpStr.empty())
            outputStr.push_back(tmpStr);

        return outputStr;
    }

}



vector<string> renameDuplicates(vector<string> input)
{
    vector<string> output = input;
    int duplicates = 0;

    for (unsigned int index=0; index<input.size(); ++index)
    {
        // count number of duplicates in lower indices
        duplicates = 0;
        for (unsigned int i=0; i<index; ++i)
        {
            if ( (i!=index) && (input[i]==input[index]) )
            {
                duplicates ++;
            }
        }

        // rename if required
        if (duplicates > 0)
        {
            output[index] += "_";
            output[index] += to_string(duplicates);
        }
    }

    return output;
}


string removeQuotes(string inputStr)
{
    string result = inputStr;
    string replacement = " ";

    if ( (inputStr == "\"\"") || (inputStr == "''") )
    {
        return "";
    }

    for (size_t i=0; i<inputStr.length(); ++i)
    {
        if ( (inputStr[i]=='\"') || (inputStr[i]=='\'') )
            result.replace(i, replacement.size(), replacement);
    }

    return result;
}


string strip(string inputStr)
{
    char target = ' ';
    size_t strSize = inputStr.size();

    size_t startPos = 0;
    size_t endPos = strSize;
    size_t currentPos;

    if (strSize==0)
    {
        return "";
    }

    currentPos = 0;
    if (inputStr[currentPos]==target)
    {
        while ((inputStr[currentPos]==target) && (currentPos<strSize))
        {
            currentPos += 1;
        }
        startPos = currentPos;
    }

    currentPos = strSize;
    if (inputStr[currentPos]==target)
    {
        while ((inputStr[currentPos-1]==target) && (currentPos>1))
        {
            currentPos -= 1;
        }
        endPos = currentPos;
    }

    string result;
    result = inputStr.substr(startPos, endPos - startPos);
    return result;
}


string getBaseName(string inputStr)
{
    // 1. split path using windows delimiter
    vector<string> backslashSplit = split(inputStr, "\\");

    // 2. split last element using UX delimiter
    vector<string> slashSplit = split(backslashSplit.back(), "/");

    string result = slashSplit.back();
    return result;
}
