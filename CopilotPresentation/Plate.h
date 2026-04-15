#pragma once

#include <string>

#include "Region3D.h"

class Plate
{
public:
    Plate() = default;

    Plate(
        const std::string& elementId,
        const Region3D& plateRegion,
        double plateThickness,
        double materialDensity,
        double modulusOfElasticity,
        double poissonsRatioValue)
        : id(elementId),
          region(plateRegion),
          thickness(plateThickness),
          density(materialDensity),
          youngsModulus(modulusOfElasticity),
          poissonsRatio(poissonsRatioValue)
    {
    }

    [[nodiscard]] double area() const
    {
        return region.projectedAreaOnXY();
    }

    [[nodiscard]] double volume() const
    {
        return area() * thickness;
    }

    [[nodiscard]] double mass() const
    {
        return volume() * density;
    }

    [[nodiscard]] double flexuralRigidity() const
    {
        const auto thicknessCubed = thickness * thickness * thickness;
        return (youngsModulus * thicknessCubed) / (12.0 * (1.0 - (poissonsRatio * poissonsRatio)));
    }

    std::string id;
    Region3D region;
    double thickness = 0.0;
    double density = 0.0;
    double youngsModulus = 0.0;
    double poissonsRatio = 0.0;
};
