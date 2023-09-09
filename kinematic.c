#include "kinematic.h"

double** matrixCreate() {
    double** result = malloc(8 * matrixDimension);

    for (int i = 0; i < 4; i++) {
        result[i] = malloc(matrixDimension * sizeof(double));
    }

    return result;
}

void matrixFree(double** matrix) {
    for (int i = 0; i < matrixDimension; i++) {
        free(matrix[i]);
    }

    free(matrix);
}

void matrixMultiplication(double** result, double** firstMatrix, double** secondMatrix) {
    for(int i = 0; i < matrixDimension; i++) {
        for (int j = 0; j < matrixDimension; j++) {
            result[i][j] = 0.0;

            for(int k = 0; k < 4; k++) {
                result[i][j] += firstMatrix[i][k] * secondMatrix[k][j];
            }
        }
    }
}

double degreesToRadianConver(double degrees) {
    return PI * degrees / 180;
}

void stepTransformMatrix(double** result, double theta, double a, double d, double alpha) {
    double cTheta = cos(theta);
    double sTheta = sin(theta);
    double cAlpha = cos(alpha);
    double sAlpha = sin(alpha);

    result[0][0] = cTheta;
    result[0][1] = -sTheta * cAlpha;
    result[0][2] = sTheta * sAlpha;
    result[0][3] = a * cTheta;

    result[1][0] = sTheta;
    result[1][1] = cTheta * cAlpha;
    result[1][2] = -cTheta * sAlpha;
    result[1][3] = a * sTheta;

    result[2][0] = 0.0;
    result[2][1] = sAlpha;
    result[2][2] = cAlpha;
    result[2][3] = d;

    result[3][0] = 0.0;
    result[3][1] = 0.0;
    result[3][2] = 0.0;
    result[3][3] = 1.0;
}

void finalTransformMatrix(double* coordinates, double* thetaDegrees) {
    double** result = matrixCreate();
    double** actualMatrix = matrixCreate();
    double** nextMatrix = matrixCreate();

    stepTransformMatrix(result, thetaDegrees[0], a_i[0], d_i[0], alphaRadian[0]);

    for (int i = 1; i < axesNum; i++) {
        stepTransformMatrix(actualMatrix, thetaDegrees[i], a_i[i], d_i[i], alphaRadian[i]);
        matrixMultiplication(nextMatrix, result, actualMatrix);

        double** temp = result; 
        result = nextMatrix;
        nextMatrix = temp;
    }

    coordinates[0] = result[0][3];
    coordinates[1] = result[1][3];
    coordinates[2] = result[2][3];
    
    matrixFree(result);
    matrixFree(actualMatrix);
    matrixFree(nextMatrix);
}