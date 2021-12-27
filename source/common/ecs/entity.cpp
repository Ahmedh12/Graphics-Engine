#include "entity.hpp"
#include "../deserialize-utils.hpp"
#include "../components/component-deserializer.hpp"

#include <glm/gtx/euler_angles.hpp>

namespace our
{
    // target: returns the transformation matrix from the entity's local space to the world space
    // Remember that you can get the transformation matrix from this entity to its parent from "localTransform"
    // To get the local to world matrix, you need to combine this entities matrix with its parent's matrix and
    // its parent's parent's matrix and so on till you reach the root.
    glm::mat4 Entity::getLocalToWorldMatrix() const
    {
        //TODO: Write this function
        // Millania Sameh ===> DONE
        glm::mat4 transformation_matrix = localTransform.toMat4(); // initialize an identity matrix
        Entity *current = parent;                          // initialize current's parent pointer
        while (current != nullptr)                         // while loop to get all the parents up to the root
        {
            transformation_matrix = current->localTransform.toMat4() * transformation_matrix; // ===>TODO check this order
            current = current->parent;                                               // advance the pointer to get next parent
        }
        return transformation_matrix;
    }

    // Deserializes the entity data and components from a json object
    void Entity::deserialize(const nlohmann::json &data)
    {
        if (!data.is_object())
            return;
        name = data.value("name", name);
        localTransform.deserialize(data);
        if (data.contains("components"))
        {
            if (const auto &components = data["components"]; components.is_array())
            {
                for (auto &component : components)
                {
                    deserializeComponent(component, this);
                }
            }
        }
    }

}