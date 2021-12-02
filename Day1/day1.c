#include <stdio.h>
#include <stdlib.h>

#define P_ERROR(x) \
            perror(x); \
            return -1;

#define WINDOW_SIZE 3


int window(FILE **f)
{
    if (f == NULL || *f == NULL)
    {
        P_ERROR("File pointer or final pointer address is null");
    }

    ssize_t curr_fpos = ftell(*f);
    int prev_depth = 0;
    size_t n = 0; // Used for getline() only
    ssize_t index, count = 0;
    char *line = NULL;

    if ((count = getline(&line, &n, *f)) < 0)
    {
        // Can't have gotten to end of file yet, so only errors at this stage
        P_ERROR("init Failed to read a new line from input file");
    }

    prev_depth = atoi(line);
    index = count + curr_fpos;

    for (int i = 0; i < WINDOW_SIZE - 1; ++i)
    {
        if ((count = getline(&line, &n, *f)) < 0)
        {
            if (feof(*f))
            {
                /*
                 * Chance that given odd multiple of the window size in the file
                 * we don't want to try read a line that isn't there.
                 */
                return prev_depth;
            }
            else if (ferror(*f))
            {
                P_ERROR("for Failed to read a new line from input file");
            }
        }

        prev_depth += atoi(line);
    }

    fseek(*f, index, SEEK_SET);

    return prev_depth;
}

int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        fprintf(stderr, "missing args");
        return -1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Couldn't open input file");
        return -1;
    }

    if (feof(fp))
    {
        printf("Input file is empty? Not carrying on...\n");
        return 0;
    }

    int prev_depth = window(&fp); // Initial value
    if (prev_depth < 0)
    {
        return -1;
    }

    int count = 0;
    while (!feof(fp))
    {
        if (ferror(fp))
        {
            P_ERROR(NULL);
        }

        int depth = window(&fp);
        if (prev_depth < 0)
        {
            return -1;
        }

        if (depth > prev_depth) // Depth has increased
        {
            count++;
        }

        prev_depth = depth;
    }

    printf("Depth changed: %d times.\n", count);

    fclose(fp);
    return 0;
}

