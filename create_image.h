#ifndef _CREATE_IMAGE_H_
#define _CREATE_IMAGE_H_

#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#define MAGIC_NUMBER "P6"
#define MAX_COULEUR 255

struct RGB {
    uint32_t r;
    uint32_t g;
    uint32_t b;
};

extern void create_image_ppm(uint32_t *pic, int32_t size_x, int32_t size_y, char *filename);
extern struct RGB convertToRgb(uint32_t color);

#endif

