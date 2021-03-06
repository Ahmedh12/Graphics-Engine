#pragma once

#include <application.hpp>

#include <ecs/world.hpp>
#include <systems/forward-renderer.hpp>
#include <systems/free-camera-controller.hpp>
#include <systems/movement.hpp>
#include <systems/spawner.hpp>
#include <systems/EnemyMovement.hpp>
#include <systems/collision.hpp>
#include <systems/winLose.hpp>
#include <systems/bullet.hpp>
#include <asset-loader.hpp>

#include <irrKlang.h>

//#pragma comment(lib, "irrKlang.lib")
// This state shows how to use the ECS framework and deserialization.
class Playstate : public our::State
{
public:
    int lives = 5;

private:
    our::World world;
    our::ForwardRenderer renderer;
    our::FreeCameraControllerSystem cameraController;
    our::MovementSystem movementSystem;
    our::SpawnerSystem spawnerSystem;
    our::EnemyMovementSystem enemyMovementSystem;
    our::CollisionSystem collisionSystem;
    our::WinLoseSystem winLoseSystem;
    our::BulletSystem bulletSysytem;
    // irrklang::ISoundEngine *SoundEngine = irrklang::createIrrKlangDevice();
    void onInitialize() override
    {
        // First of all, we get the scene configuration from the app config
        auto &config = getApp()->getConfig()["scene"];
        // If we have assets in the scene config, we deserialize them
        if (config.contains("assets"))
        {
            our::deserializeAllAssets(config["assets"]);
        }
        // If we have a world in the scene config, we use it to populate our world
        if (config.contains("world"))
        {
            world.deserialize(config["world"]);
        }
        // We initialize the camera controller system since it needs a pointer to the app
        cameraController.enter(getApp());
        // start Game Sound
        // SoundEngine->play2D("../../assets/audio/game_sound",true);
    }

    void onDraw(double deltaTime) override
    {
        // Here, we just run a bunch of systems to control the world logic
        movementSystem.update(&world, (float)deltaTime);
        cameraController.update(&world, (float)deltaTime);
        spawnerSystem.update(&world, (float)deltaTime);
        enemyMovementSystem.update(&world, (float)deltaTime);
        collisionSystem.update(&world, (float)deltaTime);
        bulletSysytem.update(&world, (float)deltaTime);
        
        int status = winLoseSystem.update(&world);

        if(status == 0)
        {
            getApp()->changeState("transform-test");
        }else if(status == 2)
        {
            getApp()->changeState("mesh-test");
        }
        // And finally we use the renderer system to draw the scene
        auto size = getApp()->getFrameBufferSize();
        renderer.render(&world, glm::ivec2(0, 0), size);
    }

    void onDestroy() override
    {
        // On exit, we call exit for the camera controller system to make sure that the mouse is unlocked
        cameraController.exit();
        // and we delete all the loaded assets to free memory on the RAM and the VRAM
        our::clearAllAssets();
    }
};