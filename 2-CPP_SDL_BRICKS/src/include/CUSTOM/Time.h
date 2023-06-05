struct Time
{
private:
    Uint32 currentTime = 0;
    Uint32 lastTime = 0;
    float _deltaTime = 0;

public:
    float deltaTime()
    {
        lastTime = currentTime;
        currentTime = SDL_GetPerformanceCounter();

        _deltaTime = (double)((currentTime - lastTime) * 1000 / (double)SDL_GetPerformanceFrequency());
        // cout << to_string(_deltaTime) << endl;
        return _deltaTime;
    }
};
