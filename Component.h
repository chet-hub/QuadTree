//
// Created by bear on 2021-10-01.
//

/*
Programmer Evaluation – Step 2 of 3

Given a 2D Entity where each has a Rectangle2D bounding box and optional Components:
• Add a Rectangle2D bounding box member to the Entity.
• Add a collection of Components to the Entity. An Entity may have any number of
Components. Assume there will be more than the three example Components below.
• Write the implementation to make Entity copyable.
• Feel free to modify the existing code as desired.
*/


#ifndef UNTITLED_COMPONENT_H
#define UNTITLED_COMPONENT_H
#include <iostream>


class Component {
public:
    virtual ~Component() = default;

    virtual char ComponentType() const{}

    bool operator==(const Component &otherComponent) const {
        return this->ComponentType() == otherComponent.ComponentType();
    }

    struct HashFunction {
        size_t operator()(const Component &component) const {
            return std::hash<int>()(component.ComponentType());
        }
    };
};


class HealthComponent : public Component {
private:
    int m_health = 0;
public:
    char ComponentType() const {
        return 'H';
    }
    ~HealthComponent(){}
};

class AttackComponent : public Component {
private:
    unsigned int m_attackPower = 0;
public:
    char ComponentType() const {
        return 'A';
    }
    ~AttackComponent(){}
};

class MovementComponent : public Component {
private:
    float m_speed = 0;
public:
    char ComponentType() const {
        return 'M';
    }
    ~MovementComponent(){}
};




#endif //UNTITLED_COMPONENT_H
