#pragma once

#include "../ecs/component.hpp"

#include <glm/glm.hpp>

namespace our
{

    class WinLoseComponent : public Component
    {
    public:
        // TODO: Add data members that are needed for the WinLose system
        int score = 0;
        int lives = 0;
        // The ID of this component type is "WinLose"
        static std::string getID() { return "WinLose"; }

        // Reads The data member .....to be decided..... from the json object
        void deserialize(const nlohmann::json &data) override;
    };

}