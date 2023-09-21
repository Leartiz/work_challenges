#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <QVector>

class PathFinder final
{
public:
    explicit PathFinder(QVector<QVector<int>>&&);
    explicit PathFinder(const QVector<QVector<int>>&);
    QVector<int> get(const int beg, const int end) const;

private:
    QVector<QVector<int>> m_matrix;
};

#endif // PATHFINDER_H
