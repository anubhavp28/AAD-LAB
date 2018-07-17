#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

struct point_pair {
    int x1, y1;
    int x2, y2;
    double distance;
};

int points[100][2];

int aux_compare_x(const int *a, const int *b)
{
    if (a[0] < b[0])
        return -1;
    return 1;
}

int aux_compare_y(const int *a, const int *b)
{
    if (a[1] < b[1])
        return -1;
    return 1;
}

double min(double a, double b)
{
    return (a < b) ? a : b;
}

double dist(int a[2], int b[2])
{
    return sqrt( pow(a[0] - b[0], 2) + pow(a[1] - b[1], 2) );
}

struct point_pair brute_force(int p[][2], int size) 
{
    double min_dist = 1e20;
    int x1, y1, x2, y2;
    for (int i=0; i<size; i++)
    {
        for (int j=i+1; j<size; j++)
        {
            if (min_dist < 0 || dist(p[i], p[j]) < min_dist)
                min_dist = dist(p[i], p[j]);
                x1 = p[i][0];
                y1 = p[i][1];
                x2 = p[j][0];
                y2 = p[j][1];
        }
    }
    struct point_pair pp = {x1, y1, x2, y2, min_dist};
    return pp;
}

struct point_pair closest_pair(int x[][2], int y[][2], int size)
{
    if (size<=3)
        return brute_force(x, size);

    int x_mid = (size - 1) / 2;
    
    int lindex, rindex;
    lindex = rindex = 0;
    
    int left_y[size][2];
    int right_y[size][2];

    for (int i=0; i<size; i++)
    {
        if (y[i][0] <= x[x_mid][0])
        {
            left_y[lindex][0] = y[i][0];
            left_y[lindex][1] = y[i][1];
            lindex++;
        }
        else
        {
            right_y[rindex][0] = y[i][0];
            right_y[rindex][1] = y[i][1];
            rindex++;
        }
    }
    printf("lindex = %d, rindex = %d \n", lindex, rindex);
    for (int i=0; i<lindex; i++)
        printf("%d %d \n", left_y[i][0], left_y[i][1]);

    struct point_pair pp1, pp2;
    pp1 = closest_pair(x, left_y, x_mid + 1);
    pp2 = closest_pair(&x[x_mid + 1], right_y, size - x_mid - 1);

    double d1 = pp1.distance;
    double d2 = pp2.distance;

    printf("d1 = %lf, d2= %lf \n", d1, d2);

    double d = (d1 < d2) ? d1 : d2;

    int strip_points[size][2];
    int strip_points_i = 0;

    for (int i=0; i<size; i++)
    {
        if ( abs(y[i][0] - x[x_mid][0]) < d )
        {
            strip_points[strip_points_i][0] = y[i][0];
            strip_points[strip_points_i][1] = y[i][1];
            strip_points_i++;
        }
    }

    double min_cross_pair_dist = 1e20;
    int x1, y1, x2, y2;

    for (int i=0; i<strip_points_i; i++)
    {
        for (int j=i+1; j < strip_points_i && (strip_points[j][1] - strip_points[i][1]) < d; j++)
        {
            if (min_cross_pair_dist < 0 || dist(strip_points[j], strip_points[i]) < min_cross_pair_dist)
            {
                min_cross_pair_dist = dist(strip_points[j], strip_points[i]);
                x1 = strip_points[i][0];
                y1 = strip_points[i][1];
                x2 = strip_points[j][0];
                y2 = strip_points[j][1];
            }
        }
    }
    
    struct point_pair pp = {x1, y1, x2, y2, min(d, min_cross_pair_dist)};
    
    return pp;

}

int main()
{
    for (int i=0; i<100; i++)
    {
        points[i][0] = i;
        points[i][1] = rand() % 100;
    }
    
//    printf("BruteForce = %lf \n", brute_force(points, 100));

    int points_x[100][2];
    int points_y[100][2];

    memcpy(points_x, points, sizeof(points));
    memcpy(points_y, points, sizeof(points));

    qsort(points_x, 100, 2 * sizeof(int), aux_compare_x);
    qsort(points_y, 100, 2 * sizeof(int), aux_compare_y);

    struct point_pair pp = closest_pair(points_x, points_y, 100);

    printf("(%d,%d) (%d,%d) %lf", pp.x1, pp.y1, pp.x2, pp.y2, pp.distance);
}
