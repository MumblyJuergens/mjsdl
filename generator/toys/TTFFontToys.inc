template<typename Guard = MJSDL_GUARD_DEFAULT>
MJSDL_NODISCARD Font(SDL_IOStream *src, bool closeio, float ptsize, Guard guard = {})
{
    item = TTF_OpenFontIO(src, closeio, ptsize);
    guard(item);
}
 
