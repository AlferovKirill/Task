#include <stdio.h>
#include <errno.h>

#include "kinematic.h"

int main(int argc, char** argv) {
    const char* fileName;

    if (argc < 2) {
        fileName = "testData/degrees.txt";
    }
    else {
        fileName = argv[1];
    }

    FILE* file = fopen(fileName, "r");
    
    if (!file) {
        perror("Ошибка: ");
        return errno;
    }

    double* thetaDegrees = malloc(sizeof(double) * axesNum);

    for (int i = 0; i < axesNum; ++i) {
        if (fscanf(file, "%lf", thetaDegrees + i) != 1) {
            free(thetaDegrees);
            printf("Неправильный формат файла!\n");
            return errno;
        }
    }

    fclose(file);

    double* coordinates = malloc(3 * sizeof(double));

    for (int i = 0; i < axesNum; ++i) {
        thetaDegrees[i] = degreesToRadianConvert(thetaDegrees[i]);
    }

    finalTransformMatrix(coordinates, thetaDegrees);

    printf("x = %f\n", coordinates[0]);
    printf("y = %f\n", coordinates[1]);
    printf("z = %f\n", coordinates[2]);

    free(thetaDegrees);
    free(coordinates);

    return 0;
}
