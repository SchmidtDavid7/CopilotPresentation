#pragma once

#include <stdexcept>
#include <string>

#include "Line3D.h"

class Beam
{
public:
    Beam() = default;

    Beam(
        const std::string& elementId,
        const Line3D& centerLine,
        double area,
        double modulusOfElasticity,
        double secondMomentOfArea)
        : id(elementId),
          axis(centerLine),
          crossSectionArea(area),
          youngsModulus(modulusOfElasticity),
          momentOfInertia(secondMomentOfArea)
    {
    }

    [[nodiscard]] double length() const
    {
        return axis.length();
    }

    [[nodiscard]] double axialStiffness() const
    {
        const auto elementLength = length();
        if (elementLength <= 0.0)
        {
            throw std::invalid_argument("Beam length must be greater than zero.");
        }

        return (youngsModulus * crossSectionArea) / elementLength;
    }

    [[nodiscard]] double flexuralRigidity() const
    {
        return youngsModulus * momentOfInertia;
    }

    std::string id;
    Line3D axis;
    double crossSectionArea = 0.0;
    double youngsModulus = 0.0;
    double momentOfInertia = 0.0;
};
