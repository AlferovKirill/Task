#pragma once

#include <vector>
#include <cmath>

namespace kin {
    using vvd = std::vector<std::vector<double>>;

    const double PI = 3.1415926;
    const int axesNum = 6;
    const int matrixDimension = 4;

    class Kinematic {
    public:
        Kinematic();
        void setThetaDegrees(std::vector<double>&& thetaDegrees);
        double degreesToRadianConvert(double degrees);
        void matrixMultiplication(vvd& result, vvd firstMatrix, vvd secondMatrix);
        void stepTransformMatrix(vvd& result, double theta, double a, double d, double alpha);
        std::vector<double> finalTransformMatrix();
        std::vector<double> getThetaDegrees();
    private:
        vvd allData;
    };
}
