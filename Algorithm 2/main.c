#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct _line_t {
    double k;
    double b;
    struct _line_t *next;
} line_t;

line_t S_inc, S_dec;

double L = 1;

void init() {
    line_t *temp_line;

    S_inc.next = NULL;
    S_dec.next = NULL;
}

void union_S_inc(double x, double y) {
    line_t *temp_line = (line_t *)malloc(sizeof(line_t));
    temp_line->b = x;
    temp_line->k = y;
    temp_line->next = S_inc.next;
    S_inc.next = temp_line;
}

void union_S_dec(double x, double y) {
    line_t *temp_line = (line_t *)malloc(sizeof(line_t));
    temp_line->b = x;
    temp_line->k = y;
    temp_line->next = S_dec.next;
    S_dec.next = temp_line;
}

double get_S_inc(double x) {
    double result = 1, temp_result;
    line_t *temp_line = S_inc.next;
    while(temp_line != NULL) {
        temp_result = temp_line->k + L * fabs(temp_line->b - x);
        if(temp_result < result) result = temp_result;
        temp_line = temp_line->next;
    }
    return result; 
} 

double get_S_dec(double x) {
    double result = 0, temp_result;
    line_t *temp_line = S_dec.next;
    while(temp_line != NULL) {
        temp_result = temp_line->k - L * fabs(temp_line->b - x);
        if(temp_result > result) result = temp_result;
        temp_line = temp_line->next;
    }
    return result;
} 

double get_y(double x) {
    return (get_S_inc(x) + get_S_dec(x)) / 2.0;
}

double get_f(double x) {
    return 0.5 * (x - 0.5) * (x - 0.5);
}

int main() {
    int T = 100;
    double y_x, f_x, x, x_length, y_length;
    init();
    srand(time((time_t *)NULL));
    // temp_node = &y_data;
    // while(temp_node->next != NULL) {
    //     printf("%lf,%lf,%lf,%lf\n", temp_node->begin, temp_node->end, temp_node->max, temp_node->min);
    //     temp_node =temp_node->next;
    // }
    while(T--) {
        x = (rand() / (double)RAND_MAX);
        y_x = get_y(x);
        f_x = get_f(x);
        if(y_x > f_x) {
            union_S_inc(x, y_x);
        } else {
            union_S_dec(x, y_x);
        }
    }

    line_t *temp_line = S_dec.next;
    while(temp_line != NULL) {
        printf("%lf,%lf,0\n", temp_line->b, temp_line->k);
        temp_line = temp_line->next;
    }
    temp_line = S_inc.next;
    while(temp_line != NULL) {
        printf("%lf,%lf,1\n", temp_line->b, temp_line->k);
        temp_line = temp_line->next;
    }
}