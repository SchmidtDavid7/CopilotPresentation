#pragma once

#include <cmath>

class Point3D
{
public:
    Point3D() = default;

    Point3D(double xCoordinate, double yCoordinate, double zCoordinate)
        : x(xCoordinate), y(yCoordinate), z(zCoordinate)
    {
    }

    [[nodiscard]] double distanceTo(const Point3D& other) const
    {
        const auto xDifference = x - other.x;
        const auto yDifference = y - other.y;
        const auto zDifference = z - other.z;
        return std::sqrt((xDifference * xDifference) + (yDifference * yDifference) + (zDifference * zDifference));
    }

    [[nodiscard]] Point3D translated(double xOffset, double yOffset, double zOffset) const
    {
        return Point3D(x + xOffset, y + yOffset, z + zOffset);
    }

    void translate(double xOffset, double yOffset, double zOffset)
    {
        x += xOffset;
        y += yOffset;
        z += zOffset;
    }

    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
};
