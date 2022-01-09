#pragma once

#include "../ecs/world.hpp"
#include "../components/winLose.hpp"
#include "../components/free-camera-controller.hpp"
#include "../components/camera.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>

namespace our
{
    class WinLoseSystem
    {
    public:
        void update(World *world, float deltaTime)
        {
        }

        int update(World *world)
        {
            // Getting the shooter Entity
            CameraComponent *cam = nullptr;
            FreeCameraControllerComponent *control = nullptr;
            WinLoseComponent *winLose = nullptr;
            Entity *health = nullptr;
            for (auto entity : world->getEntities())
            {
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
            }

            int lives = health->getComponent<WinLoseComponent>()->lives;
            int score = health->getComponent<WinLoseComponent>()->score;
            //std::cout<<"Score from winLOse Comp "<<score<<std::endl;
            
            if(score >= 20)
            {
                return 2;
            }

            if (lives > 0)
            {
                health->getComponent<WinLoseComponent>()->getOwner()->localTransform.scale.x = (float)lives;
                return 1;
            }else
            {
                return 0;
            }

        }
    };

}
