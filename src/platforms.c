#include "libs.h"

Platform platforms[24];
int numPlatforms = 24;

void  initPlatforms(void)
{
    platforms[0] = (Platform){{0, 620, 700, 1000}};
    platforms[1] = (Platform){{200, 520, MEDIUM_W, MEDIUM_H}, textureMediumb};
    platforms[2] = (Platform){{320, 420, MEDIUM_W, MEDIUM_H}, textureMediumd};
    platforms[3] = (Platform){{420, 320, SMALL_W, SMALL_H}, textureSmalld};
    platforms[4] = (Platform){{320, 220, SMALL_W, SMALL_H}, textureSmallb};
    platforms[5] = (Platform){{400, 150, LARGE_W, LARGE_H}, textureLarged};
    platforms[6] = (Platform){{770, 150, LARGE_W, LARGE_H}, textureLargeb};
    platforms[7] = (Platform){{580, 270, SMALL_W, SMALL_H}, textureSmalld};
    platforms[8] = (Platform){{780, 280, MEDIUM_W, MEDIUM_H}, textureMediumb};
    platforms[9] = (Platform){{1200, 180, MEDIUM_W, MEDIUM_H}, textureMediumd};
    platforms[10] = (Platform){{1050, 390, LARGE_W, LARGE_H}, textureLargeb};
    platforms[11] = (Platform){{1430, 390, LARGE_W, LARGE_H}, textureLargeb};
    platforms[12] = (Platform){{1830, 450, SMALL_W, SMALL_H}, textureSmallb};
    platforms[13] = (Platform){{2030, 500, SMALL_W, SMALL_H}, textureSmalld};
    platforms[14] = (Platform){{2330, 460, SMALL_W, SMALL_H}, textureSmallb};
    platforms[15] = (Platform){{2630, 490, MEDIUM_W, MEDIUM_H}, textureMediumd};


}
