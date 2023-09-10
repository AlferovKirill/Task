#ifndef KINEMATIC_H
#define KINEMATIC_H

#include <math.h>
#include <stdlib.h>

#define axesNum 6
#define PI 3.1415926

static const int matrixDimension = 4;

static double a_i[axesNum] = { 0, -0.8, -0.598, 0, 0, 0 };
static double d_i[axesNum] = { 0.21, 0.193, -0.16, 0.25, 0.25, 0.25 };
static double alphaRadian[axesNum] = { PI / 2, 0, 0, PI / 2, -PI / 2, 0 };

double** matrixCreate();
void matrixFree(double** matrix);
void matrixMultiplication(double** result, double** firstMatrix, double** secondMatrix);
double degreesToRadianConvert(double degrees);
void stepTransformMatrix(double** result, double theta, double a, double d, double alpha);
void finalTransformMatrix(double* coordinates, double* thetaDegrees);

#endif