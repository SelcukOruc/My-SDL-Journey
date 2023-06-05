namespace Colors
{

    struct Color
    {
        Uint8 r, g, b = 0;

        Color(Uint8 _r, Uint8 _g, Uint8 _b)
        {
            r = _r;
            g = _g;
            b = _b;
        }
    };

    Color White = {255, 255, 255},
          Red = {255, 0, 0},
          Gray = {128, 128, 128},
          Orange = {255, 95, 21},
          Green = {218, 247, 166},
          Black = {40, 40, 43},
          yellow = {255, 250, 205};

} // namespace Colors
