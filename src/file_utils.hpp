//
// Created by Maksym Pasichnyk on 26.01.2024.
//
#pragma once

#include "pch.hpp"

static auto file_read_bytes(std::string const& path) -> std::optional<std::vector<char>> {
    if (auto stream = std::ifstream(path, std::ios::binary); stream.is_open()) {
        return std::vector(std::istreambuf_iterator(stream), {});
    }
    return std::nullopt;
}