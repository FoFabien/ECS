#ifndef ENTITY_HPP
#define ENTITY_HPP

class Entity;
#include "manager.hpp"
#include "component.hpp"
#include <map>
#include <vector>
#include <string>

class Entity // the entity itself doesn't do much. it exists for data management purpose (component access and deletion)
{
    public:
        Entity(Manager* parent);
        ~Entity();
        void addComponent(int type, std::shared_ptr<Component> c); // bind a component
        void clearComponents(); // mark all components for deletion
        Component* getComponent(int type) const; // retrieve a component (null if error)
        Manager* getParent() const {return parent;}; // retrieve the manager
    private:
        Manager* parent;
        std::map<int, std::shared_ptr<Component> > components;
};

#endif // ENTITY_HPP
