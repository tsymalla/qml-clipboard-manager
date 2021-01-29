#include "clipboardmanager.h"
#include <QObject>
#include <QApplication>

ClipboardManager::ClipboardManager(QObject* parent): QObject(parent)
{
    _clipboard = QApplication::clipboard();
    connect(_clipboard, &QClipboard::dataChanged, this, &ClipboardManager::contentChanged);
}

QList<QVariant> ClipboardManager::content() const
{
    return _content;
}

void ClipboardManager::contentChanged()
{
    _content.insert(0, _clipboard->text());
    emit newClipboardEntry();
}
