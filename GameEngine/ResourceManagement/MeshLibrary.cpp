//
//  MeshLibrary.cpp
//  GameEngine
//
//  Created by Felippe Durán on 14/09/17.
//  Copyright © 2017 Felippe Durán. All rights reserved.
//

#include "MeshLibrary.h"
#include <tiny_obj_loader.h>
#include "Mesh.h"
#include "MaterialLibrary.h"

using namespace std;
using namespace tinyobj;
using namespace GameEngine;

void CalcNormal(float n[3], float v0[3], float v1[3], float v2[3]);

MeshLibrary::~MeshLibrary() {
    
}

Mesh *MeshLibrary::loadMesh(const string& filename) {
    attrib_t attrib;
    vector<shape_t> shapes;
    vector<material_t> materialDatas;
    
    string err;
    LoadObj(&attrib, &shapes, &materialDatas, &err, filename.c_str());
    
    if (!err.empty()) { // `err` may contain warning message.
        cerr << err << endl;
    }
    
    vector<Material *> materials;
    materials.reserve(materialDatas.size());
    for (int i = 0; i < materialDatas.size(); i++) {
        material_t materialData = materialDatas[i];
        Material *material = materialLibrary->getMaterial(materialData);
        materials.push_back(material);
    }
    
    if (attrib.normals.empty()) {
        int normalIndex = 0;
        map<tuple<real_t, real_t, real_t>, int> normalMap;
        for (int i = 0; i < shapes.size(); i++) {
            shape_t& shape = shapes[i];
            for (int f = 0; f < shape.mesh.num_face_vertices.size(); f++) {
                //            int fv = shape.mesh.num_face_vertices[f];
                //            int fv = 3;
                mesh_t& mesh = shape.mesh;
                tinyobj::index_t& idx0 = mesh.indices[3 * f + 0];
                tinyobj::index_t& idx1 = mesh.indices[3 * f + 1];
                tinyobj::index_t& idx2 = mesh.indices[3 * f + 2];
                
                float v[3][3];
                for (int k = 0; k < 3; k++) {
                    int f0 = idx0.vertex_index;
                    int f1 = idx1.vertex_index;
                    int f2 = idx2.vertex_index;
                    
                    v[0][k] = attrib.vertices[3 * f0 + k];
                    v[1][k] = attrib.vertices[3 * f1 + k];
                    v[2][k] = attrib.vertices[3 * f2 + k];
                }
                
                float normal[3];
                CalcNormal(normal, v[0], v[1], v[2]);
                
                tuple<real_t, real_t, real_t> tuple(normal[0], normal[1], normal[2]);
                if (normalMap.find(tuple) == normalMap.end()) {
                    attrib.normals.push_back(normal[0]);
                    attrib.normals.push_back(normal[1]);
                    attrib.normals.push_back(normal[2]);
                    normalMap[tuple] = normalIndex;
                    normalIndex++;
                }
                
                idx0.normal_index = normalMap[tuple];
                idx1.normal_index = normalMap[tuple];
                idx2.normal_index = normalMap[tuple];
            }
        }
    }
    
    
    
    
    int nextCombinedIdx = 0;
    vector<int> combinedIndices;
    map<tuple<int, int, int>, int> indexMap;
    vector<glm::vec3> combinedVertices;
    vector<glm::vec3> combinedNormals;
    vector<glm::vec2> combinedTexCoords;
    vector<Submesh> submeshes;
    for (int i = 0; i < shapes.size(); i++) {
        shape_t& shape = shapes[i];
        int index_offset = 0;
        for (int f = 0; f < shape.mesh.num_face_vertices.size(); f++) {
            int fv = shape.mesh.num_face_vertices[f];
            // Loop over vertices in the face.
            for (size_t v = 0; v < fv; v++) {
                // access to vertex
                tinyobj::index_t idx = shape.mesh.indices[index_offset + v];
                
                int combinedIdx;
                tuple<int, int, int> tuple(idx.vertex_index, idx.normal_index, idx.texcoord_index);
                if (indexMap.find(tuple) != indexMap.end()) combinedIdx = indexMap[tuple];
                else {
                    
                    tinyobj::real_t vx = attrib.vertices[3*idx.vertex_index+0];
                    tinyobj::real_t vy = attrib.vertices[3*idx.vertex_index+1];
                    tinyobj::real_t vz = attrib.vertices[3*idx.vertex_index+2];
                    combinedVertices.push_back(glm::vec3(vx, vy, vz));
                    
                    if (idx.normal_index >= 0) {
                        tinyobj::real_t nx = attrib.normals[3*idx.normal_index+0];
                        tinyobj::real_t ny = attrib.normals[3*idx.normal_index+1];
                        tinyobj::real_t nz = attrib.normals[3*idx.normal_index+2];
                        combinedNormals.push_back(glm::vec3(nx, ny, nz));
                    }
                    
                    if (idx.texcoord_index >= 0) {
                        tinyobj::real_t tx = attrib.texcoords[2*idx.texcoord_index+0];
                        tinyobj::real_t ty = attrib.texcoords[2*idx.texcoord_index+1];
                        combinedTexCoords.push_back(glm::vec2(tx, ty));
                    }
                    
                    combinedIdx = nextCombinedIdx;
                    indexMap[tuple] = combinedIdx;
                    nextCombinedIdx = nextCombinedIdx + 1;
                }
                combinedIndices.push_back(combinedIdx);
            }
            index_offset += fv;
//
//            // per-face material
//            shape.mesh.material_ids[f];
        }
        int size = (int)shape.mesh.indices.size();
        int offset = (int)(combinedIndices.size() - shape.mesh.indices.size());
        submeshes.push_back(Submesh(shape.mesh.material_ids[0], offset, size));
    }
    
    Mesh *mesh = new Mesh(combinedVertices, combinedNormals, combinedTexCoords, combinedIndices, submeshes, materials);
    return mesh;
}

void CalcNormal(float n[3], float v0[3], float v1[3], float v2[3]) {
    float v10[3];
    v10[0] = v1[0] - v0[0];
    v10[1] = v1[1] - v0[1];
    v10[2] = v1[2] - v0[2];
    
    float v20[3];
    v20[0] = v2[0] - v0[0];
    v20[1] = v2[1] - v0[1];
    v20[2] = v2[2] - v0[2];
    
    n[0] = v20[1] * v10[2] - v20[2] * v10[1];
    n[1] = v20[2] * v10[0] - v20[0] * v10[2];
    n[2] = v20[0] * v10[1] - v20[1] * v10[0];
    
    float len2 = n[0] * n[0] + n[1] * n[1] + n[2] * n[2];
    if (len2 > 0.0f) {
        float len = sqrtf(len2);
        
        n[0] /= len;
        n[1] /= len;
        n[2] /= len;
    }
}
