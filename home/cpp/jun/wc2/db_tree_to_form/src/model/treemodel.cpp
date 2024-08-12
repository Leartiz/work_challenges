#include <algorithm>
#include <utility>

#include <QDebug>
#include <QBrush>
#include <QSize>
#include <QStack>

#include "model/treemodel.h"
#include "db/strategy_conct/strategyconctsqlite.h"
#include "db/strategy_conct/strategyconctmysql.h"

TreeModel::TreeModel(QObject* parent)
    : QAbstractItemModel(parent), m_dbFacade(DBFacade::instance()) {
    m_rootTreeItem = new TreeItem(SimpleEntity());
    setTreeItemsFromDb();
}

void TreeModel::setTreeItemsFromDb() {
    if (!m_dbFacade.isOpened()) return;

    auto ses = m_dbFacade.selAllSimpleEntities(); // has ids!
    std::sort(ses.begin(), ses.end(), [](const SimpleEntity& lhs, const SimpleEntity& rhs) {
        return lhs.getId().value() < rhs.getId().value();
    });

    foreach(const SimpleEntity& se, ses) {
        // base!
        if (!se.getParentId().has_value()) {
            m_rootTreeItem->insertChild(se);
            continue;
        }
        // use parent id!
        m_rootTreeItem->insertChildByParentId(se);
    }
    return;
}

void TreeModel::removeTreeItemsFromDbByTreeItem(TreeItem* treeItem) {
    if (treeItem == nullptr) return;

    QStack<TreeItem*> stack;
    stack.push(treeItem);
    while (!stack.isEmpty()) {
        TreeItem* top = stack.top();
        if (top->childCount() == 0) {
            // rmv from db!
            if (top->data().getId().has_value())
                m_dbFacade.delSimpleEntityById(top->data().getId().value());

            // rmv from model!
            TreeItem* parentTop = top->parent();
            if (parentTop) {
                parentTop->removeChild(top);
            }
            stack.pop();
            continue;
        }
        stack.append(top->children());
    }
}

void TreeModel::changeDatabaseConct(const StrategyConct& sc) {
    m_dbFacade.changeConct(sc);
    reloadTreeItemsFromDb();
}

void TreeModel::clearView() {
    if (m_rootTreeItem->childCount() == 0) return;
    beginRemoveRows(QModelIndex(), 0, m_rootTreeItem->childCount() - 1);
    m_rootTreeItem->removeAllChildren();
    endRemoveRows();
}

void TreeModel::reloadTreeItemsFromDb() {
    if (!m_dbFacade.isOpened()) {
        emit databaseNotOpened();
        return;
    }

    clearView();
    setTreeItemsFromDb();
    emit layoutChanged(); // work without!
}

TreeModel::~TreeModel() {
    delete m_rootTreeItem;
}

TreeItem* TreeModel::getTreeItemByIndx(const QModelIndex& indx) const {
    if (!indx.isValid())
        return m_rootTreeItem; // not null!

    TreeItem* anyTreeItem = static_cast<TreeItem*>(indx.internalPointer());
    return !anyTreeItem ? m_rootTreeItem : anyTreeItem;
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const {
    if (index.column() == 1) // edit only name!
        return Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsEnabled;
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const {
    if (!hasIndex(row, column, parent)) // across row count and column count?
        return QModelIndex();

    TreeItem* parentTreeItem = getTreeItemByIndx(parent);
    return createIndex(row, column, parentTreeItem->child(row)); // void *adata!
}

QModelIndex TreeModel::parent(const QModelIndex &child) const {
    if (!child.isValid())
        return QModelIndex();

    TreeItem* childTreeItem = getTreeItemByIndx(child);
    TreeItem* parntTreeItem = childTreeItem->parent(); // nullptr?
    if (parntTreeItem == m_rootTreeItem || !parntTreeItem)
        return QModelIndex();

    return createIndex(parntTreeItem->childNumber(), 0, parntTreeItem); // 1
}

int TreeModel::rowCount(const QModelIndex &parent) const {
    TreeItem* parentTreeItem = getTreeItemByIndx(parent);
    return parentTreeItem->childCount();
}

int TreeModel::columnCount(const QModelIndex &) const {
    return m_rootTreeItem->fieldsCount(); // const!
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch (section) {
        // data cols!
        case 0: return SimpleEntity::Tbl::Id;
        case 1: return SimpleEntity::Tbl::Name;
        default: return {};
        }
    }
    return {};
}

QVariant TreeModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return {};

    TreeItem* treeItem = getTreeItemByIndx(index);
    if (treeItem == m_rootTreeItem) return {};

    if (role == Qt::SizeHintRole) {
        return QSize(0, 50);
    }
    if (role == Qt::BackgroundRole) {
        const int depth = treeItem->depthToRootTreeItem();
        if (depth % 2 == 0)
            return index.row() % 2 ? QBrush(Qt::white) : QBrush(Qt::gray);
        return index.row() % 2 ? QBrush(Qt::darkGray) : QBrush(Qt::lightGray);
    }
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        if (index.column() == 0)
            return treeItem->data().getId().value_or(0);
        return treeItem->data().getName();
    }

    return {};
}

bool TreeModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (!m_dbFacade.isOpened()) {
        emit databaseNotOpened();
        return false;
    }

    if (!index.isValid()) return false;
    if (index.column() == 0) return false;
    if (role != Qt::EditRole) return false;

    TreeItem* treeItem = getTreeItemByIndx(index);
    if (treeItem == m_rootTreeItem) return false;

    treeItem->data().setName(value.toString());

    // db!
    {
        m_dbFacade.updSimpleEntityById(treeItem->data());
    }
    return true;
}

bool TreeModel::insertRows(int row, int count, const QModelIndex &parent) {
    if (!m_dbFacade.isOpened()) {
        emit databaseNotOpened();
        return false;
    }

    TreeItem* parentItem = getTreeItemByIndx(parent);
    beginInsertRows(parent, row, row + count - 1);
    parentItem->insertChild(row); // add empty!
    endInsertRows();

    // db!
    {
        SimpleEntity newSe(QString("[DClick me!]"));
        newSe.setParentId(parentItem->data().getId()); // mb null!

        m_dbFacade.insSimpleEntities(newSe);
        newSe.setId(m_dbFacade.selLastInsertId());
        parentItem->child(row)->data() = std::move(newSe); // set data!
    }
    return true;
}

bool TreeModel::removeRows(int row, int count, const QModelIndex &parent) {
    if (!m_dbFacade.isOpened()) {
        emit databaseNotOpened();
        return false;
    }

    TreeItem* parentItem = getTreeItemByIndx(parent);
    // rmv only one and childs!
    beginRemoveRows(parent, row, row + count - 1);
    TreeItem* toRemoveTreeItem = parentItem->takeChild(row);
    endRemoveRows();

    // db!
    {
        removeTreeItemsFromDbByTreeItem(toRemoveTreeItem);
    }

    return true;
}
