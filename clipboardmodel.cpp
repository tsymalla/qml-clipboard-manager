#include "clipboardmodel.h"
#include <QDateTime>

ClipboardEntry::ClipboardEntry(const ClipboardEntryType type, QString data):
    _type(type),
    _data(std::move(data))
{
    _dateTime = QDateTime::currentDateTime().toString();
}

ClipboardEntryType ClipboardEntry::type() const
{
    return _type;
}

QString ClipboardEntry::typeStr() const
{
    if (_type == ClipboardEntryType::IMAGE)
    {
        return "image";
    }

    if (_type == ClipboardEntryType::TEXT)
    {
        return "text";
    }

    return "unknown";
}

QString ClipboardEntry::data() const
{
    return _data;
}

QString ClipboardEntry::dateTime() const
{
    return _dateTime;
}

ClipboardModel::ClipboardModel(QObject* parent):
    QAbstractListModel(parent)
{
}

void ClipboardModel::addClipboardEntry(const ClipboardEntry& entry)
{
    auto rowCount = _entries.count();

    beginInsertRows(QModelIndex(), rowCount, rowCount);
    _entries << entry;
    endInsertRows();
}

int ClipboardModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)

    return _entries.count();
}

QVariant ClipboardModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    const ClipboardEntry& entry = _entries[index.row()];

    switch (role)
    {
    case ClipboardRoles::TypeRole:
        return entry.typeStr();

    case ClipboardRoles::DataRole:
        return entry.data();

    case ClipboardRoles::DateTimeRole:
        return entry.dateTime();
    }

    return QVariant();
}

QHash<int, QByteArray> ClipboardModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ClipboardRoles::TypeRole] = "type";
    roles[ClipboardRoles::DataRole] = "data";
    roles[ClipboardRoles::DateTimeRole] = "dateTime";

    return roles;
}
