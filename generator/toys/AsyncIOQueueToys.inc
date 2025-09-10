MJSDL_NODISCARD bool get_result(SDL_AsyncIOOutcome *outcome)
{
    return SDL_GetAsyncIOResult(item, outcome);
}

MJSDL_NODISCARD bool wait_result(SDL_AsyncIOOutcome *outcome, Sint32 timeoutMS)
{
    return SDL_WaitAsyncIOResult(item, outcome, timeoutMS);
}
