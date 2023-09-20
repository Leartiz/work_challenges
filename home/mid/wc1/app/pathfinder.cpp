#include <QQueue>

#include <utility>
#include <algorithm>

#include "pathfinder.h"

PathFinder::PathFinder(QVector<QVector<int>>&& mx)
    : m_matrix{ std::move(mx) } {}

PathFinder::PathFinder(const QVector<QVector<int>>& matrix)
    : m_matrix{ matrix } {}

// TODO: construct a diagram of the algorithm's operation
QVector<int> PathFinder::get(const int beg, const int end) const
{
    const size_t n =
            m_matrix.size();

    QVector<int> p(n);
    p[beg] = -1;

    QQueue<int> q;
    q.push_back(beg);

    QVector<bool> visited(n, false);
    visited[beg] = true;

    while (!q.empty()) {
        const auto current = q.front();
        q.pop_front();

        // ***

        for (int i = 0; i < m_matrix[current].size(); ++i) {
            const auto hasEdge = m_matrix[current][i];
            if (hasEdge && !visited[i]) {
                q.push_back(i);
                visited[i] = true;

                p[i] = current;
            }
        }
    }

    if (!visited[end])
        return {};

    QVector<int> path;
    for (int v = end; v != -1; v = p[v])
        path.push_back(v);

    return path;
}
