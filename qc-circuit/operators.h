#ifndef OPERATORS_H
#define OPERATORS_H

#include <string>
#include <vector>
#include <complex>
#include <map>


class Operator{
  public:
    std::string tag;
    Operator();
    virtual ~Operator();
    virtual std::map<std::string, std::complex<double>> aplicar_operador( std::map<std::string, std::complex<double>> dict_probs )=0;
    virtual int get_index()=0;
};


//Clases abstractas para numero de qubits fijos
class OneQubit: public Operator{
  protected:
    int indice;
  public:
    OneQubit( const int indice );
    virtual ~OneQubit();
    virtual std::tuple<std::complex<double>, std::complex<double>> accion( const char flag, std::complex<double> prob1)=0;
    std::map<std::string, std::complex<double>> aplicar_operador( std::map<std::string, std::complex<double>> dict_probs ) final;
    int get_index() final;
};


class TwoQubit: public Operator{
  protected:
    int indice;
    int indice_2;
  public:
    TwoQubit( const int indice1, const int indice2 );
    virtual ~TwoQubit();
    virtual std::tuple< std::complex<double>, std::complex<double>, std::complex<double>, std::complex<double> > 
      accion(const char flag1, const char flag2, std::complex<double> prob)=0;
    std::map<std::string, std::complex<double>> aplicar_operador( std::map<std::string, std::complex<double>> dict_probs ) final; 
    int get_index() final;
};



//Compuertas de un qubit 
class RxGate: public OneQubit{
  private:
    double angle;
  public:
    RxGate( const int indice, const double angle );
    ~RxGate();
    std::tuple<std::complex<double>, std::complex<double>> accion( const char flag, std::complex<double> prob1) final;
};

class RyGate: public OneQubit{
  private:
    double angle;
  public:
    RyGate( const int indice, const double angle );
    ~RyGate();
    std::tuple<std::complex<double>, std::complex<double>> accion(const char flag, std::complex<double> prob1) final;
};

class RzGate: public OneQubit{
  private:
    double angle;
  public:
    RzGate( const int indice, const double angle );
    ~RzGate();
    std::tuple<std::complex<double>, std::complex<double>> accion(const char flag, std::complex<double> prob1) final;
};

class HGate: public OneQubit{
  public:
    HGate( const int indice );
    ~HGate();
    std::tuple<std::complex<double>, std::complex<double>> accion(const char flag, std::complex<double> prob1) final;
};

class XGate: public OneQubit{    
  public:
    XGate( const int indice );
    ~XGate();
    std::tuple<std::complex<double>, std::complex<double>> accion(const char flag, std::complex<double> prob1) final;
};

class ZGate: public OneQubit{
  public:
    ZGate( const int indice );
    ~ZGate();
    std::tuple<std::complex<double>, std::complex<double>> accion(const char flag, std::complex<double> prob1) final;
};

class YGate: public OneQubit{
  public:
    YGate( const int indice );
    ~YGate();
    std::tuple<std::complex<double>, std::complex<double>> accion(const char flag, std::complex<double> prob1) final;
};


//Compuerta condicionales
class CnotGate: public TwoQubit{
  public:
    CnotGate( const int indice1, const int indice2 );
    ~CnotGate();
    std::tuple< std::complex<double>, std::complex<double>, std::complex<double>, std::complex<double> >
      accion(const char flag1, const char flag2, std::complex<double> prob) final;
};

class CZGate: public TwoQubit{
  public:
    CZGate( const int indice1, const int indice2 );
    ~CZGate();
    std::tuple< std::complex<double>, std::complex<double>, std::complex<double>, std::complex<double> >
      accion(const char flag1, const char flag2, std::complex<double> prob) final;
};

class CYGate: public TwoQubit{
  public:
    CYGate( const int indice1, const int indice2 );
    ~CYGate();
    std::tuple< std::complex<double>, std::complex<double>, std::complex<double>, std::complex<double> >
      accion(const char flag1, const char flag2, std::complex<double> prob) final;
};

class CHGate: public TwoQubit{
  public:
    CHGate( const int indice1, const int indice2 );
    ~CHGate();
    std::tuple< std::complex<double>, std::complex<double>, std::complex<double>, std::complex<double> >
      accion(const char flag1, const char flag2, std::complex<double> prob) final;
};

class CRXGate: public TwoQubit{
private:
    double angle;
  public:
    CRXGate( const int indice1, const int indice2, const double angle );
    ~CRXGate();
    std::tuple< std::complex<double>, std::complex<double>, std::complex<double>, std::complex<double> >
      accion(const char flag1, const char flag2, std::complex<double> prob) final;
};


class CRYGate: public TwoQubit{
private:
    double angle;
  public:
    CRYGate( const int indice1, const int indice2, const double angle );
    ~CRYGate();
    std::tuple< std::complex<double>, std::complex<double>, std::complex<double>, std::complex<double> >
      accion(const char flag1, const char flag2, std::complex<double> prob) final;
};


class CRZGate: public TwoQubit{
private:
    double angle;
  public:
    CRZGate( const int indice1, const int indice2, const double angle );
    ~CRZGate();
    std::tuple< std::complex<double>, std::complex<double>, std::complex<double>, std::complex<double> >
      accion(const char flag1, const char flag2, std::complex<double> prob) final;
};




#endif
