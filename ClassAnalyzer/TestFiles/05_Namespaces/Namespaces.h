#ifndef A1_h
#define A1_h

class NoNamespace1{};

namespace A
{
  class A{};
  
  namespace B
  {
    class AB1{};
    
    namespace C
    {
      class ABC{};
    }
    
    class AB2{};
  }
  namespace D
  {
    class AD{};
  }
}

namespace E
{
  class E{};
}

namespace F
{
  namespace G
  {
    class FG{};
  }
}

class NoNamespace2{};

#endif // A1_h
