#include "imageutils.h"
#include <QString>
#include <QImage>
#include <QByteArray>
#include <QBuffer>
#include <QUrl>
#include <QMimeDatabase>
#include <QMimeType>

QString ImageUtils::toBase64(const QImage& image)
{
    QByteArray bytes;
    QBuffer inputBuffer(&bytes);
    inputBuffer.open(QIODevice::WriteOnly);
    image.save(&inputBuffer, "PNG");

    QString base64Data = bytes.toBase64();
    inputBuffer.close();

    return base64Data;
}

bool ImageUtils::isImage(const QUrl& url)
{
    QMimeDatabase mimeDb;
    return mimeDb.mimeTypeForUrl(url).name().startsWith("image/");
}
