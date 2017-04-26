#include "Image.h"

Image::~Image()
{
  delete[] pixels;
}

Image::Image()
{
}

Image::Image(unsigned int width, unsigned int height, unsigned int layerCount, unsigned int bitsPerPixel)
  : width(width),
    height(height),
    layerCount(layerCount),
    bitsPerPixel(bitsPerPixel)
{
  unsigned int bytesPerPixel = bitsPerPixel / 8;
  if (bytesPerPixel % 8 != 0)
  {
    bytesPerPixel++;
  }

  pixels = new unsigned char[width * height * layerCount * bytesPerPixel];
}

Image::Image(const QString &fileName)
{
  load(fileName);
  //TODO
}

bool Image::load(const QString &fileName)
{
  // look at extension

  // read xml file

  // read dimensions and further information

  // read raw file to unsigned char*

  return false; // TODO
}

bool Image::save(const QString &fileName)
{
  return false; // TODO
}
