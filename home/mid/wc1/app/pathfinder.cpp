#include <utility>
#include <algorithm>

#include "pathfinder.h"

PathFinder::PathFinder(QVector<QVector<int>>&& mx)
    : m_matrix{ std::move(mx) } {}

PathFinder::PathFinder(const QVector<QVector<int>>& matrix)
    : m_matrix{ matrix } {}

QVector<int> PathFinder::get(const int beg, const int end) const
{
    const size_t n = m_matrix.size();

    QVector<int> d(n), p(n);
    p[beg] = -1;
    QVector<bool> used(n, false);

    QVector<int> q;
    q.push_back(beg);

    used[beg] = true;

    int vis{ 0 };
    while (!q.empty()) {
        vis = q.front();
        q.pop_front();

        // ***

        for (int i = 0; i < m_matrix[vis].size(); ++i) {
            auto to = m_matrix[vis][i];
            if (to == 1 && !used[i]) {
                q.push_back(i);
                used[i] = true;

                d[i] = d[vis] + 1;
                p[i] = vis;
            }
        }
    }

    if (!used[end])
        return {};

    QVector<int> path;
    for (int v = end; v != -1; v = p[v])
        path.push_back(v);

    std::reverse(path.begin(), path.end());
    return path;
}
