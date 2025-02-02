#include <stdio.h>
#include <time.h>

int main() {

    time_t start, end;
    time(&start);
    printf("Menu code running...\n");
    for (int i = 0; i < 1000000000; i++);
    time(&end);
    double time_spent = difftime(end, start);
    printf("Time spent in menu: %.2f seconds\n", time_spent);

    return 0;
}
