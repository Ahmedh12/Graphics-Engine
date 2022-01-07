#pragma once

#include "../ecs/world.hpp"
#include "../components/enemyMovement.hpp"
#include "../components/free-camera-controller.hpp"
#include "../components/camera.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>

namespace our
{
    class EnemyMovementSystem
    {
    public:
        void update(World *world, float deltaTime)
        {
            // For each entity in the world
            for (auto entity : world->getEntities())
            {
                // Get the EnemyMovementComponent component if it exists
                EnemyMovementComponent *enemyMovement = entity->getComponent<EnemyMovementComponent>();
                // If the EnemyMovementComponent component exists
                if (enemyMovement)
                {
                    CameraComponent *cam = nullptr;
                    FreeCameraControllerComponent *control = nullptr;
                    Entity *ent = nullptr;
                    for (auto entity : world->getEntities())
                    {
                        cam = entity->getComponent<CameraComponent>();
                        control = entity->getComponent<FreeCameraControllerComponent>();
                        if ((cam && control))
                        {
                            ent = entity;
                            break;
                        }
                    }
                    glm::vec3 pos = ent->localTransform.position;
                    glm::vec3 dir = pos - entity->localTransform.position;
                    dir.y = 0;
                    entity->localTransform.position += (glm::normalize(dir) * (enemyMovement->speed));
                }
            }
        }
    };

}
