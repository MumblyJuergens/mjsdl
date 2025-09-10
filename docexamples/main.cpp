// Make sure the examples in the documentation are valid code at least.

#include "mjsdl/GPUDevice.hpp"
#include "mjsdl/Window.hpp"
#include "mjsdl/guard.hpp"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_gpu.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <mjsdl/mjsdl.hpp>
#include <stdexcept>

void sdl_example()
{
    SDL_Window *window = SDL_CreateWindow("Pure SDL", 800, 600, SDL_WINDOW_RESIZABLE);
    if (!window)
    {
        throw std::runtime_error{SDL_GetError()};
    }

    SDL_GPUDevice *device = SDL_CreateGPUDevice(
        SDL_GPU_SHADERFORMAT_SPIRV | SDL_GPU_SHADERFORMAT_DXIL | SDL_GPU_SHADERFORMAT_MSL, true, nullptr);
    if (!device)
    {
        SDL_DestroyWindow(window);
        throw std::runtime_error{SDL_GetError()};
    }

    if (!SDL_ClaimWindowForGPUDevice(device, window))
    {
        SDL_DestroyGPUDevice(device);
        SDL_DestroyWindow(window);
        throw std::runtime_error{SDL_GetError()};
    }

    SDL_DestroyGPUDevice(device);
    SDL_DestroyWindow(window);
}

void basic_mjsdl()
{
    mjsdl::Window window{"Some mjsdl", 800, 600, SDL_WINDOW_RESIZABLE};
    if (!window.is_valid())
    {
        throw std::runtime_error{SDL_GetError()};
    }

    mjsdl::GPUDevice device{SDL_GPU_SHADERFORMAT_SPIRV | SDL_GPU_SHADERFORMAT_DXIL | SDL_GPU_SHADERFORMAT_MSL, true,
                            nullptr};
    if (!device.is_valid())
    {
        throw std::runtime_error{SDL_GetError()};
    }

    if (!SDL_ClaimWindowForGPUDevice(device.get(), window.get()))
    {
        throw std::runtime_error{SDL_GetError()};
    }
}

void full_mjsdl()
{
    mjsdl::guard_throws guard;
    mjsdl::Window window{"Full mjsdl", 800, 600, SDL_WINDOW_RESIZABLE, guard};
    mjsdl::GPUDevice device{SDL_GPU_SHADERFORMAT_SPIRV | SDL_GPU_SHADERFORMAT_DXIL | SDL_GPU_SHADERFORMAT_MSL, true,
                            nullptr, guard};
    guard(SDL_ClaimWindowForGPUDevice(device.get(), window.get()));
}

std::tuple<mjsdl::Window, mjsdl::GPUDevice> buildsdl()
{
    // Rmember, in deep functions whitespace is your friend.

    auto guard = [](bool value) {
        if (value) return;
        const char *error = SDL_GetError();
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error in buildsdl: %s", error);
        throw mjsdl::ctor_error{error};
    };

    mjsdl::Window window{"Just spitballing", 800, 600, SDL_WINDOW_RESIZABLE, guard};
    mjsdl::GPUDevice device{SDL_GPU_SHADERFORMAT_SPIRV | SDL_GPU_SHADERFORMAT_DXIL | SDL_GPU_SHADERFORMAT_MSL, true,
                            nullptr, guard};

    guard(SDL_ClaimWindowForGPUDevice(device.get(), window.get()));

    return {std::move(window), std::move(device)};
}

void wrap_example()
{
    // Reduce cognitive load for the new guys, they don't need to see the details yet.
    auto [window, device] = buildsdl();
}

int main()
{
    sdl_example();
    basic_mjsdl();
    full_mjsdl();
}
