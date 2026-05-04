#include <stdio.h>
#include <stdlib.h>

struct Car {
    int position;
    double time;
};

int compare(const void* a, const void* b) {
    struct Car* c1 = (struct Car*)a;
    struct Car* c2 = (struct Car*)b;
    return c2->position - c1->position;
}

int carFleet(int target, int position[], int speed[], int n) {
    struct Car* cars = (struct Car*)malloc(n * sizeof(struct Car));

    for (int i = 0; i < n; i++) {
        cars[i].position = position[i];
        cars[i].time = (double)(target - position[i]) / speed[i];
    }

    qsort(cars, n, sizeof(struct Car), compare);

    int fleets = 0;
    double maxTime = 0;

    for (int i = 0; i < n; i++) {
        if (cars[i].time > maxTime) {
            fleets++;
            maxTime = cars[i].time;
        }
    }

    free(cars);
    return fleets;
}

int main() {
    int target = 12;
    int position[] = {10, 8, 0, 5, 3};
    int speed[] = {2, 4, 1, 1, 3};
    int n = 5;

    printf("%d\n", carFleet(target, position, speed, n));
    return 0;
}