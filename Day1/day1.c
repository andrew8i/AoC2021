#include <stdio.h>
#include <stdlib.h>

#define PERROR(x) \
        fprintf(stderr, "%s\n", x); \
        return -1;


int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        PERROR("missing args")
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        PERROR("Couldn't open input file")
    }

    if (feof(fp))
    {
        printf("Input file is empty? Not carrying on...\n");
        return 0;
    }

    int count, prev_depth = 0;
    size_t len = 0;
    char *line = NULL;
    if (getline(&line, &len, fp) < 0) // Get initial value
    {
        PERROR("Failed to read a new line from input file")
    }

    prev_depth = atoi(line);

    while(getline(&line, &len, fp) >= 0)
    {
        int depth = atoi(line);
        if (depth > prev_depth) // Depth has increased
        {
            count++;
        }

        prev_depth = depth;
    }

    printf("Depth changed: %d times.\n", count);

    return 0;
}
