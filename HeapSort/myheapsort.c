    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <ctype.h>

    void strtolower(char *s)
    {
        for (int i=0; s[i]!='\0'; i++)
            s[i] = tolower(s[i]);
    }

    void swap(char **a, char **b)
    {
        char *temp = *a;
        *a = *b;
        *b = temp;
    }

    int parent(int i)
    {
        return (i-1)/2;
    }

    void Shift_Down(char **strings, int index, int N)
    {
        int root=index;
        while (1)
        {
            int left_child = 2*root + 1;
            int right_child = 2*root + 2;
            int _max = root;
            if (left_child < N)
                _max = (strcmp(strings[_max], strings[left_child]) < 0) ? _max : left_child;
            if (right_child < N)
                _max = (strcmp(strings[_max], strings[right_child]) < 0) ? _max : right_child;
            if (_max != root)
            {
                swap(&strings[_max],&strings[root]);
                root = _max;
            }
            else return;
        }
    }

    void Build_Max_Heap(char **strings, int N)
    {
        for (int i=parent(N-1); i>=0; i--)
            Shift_Down(strings, i, N);
    }

    void Heap_Sort(char **strings, int N, char *outputfile)
    {
        FILE *fp = NULL;
        fp = fopen(outputfile, "w");
        if (!fp)
        {
            printf("Unable to write to %s\n", outputfile);
            return;
        }
        while (N > 0)
        {
            fprintf(fp, "%s\n", strings[0]);
            swap(&strings[0], &strings[N-1]);
            N--;
            Shift_Down(strings, 0, N);
        }
        fclose(fp);
    }

    int main(int argc, char *argv[])
    {
        char *strings[1000];
        FILE *fp = NULL;
        char str[100];

        if (argc!=3)
        {
            printf("Insufficient or invalid arguments provided.\n");
            return 0;
        }

        fp = fopen(argv[1],"r");
        if (!fp)
        {
            printf("Unable to read %s\n",argv[1]);
            return 0;
        }
        
        int N = 0;
        while (N<1000 && fscanf(fp,"%s",str)==1)
        {
            strings[N] = (char *)malloc(strlen(str));
            strtolower(str);
            strcpy(strings[N], str);
            N++;
        }

        Build_Max_Heap(strings,N);
        Heap_Sort(strings, N, argv[2]);

        while(N--)
            free(strings[N - 1]);
        return 0;
    }
