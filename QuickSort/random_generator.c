#include <stdio.h>
#include <stdlib.h>

int main()
{
    unsigned long int i = 0;
    FILE *fp;
    fp = fopen("random.txt", "w");
    for (; i<50000; i++)
    {
        fprintf(fp, "%d\n", rand());
    }
    fclose(fp);
}

