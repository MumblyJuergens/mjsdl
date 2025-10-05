#pragma once

#include <SDL3/SDL_storage.h>
#include <SDL3/SDL_timer.h>
#include <filesystem>
#include <vector>
#include "guard.hpp"

namespace mjsdl
{

template <typename DataType, typename Guard = MJSDL_GUARD_DEFAULT> std::vector<DataType> read_file_from_title(std::string_view filename, Guard guard = {})
{
    SDL_Storage *titleStorage = SDL_OpenTitleStorage(nullptr, 0);
    if (!titleStorage) return {};
    Uint64 length{};
    const auto path = std::filesystem::path{filename}.generic_string();
    auto result = SDL_GetStorageFileSize(titleStorage, path.c_str(), &length);
    guard(result);
    guard(length);
    std::vector<DataType> data(static_cast<size_t>(length) / sizeof(DataType));
    while (!SDL_StorageReady(titleStorage))
    {
        SDL_Delay(1);
    }
    result = SDL_ReadStorageFile(titleStorage, path.c_str(), data.data(), length);
    guard(result);
    SDL_CloseStorage(titleStorage);
    return data;
}

} // End of namespace mjsdl.
