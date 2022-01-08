#pragma once

#include "../ecs/component.hpp"

#include <glm/glm.hpp>

namespace our
{

    class CollisionComponent : public Component
    {
    public:
        // TODO: Add data members that are needed for the Collision system
        glm::vec3 center = glm::vec3(0.5f,0.5f,0.5f);
        float radius = 1.0f;
        // The ID of this component type is "Collision"
        static std::string getID() { return "Collision"; }

        // Reads The data member .....to be decided..... from the json object
        void deserialize(const nlohmann::json &data) override;
    };

}