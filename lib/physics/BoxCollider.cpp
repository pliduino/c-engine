#include "BoxCollider.h"
#include "Transform.h"
#include "GameObject.h"
#include "BoundingBox.h"
#include "ModelRenderer.h"
#include "Vector3.h"
#include "iostream"
#include "ObjReader.h"

BoxCollider::BoxCollider(/* args */)
{
    this->name = "Box Collider";
}

BoxCollider::~BoxCollider()
{
}

void BoxCollider::Start()
{
    GetParent()->Require<Transform>(&transform);
    ModelRenderer *model;
    GetParent()->Require<ModelRenderer>(&model);
    boundingBox = BoundingBox(&model->model->positions[0], model->model->positions.size());
}

void BoxCollider::Update()
{
}

inline bool BoxCollider::IsPointInside(const Vector3 point)
{
    Vector3 maxCoords = boundingBox.center + boundingBox.bounds + transform->position;
    Vector3 minCoords = boundingBox.center - boundingBox.bounds + transform->position;

    return point.x >= minCoords.x &&
           point.x <= maxCoords.x &&
           point.y >= minCoords.y && point.y <= maxCoords.y &&
           point.z >= minCoords.z && point.z <= maxCoords.z;
}

inline bool BoxCollider::Intersect(BoxCollider other)
{
    Vector3 maxCoords = boundingBox.center + boundingBox.bounds;
    Vector3 minCoords = boundingBox.center - boundingBox.bounds;
    Vector3 otherMaxCoords = other.boundingBox.center + other.boundingBox.bounds;
    Vector3 otherMinCoords = other.boundingBox.center - other.boundingBox.bounds;

    return otherMaxCoords.x >= minCoords.x && otherMinCoords.x <= maxCoords.x &&
           otherMaxCoords.y >= minCoords.y && otherMinCoords.y <= maxCoords.y &&
           otherMaxCoords.z >= minCoords.z && otherMinCoords.z <= maxCoords.z;
}