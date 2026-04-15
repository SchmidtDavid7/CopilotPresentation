#pragma once

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <vector>

#include "Point3D.h"

class Region3D
{
public:
    Region3D() = default;

    explicit Region3D(const std::vector<Point3D>& points)
        : boundaryPoints(points)
    {
    }

    void addPoint(const Point3D& point)
    {
        boundaryPoints.push_back(point);
    }

    [[nodiscard]] std::size_t pointCount() const
    {
        return boundaryPoints.size();
    }

    [[nodiscard]] Point3D centroid() const
    {
        if (boundaryPoints.empty())
        {
            throw std::invalid_argument("Region must contain at least one point.");
        }

        auto sumX = 0.0;
        auto sumY = 0.0;
        auto sumZ = 0.0;

        for (const auto& point : boundaryPoints)
        {
            sumX += point.x;
            sumY += point.y;
            sumZ += point.z;
        }

        const auto pointCountAsDouble = static_cast<double>(boundaryPoints.size());
        return Point3D(sumX / pointCountAsDouble, sumY / pointCountAsDouble, sumZ / pointCountAsDouble);
    }

    [[nodiscard]] Point3D minPoint() const
    {
        if (boundaryPoints.empty())
        {
            throw std::invalid_argument("Region must contain at least one point.");
        }

        auto minimum = boundaryPoints.front();
        for (const auto& point : boundaryPoints)
        {
            minimum.x = std::min(minimum.x, point.x);
            minimum.y = std::min(minimum.y, point.y);
            minimum.z = std::min(minimum.z, point.z);
        }

        return minimum;
    }

    [[nodiscard]] Point3D maxPoint() const
    {
        if (boundaryPoints.empty())
        {
            throw std::invalid_argument("Region must contain at least one point.");
        }

        auto maximum = boundaryPoints.front();
        for (const auto& point : boundaryPoints)
        {
            maximum.x = std::max(maximum.x, point.x);
            maximum.y = std::max(maximum.y, point.y);
            maximum.z = std::max(maximum.z, point.z);
        }

        return maximum;
    }

    [[nodiscard]] bool containsInAxisAlignedBounds(const Point3D& point) const
    {
        if (boundaryPoints.empty())
        {
            return false;
        }

        const auto minimum = minPoint();
        const auto maximum = maxPoint();
        return (point.x >= minimum.x && point.x <= maximum.x)
            && (point.y >= minimum.y && point.y <= maximum.y)
            && (point.z >= minimum.z && point.z <= maximum.z);
    }

    [[nodiscard]] double projectedAreaOnXY() const
    {
        if (boundaryPoints.size() < 3)
        {
            return 0.0;
        }

        auto signedArea = 0.0;
        for (std::size_t i = 0; i < boundaryPoints.size(); ++i)
        {
            const auto& current = boundaryPoints[i];
            const auto& next = boundaryPoints[(i + 1) % boundaryPoints.size()];
            signedArea += (current.x * next.y) - (next.x * current.y);
        }

        return std::abs(signedArea) * 0.5;
    }

    [[nodiscard]] double axisAlignedBoundingVolume() const
    {
        if (boundaryPoints.size() < 2)
        {
            return 0.0;
        }

        const auto minimum = minPoint();
        const auto maximum = maxPoint();
        return (maximum.x - minimum.x) * (maximum.y - minimum.y) * (maximum.z - minimum.z);
    }

    std::vector<Point3D> boundaryPoints;
};
