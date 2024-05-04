#pragma once

#include <aurora-engine/Objects/Component.h>

class CTransform;

class Oscilator : public CComponent
{
private:
    CTransform *transform;
    float frequency, amplitude;
    float cur;
    bool dir;

public:
    Oscilator(float frequency, float amplitude);
    ~Oscilator();

    void Start() override;
    void Update() override;
};