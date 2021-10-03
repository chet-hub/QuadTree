#include <vector>
#include <fstream>
#include <chrono>
#include "Component.h"
#include "Entity.h"
#include "QuadTreeNode.h"

/*
Programmer Evaluation – Step 3 of 3

Using the provided code below as a starting point (though you are not required to use it), create
an algorithm that:
• Reads from the included file containing Rectangle2D and Component information to
create a collection of Entities.
• Create an algorithm to determine how many Entity intersections are in the collection.
Look for unique intersections – if two Entities intersect each other, that counts as one
unique intersection rather than two. Use your intersection implementation from Part 1
and the Entity’s Rectangle2D bounding box.

 */



void DetectIntersections_SimpleLoop(const std::vector<Entity> &entities) {
    int count = 0;
    for (int i = 0; i < entities.size(); i++) {
        auto rect_0 = entities[i].GetRectangle();
        for (int j = i + 1; j < entities.size(); j++) {
            auto rect_1 = entities[j].GetRectangle();
            if (rect_0.Intersect(rect_1)) {
                count++;
            }
        }
    }
    printf("SimpleLoop - unique intersection count: %d\n", count);
}


void DetectIntersections_QuadTree(const std::vector<Entity> &entities) {
    int count = 0;
    auto root = new QuadTreeNode(-1000, -1000, 1000, 1000);
    for (int i = 0; i < entities.size(); i++) {
        auto rect = entities[i].GetRectangle();
        root->Insert(rect);
    }
    root->IntersectCount(&count);
    printf("QuadTree - unique intersection count: %d\n", count);
}


/**

SimpleLoop - unique intersection count: 13304896
SimpleLoop Algorithm executed in 839ms.
QuadTree - unique intersection count: 13304896
QuadTree Algorithm executed in 149ms.

 */
int main(int argc, const char *argv[]) {
    if (argc < 2) {
        std::cerr << "Specify a file to run this program.\n";
        return 1;
    }
    std::cout << "Running program against file: " << argv[1] << "\n";

    std::ifstream file(argv[1], std::ios::binary);

    //std::ifstream file("/home/bear/QuadTree/entityblueprints.txt", std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Failed to open file.\n";
        return 2;
    }
    unsigned int numberOfEntities = 0;
    if (!(file >> numberOfEntities)) {
        std::cerr << "Failed to get number of Entities from file.\n";
        return 3;
    }

    //Add a collection of Entities.
    std::vector<Entity> entities;

    for (unsigned int i = 0; i < numberOfEntities; ++i) {
        float x = 0;
        float y = 0;
        float width = 0;
        float height = 0;

        if (!(file >> x >> y >> width >> height)) {
            std::cerr << "Error getting bounds on line " << i + 1 << ".\n";
            return 4;
        }

        Entity entity = *new Entity(x, x, width, height);
        entities.push_back(entity);

        std::string componentTypes;
        const auto currentPos = file.tellg();
        file >> componentTypes;
        if (!componentTypes.empty() && !std::isalpha(componentTypes.back())) {
            file.seekg(currentPos);
            componentTypes.clear();
        }
        for (const char type: componentTypes) {
            switch (type) {
                case 'H':
                    entity.AddComponent(*new HealthComponent());
                    break;
                case 'A':
                    entity.AddComponent(*new AttackComponent());
                    break;
                case 'M':
                    entity.AddComponent(*new MovementComponent());
                    break;
                default:
                    std::cerr << "Unknown Component type: " << type << "\n";
                    break;
            }
        }
    }
    file.close();

    auto start = std::chrono::high_resolution_clock::now();
    DetectIntersections_SimpleLoop(entities);
    auto end = std::chrono::high_resolution_clock::now();
    auto runMS = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "SimpleLoop Algorithm executed in " << runMS.count() << "ms.\n";

    start = std::chrono::high_resolution_clock::now();
    DetectIntersections_QuadTree(entities);
    end = std::chrono::high_resolution_clock::now();
    runMS = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "QuadTree Algorithm executed in " << runMS.count() << "ms.\n";

    return 0;
}

