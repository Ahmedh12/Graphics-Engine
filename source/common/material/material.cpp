#include "material.hpp"

#include "../asset-loader.hpp"
#include "deserialize-utils.hpp"

namespace our {

    // This function should setup the pipeline state and set the shader to be used
    void Material::setup() const {
        //TODO: Write this function
        //Done:Sandra Hany
        //pipelineState.setup()->setup the pipeline state
        pipelineState.setup();
        //shader->use();->sets the shader to be used
        shader->use();
        
        
    }

    // This function read the material data from a json object
    void Material::deserialize(const nlohmann::json& data){
        if(!data.is_object()) return;

        if(data.contains("pipelineState")){
            pipelineState.deserialize(data["pipelineState"]);
        }
        shader = AssetLoader<ShaderProgram>::get(data["shader"].get<std::string>());
        transparent = data.value("transparent", false);
    }

    // This function should call the setup of its parent and
    // set the "tint" uniform to the value in the member variable tint 
    void TintedMaterial::setup() const {
        //TODO: Write this function
        //Done:Sandra Hany
        //Material::setup();->call the setup of the parent of TintedMaterial
        Material::setup();
     
       //shader->set("tint",tint);-> set the "tint" uniform to the value in the member variable tint 
       shader->set("tint",tint);
  
    }

    // This function read the material data from a json object
    void TintedMaterial::deserialize(const nlohmann::json& data){
        Material::deserialize(data);
        if(!data.is_object()) return;
        tint = data.value("tint", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    }

    // This function should call the setup of its parent and
    // set the "alphaThreshold" uniform to the value in the member variable alphaThreshold
    // Then it should bind the texture and sampler to a texture unit and send the unit number to the uniform variable "tex" 
    void TexturedMaterial::setup() const {
        //TODO: Write this function
        //Done:Sandra Hany
        TintedMaterial::setup(); 
        //Here we set the "alphaThreshold" uniform to the value in the member variable alphaThreshold
        shader->set("alphaThreshold",alphaThreshold);
        // Here we set the active texture unit to 0 then bind the texture to it
        glActiveTexture(GL_TEXTURE0);
        texture->bind();
        // Then we bind the sampler to unit 0
        sampler->bind(0);
        // Then we send 0 (the index of the texture unit we used above) to the "tex" uniform
        shader->set("tex", 0);
        
       
    }

    // This function read the material data from a json object
    void TexturedMaterial::deserialize(const nlohmann::json& data){
        TintedMaterial::deserialize(data);
        if(!data.is_object()) return;
        alphaThreshold = data.value("alphaThreshold", 0.0f);
        texture = AssetLoader<Texture2D>::get(data.value("texture", ""));
        sampler = AssetLoader<Sampler>::get(data.value("sampler", ""));
    }

    void LitMaterial::setup() const
    {
        Material::setup();
        glActiveTexture(GL_TEXTURE0);
        Albedo_tex->bind();
        sampler->bind(0);
        shader->set("material.albedo",0);
        glActiveTexture(GL_TEXTURE1);
        Specular_tex->bind();
         sampler->bind(1);
         shader->set("material.specular",1);
        glActiveTexture(GL_TEXTURE2);
        Roughness_tex->bind();
         sampler->bind(2);
         shader->set("material.roughness",2);
        glActiveTexture(GL_TEXTURE3);
        Emission_tex->bind();
         sampler->bind(3);
         shader->set("material.ambient_occlusion",3);
        glActiveTexture(GL_TEXTURE4);
        AO_tex->bind();
         sampler->bind(4);
         shader->set("material.emission",4);

    }

    void LitMaterial::deserialize(const nlohmann::json& data)
    {
        Material::deserialize(data);
        if(!data.is_object()) return;

        Albedo_tex = AssetLoader<Texture2D>::get(data.value("albedo_tex",""));
        Specular_tex = AssetLoader<Texture2D>::get(data.value("specular_tex",""));
        Roughness_tex = AssetLoader<Texture2D>::get(data.value("roughness_tex",""));
        Emission_tex = AssetLoader<Texture2D>::get(data.value("emission_tex",""));
        AO_tex = AssetLoader<Texture2D>::get(data.value("AO_tex",""));
        sampler = AssetLoader<Sampler>::get(data.value("sampler", ""));
    }

}
