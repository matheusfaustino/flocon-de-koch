/*
 * Fichier : create_image.c
 * Description : Creation d'un fichier ppm a partir d'une image sous la forme
 *               d'un tableau uint32_t *
 */
#include "create_image.h"

struct RGB convertToRgb(uint32_t color)
{
    struct RGB rgbColor;

    rgbColor.r = color % 0x100;
    color /= (0x100);
    rgbColor.g = color % 0x100;
    color /= (0x100);
    rgbColor.b = color % 0x100;

    return rgbColor;
}

void create_image_ppm(uint32_t *pic, int32_t size_x, int32_t size_y, char *filename)
{
    struct RGB coleur;

    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo\n");
         // fprintf(stderr, "Error opening file: %s\n", strerror(errno));
    }

    // normalize
    size_x--;
    size_y--;

    // Header PPM
    fprintf(file, "%s \n%d %d \n%d \n", MAGIC_NUMBER, size_x, size_y, MAX_COULEUR);

    for (int32_t col = 0; col < size_y; col++) {
        for (int32_t ligne = 0; ligne < size_x; ligne++) {
            coleur = convertToRgb(pic[col * size_x + ligne]);
            fprintf(file, "%c%c%c", coleur.r, coleur.g, coleur.b);
        }
    }

    fclose(file);
}

