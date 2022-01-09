#pragma once

#include "../ecs/world.hpp"
#include "../components/collision.hpp"
#include "../components/free-camera-controller.hpp"
#include "../components/camera.hpp"
#include "../components/winLose.hpp"
#include "../components/bullet.hpp"
#include "../components/enemyMovement.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>

namespace our
{
    class BulletSystem
    {
    public:
        void update(World *world, float deltaTime)
        {
            // Getting the shooter Position
            CameraComponent *cam = nullptr;
            FreeCameraControllerComponent *control = nullptr;
            WinLoseComponent *winLose = nullptr;
            BulletComponent *bullet = nullptr;
            EnemyMovementComponent *zombie = nullptr;
            Entity *shooter = nullptr;
            Entity *health = nullptr;

            for (auto entity : world->getEntities()) // shooter
            {
                cam = entity->getComponent<CameraComponent>();
                control = entity->getComponent<FreeCameraControllerComponent>();
                if ((cam && control))
                {
                    shooter = entity;
                    break;
                }
            }

            cam = nullptr;
            control = nullptr;

            for (auto entity : world->getEntities()) // winlose to calculates score
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

            int &score = health->getComponent<WinLoseComponent>()->score; // A reference to update the score variable

            for (auto Bentity : world->getEntities())
            {

                bullet = Bentity->getComponent<BulletComponent>(); // search for a bullet
                if (bullet)                                        // if found
                {
                    // Get its Collision Parameters from the bullet component
                    float BulletRadius = bullet->radius;
                    // find the center of the bullet wrt the world coordinates by multiplying by the entities local to world matrix
                    glm::vec3 bulletCenter = Bentity->getLocalToWorldMatrix() * glm::vec4(bullet->center, 1.0f);
                    zombie = nullptr;
                    for (auto Zentity : world->getEntities())
                    {
                        zombie = Zentity->getComponent<EnemyMovementComponent>(); // Since the zombie is the only entity with this component so we can use it as an idntifier
                        if (zombie)
                        {
                            glm::vec3 zombieCenter = Zentity->getLocalToWorldMatrix() * glm::vec4(Zentity->getComponent<CollisionComponent>()->center, 1.0f);
                            float ZombieRadius = Zentity->getComponent<CollisionComponent>()->radius;
                            // std::cout<<Zentity->localTransform.position.x<<" "<<Zentity->localTransform.position.y<<" "<<Zentity->localTransform.position.z<<" Zombie\n";
                            // std::cout<<Bentity->localTransform.position.x<<" "<<Bentity->localTransform.position.y<<" "<<Bentity->localTransform.position.z<<" bullet\n";
                            // std::cout<<"possible Zombie Bullet collision\n";
                            bulletCenter.y = 0;
                            zombieCenter.y = 0;

                            float distance = glm::distance(bulletCenter, zombieCenter);

                            if (distance < BulletRadius + ZombieRadius)
                            {
                                world->markForRemoval(Zentity);
                                world->markForRemoval(Bentity);
                                score++;
                            }

                            // std::cout<<distance<<"\n";
                        }
                    }
                }
            }
            world->deleteMarkedEntities();
            // std::cout<<score<<"\n";
        }
    };

}
