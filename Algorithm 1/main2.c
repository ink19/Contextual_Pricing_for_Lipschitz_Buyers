#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

typedef struct _interval_t {
    double x_begin;
    double x_end;
    double y_begin;
    double y_end;
    int depth;
    int split;
    struct _interval_t *small;
    struct _interval_t *big;
} interval_t;

double L = 1;
double init_interval_length = 0;
int init_interval_number = 0;

interval_t *y_data;

int init() {
    init_interval_number = ceil(L * 8);
    y_data = (interval_t *)malloc(sizeof(interval_t) * init_interval_number);
    init_interval_length = 1.0/init_interval_number;
    for (int loop_i = 0; loop_i < init_interval_number; ++loop_i) {
        (y_data + loop_i)->depth = 0;
        (y_data + loop_i)->x_begin = loop_i * init_interval_length;
        (y_data + loop_i)->x_end = (loop_i + 1) * init_interval_length;
        (y_data + loop_i)->y_begin = 0;
        (y_data + loop_i)->y_end = 1;
        (y_data + loop_i)->split = 0;
        (y_data + loop_i)->small = NULL;
        (y_data + loop_i)->big = NULL;
    }
}

double get_y(double x, interval_t **data) {
    int in_init_interval = x / init_interval_length;
    interval_t *temp_interval = y_data + in_init_interval;
    while(temp_interval->split != 0) {
        if(temp_interval->x_end - x > x - temp_interval->x_begin) {
            temp_interval = temp_interval->small;
        } else {
            temp_interval = temp_interval->big;
        }
    }
    *data = temp_interval;
    return (temp_interval->y_begin + temp_interval->y_end) / 2;
}

int split_interval(interval_t *data) {
    data->split = 1;

    data->small = (interval_t *)malloc(sizeof(interval_t));
    data->small->big = NULL;
    data->small->small = NULL;
    data->small->depth = data->depth + 1;
    data->small->split = 0;
    data->small->x_begin = data->x_begin;
    data->small->x_end = (data->x_end + data->x_begin) / 2;
    data->small->y_begin = data->y_begin;
    data->small->y_end  =data->y_end;

    data->big = (interval_t *)malloc(sizeof(interval_t));

    data->big->big = NULL;
    data->big->small = NULL;
    data->big->depth = data->depth + 1;
    data->big->split = 0;
    data->big->x_begin = (data->x_end + data->x_begin) / 2;
    data->big->x_end = data->x_end;
    data->big->y_begin = data->y_begin;
    data->big->y_end  =data->y_end;
}

double get_f(double x) {
    return x;
}

int free_interval(interval_t *data) {
    if(data->split == 1) {
        free_interval(data->big);
        free_interval(data->small);
    }
    if(data->depth != 0) {
        free(data);
    }
}

int print_interval_item(interval_t *data) {
    if(data->split == 1) {
        print_interval_item(data->small);
        print_interval_item(data->big);
    } else {
        printf("%lf,%lf,%lf,%lf\n", data->x_begin, data->x_end, data->y_end, data->y_begin);
    }
}

int print_interval() {
    for(int loop_i = 0; loop_i < init_interval_number; ++loop_i) {
        print_interval_item(y_data + loop_i);
    }
}

int destroy() {
    for(int loop_i = 0; loop_i < init_interval_number; ++loop_i) {
        free_interval(y_data + loop_i);
    }
}

int main() {
    int T = 10000000;
    double y_x, f_x, x, x_length, y_length;
    interval_t *temp_node;
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
        //printf("%lf,%lf\n", x, y_x);
        x_length = temp_node->x_end - temp_node->x_begin;
        f_x = get_f(x);
        if(y_x > f_x) {
            x = y_x + L * x_length;
            if(x < temp_node->y_end) {
                temp_node->y_end = x;
            }
        } else {
            x = y_x - L * x_length;
            if(x > temp_node->y_begin) {
                temp_node->y_begin = x;
            }
        }

        y_length = temp_node->y_end - temp_node->y_begin;
        if(y_length < 4 * L * x_length) {
            split_interval(temp_node);
        }
    }
    print_interval();
    destroy();
    return 0;
}