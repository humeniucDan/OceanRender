//
// Created by koath on 12/1/2024.
//

#ifndef OPENGL4_HELLOWINDOW_WATER_H
#define OPENGL4_HELLOWINDOW_WATER_H

#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <vector>
#include "Tools/Shader.hpp"
#include "Tools/Mesh.hpp"

namespace waterObject{
    void generatePlane(float sideLength, int subdivisions, std::vector<gps::Vertex>& vertices, std::vector<unsigned int>& indices) {
        int resolution = subdivisions + 1; // Number
        float step = sideLength / subdivisions; // Step size between vertices
        vertices.clear();
        indices.clear();

        // Generate vertices
        for (int z = 0; z < resolution; z++) {
            for (int x = 0; x < resolution; x++) {
                float posX = x * step;
                float posY = 0.0f;
                float posZ = z * step;

                // Add vertex position (x, z, z)
                vertices.push_back(
                            {
                                {posX, posY, posZ},
                                {0.0f, 0.0f, 1.0f},
                                {0.0f, 0.0f}}
                        );
            }
        }

        // Generate indices for triangles
        for (int y = 0; y < subdivisions; ++y) {
            for (int x = 0; x < subdivisions; ++x) {
                int topLeft = y * resolution + x;
                int topRight = topLeft + 1;
                int bottomLeft = (y + 1) * resolution + x;
                int bottomRight = bottomLeft + 1;

                // Triangle 1
                indices.push_back(bottomLeft);
                indices.push_back(bottomRight);
                indices.push_back(topRight);

                // Triangle 2
                indices.push_back(bottomLeft);
                indices.push_back(topRight);
                indices.push_back(topLeft);
            }
        }
    }
}

#endif //OPENGL4_HELLOWINDOW_WATER_H
