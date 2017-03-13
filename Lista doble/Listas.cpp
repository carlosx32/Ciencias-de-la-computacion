#include<iostream>
using namespace std;

struct Nodo{
	int elemento;
	Nodo *sig;
	Nodo *ant;
};
class ListaDobleDinamica{
	private:
	Nodo *cabeza;
	Nodo *fin;
	//Métodos:
	public:
	ListaDobleDinamica();
	void mostrar();//	
	void agregar(int);
	void agregarizq(int, int);
	void agregarder(int, int);
	int eliminar();
	int eliminar(int);
	int eliminar(Nodo *p);
	Nodo *buscar(int);
	void ordenar();
	bool vacia();
};
ListaDobleDinamica::ListaDobleDinamica(){
	this->cabeza=NULL;
	this->fin=NULL;
}
void ListaDobleDinamica::mostrar(){
	Nodo *p= this->cabeza;
	while(p){
		cout<<p->elemento<<" ";//<<" mem:"<< p<<"ant"<<p->ant <<endl;
		p=p->sig;
	}	
};
void ListaDobleDinamica::agregar(int elemento){
	Nodo *p= new Nodo;
	p->elemento=elemento;
	p->sig=cabeza;
	p->ant=NULL;
	if(cabeza)
		cabeza->ant=p;		
	else
		fin=p;
	cabeza=p;
}

Nodo *ListaDobleDinamica::buscar(int elemento){
	Nodo *p=cabeza;
	while(p){
		if(p->elemento==elemento)
			return p;
		else
			p=p->sig;
	}
	return NULL;
} 
int ListaDobleDinamica::eliminar(){
	Nodo *p=fin;
	int elementoe=p->elemento;
	
	if(cabeza==p)
		cabeza=NULL;
	else
		p->ant->sig=p->sig;
	fin=p->ant;
	delete p;
	return elementoe;
};

bool ListaDobleDinamica::vacia(){
	return cabeza==NULL;
};

int ListaDobleDinamica::eliminar(Nodo *p){
	int elementoe=p->elemento;
	
	if(cabeza==p)
		cabeza=p->sig;
	else
		p->ant->sig=p->sig;
	fin=p->ant;
	delete p;
	return elementoe;
};

int ListaDobleDinamica::eliminar(int elemento){
	
	Nodo *p=this->buscar(elemento);
	int elementom=p->elemento;
	if (p){
		p->ant->sig=p->sig;
		p->sig->ant=p->ant;
	}
	delete p;
	return elementom;
};

char menu(){
	char opcion;
	cout<<"\n MENU \n";
	cout<<"(A)gregar\n";
	cout<<"(E)liminar\n";
	cout<<"(M)ostrar\n";
	cout<<"(B)uscar\n";
	cout<<"(O)rdenar\n";
	cout<<"(S)alir\n";
	cout<<"Escoja una opcion: ";
	cin>>opcion;
	return opcion;
}

char menuEliminar(){
	char opcion;
	cout<<"\n MENU ELIMINAR\n";
	cout <<"(U)ltimo"<<endl;
	cout<<"(E)lemento"<<endl;
	cout<<"(R)egresar"<<endl;
	cout<<"Escoja una opcion";
	cin>>opcion;
	return opcion;
}

void atenderEliminar(ListaDobleDinamica &lista){
	int elemento;
	char opcion;
	do{	
	opcion = menuEliminar();
	switch(opcion){
		case 'u':
		case 'U':if(lista.vacia()){
					cout<<"No hay elementos para eliminar"<<endl;	
				}else{
					elemento= lista.eliminar();
					cout<<"Se ha eliminado: "<<elemento<<endl;
				}
		break;
		case 'e':
		case 'E': if(lista.vacia()){
				cout<<"No hay elementos para eliminar"<<endl;	
				}else{
					cout<<"Digite el Elemento a Eliminar: ";
					cin>>elemento;
					lista.eliminar(elemento);
					cout<<"Se ha eliminado: "<<elemento<<endl;
				}
			break;
		}
	}while(opcion!='R'&&opcion!='r');
}

int main(){
	ListaDobleDinamica lista;
	char opcion;
	int elemento;
	do{opcion=menu();
		switch(opcion){
			case 'a':
			case 'A':	
					cout<<"Digite el elemento: ";
					cin>>elemento;
					lista.agregar(elemento);
					break;
			case 'm':
			case 'M':
					cout<<"\nLos elementos almacenados:\n";
					lista.mostrar();
					break;
			case 'b':
			case 'B':
					cout<<lista.buscar(44);
					break;
			case 'e':
			case 'E':
				atenderEliminar(lista);
			/*case 'o':
			case 'O'*/
		}
	}while(opcion!='s'&&opcion!='S');
}
