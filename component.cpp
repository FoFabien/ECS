#include "component.hpp"
#include <iostream>

Component::Component(int type)
{
    this->type = type;
    parent = nullptr;
}

Component::~Component()
{

}

void Component::setParent(Entity* parent)
{
    this->parent = parent;
}

void Component::update()
{

}

