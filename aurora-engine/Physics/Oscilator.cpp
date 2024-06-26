#include "Oscilator.h"

#include <aurora-engine/Objects/GameObject.h>
#include <aurora-engine/BaseComponents/Transform.h>

Oscilator::Oscilator(float frequency, float amplitude)
{
    this->Name = "Oscilator";
    this->frequency = frequency;
    this->amplitude = amplitude;
    this->cur = 0;
    this->dir = true;
}

Oscilator::~Oscilator()
{
}

void Oscilator::Start()
{
    GetParent()->Require<CTransform>(&transform);
}

void Oscilator::Update()
{
    if (dir)
    {
        cur += (frequency * amplitude);
        transform->Position.x += frequency * amplitude;
        if (cur >= amplitude)
        {
            dir = false;
        }
    }
    else
    {
        cur -= (frequency * amplitude);
        transform->Position.x -= frequency * amplitude;
        if (cur <= -amplitude)
        {
            dir = true;
        }
    }
}