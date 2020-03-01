#pragma once

class Math
{
public:
    auto world_to_screen(v3 v3_world, float matrix[16], int width, int height) ->v2;
};

extern Math* math;