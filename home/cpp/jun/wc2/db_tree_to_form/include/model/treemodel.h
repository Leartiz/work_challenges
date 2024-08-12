#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QObject>
#include <QByteArray>
#include <QAbstractItemModel>

#include "treeitem.h"
#include "db/dbfacade.h"

class TreeModel: public QAbstractItemModel {
    Q_OBJECT

public:
    explicit TreeModel(QObject* parent = nullptr);
    ~TreeModel() override;

public:
    void changeDatabaseConct(const StrategyConct& sc);

public:
    void clearView();
    void reloadTreeItemsFromDb();
    TreeItem* getTreeItemByIndx(const QModelIndex& indx) const;

    // QAbstractItemModel interface
public:
    Qt::ItemFlags flags(const QModelIndex & index) const override;

    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &child) const override;

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    bool insertRows(int row, int count, const QModelIndex &parent) override;
    bool removeRows(int row, int count, const QModelIndex &parent) override;

signals:
    void databaseNotOpened();

private:
    void setTreeItemsFromDb();
    void removeTreeItemsFromDbByTreeItem(TreeItem* treeItem);

private:
    TreeItem* m_rootTreeItem;
    DBFacade& m_dbFacade;
};

#endif // TREEMODEL_H
