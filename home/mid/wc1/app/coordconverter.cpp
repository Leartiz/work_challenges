#include <stdexcept>

#include "coordconverter.h"

namespace CoordConverter
{


/* example:

   0   1   2   3
0 [ ] [ ] [ ] [ ]
1 [ ] [ ] [x] [ ]
2 [ ] [ ] [ ] [ ]

...

{1, 2} ---> 1*4 = 4+2 = 6

...

 0  1  2  3  4  5  6  7  8  9  10 11
[ ][ ][ ][ ][ ][ ][x][ ][ ][ ][ ][ ]


*/

// if params invalid then undefined behavior...
int pointToIndex(const QPoint& point, const int rowCount, const int colCount) {
    static_cast<void>(rowCount);

    // x ---> row
    // y ---> col

    return point.x() * colCount + point.y();
}

QPair<int, int> indexToPair(const int idx, const int rowCount, const int colCount) {
    static_cast<void>(rowCount);

    const auto row = idx / colCount;
    const auto col = idx % colCount;
    return { row, col };
}

};
