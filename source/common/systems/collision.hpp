#pragma once

#include "../ecs/world.hpp"
#include "../components/collision.hpp"
#include "../components/free-camera-controller.hpp"
#include "../components/camera.hpp"
#include "../components/winLose.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>

namespace our
{
    class CollisionSystem
    {
    public:
        void update(World *world, float deltaTime)
        {
            // Getting the shooter Position
            CameraComponent *cam = nullptr;
            FreeCameraControllerComponent *control = nullptr;
            WinLoseComponent *winLose = nullptr;
            Entity *shooter = nullptr;
            Entity *health = nullptr;
            for (auto entity : world->getEntities())
            {
                cam = entity->getComponent<CameraComponent>();
                control = entity->getComponent<FreeCameraControllerComponent>();
                if ((cam && control))
                {
                    shooter = entity;
                    break;
                }
            }

            cam=nullptr;
            control = nullptr;

            for (auto entity : world->getEntities())
            {
                if (entity->parent)
                {
                    winLose = entity->getComponent<WinLoseComponent>();
                    cam = entity->parent->getComponent<CameraComponent>();
                    control = entity->parent->getComponent<FreeCameraControllerComponent>();
                    if ((cam && control && winLose))
                    {
                        health = entity;
                        break;
                    }
                }
            }

            // Getting the shooter position and radius from its collision component
            glm::vec3 shooterCenter = shooter->getLocalToWorldMatrix() * glm::vec4(shooter->getComponent<CollisionComponent>()->center, 1.0f);
            float shooterRadius = shooter->getComponent<CollisionComponent>()->radius;

            // Getting the Shooter remianing Lives
            int& lives = health->getComponent<WinLoseComponent>()->lives;

            // For each entity in the world
            for (auto entity : world->getEntities())
            {
                // Get the CollisionComponent component if it exists
                CollisionComponent *collision = entity->getComponent<CollisionComponent>();
                // If the CollisionComponent component exists
                if (collision && (entity != shooter))
                {
                    glm::vec3 zombieCenter = entity->getLocalToWorldMatrix() * glm::vec4(collision->center, 1.0f);

                    float zombieRadius = collision->radius;
                    shooterCenter.y = 0;
                    zombieCenter.y = 0;
                    float distance = glm::distance(shooterCenter, zombieCenter);
                    /*If i wanted I could have implemeted a zombie-zombie collision logic but according to my game flow
                    it is not necessary as well as it is quite computationaly expensive as it raise the function complexity from
                    linear in the number of entities to quadratic
                    */
                    if (distance <= zombieRadius + shooterRadius)
                    {
                        std::cout << shooterCenter.x << " " << shooterCenter.y << " " << shooterCenter.z << " shooter" << std::endl;
                        std::cout << zombieCenter.x << " " << zombieCenter.y << " " << zombieCenter.z << " zombie" << std::endl;
                        std::cout << distance << " Distance" << std::endl;
                        world->markForRemoval(entity);
                        lives--;
                        std::cout << "Collision Object Detected, lives"<< lives << std::endl;
                    }
                }
            }
            world->deleteMarkedEntities();
        }
    };

}
