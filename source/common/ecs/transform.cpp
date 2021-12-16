#include "entity.hpp"
#include "../deserialize-utils.hpp"

#include <glm/gtx/euler_angles.hpp>

namespace our
{

    // This function computes and returns a matrix that represents this transform
    // Remember that the order of transformations is: Scaling, Rotation then Translation
    // HINT: to convert euler angles to a rotation matrix, you can use glm::yawPitchRoll
    glm::mat4 Transform::toMat4() const
    {
        // TODO: Write this function
        // Done: Ahmed Hussien
        /*
        The preceeding Function Calls construct the transformation matrices
        given the values of the vec3 data Members of the struct
        */
        glm::mat4 translateMat = glm::translate(glm::mat4(1.0), position);
        glm::mat4 rotateMat = glm::yawPitchRoll(rotation.y, rotation.x, rotation.z);
        glm::mat4 scaleMat = glm::scale(glm::mat4(1.0), scale);

        /*
        Multiplying the 3 matrices in the following order
        translate * rotate * scale
        yields the overall transformation matrix
        */

        glm::mat4 transformation(1.0);
        transformation = translateMat * rotateMat * scaleMat;
        return transformation;
    }

    
    // Deserializes the entity data and components from a json object
    void Transform::deserialize(const nlohmann::json &data)
    {
        position = data.value("position", position);
        rotation = glm::radians(data.value("rotation", glm::degrees(rotation)));
        scale = data.value("scale", scale);
    }

}