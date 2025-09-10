MJSDL_NODISCARD const char *get_variable(const char *name)
{
    return SDL_GetEnvironmentVariable(item, name);
}

MJSDL_NODISCARD auto get_variables() {
    char **result = SDL_GetEnvironmentVariables(item);
    return unique_sdlmem<char*>{result};
}

MJSDL_NODISCARD bool set_variable(const char *name, const char *value, bool overwrite)
{
    return SDL_SetEnvironmentVariable(item, name, value, overwrite);
}

MJSDL_NODISCARD bool unset_variable(const char *name)
{
    return SDL_UnsetEnvironmentVariable(item, name);
}
