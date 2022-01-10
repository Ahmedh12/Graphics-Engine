#include "light.hpp"
#include "../ecs/entity.hpp"
#include "../deserialize-utils.hpp"

namespace our {
    // Reads linearVelocity & angularVelocity from the given json object
    void LightComponent::deserialize(const nlohmann::json& data){
        if(!data.is_object()) return;
        lightType  = data.value("lightType",lightType);
        count = data.value("count",count);
        color = data.value("color",color);
        attenuation =  data.value("attenuation",attenuation);
        coneAngle.x =  glm::radians(data.value("coneAngle[0]",15.0f));
        coneAngle.y =  glm::radians(data.value("coneAngle[1]",30.0f));
    }
}