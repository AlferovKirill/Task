#include "Kinematic.h"

kin::Kinematic::Kinematic() {
    allData.resize(4);

    allData[0] = { 0, 0, 0, 0, 0, 0 };
    allData[1] = { 0, -0.8, -0.598, 0, 0, 0 };
    allData[2] = { 0.21, 0.193, -0.16, 0.25, 0.25, 0.25 };
    allData[3] = { PI / 2, 0, 0, PI / 2, -PI / 2, 0 };
}

void kin::Kinematic::setThetaDegrees(std::vector<double>&& thetaDegrees) {
    allData[0] = std::move(thetaDegrees);
}

double kin::Kinematic::degreesToRadianConvert(double degrees) {
    return PI * degrees / 180;
}

void kin::Kinematic::matrixMultiplication(vvd& result, vvd firstMatrix, vvd secondMatrix) {
    for(int i = 0; i < matrixDimension; i++) {
        for (int j = 0; j < matrixDimension; j++) {
            result[i][j] = 0;

            for(int k = 0; k < matrixDimension; k++) {
                result[i][j] += firstMatrix[i][k] * secondMatrix[k][j];
            }
        }
    }
}

void kin::Kinematic::stepTransformMatrix(vvd& result, double theta, double a, double d, double alpha) {
    double cTheta = std::cos(theta);
    double sTheta = std::sin(theta);
    double cAlpha = std::cos(alpha);
    double sAlpha = std::sin(alpha);

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

std::vector<double> kin::Kinematic::finalTransformMatrix() {
    vvd result(matrixDimension, std::vector<double>(matrixDimension, 0));
    vvd actualMatrix(matrixDimension, std::vector<double>(matrixDimension, 0));
    vvd nextMatrix(matrixDimension, std::vector<double>(matrixDimension, 0));

    stepTransformMatrix(result, degreesToRadianConvert(allData[0][0]), allData[1][0], allData[2][0], allData[3][0]);

    for (int i = 1; i < axesNum; i++) {
        stepTransformMatrix(actualMatrix, degreesToRadianConvert(allData[0][i]), allData[1][i], allData[2][i], allData[3][i]);
        matrixMultiplication(nextMatrix, result, actualMatrix);

        vvd temp = std::move(result);
        result = std::move(nextMatrix);
        nextMatrix = std::move(temp);
    }

    std::vector<double> coordinates(3, 0);

    coordinates[0] = result[0][3];
    coordinates[1] = result[1][3];
    coordinates[2] = result[2][3];

    return coordinates;
}

std::vector<double> kin::Kinematic::getThetaDegrees(){
    return allData[0];
}
