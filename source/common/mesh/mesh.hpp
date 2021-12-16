#pragma once

#include <glad/gl.h>
#include "vertex.hpp"

namespace our
{

#define ATTRIB_LOC_POSITION 0
#define ATTRIB_LOC_COLOR 1
#define ATTRIB_LOC_TEXCOORD 2
#define ATTRIB_LOC_NORMAL 3

    class Mesh
    {
        // Here, we store the object names of the 3 main components of a mesh:
        // A vertex array object, A vertex buffer and an element buffer
        unsigned int VBO, EBO;
        unsigned int VAO;
        // We need to remember the number of elements that will be draw by glDrawElements
        GLsizei elementCount;

    public:
        // The constructor takes two vectors:
        // - vertices which contain the vertex data.
        // - elements which contain the indices of the vertices out of which each rectangle will be constructed.
        // The mesh class does not keep a these data on the RAM. Instead, it should create
        // a vertex buffer to store the vertex data on the VRAM,
        // an element buffer to store the element data on the VRAM,
        // a vertex array object to define how to read the vertex & element buffer during rendering
        Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &elements)
        {
            // TODO: Write this function
            //  remember to store the number of elements in "elementCount" since you will need it for drawing
            //  For the attribute locations, use the constants defined above: ATTRIB_LOC_POSITION, ATTRIB_LOC_COLOR, etc

            // DONE:Ahmed Hussien
            /*fisrt step is requesting opengl to assingn memory locations for the data*/
            glGenVertexArrays(1, &VAO); // generating vertex array
            glBindVertexArray(VAO);     // Using the vertex array object we created above

            glGenBuffers(1, &VBO);              // create buffer to store vertices data
            glBindBuffer(GL_ARRAY_BUFFER, VBO); // Using the vertex buffer we created above

            glGenBuffers(1, &EBO);                      // create buffer to store element data for gl draw elements
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO); // Using the  elements buffer we created above

            elementCount = elements.size();

            /*then we need to fill the buffers with the data we want to keep on the VRAM */
            
            // data() is a built in function in vector stl that returns a pointer to the internal array allocations of the vector
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW); // moving the vertices data to the buffer on the VRAM
            /*
            the preceding four function calls are configuration calls as to specify for the vertex shaders how to read the vertex data
            */
            glVertexAttribPointer(ATTRIB_LOC_POSITION, 3,GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);      
            glVertexAttribPointer(ATTRIB_LOC_COLOR, 4, GL_UNSIGNED_BYTE, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex,color));          
            glVertexAttribPointer(ATTRIB_LOC_TEXCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex,tex_coord));
            glVertexAttribPointer(ATTRIB_LOC_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex,normal));
            /*
            1)  The first parameter specifies which vertex attribute we want to configure. Remember that we specified the location of
                the position vertex attribute in the vertex shader with layout (location = 0). This sets the location of the vertex attribute to 0 and
                since we want to pass data to this vertex attribute, we pass in 0.
            2)  The next argument specifies the size of the vertex attribute. The vertex attribute is a vec3 so it is composed of 3 values.
            3)  The third argument specifies the type of the data which is GL_FLOAT (a vec* in GLSL consists of floating point values).
            4)  The next argument specifies if we want the data to be normalized. If we're inputting integer data types (int, byte) and we've set this to GL_TRUE,
                the integer data is normalized to 0 (or -1 for signed data) and 1 when converted to float. This is not relevant for us so we'll leave this at GL_FALSE.
            5)  The fifth argument is known as the stride and tells us the space between consecutive vertex attributes.
                Since the next set of position data is located exactly 3 times the size of a float away we specify that value as the stride.
                Note that since we know that the array is tightly packed (there is no space between the next vertex attribute value)
                we could've also specified the stride as 0 to let OpenGL determine the stride (this only works when values are tightly packed).
                Whenever we have more vertex attributes we have to carefully define the spacing between each vertex attribute
            6)  The last parameter is of type void* and thus requires that weird cast. This is the offset of where the position data begins in the buffer.
                Since the position data is at the start of the data array this value is just 0. We will explore this parameter in more detail later on
            */

           /*
           The preceding function enable the attribute locations, as to be able to write in to them.
           Attributes are diabled by default
           */
            glEnableVertexAttribArray(ATTRIB_LOC_POSITION);
            glEnableVertexAttribArray(ATTRIB_LOC_COLOR);
            glEnableVertexAttribArray(ATTRIB_LOC_TEXCOORD);
            glEnableVertexAttribArray(ATTRIB_LOC_NORMAL);

            /*
            The steps above are repeated to the elements buffer
            In summary:
            1)  calling glBufferData to load the data on the buffer created on the video ram
            2)  calling glEnableAttribArray to be able to enable the location on the VRAM to be written to.
            */
            glBufferData(GL_ELEMENT_ARRAY_BUFFER,elements.size()*sizeof(unsigned int),elements.data(),GL_STATIC_DRAW);

        }

        // this function should render the mesh
        void draw()
        {
            // TODO: Write this function
            //Done: Ahmed Hussien
            glDrawElements(GL_TRIANGLES, elementCount, GL_UNSIGNED_INT, (void*)0);
        }

        // this function should delete the vertex & element buffers and the vertex array object
        ~Mesh()
        {

            // TODO: Write this function
            // Done: Ahmed Hussien
            glDeleteVertexArrays(1,&VAO);
            glDeleteBuffers(1,&VBO);
            glDeleteBuffers(1,&EBO);
        }

        Mesh(Mesh const &) = delete;
        Mesh &operator=(Mesh const &) = delete;
    };

}