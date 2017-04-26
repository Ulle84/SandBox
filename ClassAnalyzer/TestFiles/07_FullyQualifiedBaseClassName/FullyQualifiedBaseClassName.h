// header guard

class F
{
  
};

namespace Test
{
  class D
  {
    
  };
  
  namespace Test2
  {
    class A
    {

    };

    class B : public A
    {

    };
    
    class E : public D
    {
      
    };
  }
  
  class G : public F
  {
    
  };
  
  namespace Test3
  {
    class F
    {
      
    };
    
    class G : public F
    {
      
    };
    
    class H : public Test3::F
    {
      
    };
    
    class I : public Test::Test3::F
    {
      
    };
  }
}

/*
output should be
F
Test::D
Test::Test2::A
Test::Test2::B : Test::Test2::A
Test::Test2::E : Test::D
Test::G : F
Test::Test3::F
Test::Test3::G : Test::Test3::F
Test::Test3::H : Test::Test3::F
Test::Test3::I : Test::Test3::F
*/