#ifndef CLIPBOARDMODEL_H
#define CLIPBOARDMODEL_H

#include <QAbstractListModel>
#include <QStringView>

enum class ClipboardEntryType: std::size_t
{
    IMAGE,
    TEXT
};

class ClipboardEntry
{
public:
    explicit ClipboardEntry(const ClipboardEntryType type, QString data);

    ClipboardEntryType type() const;
    QString typeStr() const;
    QString data() const;
    QString dateTime() const;

private:
    ClipboardEntryType _type;
    QString _data;
    QString _dateTime;
};

enum ClipboardRoles
{
    TypeRole = Qt::UserRole + 1,
    DataRole = TypeRole + 1,
    DateTimeRole = DataRole + 1
};

class ClipboardModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ClipboardModel(QObject* parent = nullptr);

    void addClipboardEntry(const ClipboardEntry& entry);

    int rowCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role) const override;

protected:
    QHash<int, QByteArray> roleNames() const override;

private:
    QList<ClipboardEntry> _entries;
};

#endif // CLIPBOARDMODEL_H
