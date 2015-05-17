#include "../header/GameObject.h"

GameObject::GameObject(const wxPoint &point, const wxSize &size)
{
    this->size = size;
    this->position = point;
}
GameObject::~GameObject(){}
