#include "spawner.hpp"
#include "../ecs/entity.hpp"
#include "../deserialize-utils.hpp"
#include<iostream>
namespace our {
    // Reads The data member .....to be decided..... from the json object
    void SpawnerComponent::deserialize(const nlohmann::json& data){
        if(!data.is_object()) return;
        // linearVelocity = data.value("linearVelocity", linearVelocity);
        // angularVelocity = glm::radians(data.value("angularVelocity", angularVelocity));

        numberOfEnemies = data.value("numberOfEnemies",5);
        EntityToRespawnJasonObj = data["entity"]; 
    }
}