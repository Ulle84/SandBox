#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <limits>
#include <list>
#include <math.h>
#include <string>
#include <typeinfo>
#include <vector>

#include "Circle.h"
#include "Converter.h"
#include "Edge.h"
#include "FreemanCode.h"
#include "Line.h"
#include "MathHelper.h"
#include "Point.h"
#include "PolyLine.h"
#include "Rectangle.h"
#include "RunLengthCode.h"
#include "Statistics.h"

// TODO rename this header to Base.h? Here ist not only Matrix defined anymore
// TODO use const wherever possible
// TODO iterate over pointer instead using for-loop with index -> shuold have better performance
/* example
  unsigned char* z1 = pixels;
    unsigned char* z2 = p.pixels;

    for (unsigned int i = 0; i < width * height; i++) {
        *z1++ = *z2++;
    }
    */
// TODO check wrong z values everywhere
// TODO WriteMutex
// TODO with % 4 !== 0
// TODO m_referencePoint?

class Filter;
class StructuringElement;

template<typename T>
class Matrix
{
public:
  Matrix();
  Matrix(unsigned int width, unsigned int height, unsigned int qtyLayers = 1, bool setDefaultValue = true, T defaultValue = 0);
  Matrix(const Matrix& rhs);
  Matrix(Matrix&& rhs);
  virtual ~Matrix();

  Matrix& operator= (const Matrix& rhs);
  Matrix& operator= (Matrix&& rhs);
  bool operator== (const Matrix& rhs);
  bool operator!= (const Matrix& rhs);

  unsigned int getWidth() const;
  unsigned int getHeight() const;
  unsigned int getQtyLayers() const;
  
  T getMinimum() const;
  T getMaximum() const;

  T getValue(unsigned int x, unsigned int y, unsigned int z = 0) const;
  T*** getValues() const; // TODO const, so the pointer-adress can not be changed
  double getSumOfAllValues(unsigned int z = 0) const;
  const T* getLayer(unsigned int z) const;
  const T* getSingleLayer(std::vector<unsigned int> layerIndices) const;
  std::vector<unsigned int> getHistogram(unsigned int z);
  RunLengthCode getRunLengthCode(T value, unsigned int z = 0) const;
  double getAverageAlongLine(const Line& line, unsigned int z = 0) const;
  Statistics<T> getStatistics(const RunLengthCode& runLengthCode, unsigned int z = 0);

  void setIncreasingValues();
  void setRandomValues();
  void setBinomialValues(unsigned int z = 0);
  void setAllValues(T value, unsigned int z = 0);
  void setValue(T value, unsigned int x, unsigned int y, unsigned int z = 0);
  void setSingleLayer(T* buffer, std::vector<unsigned int> layerIndices);
  void setRow(T value, unsigned int y, unsigned int z = 0);
  void setColumn(T value, unsigned int x, unsigned int z = 0);
  void setPoint(T value, const Point& point, unsigned int z = 0);
  void setRectangle(T value, const Rectangle& rectangle, bool fill = true, unsigned int z = 0);
  void setLine(T value, const Line& line, bool drawArrow = false, unsigned int z = 0);
  void setCircle(T value, const Circle& circle, bool fill = true, unsigned int z = 0);
  void setFreemanCode(T value, const FreemanCode& freemanCode, unsigned int z = 0);
  void setPolyLine(T value, const PolyLine& polyLine, unsigned int z = 0);
  void setRunLengthCode(T value, const RunLengthCode& runLengthCode, unsigned int z = 0);
  void setStructureElement(T value, const StructuringElement *structuringElement, const Point& referencePointPosition, unsigned int z = 0);
  void setHistogram(const std::vector<unsigned int>& histogram, unsigned int z = 0);

  void filter(const Filter* filter, unsigned int z = 0);
  void filterQuantil(const StructuringElement *structuringElement, double quantil, unsigned int z = 0);
  void filterMedian(const StructuringElement *structuringElement, unsigned int z = 0);
  void filterConservativeSmoothing(const StructuringElement *structuringElement, unsigned int z = 0);

  void binarize(T threshold);
  void spread();
  void clear();
  void invert();
  void fillBackground(T backgroundValue, T fillValue, unsigned int z = 0);
  void replace(T currentValue, T newValue, unsigned int z = 0);

  Edges findEdges(const Line& line, float minContrast, unsigned int smoothingWidth = 1, unsigned int z = 0);

  // morphology
  void erode(const StructuringElement* structuringElement, unsigned int z = 0);
  void dilate(const StructuringElement* structuringElement, unsigned int z = 0);
  void open(const StructuringElement* structuringElement, unsigned int z = 0);
  void close(const StructuringElement* structuringElement, unsigned int z = 0);

  void mirrorOnHorizontalAxis();
  void mirrorOnVerticalAxis();
  void rotateBy90DegreeClockwise();
  void rotateBy90DegreeCounterClockwise();
  void rotateBy180Degree();

  Matrix<T> crop(const Rectangle &cropRegion);
  Matrix<T> doPolarTransformation(const Circle& circle);

  void applyLookUpTable(const std::vector<T> &lookUpTable);

  bool isPointInsideImage(const Point& point);
  bool isRectangleInsideImage(const Rectangle& rectangle);
  bool isCircleInsideImage(const Circle& circle);
  bool isLineInsideImage(const Line& line);

  void printValuesToConsole(const std::string& description) const;
  void printDifference(const Matrix& rhs) const;

  void performanceTestAccessPixels(unsigned int mode);
  
protected:
  T*** m_values;
  unsigned int m_width;
  unsigned int m_height;
  unsigned int m_size;
  unsigned int m_qtyLayers;

private:
  unsigned int minimum(unsigned int value1, unsigned int value2);
  unsigned int maximum(unsigned int value1, unsigned int value2);
  unsigned int calculateBinomialCoefficient(unsigned int n, unsigned int k);

  void create();
  void createRowBeginVector();
  void createLayers();
  void destroy();
  void destroyRowBeginVector();
  void destroyLayers();
  void copy(const Matrix&);
  void print(const std::string& message);

  void filterQuantilBool(const StructuringElement *structuringElement, double quantil, unsigned int z = 0);

  T** m_layers;
};

// TBD type short?
class Filter : public Matrix<short>
{
public:
  Filter(unsigned width, unsigned height) : Matrix<short>(width, height){m_preFactor = 1.0; m_referencePoint.m_x = width / 2; m_referencePoint.m_y = height / 2; m_shiftResultValues = false; m_invertNegativeResultValues = false;}

  void setReferencePoint(const Point& referencePoint) {m_referencePoint = referencePoint;}
  Point getReferencePoint() const {return m_referencePoint;}

  void setPreFactor(double preFactor) {m_preFactor = preFactor;}
  double getPreFactor() const {return m_preFactor;}

  bool getShiftResultValues() const {return m_shiftResultValues;}
  void setShiftResultValues(bool shiftResultValues) {m_shiftResultValues = shiftResultValues;}

  bool getInvertNegativeResultValues() const {return m_invertNegativeResultValues;}
  void setInvertNegativeResultValues(bool invertNegativeResultValues) {m_invertNegativeResultValues = invertNegativeResultValues;}

private:
  Filter(){}

  bool m_shiftResultValues;
  bool m_invertNegativeResultValues;
  double m_preFactor;
  Point m_referencePoint;
};

class StructuringElement : public Matrix<bool>
{
public:
  StructuringElement(unsigned int width, unsigned int height, bool defaultValue = true) : Matrix<bool>(width, height){m_referencePoint.m_x = width / 2; m_referencePoint.m_y = height / 2; setAllValues(defaultValue);}

  void setReferencePoint(const Point& referencePoint) {m_referencePoint = referencePoint;}
  Point getReferencePoint() const {return m_referencePoint;}

  bool isValueSet(unsigned int x, unsigned int y) const {return m_values[0][y][x];}

  // TODO is this function really needed?
  unsigned int getSumOfSetValues() const
  {
    unsigned int sum = 0;
    for (unsigned int y = 0; y < m_height; y++)
    {
      for (unsigned int x = 0; x < m_width; x++)
      {
        if (m_values[0][y][x])
        {
          sum++;
        }
      }
    }
    return sum;
  }

private:
  StructuringElement(){}

  Point m_referencePoint;
};

template<typename T>
void Matrix<T>::setSingleLayer( T* buffer, std::vector<unsigned int> layerIndices )
{
  unsigned int qtyLayerIndices = layerIndices.size();
  
  for (unsigned int y = 0; y < m_height; y++)
  {
    for (unsigned int x = 0; x < m_width; x++)
    {
      for (unsigned int z = 0; z < qtyLayerIndices; z++)
      {
        m_values[layerIndices[z]][y][x] = buffer[(y * m_width + x) * qtyLayerIndices + z];
      }
    }
  }
}

template<typename T>
Matrix<T>::Matrix() :
  m_width(512),
  m_height(512),
  m_qtyLayers(1)
{
  print("Matrix: default constructor");
  create();
  clear();
}

template<typename T>
Matrix<T>::Matrix(const Matrix &rhs)
{
  print("Matrix: copy constructor");

  m_width = rhs.m_width;
  m_height = rhs.m_height;
  m_qtyLayers = rhs.m_qtyLayers;

  create();
  copy(rhs);
}

template<typename T>
Matrix<T>::Matrix(Matrix&& rhs)
{
  print("Matrix: move constructor");

  m_height = rhs.m_height;
  m_width = rhs.m_width;
  m_size = rhs.m_size;
  m_qtyLayers = rhs.m_qtyLayers;
  m_values = rhs.m_values;
  m_layers = rhs.m_layers;

  rhs.m_height = 0;
  rhs.m_width = 0;
  rhs.m_size = 0;
  rhs.m_qtyLayers = 0;
  rhs.m_values = 0; // nullptr
  rhs.m_layers = 0; // nullptr
}

template<typename T>
Matrix<T>::Matrix(unsigned int width, unsigned int height, unsigned int qtyLayers, bool setDefaultValue, T defaultValue) :
  m_width(width),
  m_height(height),
  m_qtyLayers(qtyLayers)
{
  print("value constructor");

  if (m_width == 0)
  {
    m_width = 1;
  }

  if (m_height == 0)
  {
    m_height = 1;
  }

  if (m_qtyLayers == 0)
  {
    m_qtyLayers = 1;
  }

  create();

  if (setDefaultValue)
  {
    for (unsigned int z = 0; z < qtyLayers; z++)
    {
      setAllValues(defaultValue, z);
    }
  }
}

template<typename T>
void Matrix<T>::create()
{
  createLayers();
  createRowBeginVector();
}

template<typename T>
void Matrix<T>::createLayers()
{
  m_layers = new T*[m_qtyLayers];

  m_size = m_width * m_height;

  for (unsigned int z = 0; z < m_qtyLayers; z++)
  {
    m_layers[z] = new T[m_size];
  }
}

template<typename T>
void Matrix<T>::createRowBeginVector()
{
  m_values = new T**[m_qtyLayers];

  for (unsigned int z = 0; z < m_qtyLayers; z++)
  {
    m_values[z] = new T*[m_height];

    for (unsigned int y = 0; y < m_height; y++)
    {
      m_values[z][y] = &m_layers[z][y * m_width];
    }
  }
}

template<typename T>
void Matrix<T>::destroy()
{
  destroyRowBeginVector();
  destroyLayers();
}

template<typename T>
void Matrix<T>::destroyLayers()
{
  for (unsigned int z = 0; z < m_qtyLayers; z++)
  {
    delete[] m_layers[z];
  }

  delete[] m_layers;
}

template<typename T>
void Matrix<T>::destroyRowBeginVector()
{
  for (unsigned int z = 0; z < m_qtyLayers; z++)
  {
    delete[] m_values[z];
  }

  delete[] m_values;
}

template<typename T>
Matrix<T>::~Matrix()
{
  print("destructor");
  destroy();
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix& rhs)
{
  print("assignment operator");
  if (&rhs != this)
  {
    if (m_width != rhs.m_width || m_height != rhs.m_height || m_qtyLayers != rhs.m_qtyLayers)
    {
      // TODO improve performance -> rearange buffer if sizes match
      destroy();

      m_width = rhs.m_width;
      m_height = rhs.m_height;
      m_qtyLayers = rhs.m_qtyLayers;

      create();
    }

    copy(rhs);
  }

  return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(Matrix&& rhs)
{
  print("move assignment operator");

  if (&rhs != this)
  {
    destroy();

    m_height = rhs.m_height;
    m_width = rhs.m_width;
    m_size = rhs.m_size;
    m_qtyLayers = rhs.m_qtyLayers;
    m_values = rhs.m_values;
    m_layers = rhs.m_layers;

    rhs.m_height = 0;
    rhs.m_width = 0;
    rhs.m_size = 0;
    rhs.m_qtyLayers = 0;
    rhs.m_values = 0; // nullptr
    rhs.m_layers = 0; // nullptr
  }
  return *this;
}

template<typename T>
bool Matrix<T>::operator==(const Matrix& rhs)
{
  print("== operator");

  bool equal = true;

  equal &= m_width  == rhs.m_width;
  equal &= m_height == rhs.m_height;
  equal &= m_qtyLayers == rhs.m_qtyLayers;

  if (equal)
  {
    for (unsigned int z = 0; z < m_qtyLayers; z++)
    {
      equal &= (memcmp(m_layers[z], rhs.m_layers[z], m_width * m_height * sizeof(T)) == 0);
    }
  }

  return equal;
}

template<typename T>
bool Matrix<T>::operator!=(const Matrix& rhs)
{
  print("!= operator");
  return !(this == rhs);
}

template<typename T>
void Matrix<T>::clear()
{
  for (unsigned int z = 0; z < m_qtyLayers; z++)
  {
    memset(m_layers[z], 0, m_width * m_height * sizeof(T));
  }
}

template<typename T>
void Matrix<T>::copy(const Matrix& rhs)
{
  for (unsigned int z = 0; z < m_qtyLayers; z++)
  {
    memcpy(m_values[z][0], rhs.m_values[z][0], m_width * m_height * sizeof(T));
  }
}

template<typename T>
void Matrix<T>::print(const std::string &message)
{
  //std::cout << "Matrix: " << message << std::endl;
}

template<typename T>
void Matrix<T>::setAllValues(T value, unsigned int z)
{
  if (z >= m_qtyLayers)
  {
    return;
  }

  if (sizeof(T) == 1)
  {
    memset(m_layers[z], value, m_width * m_height);
  }
  else
  {
    T* it = m_values[z][0];
    for (unsigned int i = 0; i < m_size; i++)
    {
      *it++ = value;
    }
  }
}

template<typename T>
void Matrix<T>::setValue(T value, unsigned int x, unsigned int y, unsigned int z)
{
  if (x < m_width && y < m_height && z < m_qtyLayers)
  {
    m_values[z][y][x] = value;
  }
}

template<typename T>
T Matrix<T>::getValue(unsigned int x, unsigned int y, unsigned int z) const
{
  if (x < m_width && y < m_height && z < m_qtyLayers)
  {
    return m_values[z][y][x];
  }
  else
  {
    return 0;
  }
}

template<typename T>
T ***Matrix<T>::getValues() const
{
  return m_values;
}

template<typename T>
double Matrix<T>::getSumOfAllValues(unsigned int z) const
{
  double sum = 0.0;

  T* it = m_values[z][0];
  for (unsigned int i = 0; i < m_size; i++)
  {
    sum += *it++;
  }

  return sum;
}

template<typename T>
const T* Matrix<T>::getLayer(unsigned int z) const
{
  return *(m_values[z]);
}

template<typename T>
const T* Matrix<T>::getSingleLayer(std::vector<unsigned int> layerIndices) const
{
  unsigned int qtyLayerIndices = layerIndices.size();
  unsigned int bufferSize = m_height * m_width * qtyLayerIndices;
  T* singleLayer = new T[bufferSize]; // TODO avoid memory leak -> recycle buffer if possible

  for (unsigned int y = 0; y < m_height; y++)
  {
    for (unsigned int x = 0; x < m_width; x++)
    {
      for (unsigned int z = 0; z < qtyLayerIndices; z++)
      {
        singleLayer[(y * m_width + x) * qtyLayerIndices + z] = m_values[layerIndices[z]][y][x] ;
      }
    }
  }

  return singleLayer;
}

template<typename T>
std::vector<unsigned int> Matrix<T>::getHistogram(unsigned int z)
{
  if (std::numeric_limits<T>::is_signed && !std::numeric_limits<T>::is_integer)
  {
    // TODO how to implement negative values?
    return std::vector<unsigned int>(0);
  }

  std::vector<unsigned int> histogram(std::numeric_limits<T>::max() + 1); // TODO verify for big data types like long etc.
  std::fill(histogram.begin(), histogram.end(), 0);

  T* it = m_values[z][0];
  for (unsigned int i = 0; i < m_size; i++)
  {
    histogram[*it++]++;
  }

  return histogram;
}

template<typename T>
RunLengthCode Matrix<T>::getRunLengthCode(T value, unsigned int z) const
{
  RunLengthCode runLengthCode;
  unsigned int length = 0;

  for (unsigned int y = 0; y < m_height; y++)
  {
    length = 0;
    for (unsigned int x = 0; x < m_width; x++)
    {
      if (m_values[z][y][x] == value)
      {
        length++;
        if (x == m_width - 1) // reached end of row?
        {
          runLengthCode.push_back(RunLength(Point(x - length + 1, y), length));
          length = 0;
        }
      }
      else
      {
        if (length > 0)
        {
          runLengthCode.push_back(RunLength(Point(x - length, y), length));
          length = 0;
        }
      }
    }
  }
  return runLengthCode;
}

template<typename T>
double Matrix<T>::getAverageAlongLine(const Line &line, unsigned int z) const
{
  double average = 0.0;

  Points points = line.getPointsAlongLine();

  for (auto it = points.begin(); it != points.end(); it++)
  {
    average += m_values[z][Converter::toUInt(it->m_y)][Converter::toUInt(it->m_x)];
  }

  average /= points.size();

  return average;
}

template<typename T>
Statistics<T> Matrix<T>::getStatistics(const RunLengthCode& runLengthCode, unsigned int z)
{
  Statistics<T> statistics;

  unsigned int qtyPixels = 0;
  double sumOfPixels = 0.0;

  for (auto it = runLengthCode.begin(); it != runLengthCode.end(); it++)
  {
    qtyPixels += it->m_length;

    T* ptr = &m_values[z][Converter::toUInt(it->m_startPoint.m_y)][Converter::toUInt(it->m_startPoint.m_x)];
    for (unsigned int i = 0; i < it->m_length; i++, ptr++)
    {
      if (*ptr < statistics.minimum)
      {
        statistics.minimum = *ptr;
      }

      if (*ptr > statistics.maximum)
      {
        statistics.maximum = *ptr;
      }

      sumOfPixels += *ptr;
    }
  }

  if (qtyPixels > 0)
  {
    statistics.meanValue = sumOfPixels / qtyPixels;
  }

  return statistics;
}

template<typename T>
void Matrix<T>::setRandomValues()
{
  for (unsigned int z = 0; z < m_qtyLayers; z++)
  {
    T* it = m_values[z][0];
    for (unsigned int i = 0; i < m_size; i++)
    {
      *it++ = rand();
    }
  }
}

template<typename T>
void Matrix<T>::setBinomialValues(unsigned int z)
{
  for (unsigned int y = 0; y < m_height; y++)
  {
    for (unsigned int x = 0; x < m_width; x++)
    {
      m_values[z][y][x] = calculateBinomialCoefficient(m_width - 1, x) * calculateBinomialCoefficient(m_height - 1, y);
    }
  }
}

template<typename T>
void Matrix<T>::binarize(T threshold)
{
  for (unsigned int z = 0; z < m_qtyLayers; z++)
  {
    T* it = m_values[z][0];
    for (unsigned int i = 0; i < m_size; i++)
    {
      if (*it < threshold)
      {
        *it = std::numeric_limits<T>::min();
      }
      else
      {
        *it = std::numeric_limits<T>::max();
      }
      it++;
    }
  }
}

template<typename T>
void Matrix<T>::spread()
{
  T maximum = getMaximum();
  T minimum = getMinimum();

  if ((maximum - minimum) == 0)
  {
    // avoid division by zero
    // TBD set all values to max possible value?
    return;
  }

  for (unsigned int z = 0; z < m_qtyLayers; z++)
  {
    T* it = m_values[z][0];
    for (unsigned int i = 0; i < m_size; i++)
    {
      if (std::numeric_limits<T>::is_signed)
      {
        // TODO define spread-function for signed types
      }
      else
      {
        if (minimum != 0)
        {
          *it -= minimum;
        }

        *it *= std::numeric_limits<T>::max() / (maximum - minimum);
      }
    }
  }
}

template<typename T>
bool Matrix<T>::isPointInsideImage(const Point &point)
{
  return point.m_x >= 0.0 && point.m_y >= 0.0 && Converter::toUInt(point.m_x) <= m_width && Converter::toUInt(point.m_y) <= m_height;
}

template<typename T>
bool Matrix<T>::isRectangleInsideImage(const Rectangle& rectangle)
{
  bool rectangleInImage = true;

  Points edgePoints = rectangle.getEdgePoints();

  for (auto it = edgePoints.begin(); it != edgePoints.end(); it++)
  {
    rectangleInImage &= isPointInsideImage(*it);
  }

  return rectangleInImage;
}

template<typename T>
bool Matrix<T>::isCircleInsideImage(const Circle &circle)
{
  bool circleInImage = true;

  circleInImage &= ((circle.m_center.m_x - circle.m_radius) >=  0);
  circleInImage &= ((circle.m_center.m_y - circle.m_radius) >=  0);

  circleInImage &= ((circle.m_center.m_x + circle.m_radius) <  m_width);
  circleInImage &= ((circle.m_center.m_y + circle.m_radius) <  m_height);

  return circleInImage;
}

template<typename T>
bool Matrix<T>::isLineInsideImage(const Line &line)
{
  return isPointInsideImage(line.getStartPoint()) && isPointInsideImage(line.getEndPoint());
}

template<typename T>
void Matrix<T>::setRow(T value, unsigned int y, unsigned int z)
{
  if (y >= m_height)
  {
    return;
  }

  if (sizeof(T) == 1)
  {
    memset(m_values[z][y], value, m_width);
  }
  else
  {
    for (unsigned int x = 0; x < m_width; x++)
    {
      m_values[z][y][x] = value;
    }
  }
}

template<typename T>
void Matrix<T>::setColumn(T value, unsigned int x, unsigned int z)
{
  if (x >= m_width)
  {
    return;
  }

  for (unsigned int y = 0; y < m_width; y++)
  {
    m_values[z][y][x] = value;
  }
}

template<typename T>
void Matrix<T>::setPoint(T value, const Point &point, unsigned int z)
{
  if (point.m_x >= m_width || point.m_y >= m_height)
  {
    return;
  }
  m_values[z][Converter::toUInt(point.m_y)][Converter::toUInt(point.m_x)] = value;
}

template<typename T>
void Matrix<T>::setRectangle(T value, const Rectangle &rectangle, bool fill, unsigned int z)
{
  if (!isRectangleInsideImage(rectangle))
  {
    return;
  }

  if (rectangle.m_angle == 0)
  {
    if (fill)
    {
      for (unsigned int y = rectangle.m_origin.m_y; y < (rectangle.m_origin.m_y + rectangle.m_height); y++)
      {
        if (sizeof(T) == 1)
        {
          memset(&(m_values[z][y][Converter::toUInt(rectangle.m_origin.m_x)]), value, rectangle.m_width);
        }
        else
        {
          for (unsigned int x = rectangle.m_origin.m_x; x < (Converter::toUInt(rectangle.m_origin.m_x) + rectangle.m_width); x++)
          {
            m_values[z][y][x] = value;
          }
        }
      }
    }
    else
    {
      for (unsigned int x = rectangle.m_origin.m_x; x < (rectangle.m_origin.m_x + rectangle.m_width); x++)
      {
        // TODO use memset if sizeof(T) == 1
        m_values[z][Converter::toUInt(rectangle.m_origin.m_y)][x] = value;
        m_values[z][Converter::toUInt(rectangle.m_origin.m_y) + Converter::toUInt(rectangle.m_height) - 1][x] = value;
      }

      for (unsigned int y = rectangle.m_origin.m_y + 1; y < (rectangle.m_origin.m_y + rectangle.m_height - 1); y++)
      {
        m_values[z][y][Converter::toUInt(rectangle.m_origin.m_x)] = value;
        m_values[z][y][Converter::toUInt(rectangle.m_origin.m_x) + Converter::toUInt(rectangle.m_width) - 1] = value;
      }
    }
  }
  else
  {
    if (fill)
    {
      setRunLengthCode(value, rectangle.toPolyLine().toRunLengthCode(), z);
    }
    else
    {
      setPolyLine(value, rectangle.toPolyLine(), z);
    }
  }
}

template<typename T>
void Matrix<T>::setLine(T value, const Line & line, bool drawArrow, unsigned int z)
{
  Point p1 = line.getStartPoint();
  Point p2 = line.getEndPoint();

  if (!isPointInsideImage(p1) || !isPointInsideImage(p2))
  {
    return;
  }

  if (p1.m_x == p2.m_x)
  {
    // draw vertical line
    unsigned int min = minimum(p1.m_y, p2.m_y);
    unsigned int max = maximum(p1.m_y, p2.m_y);

    for (unsigned int y = min; y <= max; y++)
    {
      m_values[z][y][Converter::toUInt(p1.m_x)] = value;
    }
  }
  else if (p1.m_y == p2.m_y)
  {
    // draw horizontal line
    unsigned int min = minimum(p1.m_x, p2.m_x);
    unsigned int max = maximum(p1.m_x, p2.m_x);

    if (sizeof(T) == 1)
    {
      memset(&m_values[z][Converter::toUInt(p1.m_y)][min], value, max - min + 1);
    }
    else
    {
      for (unsigned int x = min; x <= max; x++)
      {
        m_values[z][Converter::toUInt(p1.m_y)][x] = value;
      }
    }
  }
  else
  {
    // code below copied partially from
    // https://de.wikipedia.org/wiki/Bresenham-Algorithmus#Kompakte_Variante

    int x0 = Converter::toUInt(p1.m_x);
    int y0 = Converter::toUInt(p1.m_y);
    int x1 = Converter::toUInt(p2.m_x);
    int y1 = Converter::toUInt(p2.m_y);

    int dx =  abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2; /* error value e_xy */

    while (true)
    {
      m_values[z][y0][x0] = value;

      if (x0 == x1 && y0 == y1)
      {
        break;
      }

      e2 = 2*err;

      if (e2 > dy)
      {
        err += dy;
        x0 += sx;
      }

      if (e2 < dx)
      {
        err += dx;
        y0 += sy;
      }
    }
  }

  if (drawArrow)
  {
    float arrowLength = 3;
    float arrowAngle = 135;

    setLine(value, Line(line.getEndPoint(), line.angle() + arrowAngle, arrowLength));
    setLine(value, Line(line.getEndPoint(), line.angle() - arrowAngle, arrowLength));
  }
}

template<typename T>
void Matrix<T>::setCircle(T value, const Circle &circle, bool fill, unsigned int z)
{
  if (z >= m_qtyLayers)
  {
    return;
  }

  // code below copied partially from
  // https://en.wikipedia.org/wiki/Midpoint_circle_algorithm

  int x = circle.m_radius;
  int y = 0;
  int decisionOver2 = 1 - x;   // Decision criterion divided by 2 evaluated at x=r, y=0

  while(y <= x)
  {
    if (fill)
    {
      for (int xx = -x; xx <= x; xx++)
      {
        m_values[z][Converter::toUInt(circle.m_center.m_y) + y][Converter::toUInt(circle.m_center.m_x) + xx] = value; // Octant 1 + Octant 4
        m_values[z][Converter::toUInt(circle.m_center.m_y) - y][Converter::toUInt(circle.m_center.m_x) + xx] = value; // Octant 5 + Octant 8
      }

      for (int yy = -y; yy <= y; yy++)
      {
        m_values[z][Converter::toUInt(circle.m_center.m_y) + x][Converter::toUInt(circle.m_center.m_x) + yy] = value; // Octant 2 + Octant 3
        m_values[z][Converter::toUInt(circle.m_center.m_y) - x][Converter::toUInt(circle.m_center.m_x) + yy] = value; // Octant 6 + Octant 7
      }

      // IP memset for sizeof(T) == 1
      // IP improve performance: memset is called "too often" for first/last line in Octant 2 + 3 and Octant 6 + 7
      /*memset(&m_pixels[( y + circle.m_center.m_y) * m_width - x + circle.m_center.m_x], value, 2 * x + 1); //  Octant 1 + Octant 4
      memset(&m_pixels[( x + circle.m_center.m_y) * m_width - y + circle.m_center.m_x], value, 2 * y + 1); //  Octant 2 + Octant 3

      memset(&m_pixels[(-y + circle.m_center.m_y) * m_width - x + circle.m_center.m_x], value, 2 * x + 1); //  Octant 5 + Octant 8
      memset(&m_pixels[(-x + circle.m_center.m_y) * m_width - y + circle.m_center.m_x], value, 2 * y + 1); //  Octant 6 + Octant 7*/
    }
    else
    {
      m_values[z][Converter::toUInt(circle.m_center.m_y) + y][Converter::toUInt(circle.m_center.m_x) + x] = value; // Octant 1
      m_values[z][Converter::toUInt(circle.m_center.m_y) + x][Converter::toUInt(circle.m_center.m_x) + y] = value; // Octant 2
      m_values[z][Converter::toUInt(circle.m_center.m_y) + x][Converter::toUInt(circle.m_center.m_x) - y] = value; // Octant 3
      m_values[z][Converter::toUInt(circle.m_center.m_y) + y][Converter::toUInt(circle.m_center.m_x) - x] = value; // Octant 4

      m_values[z][Converter::toUInt(circle.m_center.m_y) - y][Converter::toUInt(circle.m_center.m_x) - x] = value; // Octant 5
      m_values[z][Converter::toUInt(circle.m_center.m_y) - x][Converter::toUInt(circle.m_center.m_x) - y] = value; // Octant 6
      m_values[z][Converter::toUInt(circle.m_center.m_y) - x][Converter::toUInt(circle.m_center.m_x) + y] = value; // Octant 7
      m_values[z][Converter::toUInt(circle.m_center.m_y) - y][Converter::toUInt(circle.m_center.m_x) + x] = value; // Octant 8
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

template<typename T>
void Matrix<T>::setFreemanCode(T value, const FreemanCode &freemanCode, unsigned int z)
{
  setPoint(value, freemanCode.m_startPoint, z);

  unsigned int x = freemanCode.m_startPoint.m_x;
  unsigned int y = freemanCode.m_startPoint.m_y;

  for (auto it = freemanCode.m_directions.begin(); it != freemanCode.m_directions.end(); it++)
  {
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

    setPoint(value, Point(x, y), z);
  }
}

template<typename T>
void Matrix<T>::setPolyLine(T value, const PolyLine &polyLine, unsigned int z)
{
  if (polyLine.size()< 2)
  {
    return;
  }

  auto itPrevious = polyLine.begin();
  for (auto it = polyLine.begin(); it != polyLine.end(); it++)
  {
    if (it == polyLine.begin())
    {
      continue;
    }

    Line line(*itPrevious, *it);

    if (isLineInsideImage(line))
    {
      setLine(value, line, z);
    }

    itPrevious = it;
  }
}

template<typename T>
void Matrix<T>::setHistogram(const std::vector<unsigned int> &histogram, unsigned int z)
{
  clear();

  unsigned int barWidth = m_width / histogram.size();

  unsigned int maxValue = std::numeric_limits<unsigned int>::min();

  // IP use iterator
  for (unsigned int i = 0; i < histogram.size(); i++)
  {
    if (histogram[i] > maxValue)
    {
      maxValue = histogram[i];
    }
  }

  for (unsigned int i = 0; i < histogram.size(); i++)
  {
    unsigned int barHeight = histogram[i] * m_height * 1.0 / maxValue;
    for (unsigned int j = 0; j < barWidth; j++)
    {
      setLine(std::numeric_limits<T>::max(), Line(Point(i * barWidth + j, m_height - 1), Point(i * barWidth + j, m_height - barHeight)), z);
    }
  }
}

template<typename T>
void Matrix<T>::setRunLengthCode(T value, const RunLengthCode &runLengthCode, unsigned int z)
{
  for (auto it = runLengthCode.begin(); it != runLengthCode.end(); it++)
  {
    setLine(value, Line(it->m_startPoint, Point(it->m_startPoint.m_x + it->m_length - 1, it->m_startPoint.m_y)), z);
  }
}

template<typename T>
void Matrix<T>::setStructureElement(T value, const StructuringElement *structuringElement, const Point &referencePointPosition, unsigned int z)
{
  // check top
  if (Converter::toUInt(structuringElement->getReferencePoint().m_y) > Converter::toUInt(referencePointPosition.m_y))
  {
    return;
  }

  // check bottom
  if ((structuringElement->getHeight() - Converter::toUInt(structuringElement->getReferencePoint().m_y)) > (m_height - Converter::toUInt(referencePointPosition.m_y)))
  {
    return;
  }

  // check left
  if (Converter::toUInt(structuringElement->getReferencePoint().m_x) > Converter::toUInt(referencePointPosition.m_x))
  {
    return;
  }

  // check right
  if ((structuringElement->getWidth() - Converter::toUInt(structuringElement->getReferencePoint().m_x)) > (m_width - Converter::toUInt(referencePointPosition.m_x)))
  {
    return;
  }

  unsigned int dx = referencePointPosition.m_x - structuringElement->getReferencePoint().m_x;
  unsigned int dy = referencePointPosition.m_y - structuringElement->getReferencePoint().m_y;

  for (unsigned int x = 0; x < structuringElement->getWidth(); x++)
  {
    for (unsigned int y = 0; y < structuringElement->getHeight(); y++)
    {
      if (structuringElement->getValue(x, y))
      {
        m_values[z][y + dy][x + dx] = value;
      }
    }
  }
}

template<typename T>
void Matrix<T>::filter(const Filter *filter, unsigned int z)
{
  Matrix<T> original(*this);

  short*** filterValues = filter->getValues();

  unsigned int offsetLeft = filter->getReferencePoint().m_x;
  unsigned int offsetTop = filter->getReferencePoint().m_y;
  unsigned int offsetRight = filter->getWidth() - offsetLeft - 1;
  unsigned int offsetBottom = filter->getHeight() - offsetTop - 1;

  double calculatedValue;
  for (unsigned int y = offsetTop; y < (m_height - offsetBottom); y++)
  {
    for (unsigned int x = offsetLeft; x < (m_width - offsetRight); x++)
    {
      calculatedValue = 0;
      for (unsigned int fy = 0; fy < filter->getHeight(); fy++)
      {
        for (unsigned int fx = 0; fx < filter->getWidth(); fx++)
        {
          calculatedValue += original.m_values[z][y + fy - offsetTop][x + fx - offsetLeft] * filterValues[0][fy][fx];
        }
      }
      calculatedValue *= filter->getPreFactor();
      calculatedValue > 0 ? calculatedValue += 0.5 : calculatedValue -= 0.5;

      if (filter->getShiftResultValues())
      {
        calculatedValue += ((std::numeric_limits<T>::max() - std::numeric_limits<T>::min()) / 2);
      }

      if (filter->getInvertNegativeResultValues())
      {
        if (calculatedValue < 0)
        {
          calculatedValue *= -1;
        }
      }

      if (calculatedValue < std::numeric_limits<T>::min())
      {
        calculatedValue = std::numeric_limits<T>::min();
      }

      if (calculatedValue > std::numeric_limits<T>::max())
      {
        calculatedValue = std::numeric_limits<T>::max();
      }

      m_values[z][y][x] = calculatedValue;
    }
  }
}

template<typename T>
void Matrix<T>::filterQuantilBool(const StructuringElement* structuringElement, double quantil, unsigned int z)
{
  Matrix<T> original(*this);

  unsigned int offsetLeft = structuringElement->getReferencePoint().m_x;
  unsigned int offsetTop = structuringElement->getReferencePoint().m_y;
  unsigned int offsetRight = structuringElement->getWidth() - offsetLeft - 1;
  unsigned int offsetBottom = structuringElement->getHeight() - offsetTop - 1;

  unsigned int sumOfSetValues = structuringElement->getSumOfSetValues();
  unsigned int sum = 0;

  unsigned int threshold = quantil * sumOfSetValues;
  if (threshold > structuringElement->getSumOfSetValues() - 1)
  {
    threshold = structuringElement->getSumOfSetValues() - 1;
  }

  RunLengthCode runLengthCode = structuringElement->getRunLengthCode(true);

  for (unsigned int y = offsetTop; y < (m_height - offsetBottom); y++)
  {
    for (unsigned int x = offsetLeft; x < (m_width - offsetRight); x++)
    {
      if (x == offsetLeft)
      {
        sum = 0;

        for (unsigned int fy = 0; fy < structuringElement->getHeight(); fy++)
        {
          for (unsigned int fx = 0; fx < structuringElement->getWidth(); fx++)
          {
            if (structuringElement->isValueSet(fx, fy) && original.m_values[z][y + fy - offsetTop][fx])
            {
              sum++;
            }
          }
        }
      }
      else
      {
        for (auto it = runLengthCode.begin(); it != runLengthCode.end(); it++)
        {
          unsigned int dx = x - offsetLeft + it->m_startPoint.m_x - 1;

          // remove entry of left side
          if (original.m_values[z][y - offsetTop + Converter::toUInt(it->m_startPoint.m_y)][dx])
          {
            sum--;
          }

          // add entry of right side
          if (original.m_values[z][y - offsetTop + Converter::toUInt(it->m_startPoint.m_y)][dx + it->m_length])
          {
            sum++;
          }
        }
      }

      m_values[z][y][x] = (sum > threshold);
    }
  }
}

template<typename T>
void Matrix<T>::performanceTestAccessPixels(unsigned int mode)
{
  /*
    Mac OS 10.11.3 - Qt 5.2.0 clang 64bit - width = height = 65535
    method 0 took 2050 milliseconds
    method 1 took 2098 milliseconds
    method 2 took 1058 milliseconds
    method 3 took 113 milliseconds
    method 4 took 110 milliseconds
    method 5 took 113 milliseconds
    method 6 took 911 milliseconds
  */

  /*
    Windows 7 - Qt 4.8.7 - Microsoft Visual Studio C++ Compiler 10.0 (x86) - width = height = 30000
    method 0 took 4094 milliseconds
    method 1 took 4573 milliseconds
    method 2 took 572 milliseconds
    method 3 took 77 milliseconds
    method 4 took 77 milliseconds
    method 5 took 76 milliseconds
    method 6 took 76 milliseconds
  */

  // method 3 should be the best - matrix should have additional parameter m_size which is calculated each time the width or height changes
  // m_size must be <= size_t

  if (mode == 0)
  {
    for (unsigned int y = 0; y < m_height; y++)
    {
      for (unsigned int x = 0; x < m_width; x++)
      {
        m_values[0][y][x] = 255;
      }
    }
  }
  else if (mode == 1)
  {
    for (unsigned int y = 0; y < m_height; y++)
    {
      for (unsigned int x = 0; x < m_width; x++)
      {
        m_values[0][0][y * m_width + x] = 255;
      }
    }
  }
  else if (mode == 2)
  {
    T* it = m_values[0][0];
    for (unsigned int y = 0; y < m_height; y++)
    {
      for (unsigned int x = 0; x < m_width; x++)
      {
        *it++ = 255;
      }
    }
  }
  else if (mode == 3)
  {
    T* it = m_values[0][0];
    unsigned int size = m_height * m_width;
    for (unsigned int y = 0; y < size; y++)
    {
      *it++ = 255;
    }
  }
  else if (mode == 4)
  {
    memset(m_values[0][0], 255, m_height * m_width);
  }
  else if (mode == 5)
  {
    T* it = m_values[0][0];
    T* stop = &m_values[0][0][m_width * m_height - 1];

    while (it != stop)
    {
      *it++ = 255;
    }
    *it = 255;
  }
  else if (mode == 6)
  {
    T* it = m_values[0][0];
    T* stop = &m_values[0][0][m_width * m_height - 1];

    while (it <= stop)
    {
      *it++ = 255;
    }
  }
}

template<typename T>
void Matrix<T>::filterQuantil(const StructuringElement* structuringElement, double quantil, unsigned int z)
{
  if (quantil < 0.0 || quantil > 1.0)
  {
    return; // TODO throw exception ?
  }

  if (typeid(bool) == typeid(T))
  {
    filterQuantilBool(structuringElement, quantil, z);
    return;
  }

  if (std::numeric_limits<T>::is_signed || !std::numeric_limits<T>::is_integer)
  {
    return; // TODO throw exception ?
  }

  Matrix<T> original(*this);

  unsigned int offsetLeft = structuringElement->getReferencePoint().m_x;
  unsigned int offsetTop = structuringElement->getReferencePoint().m_y;
  unsigned int offsetRight = structuringElement->getWidth() - offsetLeft - 1;
  unsigned int offsetBottom = structuringElement->getHeight() - offsetTop - 1;

  unsigned long long histogram[sizeof(T) * 256];
  unsigned long long median = 0;
  unsigned int lessThanMedian = 0;
  unsigned int sumOfSetValues = structuringElement->getSumOfSetValues();

  unsigned int threshold = quantil * sumOfSetValues;
  if (threshold > structuringElement->getSumOfSetValues() - 1)
  {
    threshold = structuringElement->getSumOfSetValues() - 1;
  }

  RunLengthCode runLengthCode = structuringElement->getRunLengthCode(true);

  for (unsigned int y = offsetTop; y < (m_height - offsetBottom); y++)
  {
    for (unsigned int x = offsetLeft; x < (m_width - offsetRight); x++)
    {
      if (x == offsetLeft)
      {
        // Set up histogram for the first window (in every line)
        memset(histogram, 0, sizeof(histogram));

        for (unsigned int fy = 0; fy < structuringElement->getHeight(); fy++)
        {
          for (unsigned int fx = 0; fx < structuringElement->getWidth(); fx++)
          {
            if (structuringElement->isValueSet(fx, fy))
            {
              histogram[original.m_values[z][y + fy - offsetTop][fx]]++;
            }
          }
        }

        // find median by moving through the histogram bins
        int sum = 0;
        for (int i = 0; i < 256; i++)
        {
          sum += histogram[i];
          if (sum > threshold)
          {
            median = i;
            lessThanMedian = sum - histogram[i];
            break;
          }
        }
      }
      else
      {
        // update histogram
        for (auto it = runLengthCode.begin(); it != runLengthCode.end(); it++)
        {
          unsigned int dx = x - offsetLeft + it->m_startPoint.m_x - 1;

          // remove entry of left side
          T value = original.m_values[z][y - offsetTop + Converter::toUInt(it->m_startPoint.m_y)][dx];
          histogram[value]--;
          if (value < median)
          {
            lessThanMedian--;
          }

          // add entry of right side
          value = original.m_values[z][y - offsetTop + Converter::toUInt(it->m_startPoint.m_y)][dx + it->m_length];
          histogram[value]++;
          if (value < median)
          {
            lessThanMedian++;
          }
        }

        // find median
        if (lessThanMedian > threshold)
        {
          // the median in the current window is smaller than
          // the one in the previous window
          while (lessThanMedian > threshold)
          {
            median--;
            lessThanMedian -= histogram[median];
          }
        }
        else
        {
          while(lessThanMedian + histogram[median] <= threshold)
          {
            lessThanMedian += histogram[median];
            median++;
          }
        }
      }

      if (sumOfSetValues % 2 == 1 || quantil != 0.5) // TODO verify, is that correct?
      {
        m_values[z][y][x] = median;
      }
      else
      {
        unsigned long long medianCopy = median;
        unsigned int lessThanMedianCopy = lessThanMedian;

        while (lessThanMedianCopy > threshold - 1)
        {
          medianCopy--;
          lessThanMedianCopy -= histogram[medianCopy];
        }

        m_values[z][y][x] = ((double) median + medianCopy) / 2 + 0.5;
      }
    }
  }
}

template<typename T>
void Matrix<T>::filterConservativeSmoothing(const StructuringElement *structuringElement, unsigned int z)
{
  // look all values in structuringElement (except for reference point)
  // define minimum and maximum
  // if value at reference point is smaller than the minimum, the value is set to the minimum
  // if value at reference point is bigger than the maximum, the value is set to the maximum
  // see: http://homepages.inf.ed.ac.uk/rbf/HIPR2/csmooth.htm

  if (typeid(bool) == typeid(T))
  {
    return; // nothing to do
  }

  Matrix<T> original(*this);

  bool*** structuringElementValues = structuringElement->getValues();

  unsigned int offsetLeft = structuringElement->getReferencePoint().m_x;
  unsigned int offsetTop = structuringElement->getReferencePoint().m_y;
  unsigned int offsetRight = structuringElement->getWidth() - offsetLeft - 1;
  unsigned int offsetBottom = structuringElement->getHeight() - offsetTop - 1;

  T minimum;
  T maximum;
  for (unsigned int y = offsetTop; y < (m_height - offsetBottom); y++)
  {
    for (unsigned int x = offsetLeft; x < (m_width - offsetRight); x++)
    {
      minimum = std::numeric_limits<T>::max();
      maximum = std::numeric_limits<T>::min();

      for (unsigned int fy = 0; fy < structuringElement->getHeight(); fy++)
      {
        for (unsigned int fx = 0; fx < structuringElement->getWidth(); fx++)
        {
          bool onReferencePoint = (fx == offsetLeft && fy == offsetTop);

          if (structuringElementValues[0][fy][fx] && !onReferencePoint)
          {
            if (original.m_values[z][y + fy - offsetTop][x + fx - offsetLeft] < minimum)
            {
              minimum = original.m_values[z][y + fy - offsetTop][x + fx - offsetLeft];
            }
            if (original.m_values[z][y + fy - offsetTop][x + fx - offsetLeft] > maximum)
            {
              maximum = original.m_values[z][y + fy - offsetTop][x + fx - offsetLeft];
            }
          }
        }
      }

      if (original.m_values[z][y][x] < minimum)
      {
        m_values[z][y][x] = minimum;
      }

      if (original.m_values[z][y][x] > maximum)
      {
        m_values[z][y][x] = maximum;
      }
    }
  }
}

template<typename T>
void Matrix<T>::erode(const StructuringElement *structuringElement, unsigned int z)
{
  bool typeIsBool = (typeid(bool) == typeid(T));

  if (!typeIsBool && !std::numeric_limits<T>::is_signed && std::numeric_limits<T>::is_integer)
  {
    filterQuantil(structuringElement, 1.0, z);
    return;
  }

  Matrix<T> original(*this);

  bool*** structuringElementValues = structuringElement->getValues();

  unsigned int offsetLeft = structuringElement->getReferencePoint().m_x;
  unsigned int offsetTop = structuringElement->getReferencePoint().m_y;
  unsigned int offsetRight = structuringElement->getWidth() - offsetLeft - 1;
  unsigned int offsetBottom = structuringElement->getHeight() - offsetTop - 1;

  for (unsigned int y = offsetTop; y < (m_height - offsetBottom); y++)
  {
    for (unsigned int x = offsetLeft; x < (m_width - offsetRight); x++)
    {
      if (typeIsBool)
      {
        bool bitSet = false;
        for (unsigned int fy = 0; fy < structuringElement->getHeight() && !bitSet; fy++)
        {
          for (unsigned int fx = 0; fx < structuringElement->getWidth() && !bitSet; fx++)
          {
            if (structuringElementValues[0][fy][fx] && !original.m_values[z][y + fy - offsetTop][x + fx - offsetLeft])
            {
              m_values[z][y][x] = false;
              bitSet = true;
            }
          }
        }
        if (!bitSet)
        {
          m_values[z][y][x] = true;
        }
      }
      else
      {
        T minimum = std::numeric_limits<T>::max();

        for (unsigned int fy = 0; fy < structuringElement->getHeight(); fy++)
        {
          for (unsigned int fx = 0; fx < structuringElement->getWidth(); fx++)
          {
            if (structuringElementValues[0][fy][fx] && original.m_values[z][y + fy - offsetTop][x + fx - offsetLeft] < minimum)
            {
              minimum = original.m_values[z][y + fy - offsetTop][x + fx - offsetLeft];
            }
          }
        }
        m_values[z][y][x] = minimum;
      }
    }
  }
}

template<typename T>
void Matrix<T>::dilate(const StructuringElement *structuringElement, unsigned int z)
{
  bool typeIsBool = (typeid(bool) == typeid(T));

  if (!typeIsBool && !std::numeric_limits<T>::is_signed && std::numeric_limits<T>::is_integer)
  {
    filterQuantil(structuringElement, 0.0, z);
    return;
  }

  Matrix<T> original(*this);

  bool*** structuringElementValues = structuringElement->getValues();

  unsigned int offsetLeft = structuringElement->getReferencePoint().m_x;
  unsigned int offsetTop = structuringElement->getReferencePoint().m_y;
  unsigned int offsetRight = structuringElement->getWidth() - offsetLeft - 1;
  unsigned int offsetBottom = structuringElement->getHeight() - offsetTop - 1;

  for (unsigned int y = offsetTop; y < (m_height - offsetBottom); y++)
  {
    for (unsigned int x = offsetLeft; x < (m_width - offsetRight); x++)
    {
      if (typeIsBool)
      {
        bool bitSet = false;
        for (unsigned int fy = 0; fy < structuringElement->getHeight() && !bitSet; fy++)
        {
          for (unsigned int fx = 0; fx < structuringElement->getWidth() && !bitSet; fx++)
          {
            if (structuringElementValues[0][fy][fx] && original.m_values[z][y + fy - offsetTop][x + fx - offsetLeft])
            {
              m_values[z][y][x] = true;
              bitSet = true;
            }
          }
        }
        if (!bitSet)
        {
          m_values[z][y][x] = false;
        }
      }
      else
      {
        T maximum = std::numeric_limits<T>::min();

        for (unsigned int fy = 0; fy < structuringElement->getHeight(); fy++)
        {
          for (unsigned int fx = 0; fx < structuringElement->getWidth(); fx++)
          {
            if (structuringElementValues[0][fy][fx] && original.m_values[z][y + fy - offsetTop][x + fx - offsetLeft] > maximum)
            {
              maximum = original.m_values[z][y + fy - offsetTop][x + fx - offsetLeft];
            }
          }
        }

        m_values[z][y][x] = maximum;
      }
    }
  }
}

template<typename T>
void Matrix<T>::open(const StructuringElement *structuringElement, unsigned int z)
{
  erode(structuringElement, z);
  dilate(structuringElement, z);
}

template<typename T>
void Matrix<T>::close(const StructuringElement *structuringElement, unsigned int z)
{
  dilate(structuringElement, z);
  erode(structuringElement, z);
}

template<typename T>
void Matrix<T>::filterMedian(const StructuringElement *structuringElement, unsigned int z)
{
  if (!std::numeric_limits<T>::is_signed && std::numeric_limits<T>::is_integer)
  {
    filterQuantil(structuringElement, 0.5, z);
    return;
  }

  Matrix<T> original(*this);

  bool*** structuringElementValues = structuringElement->getValues();

  unsigned int offsetLeft = structuringElement->getReferencePoint().m_x;
  unsigned int offsetTop = structuringElement->getReferencePoint().m_y;
  unsigned int offsetRight = structuringElement->getWidth() - offsetLeft - 1;
  unsigned int offsetBottom = structuringElement->getHeight() - offsetTop - 1;

  std::vector<T> values;
  for (unsigned int y = offsetTop; y < (m_height - offsetBottom); y++)
  {
    for (unsigned int x = offsetLeft; x < (m_width - offsetRight); x++)
    {
      for (unsigned int fy = 0; fy < structuringElement->getHeight(); fy++)
      {
        for (unsigned int fx = 0; fx < structuringElement->getWidth(); fx++)
        {
          if (structuringElementValues[0][fy][fx])
          {
            values.push_back(original.m_values[z][y + fy - offsetTop][x + fx - offsetLeft]);
          }
        }
      }

      std::sort(values.begin(), values.end());

      if (values.size() % 2 == 0)
      {
        m_values[z][y][x] = ((double)values[values.size() / 2 - 1] + values[values.size() / 2]) / 2 + 0.5; // TODO correct implemenation for negative values
      }
      else
      {
        m_values[z][y][x] = values[values.size() / 2];
      }

      values.clear();
    }
  }
}

template<typename T>
void Matrix<T>::invert()
{
  for (unsigned int z = 0; z < m_qtyLayers; z++)
  {
    T* it = m_values[z][0];
    for (unsigned int i = 0; i < m_size; i++)
    {
      if (typeid(T) == typeid(bool))
      {
        *it = !(*it);
      }
      else
      {
        if (std::numeric_limits<T>::is_signed)
        {
          // TODO
        }
        else
        {
          *it = std::numeric_limits<T>::max() - *it;
        }
      }
      it++;
    }
  }
}

template<typename T>
void Matrix<T>::fillBackground(T backgroundValue, T fillValue, unsigned int z)
{

  if (m_height < 3 || m_width < 3)
  {
    replace(backgroundValue, fillValue, z);
    return;
  }

  // set edge points
  m_values[z][0][0] = fillValue;
  m_values[z][0][m_width-1] = fillValue;
  m_values[z][m_height-1][0] = fillValue;
  m_values[z][m_height-1][m_width-1] = fillValue;

  std::list<Point> floodPoints;

  // view in first line
  for (unsigned int x = 1; x < m_width - 1; x++)
  {
    if (m_values[z][0][x] == backgroundValue)
    {
      m_values[z][0][x] = fillValue;
      if (m_values[z][1][x] == backgroundValue)
      {
        floodPoints.push_back(Point(x, 1));
      }
    }
  }

  // view in first colum
  for (unsigned int y = 1; y < m_height - 1; y++)
  {
    if (m_values[z][y][0] == backgroundValue)
    {
      m_values[z][y][0] = fillValue;
      if (m_values[z][y][1] == backgroundValue)
      {
        floodPoints.push_back(Point(1, y));
      }
    }
  }

  // view in last colum
  for (unsigned int y = 1; y < m_height - 1; y++)
  {
    if (m_values[z][y][m_width - 1] == backgroundValue)
    {
      m_values[z][y][m_width - 1] = fillValue;
      if (m_values[z][y][m_width - 2] == backgroundValue)
      {
        floodPoints.push_back(Point(m_width - 2, y));
      }
    }
  }

  // view in last line
  for (unsigned int x = 1; x < m_width - 1; x++)
  {
    if (m_values[z][m_height - 1][x] == backgroundValue)
    {
      m_values[z][m_height - 1][x] = fillValue;
      if (m_values[z][m_height - 2][x] == backgroundValue)
      {
        floodPoints.push_back(Point(x, m_height - 2));
      }
    }
  }

  unsigned int x;
  unsigned int y;

  while(!floodPoints.empty())
  {
    x = floodPoints.front().m_x;
    y = floodPoints.front().m_y;

    m_values[z][y][x] = fillValue;

    // look left
    if (m_values[z][y][x-1] == backgroundValue)
    {
      floodPoints.push_back(Point(x-1, y));
    }

    // look up
    if (m_values[z][y-1][x] == backgroundValue)
    {
      floodPoints.push_back(Point(x, y-1));
    }

    // look down
    if (m_values[z][y+1][x] == backgroundValue)
    {
      floodPoints.push_back(Point(x, y+1));
    }

    // look right
    if (m_values[z][y][x+1] == backgroundValue)
    {
      floodPoints.push_back(Point(x+1, y));
    }

    floodPoints.pop_front();
  }
}

template<typename T>
void Matrix<T>::replace(T currentValue, T newValue, unsigned int z)
{
  T* it = m_values[z][0];
  for (unsigned int i = 0; i < m_size; i++, it++)
  {
    if (*it == currentValue)
    {
      *it = newValue;
    }
  }
}

template<typename T>
Edges Matrix<T>::findEdges(const Line &line, float minContrast, unsigned int smoothingWidth, unsigned int z)
{
  Edges edges;

  Points points = line.getPointsAlongLine();

  std::cout << "size: " << points.size() << std::endl;

  unsigned int stepSize = 1;

  std::list<double> averages;

  float distance1 = smoothingWidth / 2;
  float distance2 = smoothingWidth / 2;

  if (smoothingWidth % 2 == 0)
  {
    distance2--;
  }

  if (smoothingWidth > 1)
  {
    double d1 = sin(MathHelper::rad(line.angle()));
    double d2 = cos(MathHelper::rad(line.angle()));

    /*std::cout << "d1: " << d1 << std::endl;
    std::cout << "d2: " << d2 << std::endl;*/

    double lengthCorrection = d1 + d2; // TODO does not seem to be perfect

    //std::cout << "d1 + d2: " << lengthCorrection << std::endl;

    distance1 *= lengthCorrection;
    distance2 *= lengthCorrection;
  }

  for (auto it = points.begin(); it != points.end(); it++)
  {
    if (smoothingWidth > 1)
    {
      Point p1 = MathHelper::calcEndPoint(*it, line.angle() - 90, distance1);
      Point p2 = MathHelper::calcEndPoint(*it, line.angle() + 90, distance2);

      Line verticalLine(p1, p2);

      /*if (it == points.begin())
      {
        setLine(255, verticalLine);
      }*/

      averages.push_back(getAverageAlongLine(verticalLine, z));
    }
    else
    {
      averages.push_back(m_values[z][Converter::toUInt(it->m_y)][Converter::toUInt(it->m_x)]);
    }


    if (averages.size() > stepSize)
    {
      double difference = averages.back() - averages.front();

      if (difference > minContrast || difference < -minContrast)
      {
        edges.push_back(Edge(*it, line.angle(), difference));
        //std::cout << "difference: " << difference << std::endl;
        setPoint(255, *it);
      }

      averages.pop_front();
    }
  }

  return edges;
}

template<typename T>
void Matrix<T>::mirrorOnHorizontalAxis()
{
  Matrix<T> original(*this);

  for (unsigned int z = 0; z < m_qtyLayers; z++)
  {
    for (unsigned int y = 0; y < m_height; y++)
    {
      memcpy(&m_values[z][y][0], &(original.m_values[z][m_height - y - 1][0]), m_width * sizeof(T));
    }
  }
}

template<typename T>
void Matrix<T>::mirrorOnVerticalAxis()
{
  Matrix<T> original(*this);
  for (unsigned int z = 0; z < m_qtyLayers; z++)
  {
    for (unsigned int x = 0; x < m_width; x++)
    {
      for (unsigned int y = 0; y < m_height; y++)
      {
        m_values[z][y][x] = original.m_values[z][y][m_width - x - 1];
      }
    }
  }
}

template<typename T>
void Matrix<T>::rotateBy90DegreeClockwise()
{
  Matrix<T> original(*this);

  m_width = original.m_height;
  m_height = original.m_width;

  if (m_width != m_height)
  {
    destroyRowBeginVector();
    createRowBeginVector();
  }

  for (unsigned int z = 0; z < m_qtyLayers; z++)
  {
    for (unsigned int y = 0; y < m_height; y++)
    {
      for (unsigned int x = 0; x < m_width; x++)
      {
        m_values[z][y][x] = original.m_values[z][original.m_height - x - 1][y];
      }
    }
  }
}

template<typename T>
void Matrix<T>::rotateBy90DegreeCounterClockwise()
{
  Matrix<T> original(*this);

  m_width = original.m_height;
  m_height = original.m_width;

  if (m_width != m_height)
  {
    destroyRowBeginVector();
    createRowBeginVector();
  }

  for (unsigned int z = 0; z < m_qtyLayers; z++)
  {
    for (unsigned int y = 0; y < m_height; y++)
    {
      for (unsigned int x = 0; x < m_width; x++)
      {
        m_values[z][y][x] = original.m_values[z][x][original.m_width - y - 1];
      }
    }
  }
}

template<typename T>
void Matrix<T>::rotateBy180Degree()
{
  Matrix<T> original(*this);
  for (unsigned int z = 0; z < m_qtyLayers; z++)
  {
    for (unsigned int x = 0; x < m_width; x++)
    {
      for (unsigned int y = 0; y < m_height; y++)
      {
        m_values[z][y][x] = original.m_values[z][m_height - y - 1][m_width - x - 1];
      }
    }
  }
}

template<typename T>
Matrix<T> Matrix<T>::crop(const Rectangle& cropRegion)
{
  if (!isRectangleInsideImage(cropRegion))
  {
    return Matrix<T>();
  }

  Matrix<T> cropped(cropRegion.m_width, cropRegion.m_height, m_qtyLayers);

  // TODO what about rotated rectangles?

  for (unsigned int z = 0; z < m_qtyLayers; z++)
  {
    for (unsigned int y = 0; y < cropRegion.m_height; y++)
    {
      memcpy(cropped.m_values[z][y], &m_values[z][y+cropRegion.m_origin.m_y][cropRegion.m_origin.m_x], cropRegion.m_width * sizeof(T));
    }
  }

  return cropped;
}

template<typename T>
Matrix<T> Matrix<T>::doPolarTransformation(const Circle &circle)
{
  if (!isCircleInsideImage(circle))
  {
    return Matrix<T>(1, 1);
  }

  unsigned int circumference = circle.m_radius * 2 * 3.14159265359 + 0.5;

  int width = circumference;

  if (width % 4 != 0)
  {
    width += (4 - (width % 4)); // round up -> width % 4 needs to be zero!
  }

  Matrix<T> calculated(width, circle.m_radius, m_qtyLayers); // TODO correct sizes

  for (unsigned int z = 0; z < m_qtyLayers; z++)
  {
    for (unsigned int y = 0; y < circle.m_radius; y++) // radius
    {
      for (unsigned int x = 0; x < circumference; x++) // angle
      {
        // TODO improve performace -> avoid duplicated calculations -> avoid conversions

        int angle = x * 360.0 / circumference;
        int radius = y;

        int xx = radius * cos(angle * PI / 180.0);
        int yy = radius * sin(angle * PI / 180.0);

        calculated.m_values[z][y][x] = m_values[z][yy + Converter::toUInt(circle.m_center.m_y)][xx + Converter::toUInt(circle.m_center.m_x)];
      }
    }
  }

  return calculated;
}

template<typename T>
void Matrix<T>::applyLookUpTable(const std::vector<T>& lookUpTable)
{
  if (std::numeric_limits<T>::is_signed)
  {
    // TODO how to define a LUT for negative values?
    return;
  }

  if (lookUpTable.size() < std::numeric_limits<T>::max() + 1)
  {
    // LUT not fully defined
    return;
  }

  for (unsigned int z = 0; z < m_qtyLayers; z++)
  {
    T* it = m_values[z][0];
    for (unsigned int i = 0; i < m_size; i++, it++)
    {
      *it = lookUpTable[*it];
    }
  }
}

template<typename T>
unsigned int Matrix<T>::minimum(unsigned int value1, unsigned int value2)
{
  return value1 < value2 ? value1 : value2;
}

template<typename T>
unsigned int Matrix<T>::maximum(unsigned int value1, unsigned int value2)
{
  return value1 > value2 ? value1 : value2;
}

template<typename T>
unsigned int Matrix<T>::calculateBinomialCoefficient(unsigned int n, unsigned int k)
{
  if (k > n)
  {
    return 0;
  }

  // calculate n over k
  double binomialCoefficient = 1;

  for (unsigned int i = 1; i <= k; i++)
  {
    binomialCoefficient *= ((n + 1.0 - i) / i);
  }

  return binomialCoefficient;
}

template<typename T>
unsigned int Matrix<T>::getWidth() const
{
  return m_width;
}

template<typename T>
unsigned int Matrix<T>::getHeight() const
{
  return m_height;
}

template<typename T>
unsigned int Matrix<T>::getQtyLayers() const
{
  return m_qtyLayers;
}

template<typename T>
T Matrix<T>::getMinimum() const
{
  T minimum = std::numeric_limits<T>::max();
  for (unsigned int z = 0; z < m_qtyLayers; z++)
  {
    T* it = m_values[z][0];
    for (unsigned int i = 0; i < m_size; i++, it++)
    {
      if (*it < minimum)
      {
        minimum = *it;
      }
    }
  }
  return minimum;
}

template<typename T>
T Matrix<T>::getMaximum() const
{
  T maximum = std::numeric_limits<T>::min();
  for (unsigned int z = 0; z < m_qtyLayers; z++)
  {
    T* it = m_values[z][0];
    for (unsigned int i = 0; i < m_size; i++, it++)
    {
      if (*it > maximum)
      {
        maximum = *it;
      }
    }
  }
  return maximum;
}

template<typename T>
void Matrix<T>::printValuesToConsole(const std::string& description) const
{
  std::cout << "--------------------------------------------------------------------------------" << std::endl;
  std::cout << description << std::endl;
  for (unsigned int z = 0; z < m_qtyLayers; z++)
  {
    std::cout << std::endl << "layer " << z << std::endl;

    T* it = m_values[z][0];
    for (unsigned int i = 0; i < m_size; i++, it++)
    {
      if (typeid(bool) == typeid(T))
      {
        if (*it)
        {
          std::cout << "*";
        }
        else
        {
          std::cout << " ";
        }
      }
      else
      {
        if (*it < 10)
        {
          std::cout << " ";
        }

        if (*it < 100)
        {
          std::cout << " ";
        }
        if (*it < 1000)
        {
          std::cout << " ";
        }
        if (sizeof(T) > 1)
        {
          std::cout << *it << " ";
        }
        else
        {
          std::cout << (int) *it << " ";
        }
      }

      if (i % m_width == m_width - 1)
      {
        std::cout << "|" << std::endl;
      }
    }

  }
}

template<typename T>
void Matrix<T>::printDifference(const Matrix &rhs) const
{
  if (m_width  != rhs.m_width)
  {
    std::cout << "m_width is different" << std::endl;
    return;
  }

  if (m_height != rhs.m_height)
  {
    std::cout << "m_height is different" << std::endl;
    return;
  }

  if (m_qtyLayers != rhs.m_qtyLayers)
  {
    std::cout << "m_qtyLayers is different" << std::endl;
    return;
  }

  for (unsigned int z = 0; z < m_qtyLayers; z++)
  {
    for (unsigned int y = 0; y < m_height; y++)
    {
      for (unsigned int x = 0; x < m_width; x++)
      {
        if (m_values[z][y][x] != rhs.m_values[z][y][x])
        {
          std::cout << "m_values[" << z << "][" << y << "][" << x << "]: " << (int) m_values[z][y][x] << " is different to " << (int) rhs.m_values[z][y][x] << std::endl;
          return;
        }
      }
    }
  }

  std::cout << "no difference" << std::endl;
}

template<typename T>
void Matrix<T>::setIncreasingValues()
{
  T value = 0;
  for (unsigned int z = 0; z < m_qtyLayers; z++)
  {
    T* it = m_values[z][0];
    for (unsigned int i = 0; i < m_size; i++, it++)
    {
      *it = value++;
    }
  }
}

// implement function below, if you need all permutations of filter-type and image-type
/*template<typename F, typename M>
void filterMatrix(Matrix<M>* matrix, Matrix<F>* filter, const Point& referencePoint, double preFactor = 1.0, unsigned z = 0)
{
  M*** m = matrix->getValues();
  F*** f = filter->getValues();

  for (unsigned int y = 0; y < matrix->getHeight(); y++)
  {
    for (unsigned int x = 0; x < matrix->getWidth(); x++)
    {
      m[z][y][x] = f[0][referencePoint.m_y][referencePoint.m_x];
    }
  }
}*/

/* iterate over all values
for (unsigned int z = 0; z < m_qtyLayers; z++)
{
  T* it = m_values[z][0];
  for (unsigned int i = 0; i < m_size; i++, it++)
  {
    *it = ;
  }
}
*/

#endif // MATRIX_H
