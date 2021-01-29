#ifndef CLIPBOARDMANAGER_H
#define CLIPBOARDMANAGER_H

#include <QObject>
#include <QClipboard>
#include <QList>
#include <QVariant>

class ClipboardManager: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QList<QVariant> content READ content NOTIFY newClipboardEntry)
public:
    explicit ClipboardManager(QObject* parent = nullptr);

    QList<QVariant> content() const;

signals:
    void newClipboardEntry();

public slots:
    void contentChanged();

private:
    QClipboard* _clipboard = nullptr;
    QList<QVariant> _content;
};

#endif // CLIPBOARDMANAGER_H
