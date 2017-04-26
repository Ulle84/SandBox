# Snippets

## Override argc/argv
```
const char* argv_override[] = {"exe", "-v"};
const int argc_override = static_cast<int>(sizeof(argv_override)/ sizeof(const char *));
```

## IsEqualTest
```
template<typename T>
inline bool IsEqualTest(const T& val1, const T& val2, const T& threshold)
{
  double res = std::abs(val1-val2);
  return (res <= threshold);
}
```

## round
```
template<typename T>
inline int round(T value)
{
  return static_cast<int>(value + (value >= 0 ? 0.5 : -0.5));
}
```

## TransformationRule
```
class TransformationRule
{
public:
  virtual ~TransformationRule() {};

  virtual void TransformPoint(Point2d& point) const = 0;
  virtual void ReverseTransformPoint(Point2d& point) const = 0;

  virtual void TranslatePoint(Point2d& point) const = 0;
  virtual void ReverseTranslatePoint(Point2d& point) const = 0;
};
```

## Transform with TransformationRule
```
template <typename T>
void PointExT<T>::Transform( const TransformationRule& rule )
{
  Point2d pt(x, y);
  rule.TransformPoint(pt);

  x = static_cast<T>(pt.x);
  y = static_cast<T>(pt.y);
}

template <typename T>
void PointExT<T>::ReverseTransform( const TransformationRule& rule )
{
  Point2d pt(x, y);
  rule.ReverseTransformPoint(pt);

  x = static_cast<T>(pt.x);
  y = static_cast<T>(pt.y);
}
```

## Corner/Point Titles
```
// Possible Corner/Point Titles
enum {P0,  P1,  P2,  P3}; 
enum {P00, PX0, PXY, P0Y}; 
enum {A,   B,   C,   D};   // http://de.wikipedia.org/wiki/Rechteck
getPoint(A); // -> switch case with 0, 1, 2, 3 ...
```

## IsConvex
```
template <typename T>
bool        IsConvex(PolylineT<T> const & polyline)
{
  auto qtyPoints = polyline.size();
  
  if(qtyPoints < 3)
    return false;

  auto hasRightTurns  = false;
  auto hasLeftTurns   = false;

  for(auto i=0; i<qtyPoints; ++i)
  {
    auto j = (i + 1) % qtyPoints;
    auto k = (i + 2) % qtyPoints;
    auto const & Pi = polyline[i];
    auto const & Pj = polyline[j];
    auto const & Pk = polyline[k];

    auto z = GetLengthOfCrossProduct(Pj-Pi,Pk-Pj);  // PiToPj * PjToPk

    if(z < 0)                                       // Negatives Vorzeichen entspricht einem Rechts-Knick.
      hasRightTurns = true;
    else if(z > 0)                                  // Positives Vorzeichen entspricht einem Links-Knick.
      hasLeftTurns  = true;
    if(hasLeftTurns==true && hasRightTurns==true)   // Liegt eine Mischung von Links- und Rechts-Knicken vor, dann ist das Polygon nicht konvex.
      return false;
  }

  return true;
}

template <typename T>
double GetLengthOfCrossProduct(Point2T<T> const & lhs, Point2T<T> const & rhs)
{
  return lhs.x*rhs.y-lhs.y*rhs.x;
}
```

## GetIntersectionOfLines
```
template <typename T>
bool        GetIntersectionOfLines(LineT<T> const & firstLine, LineT<T> const & secondLine, Point2T<T> & intersectionPoint)
{
  double ALine1 =  firstLine.end.y-firstLine.start.y;
  double BLine1 = -firstLine.end.x+firstLine.start.x;

  double ALine2 =  secondLine.end.y-secondLine.start.y;
  double BLine2 = -secondLine.end.x+secondLine.start.x;

  double Determinant = ALine1*BLine2 - ALine2*BLine1;

  if(Determinant==0)
    return false;

  double CLine1 = ALine1*firstLine.start.x  + BLine1*firstLine.start.y;
  double CLine2 = ALine2*secondLine.start.x + BLine2*secondLine.start.y;

  intersectionPoint.x = (BLine2*CLine1 - BLine1*CLine2)/Determinant;
  intersectionPoint.y = (ALine1*CLine2 - ALine2*CLine1)/Determinant;
  
  return true;
}

template <typename T>
LineIntersectionResult GetIntersectionOfLineSegments(LineT<T> const & firstLine, LineT<T> const & secondLine, Point2T<T> & intersectionPoint)
{
  // Darstellung der Linien:
  // Linie 1: p + t * r mit 0 <= t <= 1
  // Linie 2: q + u * s mit 0 <= u <= 1

  // Einen möglichen Schnittpunkt erhalten wir durch gleichsetzen
  // p + t*r = q + u*s, 
  // Durch Kreuzmultiplikation mit s erhält man
  // (p + t*r) x s = (q + u*s) x s = q x s
  // Und durch auflösen
  // t = (q - p) x s / (r x s).
  // u = (q - p) x r / (r x s).
  // Die Linien schneiden sich unter der Bedingung 0 <= t <= 1 und 0 <= 1 <= u.
  // Ist r x s = 0 dann verlaufen die Linien parallel.
  // Ist dazu noch (q - p) x r = 0 erfüllt, dann verlaufen die Linien kolinear.

  auto const epsilon        = 1e-12;

  auto offsetfirstLine      = firstLine .start;
  auto directionfirstLine   = firstLine .end - firstLine .start;
  auto offsetSecondLine     = secondLine.start;
  auto directionSecondLine  = secondLine.end - secondLine.start;

  auto lengthOfVectorProductOfDirections = GetLengthOfCrossProduct(directionfirstLine,directionSecondLine);

  // Behandlung des parallelen Falles
  if(lengthOfVectorProductOfDirections <= epsilon && lengthOfVectorProductOfDirections >= -epsilon) // Nenner ist Null. Geraden liegen parallel zueinander.
  {
    auto lengthOfVectorProduct = GetLengthOfCrossProduct(offsetSecondLine-offsetfirstLine, directionfirstLine);
    if(lengthOfVectorProduct <= epsilon && lengthOfVectorProduct >= -epsilon) // Wenn der Zähler auch Null ist, dann liegen die Geraden kolinear zueinander
    {
      // Wenn die x-Werte der ersten Linie alle kleiner oder alle größer sind als die der zweiten Linie, dann haben wir keinen Schnittpunkt.
      auto firstLineMinX = min(firstLine.start.x,firstLine.end.x);
      auto firstLineMaxX = max(firstLine.start.x,firstLine.end.x);
      if(secondLine.start.x < firstLineMinX && secondLine.end.x < firstLineMinX ||
         secondLine.start.x > firstLineMaxX && secondLine.end.x > firstLineMaxX)
        return ColinearNoIntersection;
      else
        return ColinearIntersection;
    }
    else
    {
      return ParallelNoIntersection;
    }
  }

  auto t = GetLengthOfCrossProduct(offsetSecondLine-offsetfirstLine, directionSecondLine) / lengthOfVectorProductOfDirections;
  auto u = GetLengthOfCrossProduct(offsetSecondLine-offsetfirstLine, directionfirstLine ) / lengthOfVectorProductOfDirections;

  if(u < 0. || u > 1.)
    return NoIntersection;
  if(t < 0. || t > 1.)
    return NoIntersection;

  intersectionPoint = offsetfirstLine + directionfirstLine * t;

  return Intersection;
}
```

## GetPerpendicularDistanceToLine
```
template <typename T>
double GetPerpendicularDistanceToLine(LineT<T> const & line, Point2T<T> const & point)
{
  T DirectionVectorx = line.end.x - line.start.x;
  T DirectionVectory = line.end.y - line.start.y;

  T StartPointToTestPointx = point.x - line.start.x;
  T StartPointToTestPointy = point.y - line.start.y;

  // return fabs( GetLengthOfCrossProduct(DistanceStartPointToTestPoint,DirectionVector) / GetLength(DirectionVector) );
  return fabs( (StartPointToTestPointx*DirectionVectory-StartPointToTestPointy*DirectionVectorx) / sqrt(DirectionVectorx*DirectionVectorx + DirectionVectory*DirectionVectory) );
}
```