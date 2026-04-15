#pragma once

#include <cmath>
#include <stdexcept>
#include <string>

#include "Line3D.h"

class Column
{
public:
    Column() = default;

    Column(
        const std::string& elementId,
        const Line3D& centerLine,
        double area,
        double modulusOfElasticity,
        double secondMomentOfArea,
        double effectiveLengthFactorValue = 1.0)
        : id(elementId),
          axis(centerLine),
          crossSectionArea(area),
          youngsModulus(modulusOfElasticity),
          momentOfInertia(secondMomentOfArea),
          effectiveLengthFactor(effectiveLengthFactorValue)
    {
    }

    [[nodiscard]] double length() const
    {
        return axis.length();
    }

    [[nodiscard]] double axialCapacityFromStress(double allowableCompressiveStress) const
    {
        return allowableCompressiveStress * crossSectionArea;
    }

    [[nodiscard]] double eulerBucklingLoad() const
    {
        const auto elementLength = length();
        const auto effectiveLength = effectiveLengthFactor * elementLength;
        if (effectiveLength <= 0.0)
        {
            throw std::invalid_argument("Effective column length must be greater than zero.");
        }

        constexpr auto pi = 3.14159265358979323846;
        return (pi * pi * youngsModulus * momentOfInertia) / (effectiveLength * effectiveLength);
    }

    std::string id;
    Line3D axis;
    double crossSectionArea = 0.0;
    double youngsModulus = 0.0;
    double momentOfInertia = 0.0;
    double effectiveLengthFactor = 1.0;
};
