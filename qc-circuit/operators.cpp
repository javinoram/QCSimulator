#include "operators.h"
#include <iostream>
#include <complex>
#include <cmath>
#include <tuple>


Operator::Operator(){};
Operator::~Operator(){};

//Constructores y destructores de las clases padres
OneQubit::OneQubit( const int indice ){
  (this->indice) = indice;
};
OneQubit::~OneQubit(){ std::cout<<"Destructor OneQubit"<<std::endl; };

TwoQubit::TwoQubit( const int indice1, const int indice2 ){
  (this->indice_1) = indice_1;
  (this->indice_2) = indice_2;
};
TwoQubit::~TwoQubit(){ std::cout<<"Destructor TwoQubit"<<std::endl; };


//Metodos de las clases hijas de la clase OneQubit
RxGate::RxGate( const int indice, const double angle ): OneQubit(indice) { 
  (this->angle) = angle;
};

//cambios que hacer
//la funcion tiene que retornar una tupla con las probabilidades
RxGate::~RxGate(){std::cout<<"Destructor RxGate"<<std::endl;};
std::map<std::string, std::complex<double>> RxGate::aplicar_operador(std::map<std::string, std::complex<double>> dict_probs){
  std::map<std::string, std::complex<double>> new_probs;
  int index_accion = OneQubit::indice;

  for( auto it=dict_probs.begin(); it!=dict_probs.end(); it++ ){
    std::string estado_2 = it->first;
    estado_2[index_accion] = ( (it->first)[index_accion]=='0' ) ? '1' : '0';
    std::complex<double> p1 = it->second;
    std::complex<double> p2 = dict_probs[ estado_2 ];

    auto tuple_probs = accion( (it->first)[index_accion], p1);
    p1 = std::get<0>(tuple_probs);
    p2 = std::get<1>(tuple_probs);
      
    auto it_estado1 = new_probs.find( it->first );
    if( it_estado1 != new_probs.end() ){
      new_probs[ it->first ] = (new_probs[ it->first ]) + p1;
    }else{
      new_probs[ it->first ] = p1;
    };

    auto it_estado2 = new_probs.find( estado_2 );
    if( it_estado2 != new_probs.end() ){
      new_probs[ estado_2 ] = (new_probs[ estado_2 ]) + p2;
    }else{
      new_probs[estado_2] = p2;
    }
  };
  return new_probs;
};

std::tuple<std::complex<double>, std::complex<double>> RxGate::accion(const char flag, std::complex<double> prob1){
  std::complex<double> i(0,1);
  if( flag == '0' ){
    return { prob1*cos( (this->angle)*0.5 ), -i*prob1*sin( (this->angle)*0.5 ) };
  }
  return { -i*prob1*sin( (this->angle)*0.5 ), prob1*cos( (this->angle)*0.5 ) };
};



RyGate::RyGate( const int indice, const double angle ): OneQubit(indice){
  (this->angle) = angle;
};
RyGate::~RyGate(){std::cout<<"Destructor RyGate"<<std::endl;};
std::tuple<std::complex<double>, std::complex<double>> RyGate::accion(const char flag, std::complex<double> prob1){
  std::complex<double> i(0,1);
  if( flag=='0' ){
    return { prob1*cos( (this->angle)*0.5 ), prob1*cos( (this->angle)*0.5 ) };
  }
  return { -i*prob1*sin( (this->angle)*0.5 ), i*prob1*sin( (this->angle)*0.5 ) };
};
std::map<std::string, std::complex<double>> RyGate::aplicar_operador(std::map<std::string, std::complex<double>> dict_probs){
  std::map<std::string, std::complex<double>> new_probs;
  int index_accion = OneQubit::indice;

  for( auto it=dict_probs.begin(); it!=dict_probs.end(); it++ ){
    std::string estado_2 = it->first;
    estado_2[index_accion] = ( (it->first)[index_accion]=='0' ) ? '1' : '0';
    std::complex<double> p1 = it->second;
    std::complex<double> p2 = dict_probs[ estado_2 ];
    auto tuple_probs = accion( (it->first)[index_accion], p1);
    p1 = std::get<0>(tuple_probs);
    p2 = std::get<1>(tuple_probs);
      
    auto it_estado1 = new_probs.find( it->first );
    if( it_estado1 != new_probs.end() ){
      new_probs[ it->first ] = (new_probs[ it->first ]) + p1;
    }else{
      new_probs[ it->first ] = p1;
    };

    auto it_estado2 = new_probs.find( estado_2 );
    if( it_estado2 != new_probs.end() ){
      new_probs[ estado_2 ] = (new_probs[ estado_2 ]) + p2;
    }else{
      new_probs[estado_2] = p2;
    };

  };
  return new_probs;
};


RzGate::RzGate( const int indice, const double angle ): OneQubit(indice){
  (this->angle) = angle;
};
RzGate::~RzGate(){std::cout<<"Destructor RzGate"<<std::endl;};
std::tuple<std::complex<double>, std::complex<double>> RzGate::accion(const char flag, std::complex<double> prob1){
  std::complex<double> i(0,1);
  if( flag=='0' ){
    return { prob1*exp( -i*(this->angle)*0.5 ), 0.0 };
  };
  return { 0.0, prob1*exp( i*(this->angle)*0.5 )};
  //std::complex<double> valor_0 = (1.0*prob1*cos( (this->angle)*0.5 ) -i*prob2*sin( (this->angle)*0.5 ));
  //std::complex<double> valor_1 = (1.0*prob1*cos( (this->angle)*0.5 ) +i*prob2*sin( (this->angle)*0.5 ));
  //return {valor_0, valor_1};
};
std::map<std::string, std::complex<double>> RzGate::aplicar_operador(std::map<std::string, std::complex<double>> dict_probs){
  std::map<std::string, std::complex<double>> new_probs;
  int index_accion = OneQubit::indice;
  for( auto it=dict_probs.begin(); it!=dict_probs.end(); it++ ){
    std::string estado_2 = it->first;
    estado_2[index_accion] = ( (it->first)[index_accion]=='0' ) ? '1' : '0';
    std::complex<double> p1 = it->second;
    std::complex<double> p2 = dict_probs[ estado_2 ];
    auto tuple_probs = accion( (it->first)[index_accion], p1);
    p1 = std::get<0>(tuple_probs);
    p2 = std::get<1>(tuple_probs);
      
    auto it_estado1 = new_probs.find( it->first );
    if( it_estado1 != new_probs.end() ){
      new_probs[ it->first ] = (new_probs[ it->first ]) + p1;
    }else{
      new_probs[ it->first ] = p1;
    };

    auto it_estado2 = new_probs.find( estado_2 );
    if( it_estado2 != new_probs.end() ){
      new_probs[ estado_2 ] = (new_probs[ estado_2 ]) + p2;
    }else{
      new_probs[estado_2] = p2;
    };
  };

  return new_probs;
};


HGate::HGate( const int indice ): OneQubit(indice){};
HGate::~HGate(){std::cout<<"Destructor Hadamard"<<std::endl;};
std::tuple<std::complex<double>, std::complex<double>> HGate::accion(const char flag, std::complex<double> prob1){
  std::complex<double> i(0,1);
  std::complex<double> valor_0 = (1.0/sqrt(2.0))*(prob1);
  std::complex<double> valor_1 = (1.0/sqrt(2.0))*(prob1);
  return {valor_0, valor_1};
};
std::map<std::string, std::complex<double>> HGate::aplicar_operador(std::map<std::string, std::complex<double>> dict_probs){
  std::map<std::string, std::complex<double>> new_probs;
  int index_accion = OneQubit::indice;
  for( auto it=dict_probs.begin(); it!=dict_probs.end(); it++ ){
    std::string estado_2 = it->first;
    estado_2[index_accion] = ( (it->first)[index_accion]=='0' ) ? '1' : '0';
    std::complex<double> p1 = it->second;
    std::complex<double> p2 = dict_probs[ estado_2 ];
    //new_probs[ it->first ] = accion( it->first[index_accion], p1, p2);
    new_probs[ it->first ] = 0.0;//accion( it->first[index_accion], p1, p2);
  };
  return new_probs;
};



//Metodos de las clases hijas de la clase TwoQubit
CnotGate::CnotGate(const int indice1, const int indice2): TwoQubit(indice1, indice2){};
CnotGate::~CnotGate(){std::cout<<"Destructor Cnot gate"<<std::endl;};
std::string CnotGate::accion(std::string estado, std::complex<double> prob){return estado;};
std::map<std::string, std::complex<double>> CnotGate::aplicar_operador( std::map<std::string, std::complex<double>> dict_probs ){return dict_probs;};

