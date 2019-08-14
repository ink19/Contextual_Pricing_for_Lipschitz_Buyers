#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct __interval_t{
    double begin;
    double end;
    double max;
    double min;
    int r;
    struct __interval_t *next;
} interval_t;

int L = 1;

interval_t y_data;

void init() {
    int j = ceil(8 * L); 
    double step = 1.0 / j;
    y_data.next = NULL;
    interval_t *temp_node;
    for (int loop_i = 0; loop_i < j; ++loop_i) {
        temp_node = (interval_t *) malloc(sizeof(interval_t));
        temp_node->next = y_data.next;
        y_data.next = temp_node;
        temp_node->begin = (7 - loop_i) * step;
        temp_node->end = (8 - loop_i) * step;
        temp_node->max = 1;
        temp_node->min = 0;
        temp_node->r = 0;
    }
}

double get_y(double x, interval_t **pre_node) {
    interval_t *temp_node = &y_data;
    while(temp_node->next != NULL) {
        //printf("%lf,%lf\n", temp_node->next->begin, temp_node->next->end);
        if(temp_node->next->begin <= x && temp_node->next->end >= x) {
            break;
        }
        temp_node = temp_node->next;
    }
    //printf("\n");
    *pre_node = temp_node;
    return (temp_node->next->max + temp_node->next->min)/2;
}

double get_f(double x) {
    return sin(exp(x));
}

double symmetric_loss(double f_x, double y_x) {
    return fabs(f_x - y_x);
}

int main() {
    int T = 1000;
    double y_x, f_x, x, x_length, y_length;
    interval_t *temp_node, *temp_node2;
    init();
    srand(time((time_t *)NULL));
    // temp_node = &y_data;
    // while(temp_node->next != NULL) {
    //     printf("%lf,%lf,%lf,%lf\n", temp_node->begin, temp_node->end, temp_node->max, temp_node->min);
    //     temp_node =temp_node->next;
    // }
    while(T--) {
        x = (rand() / (double)RAND_MAX);
        y_x = get_y(x, &temp_node);
        x_length = temp_node->next->end - temp_node->next->begin;
        f_x = get_f(x);
        if(y_x > f_x) {
            x = y_x + L * x_length;
            if(x < temp_node->next->max) {
                temp_node->next->max = x;
            }
        } else {
            x = y_x - L * x_length;
            if(x > temp_node->next->min) {
                temp_node->next->min = x;
            }
        }

        y_length = temp_node->next->max - temp_node->next->min;
        if(y_length < 4 * L * x_length) {
            x_length /= 2;
            temp_node->next->end = temp_node->next->begin + x_length;
            temp_node->next->r += 1;
            temp_node2 = (interval_t *)malloc(sizeof(interval_t));
            temp_node2->begin = temp_node->next->end;
            temp_node2->end = temp_node2->begin + x_length;
            temp_node2->max = temp_node->next->max;
            temp_node2->min = temp_node->next->min;
            temp_node2->r = temp_node->next->r;

            temp_node2->next = temp_node->next->next;
            temp_node->next->next = temp_node2;
        }
    }
    temp_node = &y_data;
    while(temp_node->next != NULL) {
        printf("%lf,%lf,%lf,%lf\n", temp_node->next->begin, temp_node->next->end, temp_node->next->max, temp_node->next->min);
        temp_node =temp_node->next;
    }
    return 0;
}