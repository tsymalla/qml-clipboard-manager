#ifndef IMAGEUTILS_H
#define IMAGEUTILS_H

class QString;
class QImage;
class QUrl;

class ImageUtils
{
public:
    ImageUtils() = default;

    static QString toBase64(const QUrl& imageUrl);
    static bool isImage(const QUrl& url);
};

#endif // IMAGEUTILS_H
