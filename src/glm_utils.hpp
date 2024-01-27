//
// Created by Maksym Pasichnyk on 26.01.2024.
//
#pragma once

#include "pch.hpp"

struct alignas(8) f32vec2 {
    f32 x;
    f32 y;
};

struct alignas(16) f32vec3 {
    f32 x;
    f32 y;
    f32 z;
};

struct alignas(16) f32vec4 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
};