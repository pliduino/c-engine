#include "ObjReader.h"

ObjReader::ObjReader(/* args */)
{
}

ObjReader::~ObjReader()
{
}

void ObjReader::ReadFile(const char *path)
{
    std::ifstream file;

    file.open(path);

    std::string line, word, sing;
    std::stringstream sLine, sWord;

    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            sLine = std::stringstream(line);
            std::getline(sLine, word, ' ');

            if (word == "#")
            {
            }
            else if (word == "v")
            {
                double v[3];
                for (int i = 0; i < 3; i++)
                {
                    std::getline(sLine, word, ' ');
                    v[i] = std::stof(word);
                }

                positions.push_back(Vector3(v[0], v[1], v[2]));
            }
            else if (word == "f")
            {
                std::vector<ObjVertexInfo> face;
                while (std::getline(sLine, word, ' '))
                {
                    int v = 0, t = 0, n = 0;
                    sWord = std::stringstream(word);
                    if (std::getline(sWord, sing, '/'))
                    {
                        v = std::stoi(sing);
                    }
                    if (std::getline(sWord, sing, '/'))
                    {
                        t = std::stoi(sing);
                    }
                    if (std::getline(sWord, sing, '/'))
                    {
                        n = std::stoi(sing);
                    }
                    face.push_back(ObjVertexInfo(v, t, n));
                }

                faces.push_back(face);
            }
            else if (word == "vt")
            {
                double vt[2];
                for (int i = 0; std::getline(sLine, word, ' ') && i < 2; i++)
                {
                    vt[i] = std::stof(word);
                }

                textureCoordinates.push_back(Vector2(vt[0], vt[1]));
            }
            else if (word == "vn")
            {
                double vn[3];
                for (int i = 0; std::getline(sLine, word, ' ') && i < 3; i++)
                {
                    vn[i] = std::stof(word);
                }

                normals.push_back(Vector3(vn[0], vn[1], vn[2]));
            }
        }
    }

    file.close();

    Triangulate();
}

void ObjReader::Triangulate()
{
    for (auto face : faces)
    {
        int size = face.size();
        for (int i = 0; i < size; i += 2)
        {
            int indexVertex[3] = {face[i].vertex - 1, face[(i + 1) % size].vertex - 1, face[(i + 2) % size].vertex - 1};
            int indexTex[3] = {face[i].textureCoordinate - 1, face[(i + 1) % size].textureCoordinate - 1, face[(i + 2) % size].textureCoordinate - 1};
            int indexNrm[3] = {face[i].normal - 1, face[(i + 1) % size].normal - 1, face[(i + 2) % size].normal - 1};

            vertexData.push_back(positions[indexVertex[0]].x);
            vertexData.push_back(positions[indexVertex[0]].y);
            vertexData.push_back(positions[indexVertex[0]].z);
            vertexData.push_back(textureCoordinates[indexTex[0]].x);
            vertexData.push_back(textureCoordinates[indexTex[0]].y);
            vertexData.push_back(normals[indexNrm[0]].x);
            vertexData.push_back(normals[indexNrm[0]].y);
            vertexData.push_back(normals[indexNrm[0]].z);

            vertexData.push_back(positions[indexVertex[1]].x);
            vertexData.push_back(positions[indexVertex[1]].y);
            vertexData.push_back(positions[indexVertex[1]].z);
            vertexData.push_back(textureCoordinates[indexTex[1]].x);
            vertexData.push_back(textureCoordinates[indexTex[1]].y);
            vertexData.push_back(normals[indexNrm[1]].x);
            vertexData.push_back(normals[indexNrm[1]].y);
            vertexData.push_back(normals[indexNrm[1]].z);

            vertexData.push_back(positions[indexVertex[2]].x);
            vertexData.push_back(positions[indexVertex[2]].y);
            vertexData.push_back(positions[indexVertex[2]].z);
            vertexData.push_back(textureCoordinates[indexTex[2]].x);
            vertexData.push_back(textureCoordinates[indexTex[2]].y);
            vertexData.push_back(normals[indexNrm[2]].x);
            vertexData.push_back(normals[indexNrm[2]].y);
            vertexData.push_back(normals[indexNrm[2]].z);
        }
    }
}
