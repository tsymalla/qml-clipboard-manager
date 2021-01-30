#ifndef CLIPBOARDMANAGER_H
#define CLIPBOARDMANAGER_H

#include <QObject>
#include <QClipboard>
#include "clipboardmodel.h"

class ClipboardManager: public QObject
{
    Q_OBJECT
    Q_PROPERTY(ClipboardModel* model MEMBER _model NOTIFY modelChanged)
    Q_PROPERTY(int entryCount READ entryCount NOTIFY entryCountChanged)
public:
    explicit ClipboardManager(QObject* parent = nullptr);

    size_t entryCount() const;
    Q_INVOKABLE void setClipboardEntry(QVariant index) const;

public slots:
    void contentChanged();

signals:
    void modelChanged();
    void entryCountChanged();

private:
    QClipboard* _clipboard = nullptr;
    ClipboardModel* _model = nullptr;
};

#endif // CLIPBOARDMANAGER_H
