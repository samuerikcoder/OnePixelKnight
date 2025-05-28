#include "libs.h"

Platform platforms[40];
int numPlatforms = 40;

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
    platforms[16] = (Platform){{2830, 400, SMALL_W, SMALL_H}, textureSmalld};
    platforms[17] = (Platform){{2630, 330, SMALL_W, SMALL_H}, textureSmallb};
    platforms[18] = (Platform){{2830, 260, SMALL_W, SMALL_H}, textureSmalld};
    platforms[19] = (Platform){{3030, 170, MEDIUM_W, MEDIUM_H}, textureMediumb};
    platforms[20] = (Platform){{3530, 400, SMALL_W, SMALL_H}, textureSmalld};
    platforms[21] = (Platform){{3730, 300, LARGE_W, LARGE_H}, textureLargeb};
    platforms[22] = (Platform){{3730, 500, LARGE_W, LARGE_H}, textureLarged};
    platforms[23] = (Platform){{4130, 600, MEDIUM_W, MEDIUM_H}, textureMediumd};
    platforms[24] = (Platform){{4130, 200, MEDIUM_W, MEDIUM_H}, textureMediumb};
    platforms[25] = (Platform){{4430, 300, MEDIUM_W, MEDIUM_H}, textureMediumb};
    platforms[26] = (Platform){{4430, 500, MEDIUM_W, MEDIUM_H}, textureMediumd};
    platforms[27] = (Platform){{4670, 200, SMALL_W, SMALL_H}, textureSmallb};
    platforms[29] = (Platform){{4830, 300, LARGE_W, LARGE_H}, textureLargeb};
    platforms[30] = (Platform){{4830, 500, SMALL_W, SMALL_H}, textureSmalld};
    platforms[31] = (Platform){{5130, 200, LARGE_W, LARGE_H}, textureLargeb};
    platforms[32] = (Platform){{5150, 550, MEDIUM_W, MEDIUM_H}, textureMediumd};
    platforms[33] = (Platform){{5430, 100, LARGE_W, LARGE_H}, textureLargeb};
    platforms[34] = (Platform){{5490, 600, SMALL_W, SMALL_H}, textureSmalld};
    platforms[35] = (Platform){{5730, 500, LARGE_W, LARGE_H}, textureLarged};

}
