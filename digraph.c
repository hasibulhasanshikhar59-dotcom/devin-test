/* Mini Project 2 (odd group number)
 * Randomly generate a directed graph as an adjacency matrix (n vertices),
 * find in-degree and out-degree of every vertex, show that
 * sum of in-degrees == sum of out-degrees, and measure the time (ms)
 * taken by the degree-counting step for n = 1000, 2000, 3000, 4000, 5000.
 *
 * Compile: gcc digraph.c -o digraph
 * Run:     ./digraph
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXN 5000

/* one static matrix reused for every n, so no dynamic memory is needed */
static char adj[MAXN][MAXN];
static int in_deg[MAXN];
static int out_deg[MAXN];

/* fill adj[0..n-1][0..n-1] with random 0/1, no self loop */
void generate_graph(int n)
{
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (i == j)
                adj[i][j] = 0;
            else
                adj[i][j] = rand() % 2;
        }
    }
}

/* count in-degree and out-degree of all vertices */
void find_degrees(int n)
{
    int i, j;
    for (i = 0; i < n; i++) {
        in_deg[i] = 0;
        out_deg[i] = 0;
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (adj[i][j] == 1) {
                out_deg[i] = out_deg[i] + 1;
                in_deg[j] = in_deg[j] + 1;
            }
        }
    }
}

int main(void)
{
    int sizes[5] = {1000, 2000, 3000, 4000, 5000};
    int k, i, n;
    long sum_in, sum_out;
    clock_t start, end;
    double time_ms;
    FILE *fp;

    srand((unsigned int) time(NULL));

    fp = fopen("timing.csv", "w");
    if (fp == NULL) {
        printf("Cannot open timing.csv\n");
        return 1;
    }
    fprintf(fp, "n,time_ms\n");

    for (k = 0; k < 5; k++) {
        n = sizes[k];

        generate_graph(n);

        start = clock();
        find_degrees(n);
        end = clock();
        time_ms = ((double) (end - start)) * 1000.0 / CLOCKS_PER_SEC;

        sum_in = 0;
        sum_out = 0;
        for (i = 0; i < n; i++) {
            sum_in = sum_in + in_deg[i];
            sum_out = sum_out + out_deg[i];
        }

        printf("n = %d\n", n);
        printf("  first 5 vertices (vertex: in-degree, out-degree)\n");
        for (i = 0; i < 5 && i < n; i++)
            printf("    %d: %d, %d\n", i, in_deg[i], out_deg[i]);
        printf("  sum of in-degrees  = %ld\n", sum_in);
        printf("  sum of out-degrees = %ld\n", sum_out);
        if (sum_in == sum_out)
            printf("  EQUAL (verified)\n");
        else
            printf("  NOT EQUAL (error)\n");
        printf("  time for degree step = %.3f ms\n\n", time_ms);

        fprintf(fp, "%d,%.3f\n", n, time_ms);
    }

    fclose(fp);
    printf("Timing data written to timing.csv (open it in Excel for the line graph)\n");
    return 0;
}
