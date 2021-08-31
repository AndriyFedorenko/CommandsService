//
// Created by andrii on 31.08.21.
//

#include "DataReader.h"
#include <fstream>
#include <streambuf>

bool DataReader::read(const std::string& source, std::string& data)
{
    std::ifstream file(source);
    if(file.good())
    {
        data.assign((std::istreambuf_iterator<char>(file)),
                    std::istreambuf_iterator<char>());
        file.close();

        return true;
    }

    return false;
}
