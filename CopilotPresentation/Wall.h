#pragma once

#include <algorithm>
#include <string>

#include "Region3D.h"

class Wall
{
public:
    Wall() = default;

    Wall(
        const std::string& elementId,
        const Region3D& baseRegion,
        double wallThickness,
        double wallHeight,
        double materialDensity)
        : id(elementId),
          footprint(baseRegion),
          thickness(wallThickness),
          height(wallHeight),
          density(materialDensity)
    {
    }

    [[nodiscard]] double baseArea() const
    {
        return footprint.projectedAreaOnXY();
    }

    [[nodiscard]] double wallLength() const
    {
        if (footprint.boundaryPoints.size() < 2)
        {
            return 0.0;
        }

        const auto minimum = footprint.minPoint();
        const auto maximum = footprint.maxPoint();
        return std::max(maximum.x - minimum.x, maximum.y - minimum.y);
    }

    [[nodiscard]] double volume() const
    {
        return wallLength() * height * thickness;
    }

    [[nodiscard]] double mass() const
    {
        return volume() * density;
    }

    std::string id;
    Region3D footprint;
    double thickness = 0.0;
    double height = 0.0;
    double density = 0.0;
};
