#ifndef Class_h
#define Class_h

#include <QString>
#include <QStringList>

// ToDo use class Class of CodeCreator (via DLL etc.)

class Class
{
public:
  Class(const QString& name);

  QString name() const;
  void setName(const QString& name);

  QStringList baseClasses() const;
  void setBaseClasses(const QStringList& baseClasses);

  QString header() const;
  void setHeader(const QString& header);

private:
  QString m_name;
  QStringList m_baseClasses;
  QString m_header;
};

#endif // Class_h
