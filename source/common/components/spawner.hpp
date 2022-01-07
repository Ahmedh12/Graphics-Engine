#pragma once

#include "../ecs/component.hpp"

#include <glm/glm.hpp>

namespace our {

    class SpawnerComponent : public Component {
    public:
        //TODO: Add data members that are needed for the spawner system
        int numberOfEnemies; //A number that indicates how many we need to respawn of that entity
        double lastRespawnTime = 0; //a timer to respawn every specific number of frames
        nlohmann::json EntityToRespawnJasonObj = {""};
        // The ID of this component type is "Spawner"
        static std::string getID() { return "Spawner"; }

        // Reads The data member .....to be decided..... from the json object
        void deserialize(const nlohmann::json& data) override;
    };

}