#ifndef IMAGE_H
#define IMAGE_H

#include <string>

#include "Point.h"
#include "Rectangle.h"
#include "Circle.h"
#include "FilterMask.h"
#include "FreemanCode.h"
#include "PolyLine.h"
#include "Histogram.h"
#include "LookUpTable.h"

class Image
{
public:
  Image();
  Image(unsigned int width, unsigned int height);
  Image(const Image& rhs);
  ~Image();

  Image& operator= (const Image& rhs);

  void printToConsole(const std::string& description) const;

  unsigned char getPixelValue(unsigned int x, unsigned int y) const;
  unsigned int getHeight() const;
  unsigned int getWidth() const;
  unsigned char** getMatrix() const;
  unsigned char* getPixels() const;
  unsigned char getMinimum() const;
  unsigned char getMaximum() const;

  void setAllPixelValues(unsigned char value);
  void setPixelValue(unsigned int x, unsigned int y, unsigned char value);
  void setIncreasingPixelValues();
  void setRandomPixelValues();

  void binarize(unsigned char threshold);
  void spread();
  void clear();

  bool isPointInImage(const Point& point);

  void markLine(unsigned int lineNumber, unsigned char value);
  void markColumn(unsigned int columnNumber, unsigned char value);

  void drawPoint(const Point& point, unsigned char value);
  void drawRectangle(const Rectangle& rectangle, unsigned char value);
  void drawLine(const Point& p1, const Point& p2, unsigned char value);

  void drawCircle(const Circle& circle, unsigned char value, bool fill);
  void drawFreemanCode(const FreemanCode& freemanCode);
  void drawPolyLine(const PolyLine& polyLine);
  void invert();
  
  void mirrorOnHorizontalAxis();
  void mirrorOnVerticalAxis();
  void rotateBy90DegreeClockwise();
  void rotateBy90DegreeCounterClockwise();
  void rotateBy180Degree();
  
  Image* doPolarTransformation(const Circle& circle);
  
  void applyLookUpTable(const LookUpTable& lookUpTable);
  
  Histogram getHistogram();
    void drawHistogram(const Histogram& histogram);

  friend bool operator== (const Image& image1, const Image& image2);
  friend bool operator!= (const Image& image1, const Image& image2);
  
   void dilate(unsigned int filterSize);
  void erode(unsigned int filterSize);
  void doOpening(unsigned int filterSize);
  void doClosing(unsigned int filterSize);
  void filterMean(unsigned int filterSize);

  void filterWithMask(const FilterMask& filterMask);
  
  

  // TODO move all possible functions below to Matrix




 

private:
  void initPixels();

  unsigned int minimum(unsigned int value1, unsigned int value2);
  unsigned int maximum(unsigned int value1, unsigned int value2);

  unsigned int m_width;
  unsigned int m_height;

  unsigned char* m_pixels;
  unsigned char** m_matrix;
};

#endif // IMAGE_H
