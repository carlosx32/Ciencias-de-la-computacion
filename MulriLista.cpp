#include<iostream>
using namespace std;

struct Nodo{
	float valor;
	int fila, columna;
	Nodo *SigFila,*SigColumna;
};
struct NodoLinea{
	int noLinea;
	Nodo *cabezaLinea;
	NodoLinea *sigLinea;
};
class Matriz{
	private:
		NodoLinea *cabezaFila;
		NodoLinea *cabezaColumna;
		int filas,columnas;
	public:
		Matriz(int, int);
		Matriz();
		void agregarxFila(int, Nodo);
		void agregarxColumna(int, Nodo);
		void cargar();
		void mostrar();
		Matriz operator=(Matriz);
		Matriz operator+(Matriz);
		Matriz operator*(Matriz);
};

void Matriz::agregarxColumna(int noColumna, Nodo q){

}
void Matriz::agregarxFila(int noFila, Nodo q){

}


void Matriz::cargar(){
	
//	cin>>elemento;
}

void Matriz::mostrar(){
	int i=1,j=1;
	NodoLinea *p;
	Nodo *q;
	p= cabezaFila;
	while(i<=this->filas){
		if( p->noLinea==i)
			q=p->cabezaLinea;
		j=1;
		while(q->SigColumna!=NULL){
			if(j==q->columna){
				//cout<<"Elemento en "<<i<<","<<j<<": "<< cabezaColumna->cabezaLinea->valor;	
				cout<<q->valor<<"  ";
				q=q->SigColumna;
			}
			else{
				cout<<"0  ";				//cout<<"Elemento en "<<cabezaFila->noLinea<<","<<cabezaColumna->noLinea<<": 0";	
			}
			j++;
		}
		while(j<=columnas){
			cout<<"0  ";
			j++;
		}
		p=p->sigLinea;
		cout<<endl;
		i++;
	}
	while(i<=filas){
			cout<<"0  ";
		j=1;	
		while(j<=columnas){
			cout<<"0  ";
			j++;
		}
	}	
}

Matriz::Matriz(int filas, int columnas){
	this->filas=filas;
	this->columnas=columnas;
	this->cabezaColumna=NULL;
	this->cabezaFila=NULL;
	cout<<"creado"<<filas<<columnas;
};

Matriz::Matriz(){
	this->cabezaColumna=this->cabezaFila=NULL;
};

int main(){
	int i, j;
	cin>>i;
	cin>>j;
	Matriz a(int i, int j);
	
	//a.mostrar();
}



