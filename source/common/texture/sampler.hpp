#pragma once

#include <glad/gl.h>
#include <json/json.hpp>
#include <glm/vec4.hpp>

namespace our {

    // This class defined an OpenGL sampler
    class Sampler {
        // The OpenGL object name of this sampler 
        GLuint name;
    public:
        // This constructor creates an OpenGL sampler and saves its object name in the member variable "name" 
        Sampler() {
            //TODO: Complete this function
            //Done:Sandra Hany
            //glGenSamplers —> generate sampler object names
            //1st argument-> specifies the number of sampler object names to generate.
            //2nd argument-> specifies an array in which the generated sampler object names are stored.
            glGenSamplers(1,&name);
        };

        // This deconstructor deletes the underlying OpenGL sampler
        ~Sampler() { 
            //TODO: Complete this function
           //Done:Sandra Hany
           //glDeleteSamplers —> delete named sampler objects
           //1st argument-> specifies the number of sampler objects to be deleted.
           //2nd argument -> specifies an array of sampler objects to be deleted.
           glDeleteSamplers(1,&name);
         }

        // This method binds this sampler to the given texture unit
        void bind(GLuint textureUnit) const {
            //TODO: Complete this function
            //Done:Sandra Hany
            //glBindSampler —> bind a named sampler to a texturing target
            //1st argument-> specifies the index of the texture unit to which the sampler is bound.
            //2nd argument-> specifies the name of a sampler.
            
            glBindSampler(textureUnit,name);
        }

        // This static method ensures that no sampler is bound to the given texture unit
        static void unbind(GLuint textureUnit){
            //TODO: Complete this function
            //Done:Sandra Hany
           //glBindTexture(textureUnit,0);
           //glDeleteTextures(1,&textureUnit);
            glBindSampler(textureUnit,0);
        }

        // This function sets a sampler paramter where the value is of type "GLint"
        // This can be used to set the filtering and wrapping parameters
        void set(GLenum parameter, GLint value) const {
            //TODO: Complete this function
           //Done:Sandra Hany
           // 1st argument->specifies the sampler object whose parameter to modify.
           // 2nd argument -> specifies the symbolic name of a sampler parameter.
           // 3rd argument -> specifies the value of 2nd argument.
            glSamplerParameteri(name, parameter, value);
        }

        // This function sets a sampler paramter where the value is of type "GLfloat"
        // This can be used to set the "GL_TEXTURE_MAX_ANISOTROPY_EXT" parameter
        void set(GLenum parameter, GLfloat value) const {
            //TODO: Complete this function
            //Done:Sandra Hany
            glSamplerParameterf(name, parameter,value);
        }

        // This function sets a sampler paramter where the value is of type "GLfloat[4]"
        // This can be used to set the "GL_TEXTURE_BORDER_COLOR" parameter
        void set(GLenum parameter, glm::vec4 value) const {
            //3rd argument-> specifies a pointer to an array where the value or values of pname are stored.
            glSamplerParameterfv(name, parameter, &(value.r));
        }

        // Given a json object, this function deserializes the sampler state
        void deserialize(const nlohmann::json& data);

        Sampler(const Sampler&) = delete;
        Sampler& operator=(const Sampler&) = delete;
    };

}
