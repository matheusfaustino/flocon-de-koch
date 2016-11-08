/*
 * Fichier : koch_ihm.c
 * Description : Saisie et initialisation des parametres - flocon de koch
 */

#include "koch_fonctions.h"

void init_parameters(struct parameters *parameters, int argc, char *argv[])
{
    // if (argc != 7) { // 6 args
    //     printf("Você precisa passar todos os parametros...\n");
    //     exit(1);
    // }

    // nao recomendam o uso do atoi e do strtol. Preferivel usar o sscanf
    // usar while para ficar pedindo as informacoes de forma interativa + sscanf

    parameters->segment_length = (uint32_t) atoi(argv[1]);
    parameters->nb_iterations = (uint32_t)  atoi(argv[2]);
    parameters->fg_color = (uint32_t) strtol(argv[3], NULL, 0); // 0 porque começa com 0x
    parameters->bg_color = (uint32_t) strtol(argv[4], NULL, 0);
    parameters->outfile = argv[5];
    parameters->all_images = argc == 7 && argv[6] ? true : false;

    /*
    Ne marche pas...
    int noError = 1;
    char *hexaError = NULL;

    do {
        if (noError < 1) {
            printf("\nsegment_length: ");
            scanf("%s", argv[1]);
        }
        noError = sscanf(argv[1], "%u", &parameters->segment_length);
    } while (noError < 1);
    noError = 1;

    do {
        if (noError < 1) {
            printf("\nnb_iterations: ");
            scanf("%s", argv[2]);
        }
        noError = sscanf(argv[2], "%u", &parameters->nb_iterations);
    } while (noError < 1);
    noError = 1;

    do {
        if (*hexaError != '\0') {
            printf("\nfg_color: ");
            scanf("%s", argv[3]);
        }
        parameters->fg_color = (uint32_t) strtol(argv[3], &hexaError, 0);
    } while (*hexaError != '\0');
    hexaError = NULL;

    do {
        if (*hexaError != '\0') {
            printf("\nbg_color: ");
            scanf("%s", argv[4]);
        }
        parameters->bg_color = (uint32_t) strtol(argv[4], &hexaError, 0);
    } while (*hexaError != '\0');
    noError = 1;

    do {
        if (argc < 6) {
            printf("\noutfile: ");
            scanf("%s", argv[5]);
        }
        parameters->outfile = argv[5];
    } while (!parameters->outfile);
    */
}

void show_koch_list(struct list *koch)
{
    printf("\nShow Koch List\n");
    while(koch != NULL) {
        printf("(%u, %u) -> ", koch->x, koch->y);
        koch = koch->next;
    }
}

void show_parameters(const struct parameters *parameters)
{
    printf("Segment Length: %u \nNB Iterations: %u \nFG Color: 0x%x  \nBG Color: 0x%x \nOutfile: %s \nAll Images: %s\n"
        , parameters->segment_length, parameters->nb_iterations, parameters->fg_color, parameters->bg_color, parameters->outfile, parameters->all_images ? "true" : "false");
}
