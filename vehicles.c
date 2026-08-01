#include <stdio.h>

#define NUM_VEHICLES 5

struct Vehicle {
    char id[20];
    char type[30];
    double price;
};

int main(void) {
    struct Vehicle vehicles[NUM_VEHICLES];

    for (int i = 0; i < NUM_VEHICLES; i++) {
        printf("Vehicle %d\n", i + 1);

        printf("  Vehicle ID: ");
        if (scanf("%19s", vehicles[i].id) != 1) {
            fprintf(stderr, "Failed to read vehicle ID.\n");
            return 1;
        }

        printf("  Type: ");
        if (scanf("%29s", vehicles[i].type) != 1) {
            fprintf(stderr, "Failed to read type.\n");
            return 1;
        }

        printf("  Price: ");
        if (scanf("%lf", &vehicles[i].price) != 1) {
            fprintf(stderr, "Failed to read price.\n");
            return 1;
        }
    }

    int most = 0;
    int least = 0;
    for (int i = 1; i < NUM_VEHICLES; i++) {
        if (vehicles[i].price > vehicles[most].price) {
            most = i;
        }
        if (vehicles[i].price < vehicles[least].price) {
            least = i;
        }
    }

    printf("\nMost expensive vehicle:\n");
    printf("  ID: %s\n  Type: %s\n  Price: %.2f\n",
           vehicles[most].id, vehicles[most].type, vehicles[most].price);

    printf("\nLeast expensive vehicle:\n");
    printf("  ID: %s\n  Type: %s\n  Price: %.2f\n",
           vehicles[least].id, vehicles[least].type, vehicles[least].price);

    return 0;
}
