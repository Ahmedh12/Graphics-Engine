#include "bullet.hpp"
#include "../ecs/entity.hpp"
#include "../deserialize-utils.hpp"

namespace our {
    // Reads linearVelocity & angularVelocity from the given json object
    void BulletComponent::deserialize(const nlohmann::json& data){
        if(!data.is_object()) return;
        radius = data.value("radius",radius);
        center = data.value("center",center);
    }
}