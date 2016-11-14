/*
 * Fichier : koch_main.c
 * Description : Trace de fractales geometriques - flocon de koch - programme principal
 */

#include <stdlib.h>
#include <math.h>
#include "koch_fonctions.h"
#include "koch_ihm.h"
#include "create_image.h"

int main(int argc, char **argv)
{
    struct parameters *params = malloc(sizeof *params);
    struct list *points = malloc(sizeof *points);
    uint32_t image_size;

    init_parameters(params, argc, argv);
    show_parameters(params);

    // la formule de la circonférence du triangle
    image_size = (sqrt(3.0)/3.0 * params->segment_length) * 2.5;

    init_koch(&points, image_size, params->segment_length);

    if (params->all_images) {
        char *filename_all;

        for (uint32_t i = 0; i < params->nb_iterations; i++) {
            uint32_t *picture_part = NULL;

            init_picture(&picture_part, image_size, params->bg_color);

            generer_koch(points, 1);
            render_image_bresenham(picture_part, points, image_size, params->fg_color);

            asprintf(&filename_all, "%02d_%s", i, params->outfile);
            create_image_ppm(picture_part, image_size, image_size, filename_all);

            free(picture_part);
        }
    } else {
        uint32_t *picture = NULL;

        init_picture(&picture, image_size, params->bg_color);
        generer_koch(points, params->nb_iterations);
        render_image_bresenham(picture, points, image_size, params->fg_color);

        create_image_ppm(picture, image_size, image_size, params->outfile);
        free(picture);
    }

    free(params);
    free_koch(points);
    return EXIT_SUCCESS;
}
