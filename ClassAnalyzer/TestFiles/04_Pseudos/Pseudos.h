#ifndef A1_h
#define A1_h



class fowardDeclarationNotAClass;



typedef std::vector< class String> typeDefNotAClass;



/* this is a comment with the keyword class */

void emptyFunctionNotAClass(){};



class Class : public QList<A, 1>, public B
{
  void method(const class QString& parameterNotAClass)
  {
    // inline implementation;
  }
};

template <class templateNotAClassA, class templateNotAClassA> class RealClassA
{
  
};

template <class templateNotAClassA, class templateNotAClassA> class RealClassB : public QList<A, 1>
{
  
};

template <class templateNotAClassA, class templateNotAClassA> class RealClassC
{
  
};

class B
{
  
};

class ComplexClass:LUCENE_BASE, public CL_NS(util)::Compare::_base //<Token*>
{
public:
  bool operator()( Token* t1, Token* t2 ) const;
};

// TODO template class

#endif // A1_h
