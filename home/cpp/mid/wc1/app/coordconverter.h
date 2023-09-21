#ifndef COORDCONVERTER_H
#define COORDCONVERTER_H

#include <QPair>
#include <QPoint>

namespace CoordConverter
{

int pointToIndex(const QPoint& point, const int rowCount, const int colCount);
QPair<int, int> indexToPair(const int idx, const int rowCount, const int colCount);

};

#endif // COORDCONVERTER_H
