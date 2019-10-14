#ifndef COMPONENT_HPP
#define COMPONENT_HPP

class Component;
#include "entity.hpp"
#include <memory>

class Component // make your own child components
{
    public:
        Component(int type);
        virtual ~Component();
        virtual void setParent(Entity* parent);
        virtual Entity* getParent() const {return parent;};
        virtual void update(); // called by the manager
        virtual int getType() const {return type;}
    protected:
        int type;
        Entity* parent;
};

#endif // COMPONENT_HPP
