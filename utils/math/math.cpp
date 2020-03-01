#include "../../include.h"

auto Math::world_to_screen(v3 v3_world, float matrix[16], int width, int height) -> v2
{
    v4 convert;
    convert.x = (v3_world.x * matrix[0]) + (v3_world.y * matrix[4]) + (v3_world.z * matrix[8]) + matrix[12];
    convert.y = (v3_world.x * matrix[1]) + (v3_world.y * matrix[5]) + (v3_world.z * matrix[9]) + matrix[13];
    convert.z = (v3_world.x * matrix[2]) + (v3_world.y * matrix[6]) + (v3_world.z * matrix[10]) + matrix[14]; // not used
    convert.w = (v3_world.x * matrix[3]) + (v3_world.y * matrix[7]) + (v3_world.z * matrix[11]) + matrix[15];

    if (convert.w < 0.001f)
        return v2(-1, -1);

    v2 cam;
    cam.x = width / 2.0f;
    cam.y = height / 2.0f;

    v2 screen;
    screen.x = cam.x + (cam.x * convert.x / convert.w);
    screen.y = cam.y - (cam.y * convert.y / convert.w);

    return screen;
}

Math* math = new Math();