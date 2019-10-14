#ifndef MANAGER_HPP
#define MANAGER_HPP

struct ManagerEvent;
class Manager;
#include "entity.hpp"
#include "component.hpp"
#include <memory>
#include <map>
#include <vector>
#include <set>
#include <functional>

struct ManagerEvent // event container
{
    std::vector<int> i;
    std::vector<float> f;
    std::vector<std::string> s;
    Entity* source;
};

class Manager // manage components and entities
{
    public:
        Manager(std::function<void(int, Manager*, Entity*)> entity_builder, std::function<std::shared_ptr<Component>(int)> component_builder); // see the private members
        ~Manager();
        std::shared_ptr<Entity> generateEntity(int type); // creates an entity and its components
        std::shared_ptr<Component> generateComponent(int type, Entity* parent); // creates a component and adds itself to the parent. usually called by generateEntity
        void endEntity(const Entity* ptr); // kill an entity
        void endComponent(const Component* ptr); // kill a component
        void update(); // update the components
        void addEvent(int type, ManagerEvent ev); // add an event
        const std::vector<ManagerEvent>* listenEvents(int type) const; // retrieve the event list (nullptr if it doesn't exist)

    private:
        // custom functions
        std::function<void(int, Manager*, Entity*)> entity_builder; // called by generateEntity. define how your entities are built
        std::function<std::shared_ptr<Component>(int)> component_builder; // called by generateComponent. define how your components are built
        // storage
        std::vector<std::shared_ptr<Entity> > entities;
        std::map<int, std::vector<std::shared_ptr<Component> > > components; // sorted by type (int)
        std::set<const Component*> compTrash; // components to delete
        std::map<int, std::vector<ManagerEvent> > events; // event lists, sorted by type (int)
};

#endif // MANAGER_HPP
