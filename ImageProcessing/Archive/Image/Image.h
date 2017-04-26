#ifndef IMAGE_H
#define IMAGE_H

#include <QString>
#include <QDomDocument>

/* image types
binary
Gray -> 8bit, 10bit, 12bit ...
color
  rgb
  hsi
  yuv
  bayer -> various formats
*/

// conversion to QImage or QPixMap

/* test
- filter algorithms
- median
*/

// implementation with templates possible?


class Image
{
public:
  ~Image();
  Image(); // private?
  Image(unsigned int width, unsigned int height, unsigned int layerCount = 1, unsigned int bitsPerPixel = 8);
  Image(const QString& fileName);

  bool save(const QString& fileName);
  // read from file
  // write to file
  //...

private:
  bool load(const QString& fileName);

  QDomDocument domDocument;

  // type
  // additional data -> QDomDocument?
  unsigned int width;
  unsigned int height;
  unsigned int bitsPerPixel;
  unsigned int layerCount;

  unsigned char* pixels; // size: width * height * bytesPerPixel * layerCount
};

#endif // IMAGE_H
