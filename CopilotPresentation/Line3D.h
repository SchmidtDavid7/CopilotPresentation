#pragma once

#include <stdexcept>

#include "Point3D.h"

class Line3D
{
public:
    Line3D() = default;

    Line3D(const Point3D& start, const Point3D& end)
        : startPoint(start), endPoint(end)
    {
    }

    [[nodiscard]] double length() const
    {
        return startPoint.distanceTo(endPoint);
    }

    [[nodiscard]] Point3D midpoint() const
    {
        return Point3D(
            (startPoint.x + endPoint.x) / 2.0,
            (startPoint.y + endPoint.y) / 2.0,
            (startPoint.z + endPoint.z) / 2.0);
    }

    [[nodiscard]] Point3D unitDirection() const
    {
        const auto lineLength = length();
        if (lineLength <= 0.0)
        {
            throw std::invalid_argument("Line length must be greater than zero.");
        }

        return Point3D(
            (endPoint.x - startPoint.x) / lineLength,
            (endPoint.y - startPoint.y) / lineLength,
            (endPoint.z - startPoint.z) / lineLength);
    }

    void translate(double xOffset, double yOffset, double zOffset)
    {
        startPoint.translate(xOffset, yOffset, zOffset);
        endPoint.translate(xOffset, yOffset, zOffset);
    }

    Point3D startPoint;
    Point3D endPoint;
};
