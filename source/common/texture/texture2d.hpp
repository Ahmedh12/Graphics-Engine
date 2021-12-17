#pragma once

#include <glad/gl.h>

namespace our {

    // This class defined an OpenGL texture which will be used as a GL_TEXTURE_2D
    class Texture2D {
        // The OpenGL object name of this texture 
        GLuint name = 0;
    public:
        // This constructor creates an OpenGL texture and saves its object name in the member variable "name" 
        Texture2D() {
            //TODO: Complete this function
            //Done:Sandra Hany 
            // glGenTextures: generate texture names
            //1: number of texture names to be generated 
            // name: array in which the generated texture names are stored
            glGenTextures(1, &name);
        };

        // This deconstructor deletes the underlying OpenGL texture
        ~Texture2D() { 
            //TODO: Complete this function
             //Done:Sandra Hany 
             //glDeleteTextures :delete named textures
             //1: number of textures to be deleted.
             //name: Specifies an array of textures to be deleted.
            glDeleteTextures(1,&name);
        }

        // This method binds this texture to GL_TEXTURE_2D
        void bind() const {
            //TODO: Complete this function
            //Done:Sandra Hany 
            //glBindTexture: bind a named texture to a texturing target
            // GL_TEXTURE_2D: Specifies the target of the active texture unit to which the texture is bound
           // name: Specifies the name of a texture.
            glBindTexture(GL_TEXTURE_2D,name);
        }

        // This static method ensures that no texture is bound to GL_TEXTURE_2D
        static void unbind(){
            //TODO: Complete this function
            //Done:Sandra Hany 
           glBindTexture(GL_TEXTURE_2D,0);
        }

        Texture2D(const Texture2D&) = delete;
        Texture2D& operator=(const Texture2D&) = delete;
    };
    
}
