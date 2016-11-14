/*
 * Fichier : koch_fonctions.c
 * Description : Trace de fractales geometriques - flocon de koch - generation des points et rendu des lignes
 */

#include "koch_fonctions.h"

/* Initialisation de la liste chainee koch correspondant au triangle
   de Koch initial */
void init_koch(struct list **koch, uint32_t size, uint32_t segment_length)
{
    struct list *pointb = malloc(sizeof *pointb);
    struct list *pointc = malloc(sizeof *pointc);
    uint32_t alteur = (float)segment_length*sqrt(3.0)/2.0;

    (*koch)->x = (size - segment_length)/2;
    (*koch)->y = size - alteur;

    pointb->x = size/2;
    pointb->y = size;

    pointc->x = (*koch)->x + segment_length;
    pointc->y = size - alteur;

    (*koch)->next = pointb;
    pointb->next = pointc;
    pointc->next = NULL;
}

/* Initialisation de l'image avec la couleur de fond definie dans les
   parametres */
void init_picture(uint32_t **picture, uint32_t size, uint32_t bg_color)
{
    const uint32_t SIZE_TABLEAU = size * size;

    (*picture) = (uint32_t *) calloc(SIZE_TABLEAU, sizeof(uint32_t));
    for (uint32_t i = 0; i < SIZE_TABLEAU; ++i) {
        (*picture)[i] = bg_color;
    }
}

/* Calcul de la fractale de Koch apres un nombre d'iterations donne ;
   generation de la liste chainee koch correspondante */
void generer_koch(struct list *koch, uint32_t nb_iterations)
{
    struct list *nextCoordenate;
    struct list *initialPoint = koch, *koch_aux = koch;
    const double COS60 = cos(M_PI / 180.0 * 60.0);
    const double SIN60 = sin(M_PI / 180.0 * 60.0);

    for (uint32_t i = 0; i < nb_iterations; i++) {
        koch_aux = initialPoint;
        while (koch_aux != NULL) {
            struct list *segment1 = (struct list *) malloc(sizeof(struct list));
            struct list *segment2 = (struct list *) malloc(sizeof(struct list));
            struct list *segment3 = (struct list *) malloc(sizeof(struct list));

            // pour le dernier élément
            nextCoordenate = koch_aux->next == NULL ? initialPoint : koch_aux->next;

            segment1->x = (uint32_t)((float)koch_aux->x + ((float)nextCoordenate->x - (float)koch_aux->x) / 3.0);
            segment1->y = (uint32_t)((float)koch_aux->y + ((float)nextCoordenate->y - (float)koch_aux->y) / 3.0);

            segment3->x = (uint32_t)((float)koch_aux->x + 2.0 * ((float)nextCoordenate->x - (float)koch_aux->x) / 3.0);
            segment3->y = (uint32_t)((float)koch_aux->y + 2.0 * ((float)nextCoordenate->y - (float)koch_aux->y) / 3.0);

            segment2->x = (uint32_t)(((float)segment1->x + (float)segment3->x) * COS60 - ((float)segment3->y - (float)segment1->y) * SIN60);
            segment2->y = (uint32_t)((float)segment1->y + (float)segment3->y) * COS60 + ((float)segment3->x - (float)segment1->x) * SIN60;

            segment1->next = segment2;
            segment2->next = segment3;
            segment3->next = koch_aux->next == NULL ? NULL : nextCoordenate;

            koch_aux->next = segment1;
            koch_aux = segment3->next;
        }
    }
}

/*
 * Tracez des lignes
 */
void line(uint32_t *picture, uint32_t size, uint32_t fg_color, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2)
{
    int32_t dx, dy, sx, sy, err, e2;

    dx = abs(x2 - x1);
    dy = abs(y2 - y1);
    sx = x1 < x2 ? 1 : -1;
    sy = y1 < y2 ? 1 : -1;
    err = dx - dy;

    while (true) {
        picture[y1 * (size - 1) + x1] = fg_color;

        if (x1 == x2 && y1 == y2)
            break;

        e2 = err;
        if (e2 > -dx) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dy) {
            err += dx;
            y1 += sy;
        }
    }
}

/* Rendu image via algorithme bresehem - version generalisee
   simplifiee */
void render_image_bresenham(uint32_t *picture, struct list *koch, uint32_t size, uint32_t fg_color)
{
    struct list *point2, *point1 = koch;

    while (point1->next != NULL) {
        point2 = point1->next;

        line(picture, size, fg_color, point1->x, point1->y, point2->x, point2->y);

        point1 = point1->next;
    }
    // dernière ligne lien avec le premiere
    line(picture, size, fg_color, point1->x, point1->y, koch->x, koch->y);
}

/* Liberation de la memoire allouee a la liste chainee */
void free_koch(struct list *koch)
{
    struct list *item;
    while(koch != NULL) {
        item = koch;
        koch = koch->next;
        free(item);
    }
}
