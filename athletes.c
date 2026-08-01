#include <stdio.h>

#define NUM_ATHLETES 5

struct Athlete {
    char name[50];
    char sport[50];
    int medals;
};

int main(void) {
    struct Athlete athletes[NUM_ATHLETES];

    for (int i = 0; i < NUM_ATHLETES; i++) {
        printf("Athlete %d\n", i + 1);

        printf("  Name: ");
        if (scanf("%49s", athletes[i].name) != 1) {
            fprintf(stderr, "Failed to read name.\n");
            return 1;
        }

        printf("  Sport: ");
        if (scanf("%49s", athletes[i].sport) != 1) {
            fprintf(stderr, "Failed to read sport.\n");
            return 1;
        }

        printf("  Medals won: ");
        if (scanf("%d", &athletes[i].medals) != 1) {
            fprintf(stderr, "Failed to read medal count.\n");
            return 1;
        }
    }

    int best = 0;
    for (int i = 1; i < NUM_ATHLETES; i++) {
        if (athletes[i].medals > athletes[best].medals) {
            best = i;
        }
    }

    printf("\nAthlete with the most medals:\n");
    printf("  Name: %s\n", athletes[best].name);
    printf("  Sport: %s\n", athletes[best].sport);
    printf("  Medals: %d\n", athletes[best].medals);

    return 0;
}
