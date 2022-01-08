#include "winLose.hpp"
#include "../ecs/entity.hpp"
#include "../deserialize-utils.hpp"

namespace our {
    // Reads linearVelocity & angularVelocity from the given json object
    void WinLoseComponent::deserialize(const nlohmann::json& data){
        if(!data.is_object()) return;
        score = data.value("score",score);
        lives = data.value("lives",lives);
    }
}