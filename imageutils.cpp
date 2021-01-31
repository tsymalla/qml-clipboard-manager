#include "imageutils.h"
#include <QString>
#include <QImage>
#include <QByteArray>
#include <QUrl>
#include <QMimeDatabase>
#include <QMimeType>
#include <QFile>

QString ImageUtils::toBase64(const QUrl& imageUrl)
{
    QFile source(imageUrl.toLocalFile());

    source.open(QIODevice::ReadOnly);
    if (!source.isOpen())
    {
        return QString();
    }

    QByteArray bytes = source.readAll();

    source.close();

    return bytes.toBase64();
}

bool ImageUtils::isImage(const QUrl& url)
{
    QMimeDatabase mimeDb;
    return mimeDb.mimeTypeForUrl(url).name().startsWith("image/");
}
