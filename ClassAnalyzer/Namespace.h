#ifndef Namespace_h
#define Namespace_h

#include <QString>

class Namespace
{
public:
  Namespace();
  ~Namespace();

  int startPosition() const;
  int stopPosition() const;
  QString name() const;

  void setStartPosition(int startPosition);
  void setStopPosition(int stopPosition);
  void setName(const QString& name);

private:
  int m_startPosition;
  int m_stopPosition;
  QString m_name;
};

#endif // Namespace_h
