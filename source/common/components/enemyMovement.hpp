#pragma once

#include "../ecs/component.hpp"

#include <glm/glm.hpp>

namespace our
{

    class EnemyMovementComponent : public Component
    {
    public:
        // TODO: Add data members that are needed for the EnemyMovement system
        float speed = 0.01f; //The speed for which the zombie will move towards the player
        // The ID of this component type is "EnemyMovement"
        static std::string getID() { return "EnemyMovement"; }

        // Reads The data member .....to be decided..... from the json object
        void deserialize(const nlohmann::json &data) override;
    };

}