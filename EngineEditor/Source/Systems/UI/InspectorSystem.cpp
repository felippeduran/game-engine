//
//  InspectorSystem.cpp
//  GameEngine
//
//  Created by Felippe Durán on 28/09/18.
//  Copyright © 2018 Felippe Durán. All rights reserved.
//

#include "InspectorSystem.h"
#include "Inspector.h"
#include "imgui.h"
#include "InspectorHighlight.h"

#include "Name.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "DirectionalLight.h"
#include "Camera.h"

#include "Mesh.h"
#include "Material.h"

using namespace entityx;
using namespace glm;

void InspectorSystem::update(EntityManager &es, EventManager &events, TimeDelta dt) {
    es.each<Inspector>([this, &es, &events, dt] (Entity entity, Inspector &inspector) {
        if (ImGui::Begin("Inspector", NULL, 0)) {
            es.each<InspectorHighlight>([this, &es, &events, dt] (Entity entity, InspectorHighlight &highlight) {
                ImGui::Text("%s", entity.component<Name>()->name.c_str());
                
                if (ImGui::CollapsingHeader("Transform")) {
                    ComponentHandle<Transform> transform = entity.component<Transform>();
                    float position[3] = { transform->localPosition.x, transform->localPosition.y, transform->localPosition.z };
                    if (ImGui::InputFloat3("Position", position)) {
                        transform->localPosition = vec3(position[0], position[1], position[2]);
                    }
                    
                    vec3 rotation = glm::degrees(glm::eulerAngles(transform->localRotation));
                    float localRotation[3] = { rotation.x, rotation.y, rotation.z };
                    if (ImGui::InputFloat3("Rotation", localRotation)) {
                        transform->localRotation = glm::quat(glm::radians(vec3(localRotation[0], localRotation[1], localRotation[2])));
                    }
                    
                    float localScale[3] = { transform->localScale.x, transform->localScale.y, transform->localScale.z };
                    if (ImGui::InputFloat3("Scale", localScale)) {
                        transform->localScale = vec3(localScale[0], localScale[1], localScale[2]);
                    }
                }
                
                if (entity.has_component<MeshRenderer>() && ImGui::CollapsingHeader("Mesh Renderer")) {
                    ImGui::BeginChild("MeshRendererChild");
                    ComponentHandle<MeshRenderer> renderer = entity.component<MeshRenderer>();
                    
                    for (Material *material : renderer->mesh->materials) {
                        std::string materialName = material->name + "##" + std::to_string((long)material);
                        if (ImGui::CollapsingHeader(materialName.c_str())) {
                            
                            std::string ambientName = "Ambient Color##" + std::to_string((long)material);
                            float ambient[3] = { material->colorAmbient.r, material->colorAmbient.g, material->colorAmbient.b };
                            if (ImGui::InputFloat3(ambientName.c_str(), ambient)) {
                                material->colorAmbient = vec3(ambient[0], ambient[1], ambient[2]);
                            }
                            
                            std::string diffuseName = "Diffuse Color##" + std::to_string((long)material);
                            float diffuse[3] = { material->colorDiffuse.r, material->colorDiffuse.g, material->colorDiffuse.b };
                            if (ImGui::InputFloat3(diffuseName.c_str(), diffuse)) {
                                material->colorDiffuse = vec3(diffuse[0], diffuse[1], diffuse[2]);
                            }
                            
                            std::string specularName = "Specular Color##" + std::to_string((long)material);
                            float specular[3] = { material->colorSpecular.r, material->colorSpecular.g, material->colorSpecular.b };
                            if (ImGui::InputFloat3(specularName.c_str(), specular)) {
                                material->colorSpecular = vec3(specular[0], specular[1], specular[2]);
                            }
                            
                            ImGui::PushItemWidth(100);
                            ImGui::InputFloat("Dissolve", &material->dissolve);
                            ImGui::InputFloat("Refraction Index", &material->refractionIndex);
                            ImGui::InputFloat("Specular Exponent", &material->specularExponent);
                            ImGui::PopItemWidth();
                        }
                    }
                    ImGui::EndChild();
                }
                
                if (entity.has_component<Camera>() && ImGui::CollapsingHeader("Camera")) {
                    ComponentHandle<Camera> camera = entity.component<Camera>();
                    ImGui::PushItemWidth(100);
                    ImGui::InputFloat("Field Of View", &camera->fieldOfView);
                    ImGui::InputFloat("Aspect Ratio", &camera->aspectRatio);
                    ImGui::InputFloat("Near Plane", &camera->zNear);
                    ImGui::InputFloat("Far Plane", &camera->zFar);
                    ImGui::PopItemWidth();
                }
                
                if (entity.has_component<DirectionalLight>() && ImGui::CollapsingHeader("Directional Light")) {
                    ComponentHandle<DirectionalLight> light = entity.component<DirectionalLight>();
                    
                    std::string ambientName = "Ambient Color##" + std::to_string((long)light);
                    float ambient[3] = { light->ambient.r, light->ambient.g, light->ambient.b };
                    if (ImGui::InputFloat3(ambientName.c_str(), ambient)) {
                        light->ambient = vec3(ambient[0], ambient[1], ambient[2]);
                    }
                    
                    std::string diffuseName = "Diffuse Color##" + std::to_string((long)light);
                    float diffuse[3] = { light->diffuse.r, light->diffuse.g, light->diffuse.b };
                    if (ImGui::InputFloat3(diffuseName.c_str(), diffuse)) {
                        light->diffuse = vec3(diffuse[0], diffuse[1], diffuse[2]);
                    }
                    
                    std::string specularName = "Specular Color##" + std::to_string((long)light);
                    float specular[3] = { light->specular.r, light->specular.g, light->specular.b };
                    if (ImGui::InputFloat3(specularName.c_str(), specular)) {
                        light->specular = vec3(specular[0], specular[1], specular[2]);
                    }
                }
            });
        }
        ImGui::End();
    });
};
