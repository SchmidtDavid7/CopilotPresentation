#pragma once

#include <algorithm>
#include <cstddef>
#include <cmath>
#include <stdexcept>
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

    [[nodiscard]] double maxPlanDimension() const
    {
        if (footprint.boundaryPoints.size() < 2)
        {
            return 0.0;
        }

        auto maxDistance = 0.0;
        for (std::size_t firstPointIndex = 0; firstPointIndex < footprint.boundaryPoints.size(); ++firstPointIndex)
        {
            for (std::size_t secondPointIndex = firstPointIndex + 1; secondPointIndex < footprint.boundaryPoints.size(); ++secondPointIndex)
            {
                const auto deltaX = footprint.boundaryPoints[secondPointIndex].x - footprint.boundaryPoints[firstPointIndex].x;
                const auto deltaY = footprint.boundaryPoints[secondPointIndex].y - footprint.boundaryPoints[firstPointIndex].y;
                const auto distance = std::sqrt((deltaX * deltaX) + (deltaY * deltaY));
                maxDistance = std::max(maxDistance, distance);
            }
        }

        return maxDistance;
    }

    [[nodiscard]] double volume() const
    {
        return baseArea() * height;
    }

    [[nodiscard]] double slendernessRatio() const
    {
        if (thickness <= 0.0)
        {
            throw std::invalid_argument("Wall thickness must be greater than zero.");
        }

        return maxPlanDimension() / thickness;
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
