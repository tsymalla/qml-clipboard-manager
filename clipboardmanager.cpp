#include "clipboardmanager.h"
#include <QObject>
#include <QApplication>
#include <QImage>
#include <QMimeData>
#include <QUrl>
#include "imageutils.h"

ClipboardManager::ClipboardManager(QObject* parent): QObject(parent)
{
    _clipboard = QApplication::clipboard();
    _model = new ClipboardModel(this);
    connect(_clipboard, &QClipboard::changed, this, &ClipboardManager::contentChanged);

    // update entry count.
    connect(_model, &QAbstractListModel::rowsInserted, this, &ClipboardManager::entryCountChanged);
    connect(_model, &QAbstractListModel::rowsRemoved, this, &ClipboardManager::entryCountChanged);
}

size_t ClipboardManager::entryCount() const
{
    return _model->rowCount(QModelIndex());
}

void ClipboardManager::setClipboardEntry(QVariant index) const
{
    QModelIndex newIndex = _model->index(index.toInt(), 0);

    if (!newIndex.isValid())
    {
        return;
    }

    const auto& data = _model->data(newIndex, ClipboardRoles::ContentRole);
    _clipboard->setText(data.toString());
}

void ClipboardManager::contentChanged()
{
    const auto mimeData = _clipboard->mimeData();

    if (mimeData == nullptr)
    {
        return;
    }

    QString data;
    ClipboardEntryType entryType = ClipboardEntryType::TEXT;

    if (mimeData->hasUrls())
    {
        foreach (const QUrl& url, mimeData->urls())
        {
            if (ImageUtils::isImage(url))
            {
                data = ImageUtils::toBase64(url);
                entryType = ClipboardEntryType::IMAGE;
            }
        }
    }
    else
    {
        data = _clipboard->text();
    }

    if (!data.isEmpty())
    {
        _model->addClipboardEntry(ClipboardEntry(entryType, std::move(data)));
    }
}
