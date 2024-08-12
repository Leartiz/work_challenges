#ifndef TREEITEM_H
#define TREEITEM_H

#include <QObject>
#include <QVector>

#include "db/entities/simpleentity.h"

class TreeItem final /*: public QObject*/ {
public:
    explicit TreeItem(const SimpleEntity& data, TreeItem* parent = nullptr);
    ~TreeItem();

public:
    TreeItem* child(const int ix);
    QVector<TreeItem*> children();

    int childNumber();

    int childCount() const;
    int fieldsCount() const;

    bool insertChild(int row);
    bool insertChild(const SimpleEntity& se);
    bool insertChildByParentId(const SimpleEntity& se);

    TreeItem* takeChild(int row);
    bool removeChild(TreeItem* child);
    bool removeChild(int row);
    bool removeAllChildren();

    TreeItem* parent();
    int depthToRootTreeItem();

public:
    SimpleEntity& data();
    const SimpleEntity& data() const;

private:
    QVector<TreeItem*> m_childs;
    SimpleEntity m_data; // bad?
    TreeItem* m_prnt;
};

#endif // TREEITEM_H
