#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    FILE *file = fopen("data/sample_data.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    clock_t start_time = clock();

    char buffer[256];
    int total_chars = 0;

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        int i = 0;
        while (buffer[i] != '\0') {
            total_chars++;
            i++;
        }
    }

    fclose(file);

    clock_t end_time = clock();
    double run_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("Read %d characters from data/sample_data.txt\n", total_chars);
    printf("Runtime: %.6f seconds\n", run_time);

    return 0;
}
