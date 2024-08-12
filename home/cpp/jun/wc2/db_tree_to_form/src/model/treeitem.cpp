#include <QDebug>
#include <QStack>

#include "model/treeitem.h"

TreeItem::TreeItem(const SimpleEntity& data, TreeItem* parent)
    : m_data(data), m_prnt(parent) {
}

TreeItem::~TreeItem() {
    qDeleteAll(m_childs);
}

TreeItem* TreeItem::child(const int ix) {
    if (ix < 0 || ix >= childCount()) return nullptr;
    return m_childs[ix];
}

QVector<TreeItem*> TreeItem::children() {
    return m_childs;
}

int TreeItem::childCount() const {
    return m_childs.size();
}

int TreeItem::childNumber() {
    if (!m_prnt) return 0;
    return m_prnt->m_childs.indexOf(this);
}

int TreeItem::fieldsCount() const {
    return 2; // displayed data fields!
}

TreeItem* TreeItem::parent() {
    return m_prnt;
}

SimpleEntity& TreeItem::data() {
    return m_data;
}

int TreeItem::depthToRootTreeItem() {
    int depth = 0;
    TreeItem* treeItem = m_prnt;
    while (treeItem) {
        treeItem = treeItem->m_prnt;
        ++depth;
    }
    return depth;
}

const SimpleEntity& TreeItem::data() const {
    return m_data;
}

bool TreeItem::insertChild(int row) {
    if (row < 0 || row > m_childs.size())
        return false;

    // empty!
    TreeItem *newTreeItem = new TreeItem(SimpleEntity(), this);
    m_childs.insert(row, newTreeItem);
    return true;
}

bool TreeItem::insertChild(const SimpleEntity& se) {
    if (!insertChild(childCount())) return false;
    m_childs.last()->data() = se;
    return true;
}

bool TreeItem::insertChildByParentId(const SimpleEntity& se) {
    if (!se.getParentId().has_value())
        return false;

    QStack<TreeItem*> stack;
    stack.append(this);
    while (!stack.isEmpty()) {
        TreeItem *top = stack.top();    stack.pop();
        stack.append(top->m_childs);

        // mb root!
        if (!top->data().getId().has_value()){
            continue;
        }

        if (top->data().getId().value() == se.getParentId().value()) {
            top->insertChild(se);
            return true;
        }
    }
    return false;
}

TreeItem* TreeItem::takeChild(int row) {
    if (row < 0 || row >= m_childs.size())
        return nullptr;
    return m_childs.takeAt(row);
}

bool TreeItem::removeChild(TreeItem* child) {
    if (!m_childs.removeOne(child)) return false;
    delete child;
    return true;
}

bool TreeItem::removeChild(int row) {
    if (row < 0 || row >= m_childs.size())
        return false;

    delete m_childs.takeAt(row);
    return true;
}

bool TreeItem::removeAllChildren() {
    qDeleteAll(m_childs);
    m_childs.clear();
    return true;
}
