#include "entity.hpp"

Entity::Entity(Manager* parent)
{
    this->parent = parent;
}

Entity::~Entity()
{
    clearComponents();
}

void Entity::addComponent(int type, std::shared_ptr<Component> c)
{
    components[type] = c;
}

void Entity::clearComponents()
{
    for(auto it = components.begin(); it != components.end(); ++it)
    {
        parent->endComponent(it->second.get());
    }
}

Component* Entity::getComponent(int type) const
{
    std::map<int, std::shared_ptr<Component> >::const_iterator it = components.find(type);
    if(it == components.end()) return nullptr;
    return it->second.get();
}
