#pragma once

#include "../ecs/component.hpp"

#include <glm/glm.hpp>

namespace our
{

    class LightComponent : public Component
    {
    public:
        int lightType; // 0:directional 1:Point 2:spot
        int count = 0;
        glm::vec3 color = glm::vec3(1.0f);
        glm::vec3 attenuation = glm::vec3(0.0f);
        glm::vec2 coneAngle = glm::vec2(glm::radians(15.0f), glm::radians(30.0f));
        glm::vec3 direction = glm::vec3(0.0,-1.0,0.0);
        // The ID of this component type is "Movement"
        static std::string getID() { return "Light"; }

        // Reads linearVelocity & angularVelocity from the given json object
        void deserialize(const nlohmann::json &data) override;
    };

}