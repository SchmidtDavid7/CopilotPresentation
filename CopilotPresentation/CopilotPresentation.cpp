#include <iostream>

#include "Beam.h"
#include "Column.h"
#include "Plate.h"
#include "Region3D.h"
#include "Wall.h"

int main()
{
    const Region3D rectangularRegion({
        Point3D(0.0, 0.0, 0.0),
        Point3D(5.0, 0.0, 0.0),
        Point3D(5.0, 2.0, 0.0),
        Point3D(0.0, 2.0, 0.0) });

    const Line3D elementAxis(Point3D(0.0, 0.0, 0.0), Point3D(0.0, 0.0, 3.0));
    const Beam beam("B1", elementAxis, 0.02, 210'000'000'000.0, 0.0000085);
    const Column column("C1", elementAxis, 0.04, 210'000'000'000.0, 0.0000150, 1.0);
    const Wall wall("W1", rectangularRegion, 0.2, 3.0, 2'400.0);
    const Plate plate("P1", rectangularRegion, 0.25, 2'500.0, 30'000'000'000.0, 0.2);

    std::cout
        << "Beam length: " << beam.length() << "\n"
        << "Column Euler load: " << column.eulerBucklingLoad() << "\n"
        << "Wall mass: " << wall.mass() << "\n"
        << "Plate mass: " << plate.mass() << "\n";
}
