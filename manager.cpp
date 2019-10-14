#include "manager.hpp"

Manager::Manager(std::function<void(int, Manager*, Entity*)> entity_builder, std::function<std::shared_ptr<Component>(int)> component_builder)
{
    this->entity_builder = entity_builder;
    this->component_builder = component_builder;
}

Manager::~Manager()
{
    events.clear();
    entities.clear();
    compTrash.clear();
    components.clear();
}

std::shared_ptr<Entity> Manager::generateEntity(int type)
{
    std::shared_ptr<Entity> e = std::make_shared<Entity>(this); // allocate
    entity_builder(type, this, e.get()); // build
    entities.push_back(e); // add to the list
    return e; // return if needed
}

std::shared_ptr<Component> Manager::generateComponent(int type, Entity* parent)
{
    std::shared_ptr<Component> c = component_builder(type); // allocate and build
    c->setParent(parent); // set the parent entity (can be null but not recommended)
    if(components.find(type) == components.end()) components[type] = std::vector<std::shared_ptr<Component> >(); // create the type if not found
    components[type].push_back(c); // add to that list
    return c; // return if needed
}

void Manager::endEntity(const Entity* ptr)
{
    for(auto it = entities.begin(); it != entities.end(); ++it) // search the entity
    {
        if(it->get() == ptr)
        {
            it->get()->clearComponents(); // mark components for deletion
            entities.erase(it); // delete it
            return;
        }
    }
}

void Manager::endComponent(const Component* ptr)
{
    compTrash.insert(ptr); // add to the deletion list
}

void Manager::update()
{
    for(auto& t: components) // update each type in order
    {
        for(auto it = t.second.begin(); it != t.second.end();)
        {
            auto jt = compTrash.find((*it).get()); // delete if the component is in the deletion list
            if(jt != compTrash.end())
            {
                it = t.second.erase(it);
                compTrash.erase(jt);
            }
            else
            {
                (*it)->update();
                ++it;
            }
        }
    }
    events.clear(); // clear the event list (they last "one cycle")
}

void Manager::addEvent(int type, ManagerEvent ev)
{
    if(events.find(type) == events.end()) events[type] = std::vector<ManagerEvent>();
    events[type].push_back(ev); // add the event to the list
}

const std::vector<ManagerEvent>* Manager::listenEvents(int type) const
{
    if(events.find(type) == events.end()) return nullptr;
    return &(events.at(type));
}
