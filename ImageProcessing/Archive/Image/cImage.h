#pragma once

#include <string>

class cImage
{
public:
  cImage();
  cImage(unsigned int width, unsigned int height);
  cImage(const cImage& rhs);
  ~cImage();

  cImage& operator= (const cImage& rhs);

  void printToConsole(const std::string& description) const;

  unsigned char getPixelValue(unsigned int x, unsigned int y) const;
  unsigned int getHeight() const;
  unsigned int getWidth() const;
  unsigned char** getMatrix() const;

  void setAllPixelValues(unsigned char value);
  void setPixelValue(unsigned int x, unsigned int y, unsigned char value);
  void setIncreasingPixelValues();

  friend bool operator== (const cImage& image1, const cImage& image2);
  friend bool operator!= (const cImage& image1, const cImage& image2);

private:
  void initPixels();

  unsigned int m_width;
  unsigned int m_height;

  unsigned char* m_pixels;
  unsigned char** m_matrix;
};