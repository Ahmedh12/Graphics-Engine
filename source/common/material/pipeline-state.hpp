#pragma once

#include <glad/gl.h>
#include <glm/vec4.hpp>
#include <json/json.hpp>

namespace our
{
    // There are some options in the render pipeline that we cannot control via shaders
    // such as blending, depth testing and so on
    // Since each material could require different options (e.g. transparent materials usually use blending),
    // we will encapsulate all these options into a single structure that will also be responsible for configuring OpenGL's pipeline
    struct PipelineState
    {
        // This set of pipeline options specifies whether face culling will be used or not and how it will be configured
        struct
        {
            bool enabled = false;
            GLenum culledFace = GL_BACK;
            GLenum frontFace = GL_CCW;
        } faceCulling;

        // This set of pipeline options specifies whether depth testing will be used or not and how it will be configured
        struct
        {
            bool enabled = false;
            GLenum function = GL_LEQUAL;
        } depthTesting;

        // This set of pipeline options specifies whether blending will be used or not and how it will be configured
        struct
        {
            bool enabled = false;
            GLenum equation = GL_FUNC_ADD;
            GLenum sourceFactor = GL_SRC_ALPHA;
            GLenum destinationFactor = GL_ONE_MINUS_SRC_ALPHA;
            glm::vec4 constantColor = {0, 0, 0, 0};
        } blending;

        // These options specify the color and depth mask which can be used to
        // prevent the rendering/clearing from modifying certain channels of certain targets in the framebuffer
        glm::bvec4 colorMask = {true, true, true, true}; // To know how to use it, check glColorMask
        bool depthMask = true;                           // To know how to use it, check glDepthMask

        // This function should set the OpenGL options to the values specified by this structure
        // For example, if faceCulling.enabled is true, you should call glEnable(GL_CULL_FACE), otherwise, you should call glDisable(GL_CULL_FACE)
        void setup() const
        {
            // TODO: Write this function
            // DONE: Ahmed Hussien
            
            /*
            setting the values of the color mask and depth mask
            */

            glColorMask(colorMask.x, colorMask.y, colorMask.z, colorMask.w); // Specify whether red, green, blue, and alpha can or cannot be written into the frame buffer.
                                                                             // The initial values are all GL_TRUE, indicating that the color components can be written.
            glDepthMask(depthMask);                                          // Specifies wether to allow drawing on the depth buffer e.g. false --> dont draw keep the values alraedy stored

            /*
            checking if face Culling is enabled
            and hence setting it parameters
            */
            if (faceCulling.enabled) // This option prevent drawing of back Faces
            {
                glEnable(GL_CULL_FACE);             // This call allows enabling the face culling option
                glCullFace(faceCulling.culledFace); // Specifies whether front- or back-facing facets are candidates for culling, Deafault is GL_BACK
                glFrontFace(faceCulling.frontFace); // Specifies the orientation of front-facing polygons. GL_CW and GL_CCW are accepted. The initial value is GL_CCW
            }
            else
                glDisable(GL_CULL_FACE);

            /*
            checking if depth testing is enabled
            and hence setting it parameters
            */
            if (depthTesting.enabled)
            {
                glEnable(GL_DEPTH_TEST);            // This call allows enabling the  depth testing option
                glDepthFunc(depthTesting.function); //  Specifies the depth comparison function. Symbolic constants GL_NEVER, GL_LESS, GL_EQUAL, GL_LEQUAL,
                                                    // GL_GREATER, GL_NOTEQUAL, GL_GEQUAL, and GL_ALWAYS are accepted. The initial value is GL_LESS.
            }
            else
                glDisable(GL_DEPTH_TEST);

            /*
            checking if Blending is enabled
            and hence setting it parameters
            */

            if (blending.enabled)
            {
                glEnable(GL_BLEND);                 // This calls enables the blending option, it is related to transperency and depends on order of drawing
                glBlendEquation(blending.equation); // specifies how source and destination colors are combined.
                                                    // It must be GL_FUNC_ADD, GL_FUNC_SUBTRACT, GL_FUNC_REVERSE_SUBTRACT, GL_MIN, GL_MAX.

                glBlendFunc(blending.sourceFactor, blending.destinationFactor); // Pixels can be drawn using a function that blends the incoming (source) RGBA values
                                                                                // with the RGBA values that are already in the frame buffer (the destination values). Blending is
                                                                                // initially disabled. Use glEnable and glDisable with argument GL_BLEND to enable and disable blending.

                glBlendColor(blending.constantColor.x, blending.constantColor.y, blending.constantColor.z, blending.constantColor.w); // The GL_BLEND_COLOR may be used to calculate
                                                                                                                                      // the source and destination blending factors
                                                                                                                                      // mawgodeen fl eq. al heya glBlendFunc
                                                                                                                                      // intialy equals zero
            }
            else
                glDisable(GL_BLEND);
        }

        // Given a json object, this function deserializes a PipelineState structure
        void deserialize(const nlohmann::json &data);
    };

}