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
#include "Material.h"
#include <glm/gtc/quaternion.hpp>
#include <rttr/type>
#include "MetadataType.h"

using namespace entityx;
using namespace glm;
using namespace GameEngine;
using namespace GameEngine::Editor;
using namespace rttr;
using namespace std;

void setupPropertiesFromVariant(type type, variant valueVariant);
bool setupPropertyFromVariant(property property, variant valueVariant);

void InspectorSystem::update(EntityManager &es, EventManager &events, TimeDelta dt) {
    es.each<Inspector>([this, &es, &events, dt] (Entity entity, Inspector &inspector) {
        if (ImGui::Begin("Inspector", NULL, 0)) {
            es.each<InspectorHighlight>([this, &es, &events, dt] (Entity entity, InspectorHighlight &highlight) {
                ImGui::Text("%s", entity.component<Name>()->name.c_str());

                for (type t : type::get_types()) {
                    if(t.get_metadata(MetadataType::Component).is_valid()) {
                        if(t.invoke("hasComponent", rttr::instance(), { entity }).get_value<bool>()) {
                            variant componentVariant = t.invoke("retrieveComponent", rttr::instance(), { entity });
                            if (ImGui::CollapsingHeader(((string)t.get_name()).c_str())) {
                                setupPropertiesFromVariant(t, componentVariant);
                            }
                        }
                    }
                }
            });
        }
        ImGui::End();
    });
};

void setupPropertiesFromVariant(type type, variant valueVariant) {
    for (auto& property : type.get_properties()) {
        if (!setupPropertyFromVariant(property, valueVariant)) {
            variant propertyVariant = property.get_value(valueVariant);
            setupPropertiesFromVariant(property.get_type(), propertyVariant);
        }
    }
}

bool setupPropertyFromVariant(property property, variant valueVariant)
{
    bool evaluated = true;
    variant propertyVariant = property.get_value(valueVariant);
    if (property.get_type() == type::get<vec3>()) {
        vec3 value = propertyVariant.get_value<vec3>();
        float values[3] = { value.x, value.y, value.z };
        if (ImGui::InputFloat3(((string)property.get_name()).c_str(), values)) {
            property.set_value(valueVariant, vec3(values[0], values[1], values[2]));
        }
    } else if (property.get_type() == type::get<quat>()) {
        vec3 value = glm::degrees(glm::eulerAngles(propertyVariant.get_value<quat>()));
        float values[3] = { value.x, value.y, value.z };
        if (ImGui::InputFloat3(((string)property.get_name()).c_str(), values)) {
            property.set_value(valueVariant, glm::quat(glm::radians(vec3(values[0], values[1], values[2]))));
        }
    } if (property.get_type() == type::get<float>()) {
        float value = propertyVariant.get_value<float>();
        if (ImGui::InputFloat(((string)property.get_name()).c_str(), &value)) {
            property.set_value(valueVariant, value);
        }
    } else if (propertyVariant.is_sequential_container()) {
        variant_sequential_view seq_variant = propertyVariant.create_sequential_view();
        for (int i = 0; i < seq_variant.get_size(); i++) {
            variant variant = seq_variant.get_value(i).extract_wrapped_value();
            if (variant.get_type() == type::get<Material *>()) {
                string name = variant.get_value<Material *>()->name;
                ImGui::BeginChild(((string)property.get_name()).c_str());
                if (ImGui::CollapsingHeader(name.c_str())) {
                    setupPropertiesFromVariant(variant.get_type(), variant);
                }
                ImGui::EndChild();
            }
        }
    } else evaluated = false;
    return evaluated;
}
