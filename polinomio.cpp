/*
		carlos David Camacho panche	20151020034
		Esteban elias Romero			20151020048
		Universidad Distrital francisco jose de caldas
		Hace falta una funcioon que nos simplifique el polinomio
*/
#include<iostream>
#include <math.h>
using namespace std;

struct Nodo{
  int expo;
  float coef;
  Nodo *sig;
};

class Polinomio{
  int grado;
  Nodo *cab;
  void ordenar();
  void agregar(int,float);
  public:
  	 Polinomio();
	 Polinomio(int);
	 void cargar();
	 void mostrar();
	 void dividir(float);
	 void derivar();
	 void integrar();
	 float evaluar(float);
	 void simplificar();
	 Polinomio operator+(Polinomio);
};
Polinomio::Polinomio(){
	this->grado=0;					 
    cab=NULL;
}

Polinomio Polinomio::operator+(Polinomio pol){
	int n;
	Nodo *p;
	Nodo *q;	
	if((this->grado) < (pol.grado)){
		n=pol.grado;
		p=pol.cab;
		q=this->cab;
	}else{
		n=this->grado;
		p=this->cab;
		q=pol.cab;
	}
	Polinomio pol3(n);
	
	
	while(p!=NULL){   //while(p)
		pol3.agregar(p->expo,p->coef);
	   p=p->sig;
    }
    
	while(q!=NULL){   //while(p)
		pol3.agregar(q->expo,q->coef);
	   q=q->sig;
    } 
    pol3.ordenar();
	//pol3.simplificar():
	return pol3;
}


Polinomio::Polinomio(int grado){
	this->grado=grado;					 
    cab=NULL;
}

void Polinomio::cargar(){
	 int expo;
	 float coef;
	 cout<<"exponente(para terminar -1): ";
	 cin>>expo;
	 while(expo!=-1){
	     cout<<"Coeficiente: ";
	     cin>>coef;
	     agregar(expo,coef);
	     cout<<"exponente(para terminar -1): ";
	     cin>>expo;
	 }
	 ordenar();   
}
void Polinomio::agregar(int expo,float coef){
	 Nodo *p=new Nodo;
	 (*p).expo=expo;
	 (*p).coef=coef;   
	 (*p).sig=cab;
	 cab=p;
}
void Polinomio::mostrar(){
	 Nodo *p=cab;
	 while(p!=NULL){   //while(p)
	   cout<<p->coef<<"X^"<<p->expo<<"+";
	   p=p->sig;
     }
}
void Polinomio::ordenar(){
	  Nodo *p,*q;
	  int auxExpo;
	  float auxCoef;
   p=cab;
   while(p->sig){
   	  q=p->sig;
	  while(q){
	     if(p->expo<q->expo	){
		 	auxExpo=p->expo;
			p->expo=q->expo;
			q->expo=auxExpo;
			auxCoef=p->coef;
			p->coef=q->coef;
			q->coef=auxCoef;
			}
		q=q->sig;
		}
	p=p->sig;						 
   }
}
void Polinomio::derivar(){
	 Nodo *p=cab;
	 while(p!=NULL){
	   cout<<(p->coef*p->expo)<<"X^"<<(p->expo-1)<<"+";
	   p=p->sig;
     }
}

void Polinomio::integrar(){
	 Nodo *p=cab;
	 while(p!=NULL){ 
	   cout<<(p->coef/(p->expo+1))<<"X^"<<(p->expo+1)<<"+";
	   p=p->sig;
     }
     cout<<"c"<<endl;
}
float Polinomio::evaluar(float x){
	float valor=0;
	Nodo *p=cab;
	while(p!=NULL){ 
		valor= valor + p->coef*pow(x,p->expo);
		p=p->sig;
    	
	}
	return valor;
}
void Polinomio::dividir(float a){
	cout<<"Metodo aun no implementado "<<endl;
	mostrar();
	cout<<"/(x-"<<a<<")"<<endl;
}



char menu(){
  char opcion;
  cout<<"\n   MENU\n";
  cout<<"(C)argar\n";
  cout<<"(M)ostrar\n";
  cout<<"(D)erivar\n";
  cout<<"(I)ntegrar\n";
  cout<<"(E)valuar\n";
  cout<<"(S)umar\n";
  cout<<"(R)dividir\n";
  cout<<"(T)erminar\n";
  cout<<"Escoja una opcion: ";
  cin>> opcion;
  return opcion;
}	 
int main(){
	int n,elemento;
	char opcion;
	cout<<"De que grado es el polinomio? ";
	cin>>n;
	Polinomio polinomio(n);
	do{
	   opcion=menu();
	   switch (opcion){
		case 'c':
			case 'C':	cout<<"Ingrese el polinomio: \n";
		        polinomio.cargar();
		        break;
    	case 'm':
			case 'M':	cout<<"El polinomio almacenado: \n";
		            polinomio.mostrar();
		            cout<<endl;
		            break;
		case 'D':
		case 'd':
					cout<<"El polinomio Derivado: \n";
					polinomio.derivar();
					break;
		case 'i':
		case 'I':
					cout<<"El polinomio Integrado: \n";
		 			polinomio.integrar();
		 			break;
		case 'E':
		case 'e':
					cout<<"Ingrese el valor de X a evaluar: \n";
		 			float valx;
					cin>>valx;
		 			cout<<"El valor del polinomio en x="<<valx<<"es: "<<polinomio.evaluar(valx);
		 			break;
		case 'r':
		case 'R':
				cout<<"Dividiremos el polinomio entre x-a, ingrese el valor de a: ";
				float a;
				cin>>a;
				polinomio.dividir(a);
				break;
		case 'S':
		case 's':
				cout<<"De que grado es el nuevo polinomio? ";
				cin>>n;
				Polinomio polinomio2(n);
				cout<<"Ingrese el nuevo polinomio: \n";
				polinomio2.cargar();
				//realizamos la suma
				Polinomio polinomio3;
				polinomio3=polinomio+polinomio2;
				cout<<"La suma de los polinomios es:\n";
				polinomio3.mostrar();
				cout<<endl;
				break;
		}
   }while(opcion!='t' && opcion!='T');
	system("pause");
	return 1;
}
