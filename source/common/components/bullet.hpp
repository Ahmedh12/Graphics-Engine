#pragma once

#include "../ecs/component.hpp"

#include <glm/glm.hpp>

namespace our
{

    class BulletComponent : public Component
    {
    public:
        // TODO: Add data members that are needed for the Bullet system
        glm::vec3 center = glm::vec3(0.5f,0.5f,0.5f);
        float radius = 0.5f;
        // The ID of this component type is "Bullet"
        static std::string getID() { return "Bullet"; }

        // Reads The data member .....to be decided..... from the json object
        void deserialize(const nlohmann::json &data) override;
    };

}