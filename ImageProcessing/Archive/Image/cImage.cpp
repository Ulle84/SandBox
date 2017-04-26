#include <iostream>

#include "cImage.h"

cImage::cImage() :
  m_width(5),
  m_height(3)
{
  initPixels();
}

cImage::cImage(unsigned int width, unsigned int height) :
  m_width(width),
  m_height(height)
{
  initPixels();
}

cImage::cImage(const cImage& rhs)
{
  m_width = rhs.m_width;
  m_height = rhs.m_height;

  m_pixels = new unsigned char [m_width * m_height];
  memcpy(m_pixels, rhs.m_pixels, m_width * m_height);

  m_matrix = new unsigned char*[m_height];

  for (unsigned int i = 0; i < m_height; i++)
  {
    m_matrix[i] = &m_pixels[i * m_width];
  }
}

cImage& cImage::operator=(const cImage& rhs)
{
  if (&rhs != this)
  {
    if (m_width != rhs.m_width || m_height != rhs.m_height)
    {
      if (m_width * m_height != rhs.m_width * rhs.m_height)
      {
        delete[] m_pixels;
        m_pixels = new unsigned char[rhs.m_width * rhs.m_height];
      }

      if (m_height != rhs.m_height)
      {
        delete[] m_matrix;
        m_matrix = new unsigned char*[rhs.m_height];
      }

      for (unsigned int i = 0; i < rhs.m_height; i++)
      {
        m_matrix[i] = &m_pixels[i * rhs.m_width];
      }

      m_width = rhs.m_width;
      m_height = rhs.m_height;
    }

    memcpy(m_pixels, rhs.m_pixels, m_width * m_height);
  }

  return *this;
}


cImage::~cImage()
{
  delete[] m_pixels;
  delete[] m_matrix;
}

void cImage::initPixels()
{
  m_pixels = new unsigned char[m_width * m_height];
  m_matrix = new unsigned char*[m_height];

  for (unsigned int i = 0; i < m_height; i++)
  {
    m_matrix[i] = &m_pixels[i * m_width];
  }

  memset(m_pixels, 0, m_width * m_height);
}

void cImage::setAllPixelValues(unsigned char value)
{
  memset(m_pixels, value, m_width * m_height);
}

void cImage::setPixelValue(unsigned int x, unsigned int y, unsigned char value)
{
  if (x < m_width && y < m_height)
  {
    m_matrix[y][x] = value;
  }  
}

unsigned char cImage::getPixelValue(unsigned int x, unsigned int y) const
{
  if (x < m_width && y < m_height)
  {
    return m_matrix[y][x];
  }
  else
  {
    return 0;
  }  
}

unsigned int cImage::getHeight() const
{
  return m_height;
}

unsigned int cImage::getWidth() const
{
  return m_width;
}

unsigned char** cImage::getMatrix() const
{
  return m_matrix;
}

void cImage::setIncreasingPixelValues()
{
  for (unsigned int i = 0; i < m_height * m_width; i++)
  {
    m_pixels[i] = i % 256;
  }
}

void cImage::printToConsole(const std::string& description) const
{
  std::cout << "--------------------------------------------------------------------------------" << std::endl;
  std::cout << description << std::endl;

  for (int y = 0; y < m_height; y++)
  {
    for (int x = 0; x < m_width; x++)
    {
      if (m_matrix[y][x] < 10)
      {
        std::cout << " ";
      }

      if (m_matrix[y][x] < 100)
      {
        std::cout << " ";
      }

      std::cout << (int) m_matrix[y][x] << " ";
    }

    std::cout << std::endl;
  }
}

bool operator== (const cImage& image1, const cImage& image2)
{
  bool equal = true;

  equal &= image1.m_width  == image2.m_width;
  equal &= image1.m_height == image2.m_height;

  if (equal)
  {
    equal &= memcmp(image1.m_pixels, image2.m_pixels, image1.m_width * image1.m_height) == 0;
  }

  return equal;
}

bool operator!= (const cImage& image1, const cImage& image2)
{
  return !(image1 == image2);
}