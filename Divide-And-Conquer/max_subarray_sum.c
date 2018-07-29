#include <stdio.h>
#include <limits.h>

int max(int a, int b, int c)
{
    int m = (a > b) ?  a : b;
    return (m > c) ? m : c;
}

int max_sum_subarray(int ar[], int low, int high)
{
    if (low == high)
        return ar[low];

    int mid = low + (high - low)/2;

    int l = max_sum_subarray(ar, low, mid);
    int r = max_sum_subarray(ar, mid + 1, high);

    int max_left_sum = INT_MIN;
    int sum = 0;
    for (int i=mid; i>=low; i--)
    {
        sum += ar[i];
        if (sum > max_left_sum)
            max_left_sum = sum;
    }
    
    sum = 0;
    int max_right_sum = INT_MIN;
    for (int i=mid + 1; i<=high; i++)
    {
        sum += ar[i];
        if (sum > max_right_sum)
            max_right_sum = sum;
    }

    int max_crossing_sum = max_left_sum + max_right_sum;

    return max(l, r, max_crossing_sum);
}

int main()
{
    int ar[] = {-3, -5, -2, -9, -6, -11, -4};
    int N = sizeof(ar)/sizeof(ar[0]);
    printf(" %d ", max_sum_subarray(ar, 0, N - 1));
}
