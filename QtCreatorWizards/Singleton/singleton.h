#ifndef %ClassName:u%_H
#define %ClassName:u%_H
@if "%Initialization%" == "Lazy initialization"

#include <QMutex>

@endif
class %ClassName%
{
public:
  static %ClassName%* getInstance();

private:
  %ClassName%();
  ~%ClassName%();
  %ClassName%(const %ClassName%& rhs);
  %ClassName%(%ClassName%&& rhs);
  %ClassName%& operator=(const %ClassName%& rhs);
@if "%ADDTESTCOMMENT%" == "true"

  // this is the required test comment :-)

@endif

  static %ClassName%* mInstance;
@if "%Initialization%" == "Lazy initialization"
  static QMutex m_mutex;
@endif
};

#endif // %ClassName:u%_H