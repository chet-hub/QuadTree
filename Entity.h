//
// Created by bear on 2021-10-01.
//

#ifndef UNTITLED_ENTITY_H
#define UNTITLED_ENTITY_H


#include "Rectangle2D.h"
#include "Component.h"
#include "QuadTreeNode.h"


#include <unordered_set>

class Entity {
private:
    Rectangle2D rectangle2D;
    std::unordered_set<Component, Component::HashFunction> components;
public:
    Entity(float x, float y, float width, float height) : rectangle2D(x, y, width, height) {}

    Entity(const Entity &entity) : rectangle2D(entity.rectangle2D), components(entity.components) {}

    void AddComponent(Component component) {
        this->components.insert(component);
    }

    Rectangle2D GetRectangle() const {
        return this->rectangle2D;
    }

};


#endif //UNTITLED_ENTITY_H
