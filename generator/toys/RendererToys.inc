#if SDL_VERSION_ATLEAST(3,4,0)

template<typename Guard = MJSDL_GUARD_DEFAULT>
MJSDL_NODISCARD static std::tuple<Renderer, GPUDevice> create_gpu_renderer(SDL_Window *window, SDL_GPUShaderFormat format_flags, Guard guard = {})
{
    SDL_GPUDevice *device = nullptr;
    SDL_Renderer *renderer = SDL_CreateGPURenderer(window, format_flags, &device);
    guard(renderer && device);
    return {Renderer{renderer}, GPUDevice{device}};
}

MJSDL_NODISCARD bool set_render_state(SDL_GPURenderState *state)
{
    return SDL_SetRenderGPUState(item, state);
}

#endif
