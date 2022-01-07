#pragma once

#include "../ecs/world.hpp"
#include "../components/spawner.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>

namespace our
{
    class SpawnerSystem
    {
    public:
        void update(World *world, float deltaTime)
        {
            // For each entity in the world
            for (auto entity : world->getEntities())
            {
                // Get the spawner component if it exists
                SpawnerComponent *spawner = entity->getComponent<SpawnerComponent>();
                // If the spawner component exists
                if (spawner)
                {
                    // TODO:logic to respawn enemies
                    int numberOfRemainingEnemies = spawner->numberOfEnemies;
                    double lastRespawnTime = spawner->lastRespawnTime; // last respawn time is used to respawn a new zombie every 1 minute e.g. 3600 frames
                    spawner->lastRespawnTime += deltaTime;
                    if (numberOfRemainingEnemies > 0 && lastRespawnTime > 3600 * deltaTime)
                    {
                        spawner->numberOfEnemies--;
                        spawner->lastRespawnTime = 0;
                        //std::cout << "Spawning" << std::endl;
                        // randomizing spawner position and velocity
                        int prevX = spawner->EntityToRespawnJasonObj["position"][0].get<int>();
                        int prevZ = spawner->EntityToRespawnJasonObj["position"][2].get<int>();
                        world->add()->deserialize(spawner->EntityToRespawnJasonObj);
                        spawner->EntityToRespawnJasonObj["position"][0] = -prevX;
                        spawner->EntityToRespawnJasonObj["position"][2] = -prevZ;
                        world->add()->deserialize(spawner->EntityToRespawnJasonObj);
                        srand(time(NULL));
                        int random = rand();
                        int deltaPosX = random % 500;
                        srand(time(NULL));
                        random = rand();
                        int deltaPosZ = random % 50;
                        float speed = ((rand()%10)+1)/100.0f;
                        spawner->EntityToRespawnJasonObj["position"][0] = prevX + (numberOfRemainingEnemies % 2) ? deltaPosX : -deltaPosX;
                        spawner->EntityToRespawnJasonObj["position"][2] = prevZ + (numberOfRemainingEnemies % 2) ? deltaPosZ : -deltaPosZ;
                        spawner->EntityToRespawnJasonObj["components"][2]["speed"] = speed ;
                        std::cout<<speed<<std::endl;
                    }
                }
            }
        }
    };

}
