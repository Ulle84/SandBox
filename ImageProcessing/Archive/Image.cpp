#include <iostream>

#include <QDebug>

#include "ImageOld.h"

#include <math.h>

#define PI 3.14159265359

Image::Image() :
  m_width(5),
  m_height(3)
{
  initPixels();
}

Image::Image(unsigned int width, unsigned int height) :
  m_width(width),
  m_height(height)
{
  initPixels();
}

Image::Image(const Image& rhs)
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

Image& Image::operator=(const Image& rhs)
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


Image::~Image()
{
  delete[] m_pixels;
  delete[] m_matrix;
}

void Image::initPixels()
{
  m_pixels = new unsigned char[m_width * m_height];
  m_matrix = new unsigned char*[m_height];

  for (unsigned int i = 0; i < m_height; i++)
  {
    m_matrix[i] = &m_pixels[i * m_width];
  }

  memset(m_pixels, 0, m_width * m_height);
}

unsigned int Image::minimum(unsigned int value1, unsigned int value2)
{
  return value1 < value2 ? value1 : value2;
}

unsigned int Image::maximum(unsigned int value1, unsigned int value2)
{
  return value1 > value2 ? value1 : value2;
}

void Image::setAllPixelValues(unsigned char value)
{
  memset(m_pixels, value, m_width * m_height);
}

void Image::setPixelValue(unsigned int x, unsigned int y, unsigned char value)
{
  if (x < m_width && y < m_height)
  {
    m_matrix[y][x] = value;
  }
}

unsigned char Image::getPixelValue(unsigned int x, unsigned int y) const
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

unsigned int Image::getHeight() const
{
  return m_height;
}

unsigned int Image::getWidth() const
{
  return m_width;
}

unsigned char** Image::getMatrix() const
{
  return m_matrix;
}

unsigned char* Image::getPixels() const
{
  return m_pixels;
}

unsigned char Image::getMinimum() const
{
  unsigned char minimum = 255;
  for (unsigned int i = 0; i < m_height * m_width; i++)
  {
    if(m_pixels[i] < minimum)
    {
      minimum = m_pixels[i];
    }
  }
  return minimum;
}

unsigned char Image::getMaximum() const
{
  unsigned char maximum = 0;
  for (unsigned int i = 0; i < m_height * m_width; i++)
  {
    if(m_pixels[i] > maximum)
    {
      maximum = m_pixels[i];
    }
  }
  return maximum;
}

Histogram Image::getHistogram()
{
  Histogram histogram;

  for (unsigned int i = 0; i < m_height * m_width; i++)
  {
    histogram.m_values[m_pixels[i]]++;
  }

  return histogram;
}

void Image::drawHistogram(const Histogram &histogram)
{
  clear();

  unsigned int barWidth = m_width / 256; // TODO use this value
  qDebug() << "barWidth" << barWidth;

  unsigned int maxValue = histogram.getMaxValue();

  for (unsigned int i = 0; i < 256; i++)
  {
    unsigned int barHeight = histogram.m_values[i] * m_height * 1.0 / maxValue;
    for (unsigned int j = 0; j < barWidth; j++)
    {
      drawLine(Point(i*barWidth + j, m_height - 1), Point(i*barWidth + j, m_height - barHeight), 255);
    }
  }
}

void Image::setIncreasingPixelValues()
{
  for (unsigned int i = 0; i < m_height * m_width; i++)
  {
    m_pixels[i] = i % 256;
  }
}

void Image::setRandomPixelValues()
{
  for (unsigned int i = 0; i < m_height * m_width; i++)
  {
    m_pixels[i] = rand() % 256;
  }
}

void Image::dilate(unsigned int filterSize)
{
  Image original(*this);

  int offset = filterSize / 2;

  for (unsigned int y = offset; y < (m_height - offset); y++)
  {
    for (unsigned int x = offset; x < (m_width - offset); x++)
    {
      unsigned char maximum = 0;
      for (int fy = -offset; fy <= offset; fy++)
      {
        for (int fx = -offset; fx <= offset; fx++)
        {
          if (original.m_matrix[y+fy][x+fx] > maximum)
          {
            maximum = original.m_matrix[y+fy][x+fx];
          }
        }
      }
      m_matrix[y][x] = maximum;
    }
  }
}

void Image::erode(unsigned int filterSize)
{
  Image original(*this);

  int offset = filterSize / 2;

  for (unsigned int y = offset; y < (m_height - offset); y++)
  {
    for (unsigned int x = offset; x < (m_width - offset); x++)
    {
      unsigned char minimum = 255;
      for (int fy = -offset; fy <= offset; fy++)
      {
        for (int fx = -offset; fx <= offset; fx++)
        {
          if (original.m_matrix[y+fy][x+fx] < minimum)
          {
            minimum = original.m_matrix[y+fy][x+fx];
          }
        }
      }
      m_matrix[y][x] = minimum;
    }
  }
}

void Image::doOpening(unsigned int filterSize)
{
  erode(filterSize);
  dilate(filterSize);
}

void Image::doClosing(unsigned int filterSize)
{
  dilate(filterSize);
  erode(filterSize);
}

void Image::filterMean(unsigned int filterSize)
{
  Image original(*this);

  int offset = filterSize / 2;
  double calculatedValue;

  for (unsigned int y = offset; y < (m_height - offset); y++)
  {
    for (unsigned int x = offset; x < (m_width - offset); x++)
    {
      calculatedValue = 0;
      for (int fy = -offset; fy <= offset; fy++)
      {
        for (int fx = -offset; fx <= offset; fx++)
        {
          calculatedValue += original.m_matrix[y+fy][x+fx];
        }
      }
      calculatedValue /= (filterSize * filterSize);
      m_matrix[y][x] = calculatedValue + 0.5;
    }
  }
}

void Image::filterWithMask(const FilterMask &filterMask)
{
  Image original(*this);

  int offset= filterMask.m_width / 2;
  double calculatedValue;

  // TODO use code below --> correct offsets depend on filterMask dimensions and referencePoint
  //int offsetX = filterMask.m_referencePoint.m_x; // TODO offset left and right depending on referencpoint
  //int offsetY = filterMask.m_referencePoint.m_y; // TODO offset top and bottom depending on referencpoint

  for (unsigned int y = offset; y < (m_height - offset); y++)
  {
    for (unsigned int x = offset; x < (m_width - offset); x++)
    {
      calculatedValue = 0;
      for (int fy = -offset; fy <= offset; fy++)
      {
        for (int fx = -offset; fx <= offset; fx++)
        {
          //qDebug() << "original:" << original.m_matrix[y+fy][x+fx];
          //qDebug() << "filterMask:" << filterMask.m_matrix[fy+offset][fx+offset];

          calculatedValue += original.m_matrix[y+fy][x+fx] * filterMask.m_matrix[fy+offset][fx+offset];
        }
      }
      //calculatedValue /= filterMask.getSumOfMatrix(); // TODO define correct divisor and apply
      m_matrix[y][x] = calculatedValue + 0.5;
      //qDebug() << "image:" << m_matrix[y][x];
    }
  }
}

void Image::binarize(unsigned char threshold)
{
  for (unsigned int i = 0; i < m_height * m_width; i++)
  {
    if (m_pixels[i] <= threshold)
    {
      m_pixels[i] = 0;
    }
    else
    {
      m_pixels[i] = 255;
    }
  }
}

void Image::spread()
{
  unsigned char maximum = getMaximum();
  unsigned char minimum = getMinimum();

  if ((maximum - minimum) == 0)
  {
    return;
  }

  // map minimum to zero
  for (unsigned int i = 0; i < m_height * m_width; i++)
  {
    m_pixels[i] -= minimum;
  }

  // spread
  for (unsigned int i = 0; i < m_height * m_width; i++)
  {
    m_pixels[i] = m_pixels[i] * 255 / (maximum - minimum);
  }
}

void Image::clear()
{
  setAllPixelValues(0);
}

bool Image::isPointInImage(const Point &point)
{
  return point.m_x < m_width && point.m_y < m_height;
}

void Image::drawPoint(const Point &point, unsigned char value)
{
  if (isPointInImage(point))
  {
    m_matrix[point.m_y][point.m_x] = value;
  }
}

void Image::markLine(unsigned int lineNumber, unsigned char value)
{
  if (lineNumber >= m_height)
  {
    return;
  }

  memset(&m_pixels[lineNumber * m_width], value, m_width);
}

void Image::markColumn(unsigned int columnNumber, unsigned char value)
{
  if (columnNumber >= m_width)
  {
    return;
  }

  for (unsigned int y = 0; y < m_height; y++)
  {
    m_matrix[y][columnNumber] = value;
  }
}

void Image::drawRectangle(const Rectangle &rectangle, unsigned char value)
{  
  if ((rectangle.m_topLeftCorner.m_x + rectangle.m_width) >= m_width)
  {
    return;
  }

  if ((rectangle.m_topLeftCorner.m_y + rectangle.m_height) >= m_height)
  {
    return;
  }

  for (unsigned int y = rectangle.m_topLeftCorner.m_y; y < (rectangle.m_topLeftCorner.m_y + rectangle.m_height); y++)
  {
    memset(&m_pixels[y * m_width + rectangle.m_topLeftCorner.m_x], value, rectangle.m_width);
  }
}

void Image::drawCircle(const Circle &circle, unsigned char value, bool fill)
{
  // code below copied partially from
  // https://en.wikipedia.org/wiki/Midpoint_circle_algorithm

  int x = circle.m_radius;
  int y = 0;
  int decisionOver2 = 1 - x;   // Decision criterion divided by 2 evaluated at x=r, y=0

  while(y <= x)
  {
    if (fill)
    {
      // TODO improve performance: memset is called "too often" for first/last line in Octant 2 + 3 and Octant 6 + 7
      memset(&m_pixels[( y + circle.m_center.m_y) * m_width - x + circle.m_center.m_x], value, 2 * x + 1); //  Octant 1 + Octant 4
      memset(&m_pixels[( x + circle.m_center.m_y) * m_width - y + circle.m_center.m_x], value, 2 * y + 1); //  Octant 2 + Octant 3

      memset(&m_pixels[(-y + circle.m_center.m_y) * m_width - x + circle.m_center.m_x], value, 2 * x + 1); //  Octant 5 + Octant 8
      memset(&m_pixels[(-x + circle.m_center.m_y) * m_width - y + circle.m_center.m_x], value, 2 * y + 1); //  Octant 6 + Octant 7
    }
    else
    {
      m_matrix[ y + circle.m_center.m_y][ x + circle.m_center.m_x] = value; // Octant 1
      m_matrix[ x + circle.m_center.m_y][ y + circle.m_center.m_x] = value; // Octant 2
      m_matrix[ x + circle.m_center.m_y][-y + circle.m_center.m_x] = value; // Octant 3
      m_matrix[ y + circle.m_center.m_y][-x + circle.m_center.m_x] = value; // Octant 4

      m_matrix[-y + circle.m_center.m_y][-x + circle.m_center.m_x] = value; // Octant 5
      m_matrix[-x + circle.m_center.m_y][-y + circle.m_center.m_x] = value; // Octant 6
      m_matrix[-x + circle.m_center.m_y][ y + circle.m_center.m_x] = value; // Octant 7
      m_matrix[-y + circle.m_center.m_y][ x + circle.m_center.m_x] = value; // Octant 8
    }

    y++;

    if (decisionOver2 <= 0)
    {
      decisionOver2 += 2 * y + 1;   // Change in decision criterion for y -> y+1
    }
    else
    {
      x--;
      decisionOver2 += 2 * (y - x) + 1;   // Change for y -> y+1, x -> x-1
    }
  }
}

void Image::drawLine(const Point &p1, const Point &p2, unsigned char value)
{
  if (!isPointInImage(p1) || !isPointInImage(p2))
  {
    return;
  }

  if (p1.m_x == p2.m_x)
  {
    // draw vertical line
    unsigned int min = minimum(p1.m_y, p2.m_y);
    unsigned int max = maximum(p1.m_y, p2.m_y);

    for (unsigned int i = min; i <= max; i++)
    {
      m_matrix[i][p1.m_x] = value;
    }

    return;
  }

  if (p1.m_y == p2.m_y)
  {
    // draw horizontal line
    unsigned int min = minimum(p1.m_x, p2.m_x);
    unsigned int max = maximum(p1.m_x, p2.m_x);

    memset(&m_pixels[p1.m_y * m_width + min] , value, max - min + 1);

    return;
  }

  // code below copied partially from
  // https://de.wikipedia.org/wiki/Bresenham-Algorithmus#Kompakte_Variante

  int x0 = p1.m_x;
  int y0 = p1.m_y;
  int x1 = p2.m_x;
  int y1 = p2.m_y;

  int dx =  abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
  int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
  int err = dx + dy, e2; /* error value e_xy */

  while(1){
    m_matrix[y0][x0] = value; //setPixel(x0,y0);
    if (x0==x1 && y0==y1) break;
    e2 = 2*err;
    if (e2 > dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
    if (e2 < dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
  }
}

void Image::drawFreemanCode(const FreemanCode &freemanCode)
{
  drawPoint(freemanCode.m_startPoint, 255);

  unsigned int x = freemanCode.m_startPoint.m_x;
  unsigned int y = freemanCode.m_startPoint.m_y;

  for (auto it = freemanCode.m_directions.begin(); it != freemanCode.m_directions.end(); it++)
  {
    qDebug() << "code: " << *it;

    /* 321
     * 4*0
     * 567 */

    switch (*it)
    {
    case 0:
      x++;
      break;
    case 1:
      x++;
      y--;
      break;
    case 2:
      y--;
      break;
    case 3:
      x--;
      y--;
      break;
    case 4:
      x--;
      break;
    case 5:
      x--;
      y++;
      break;
    case 6:
      y++;
      break;
    case 7:
      x++;
      y++;
      break;
    default:
      // should not happen
      break;
    }

    m_matrix[y][x] = 255;
  }
}

void Image::drawPolyLine(const PolyLine &polyLine)
{
  if (polyLine.m_points.size() < 2)
  {
    return;
  }

  auto itPrevious = polyLine.m_points.begin();
  for (auto it = polyLine.m_points.begin(); it != polyLine.m_points.end(); it++)
  {
    if (it == polyLine.m_points.begin())
    {
      continue;
    }

    drawLine(*itPrevious, *it, 255);

    itPrevious = it;
  }
}

// TODO remove potential memory leak
Image* Image::doPolarTransformation(const Circle &circle)
{
  unsigned int circumference = circle.m_radius * 2 * 3.14159265359 + 0.5;

  int width = circumference;

  if (width % 4 != 0)
  {
    width += (4 - (width % 4)); // round up -> width % 4 needs to be zero!
  }

  Image* calculated = new Image(width, circle.m_radius); // TODO correct sizes

  for (unsigned int y = 0; y < circle.m_radius; y++) // radius
  {
    for (unsigned int x = 0; x < circumference; x++) // angle
    {
      // TODO improve performace -> avoid duplicated calculations -> avoid conversions

      int angle = x * 360.0 / circumference;
      int radius = y;

      // x = radius * cos (angle)
      // y = radius * sin (angle)

      int xx = radius * cos ( angle * PI / 180.0 );
      int yy = radius * sin ( angle * PI / 180.0 );

      /*if (y == circle.m_radius - 1)
      {
        qDebug() << xx;
      }*/

      calculated->m_matrix[y][x] = m_matrix[yy + circle.m_center.m_y][xx + circle.m_center.m_x];
    }
  }

  return calculated;
}

void Image::mirrorOnHorizontalAxis()
{
  Image original(*this);

  for (unsigned int y = 0; y < m_height; y++)
  {
    memcpy(&m_matrix[y][0], &(original.m_matrix[m_height - y - 1][0]), m_width);
  }
}

void Image::mirrorOnVerticalAxis()
{
  Image original(*this);

  for (unsigned int x = 0; x < m_width; x++)
  {
    for (unsigned int y = 0; y < m_height; y++)
    {
      m_matrix[y][x] = original.m_matrix[y][m_width - x - 1];
    }
  }
}

void Image::rotateBy90DegreeClockwise()
{
  Image original(*this);

  m_width = original.m_height;
  m_height = original.m_width;

  delete[] m_matrix;
  m_matrix = new unsigned char*[m_height];

  for (unsigned int i = 0; i < m_height; i++)
  {
    m_matrix[i] = &m_pixels[i * m_width];
  }

  for (unsigned int y = 0; y < m_height; y++)
  {
    for (unsigned int x = 0; x < m_width; x++)
    {
      m_matrix[y][x] = original.m_matrix[original.m_height - x - 1][y];
    }
  }
}

void Image::rotateBy90DegreeCounterClockwise()
{
  Image original(*this);

  m_width = original.m_height;
  m_height = original.m_width;

  delete[] m_matrix;
  m_matrix = new unsigned char*[m_height];

  for (unsigned int i = 0; i < m_height; i++)
  {
    m_matrix[i] = &m_pixels[i * m_width];
  }

  for (unsigned int y = 0; y < m_height; y++)
  {
    for (unsigned int x = 0; x < m_width; x++)
    {
      m_matrix[y][x] = original.m_matrix[x][original.m_width - y - 1];
    }
  }
}

void Image::rotateBy180Degree()
{
  Image original(*this);

  for (unsigned int y = 0; y < m_height; y++)
  {
    for (unsigned int x = 0; x < m_width; x++)
    {
      m_matrix[y][x] = original.m_matrix[m_height - y - 1][m_width - x - 1];
    }
  }
}

void Image::invert()
{
  for (unsigned int y = 0; y < m_height; y++)
  {
    for (unsigned int x = 0; x < m_width; x++)
    {
      m_matrix[y][x] = 255 - m_matrix[y][x];
    }
  }
}

void Image::applyLookUpTable(const LookUpTable &lookUpTable)
{
  for (unsigned int y = 0; y < m_height; y++)
  {
    for (unsigned int x = 0; x < m_width; x++)
    {
      m_matrix[y][x] = lookUpTable.m_values[m_matrix[y][x]];
    }
  }
}

void Image::printToConsole(const std::string& description) const
{
  std::cout << "--------------------------------------------------------------------------------" << std::endl;
  std::cout << description << std::endl;

  for (unsigned int y = 0; y < m_height; y++)
  {
    for (unsigned int x = 0; x < m_width; x++)
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

bool operator== (const Image& image1, const Image& image2)
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

bool operator!= (const Image& image1, const Image& image2)
{
  return !(image1 == image2);
}
