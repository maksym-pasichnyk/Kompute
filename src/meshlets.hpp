//
// Created by Maksym Pasichnyk on 26.01.2024.
//
#pragma once

#include "glm_utils.hpp"

struct Vertex {
    f32vec3 Position;
    f32vec4 Colour;
    f32vec2 Texcoord;
};

struct Meshlet {
    u32 VertexBegin;
    u32 VertexCount;
    u32 PrimitiveBegin;
    u32 PrimitiveCount;
};