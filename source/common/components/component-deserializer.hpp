#pragma once

#include "../ecs/entity.hpp"
#include "camera.hpp"
#include "mesh-renderer.hpp"
#include "free-camera-controller.hpp"
#include "movement.hpp"
#include "spawner.hpp"
#include "enemyMovement.hpp"
#include "winLose.hpp"
#include "collision.hpp"
#include "bullet.hpp"

//TODO:Include all your components header files here and complete the function below accordingly to fill the entity components list

namespace our {

    // Given a json object, this function picks and creates a component in the given entity
    // based on the "type" specified in the json object which is later deserialized from the rest of the json object
    inline void deserializeComponent(const nlohmann::json& data, Entity* entity){
        std::string type = data.value("type", "");
        Component* component = nullptr;
        if(type == CameraComponent::getID()){
            component = entity->addComponent<CameraComponent>();
        } else if (type == MeshRendererComponent::getID()) {
            component = entity->addComponent<MeshRendererComponent>();
        } else if (type == FreeCameraControllerComponent::getID()) {
            component = entity->addComponent<FreeCameraControllerComponent>();
        } else if (type == MovementComponent::getID()) {
            component = entity->addComponent<MovementComponent>();
        }else if (type == SpawnerComponent::getID()){
            component = entity->addComponent<SpawnerComponent>();
        }else if (type == EnemyMovementComponent::getID()){
            component = entity->addComponent<EnemyMovementComponent>();
        }else if (type == CollisionComponent::getID()){
            component = entity->addComponent<CollisionComponent>();
        }else if (type == WinLoseComponent::getID()){
            component = entity->addComponent<WinLoseComponent>();
        }else if (type == BulletComponent::getID()){
            component = entity->addComponent<BulletComponent>();
        }
        if(component) component->deserialize(data);
    }

}