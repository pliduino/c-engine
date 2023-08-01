#include "Oscilator.h"

#include "GameObject.h"
#include "Transform.h"

Oscilator::Oscilator(float frequency, float amplitude)
{
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
    GetParent()->Require<Transform>(&transform);
}

void Oscilator::Update()
{
    if (dir)
    {
        cur += (frequency * amplitude);
        transform->position.x += frequency * amplitude;
        if (cur >= amplitude)
        {
            dir = false;
        }
    }
    else
    {
        cur -= (frequency * amplitude);
        transform->position.x -= frequency * amplitude;
        if (cur <= -amplitude)
        {
            dir = true;
        }
    }
}