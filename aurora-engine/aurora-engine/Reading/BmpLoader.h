#pragma once

#include <fstream>

class BmpLoader
{
private:
    bool CheckIntegrity();

public:
    unsigned char header[54];
    unsigned int dataPos;
    unsigned int width, height;
    unsigned long int imageSize;
    unsigned char *data;

    BmpLoader(/* args */);
    ~BmpLoader();

    void LoadFile(const char *path);

    unsigned char *CloneData();
};

BmpLoader::BmpLoader(/* args */)
{
}

BmpLoader::~BmpLoader()
{
    delete data;
}

void BmpLoader::LoadFile(const char *path)
{
    std::ifstream file;

    file.open(path, std::ios::binary | std::ios::in);

    file.read((char *)header, 54);

    if (header[0] == 'B' || header[1] == 'M')
    {
        width = *(int *)&header[18];
        height = *(int *)&header[22];
    }

    // if (imageSize == 0)
    // {
    imageSize = width * height * 3;
    // }

    if (dataPos == 0)
    {
        dataPos = 54;
    }

    data = new unsigned char[imageSize];

    file.read((char *)data, imageSize);

    file.close();
}

unsigned char *BmpLoader::CloneData()
{
    return data;
}

bool BmpLoader::CheckIntegrity()
{
    return width * height * 3 == imageSize;
}
