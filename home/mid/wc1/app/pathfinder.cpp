#include <utility>
#include <algorithm>

#include "pathfinder.h"

PathFinder::PathFinder(QVector<QVector<int>>&& mx)
    : m_matrix{ std::move(mx) } {}

PathFinder::PathFinder(const QVector<QVector<int>>& matrix)
    : m_matrix{ matrix } {}

QVector<int> PathFinder::get(const int beg, const int end) const
{
    const size_t n =
            m_matrix.size();

    QVector<int> p(n);
    p[beg] = -1;
    QVector<bool> visited(n, false);

    QVector<int> q;
    q.push_back(beg);

    visited[beg] = true;

    int vis{ 0 };
    while (!q.empty()) {
        vis = q.front();
        q.pop_front();

        // ***

        for (int i = 0; i < m_matrix[vis].size(); ++i) {
            auto to = m_matrix[vis][i];
            if (to == 1 && !visited[i]) {
                q.push_back(i);
                visited[i] = true;

                p[i] = vis;
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
