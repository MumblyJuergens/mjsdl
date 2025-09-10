MJSDL_NODISCARD bool set_fragment_uniforms(Uint32 slot_index, const void *data, Uint32 length)
{
    return SDL_SetGPURenderStateFragmentUniforms(item, slot_index, data, length);
}
