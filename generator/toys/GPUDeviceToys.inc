MJSDL_NODISCARD static GPUDevice create_with_properties(SDL_PropertiesID props)
{
    return GPUDevice{SDL_CreateGPUDeviceWithProperties(props)};
}
