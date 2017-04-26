#include "%ClassName%.%CppHeaderSuffix%"

@if "%Initialization%" == "Eager initialization"
%ClassName%* %ClassName%::mInstance = new %ClassName%();
@endif
@if "%Initialization%" == "Lazy initialization"
%ClassName%* %ClassName%::mInstance = nullptr;
@endif

%ClassName%::%ClassName%()
{
  
}

%ClassName%::~%ClassName%()
{
  
}

%ClassName%* %ClassName%::getInstance()
{
@if "%Initialization%" == "Lazy initialization"
  m_mutex.lock();
  if (mInstance == nullptr)
  {
    mInstance = new SingletonLazy();
  }
  m_mutex.unlock();
@endif
  return mInstance;
}