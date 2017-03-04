#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include <QJsonObject>

class TreeItem;

class TreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    TreeModel(QObject *parent = 0);
    ~TreeModel();

    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override;

    bool insertColumns(int position, int columns, const QModelIndex &parent = QModelIndex()) override;
    bool removeColumns(int position, int columns, const QModelIndex &parent = QModelIndex()) override;
    bool insertRows(int position, int rows, const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int position, int rows, const QModelIndex &parent = QModelIndex()) override;

    // TODO make enum and move-method public and delete this methods?
    bool moveUp(const QModelIndex &index);
    bool moveDown(const QModelIndex &index);
    bool moveRight(const QModelIndex &index);
    bool moveLeft(const QModelIndex &index);

    // TODO check methods
    QJsonObject toJson();
    void writeFile();
    QJsonObject readFile();

private:
    enum class MoveDirection
    {
      Up,
      Down,
      Left,
      Right
    };

    bool move (const QModelIndex &modelIndex, MoveDirection moveDirection);
    TreeItem *getItem(const QModelIndex &index) const;

    TreeItem *m_rootItem;

    // TODO this is temporary - needs to be given by constructor?
    const QString m_fileName = "/Users/Ulle/temp/content.txt";
};

#endif
