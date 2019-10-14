# Minimalistic ECS  
* Simple C++11 Entity Component System.  
* WIP, might change in the future.  
  
# Usage Notes  
* Simply `#include "manager.hpp"`.  
* Derive the `Component` class and define `entity_builder()` and `component_builder()` to determine how they will be paired in an entity.  
* A component `type` acts like a general identifier and determines in which order they are updated by the `Manager`. Very important to have interactions between components (an event listener component should be last, for example).  
* Small example for the builder definitions:
```cpp
void entity_builder(int type, Manager* m, Entity* e)
{
    switch(type)
    {
        case 0: // type 0 has two components of type 0 and 1
            e->addComponent(0, m->generateComponent(0, e));
            e->addComponent(1, m->generateComponent(1, e));
            break;
        case 1: // type 1 has two components of type 1 and 2
            e->addComponent(1, m->generateComponent(1, e));
            e->addComponent(2, m->generateComponent(2, e));
            break;
        default:
            break;
    }
}

std::shared_ptr<Component> component_builder(int type)
{
    std::shared_ptr<Component> c;
    switch(type)
    {
        case 0: c = std::make_shared<MyComp0>(type); break; // each type correspond to a child class
        case 1: c = std::make_shared<MyComp1>(type); break;
        case 2: c = std::make_shared<MyComp2>(type); break;
        default: c = std::make_shared<Component>(type); break; // can probably add some error handling here instead
    }
    return c;
}
```  
