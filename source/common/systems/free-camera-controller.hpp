#pragma once

#include "../ecs/world.hpp"
#include "../components/camera.hpp"
#include "../components/free-camera-controller.hpp"

#include "../application.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>
#include <glm/gtx/euler_angles.hpp>

namespace our
{

    // The free camera controller system is responsible for moving every entity which contains a FreeCameraControllerComponent.
    // This system is added as a slightly complex example for how use the ECS framework to implement logic.
    // For more information, see "common/components/free-camera-controller.hpp"
    class FreeCameraControllerSystem
    {
        Application *app;          // The application in which the state runs
        bool mouse_locked = false; // Is the mouse locked
        double last_shot = 0;
    public:
        // When a state enters, it should call this function and give it the pointer to the application
        void enter(Application *app)
        {
            this->app = app;
        }

        // This should be called every frame to update all entities containing a FreeCameraControllerComponent
        void update(World *world, float deltaTime)
        {
            CameraComponent *camera = nullptr;
            FreeCameraControllerComponent *controller = nullptr;
            for (auto entity : world->getEntities())
            {
                if ((entity->parent)) // rifle is a child of the world which has the camera and free camera controller components
                {
                    camera = entity->parent->getComponent<CameraComponent>();
                    controller = entity->parent->getComponent<FreeCameraControllerComponent>();
                }

                if (camera && controller)
                    break;
            }
            // If there is no entity with both a CameraComponent and a FreeCameraControllerComponent, we can do nothing so we return
            if (!(camera && controller))
                return;
            // Get the entity that we found via getOwner of camera (we could use controller->getOwner())
            Entity *entity = camera->getOwner(); // shooter e.g. Rifle

            camera = nullptr;
            controller = nullptr;

            // getting the camera owner itself , above we fetched his child
            for (auto entity : world->getEntities())
            {
                camera = entity->getComponent<CameraComponent>();
                controller = entity->getComponent<FreeCameraControllerComponent>();

                if (camera && controller)
                    break;
            }

            // If the left mouse button is pressed, we lock and hide the mouse. This common in First Person Games.
            // if (app->getMouse().isPressed(GLFW_MOUSE_BUTTON_1) && !mouse_locked)
            // {
            //     app->getMouse().lockMouse(app->getWindow());
            //     mouse_locked = true;
            //     // If the left mouse button is released, we unlock and unhide the mouse.
            // }
            // else if (!app->getMouse().isPressed(GLFW_MOUSE_BUTTON_1) && mouse_locked)
            // {
            //     app->getMouse().unlockMouse(app->getWindow());
            //     mouse_locked = false;
            // }

            // We get a reference to the entity's position and rotation
            glm::vec3 &position = entity->localTransform.position;
            glm::vec3 &rotation = entity->localTransform.rotation;

            if (!app->getKeyboard().isPressed(GLFW_KEY_ESCAPE)) //lock the the mouse if the ESC key is not pressed
            {
                app->getMouse().lockMouse(app->getWindow());
                mouse_locked = true;
            }

            // and use it to update the camera rotation
            // if (app->getMouse().isPressed(GLFW_MOUSE_BUTTON_1))
            // {
            // glm::vec2 delta = app->getMouse().getMouseDelta();
            // rotation.x -= delta.y * controller->rotationSensitivity; // The y-axis controls the pitch
            // rotation.y -= delta.x * controller->rotationSensitivity; // The x-axis controls the yaw
            // }

            if (app->getKeyboard().isPressed(GLFW_KEY_ESCAPE)) // Unlock the mouse if escape is pressed
            {
                app->getMouse().unlockMouse(app->getWindow());
                mouse_locked = false;
            }


            if (mouse_locked)
            {
                glm::vec2 delta = app->getMouse().getMouseDelta();
                rotation.x -= delta.y * controller->rotationSensitivity; // The y-axis controls the pitch
                rotation.y -= delta.x * controller->rotationSensitivity; // The x-axis controls the yaw

                //Calcutaing Matrix for the bullet firing poition
                glm::mat4 translateMat = glm::translate(glm::mat4(1.0f), position);
                glm::mat4 rotateMat = glm::yawPitchRoll(rotation.y, rotation.x, rotation.z);
                glm::mat4 transformation = translateMat * rotateMat;
                glm::vec3 fireAt = transformation * glm::vec4(0.0f,-0.5f,-1.0f,1.0f);

                //Setting the bullet firing position
                controller->bullet["position"][0] = fireAt.x;
                controller->bullet["position"][1] = fireAt.y;
                controller->bullet["position"][2] = fireAt.z;

                glm::vec3 dir = fireAt - position;
                glm::normalize(dir);
                //Adjust the velocity vector of movement component to be in the direction of the firing position
                controller->bullet["components"][1]["linearVelocity"][0] = 20 * dir.x;
                controller->bullet["components"][1]["linearVelocity"][1] = dir.y;
                controller->bullet["components"][1]["linearVelocity"][2] = 20 * dir.z;

                mouse_locked = true;
                //std::cout << app->getMouse().getMousePosition().x << " " << app->getMouse().getMousePosition().y << "\n";
            }

            if (app->getMouse().isPressed(GLFW_MOUSE_BUTTON_1) && last_shot > 200 * deltaTime)
            {
                //std::cout<<"bullet\n";
                last_shot=0.0;
                Entity *bullet = world->add();
                bullet->deserialize(controller->bullet);
            }

            // We prevent the pitch from exceeding a certain angle from the XZ plane to prevent gimbal locks
            if (rotation.x < -glm::half_pi<float>() * 0.4f)
                rotation.x = -glm::half_pi<float>() * 0.4f;
            if (rotation.x > glm::half_pi<float>() * 0.4f)
                rotation.x = glm::half_pi<float>() * 0.4f;

            // We prevent the yaw from exceeding a certain angle from the YZ plane as the player cant look back
            if (rotation.y < -glm::half_pi<float>() * 0.8f)
                rotation.y = -glm::half_pi<float>() * 0.8f;
            if (rotation.y > glm::half_pi<float>() * 0.8f)
                rotation.y = glm::half_pi<float>() * 0.8f;

            // This is not necessary, but whenever the rotation goes outside the 0 to 2*PI range, we wrap it back inside.
            // This could prevent floating point error if the player rotates in single direction for an extremely long time.
            // rotation.y = glm::wrapAngle(rotation.y);

            // // We update the camera fov based on the mouse wheel scrolling amount
            // float fov = camera->fovY + app->getMouse().getScrollOffset().y * controller->fovSensitivity;
            // fov = glm::clamp(fov, glm::pi<float>() * 0.01f, glm::pi<float>() * 0.99f); // We keep the fov in the range 0.01*PI to 0.99*PI
            // camera->fovY = fov;

            // // We get the camera model matrix (relative to its parent) to compute the front, up and right directions
            // glm::mat4 matrix = entity->localTransform.toMat4();

            // glm::vec3 front = glm::vec3(matrix * glm::vec4(0, 0, -1, 0)),
            //           up = glm::vec3(matrix * glm::vec4(0, 1, 0, 0)),
            //           right = glm::vec3(matrix * glm::vec4(1, 0, 0, 0));

            // glm::vec3 current_sensitivity = controller->positionSensitivity;
            // // If the LEFT SHIFT key is pressed, we multiply the position sensitivity by the speed up factor
            // if(app->getKeyboard().isPressed(GLFW_KEY_LEFT_SHIFT)) current_sensitivity *= controller->speedupFactor;

            // // We change the camera position based on the keys WASD/QE
            // // S & W moves the player back and forth
            // if(app->getKeyboard().isPressed(GLFW_KEY_W)) position += front * (deltaTime * current_sensitivity.z);
            // if(app->getKeyboard().isPressed(GLFW_KEY_S)) position -= front * (deltaTime * current_sensitivity.z);
            // // Q & E moves the player up and down
            // if(app->getKeyboard().isPressed(GLFW_KEY_Q)) position += up * (deltaTime * current_sensitivity.y);
            // if(app->getKeyboard().isPressed(GLFW_KEY_E)) position -= up * (deltaTime * current_sensitivity.y);
            // // A & D moves the player left or right
            // if(app->getKeyboard().isPressed(GLFW_KEY_D)) position += right * (deltaTime * current_sensitivity.x);
            // if(app->getKeyboard().isPressed(GLFW_KEY_A)) position -= right * (deltaTime * current_sensitivity.x);

            last_shot+=deltaTime;
        }

        // When the state exits, it should call this function to ensure the mouse is unlocked
        void exit()
        {
            if (mouse_locked)
            {
                mouse_locked = false;
                app->getMouse().unlockMouse(app->getWindow());
            }
        }
    };


}
