#include <iostream>
#include <queue>

using namespace std;
 
struct Nodo{
		int elemento;
		Nodo* izq;
		Nodo* der;		
};

class ArbolBinario{
	private:
		Nodo* raiz;
	public:
		ArbolBinario();
		Nodo *getRaiz();
		void setRaiz(Nodo*);
		void agregar(int);
		Nodo *agregar(Nodo *, int);
		int profundidad(Nodo*);
		void recorridoPreorden(Nodo *);
		void recorridoInorden(Nodo *);
		void recorridoPostorden(Nodo *);
		void recorridoNiveles();
		int cantidadDeNodos(Nodo *);
		int cantidadDeHojas(Nodo *);
		Nodo* buscar(Nodo*, int);
		int eliminar(Nodo*);
};

ArbolBinario::ArbolBinario(){
	raiz=NULL;
};
Nodo *ArbolBinario::getRaiz(){
	return raiz;
};
void ArbolBinario::setRaiz(Nodo* raiz){
	this->raiz= raiz;
};

Nodo *ArbolBinario::agregar(Nodo* raiz, int elemento){//se agregara un elemento al sub arbol menos profundo
	//Nodo *p;
	if(raiz){
		if(profundidad(raiz->izq)<profundidad(raiz->der))
			raiz->izq= agregar(raiz->izq, elemento);
		else
			raiz->der= agregar(raiz->der, elemento);
	}else{
		//p = new Nodo;
		raiz=new Nodo;
		raiz->elemento=elemento;
		raiz->izq=NULL;
		raiz->der=NULL;
	}
	return raiz;
}		


int ArbolBinario::profundidad(Nodo* raiz){
	int profIzq, profDer;
	if(raiz){
		profIzq = profundidad(raiz->izq);
		profDer = profundidad(raiz->der);
		if(profIzq > profDer){
			return profIzq + 1;
		}
		return profDer + 1;
	}
	if(raiz==NULL){
		return 0;
	}
}
void ArbolBinario::recorridoPreorden(Nodo *raiz){
	if(raiz){
		cout<<raiz->elemento<<" ";
		recorridoPreorden(raiz->izq);
		recorridoPreorden(raiz->der);
	}
}
void ArbolBinario::recorridoInorden(Nodo *raiz){
	if(raiz){
		recorridoInorden(raiz->izq);
		cout<<raiz->elemento<<" ";
		recorridoInorden(raiz->der);
	}
}
void ArbolBinario::recorridoPostorden(Nodo *raiz){
	if(raiz){
		recorridoPostorden(raiz->izq);
		recorridoPostorden(raiz->der);
		cout<<raiz->elemento<<" ";
	}
}

void ArbolBinario::recorridoNiveles(){
	Nodo *p;
	cout<<"Metodo aun no implementado";
	queue<Nodo *> c;
	c.push(raiz);
	while (!c.empty() ){
		p = c.front();
		c.pop();
		cout<< p->elemento<<" ";
		c.push(raiz->izq);
		c.push(raiz->der);
	 }
	  
	//ciclo (cola no vacia)
	//eliminamos
	//mostrar elemento
	//agregar izq
	//agregar der
}

int ArbolBinario::cantidadDeNodos( Nodo *raiz){
	int nizq, nder;
	if(raiz){
		nizq = cantidadDeNodos(raiz->izq);
		nder = cantidadDeNodos(raiz->der);
		return nizq+nder+1;
	}
	if(raiz==NULL){
			return 0;
	}			
}

int ArbolBinario::cantidadDeHojas(Nodo *raiz){
	
}
Nodo *ArbolBinario::buscar(Nodo *raiz , int elemento ){
	if (raiz){
		if(raiz->elemento!=elemento){
			//cout<<raiz->elemento<<" ";
			buscar(raiz->izq, elemento);
			buscar(raiz->der, elemento);
		}else{
			return raiz;
		}	
	}
	else{
		return NULL;
	}
}


int ArbolBinario::eliminar(Nodo* q){
	int elementoeliminado= q->elemento;
	
	return elementoeliminado;			
}
char menu(){
	char t;
	cout<<endl<<"Menu: ";
	cout<<"\t(A)gregar"<<endl;
	cout<<"\t(E)liminar"<<endl;
	cout<<"\t(P)rofundidad"<<endl;
	cout<<"\t(M)ostrar"<<endl;
	cout<<"\t(B)uscar"<<endl;
	cout<<"\t(C)ontar nodos"<<endl;
	cout<<"\tcontar (H)ojas"<<endl;
	cout<<"\t(T)erminar"<<endl;
	cin>>t;
	return t;
}

int main(){
		
	ArbolBinario arbol;
	Nodo *raiz= arbol.getRaiz();
	Nodo *encontrado;
	int elemento;
	
	char opcion;
	do{		
		opcion=menu();	
		switch (opcion){
			case 'a':
			case 'A':
				cout<<"Porfavor, inserté un elemento"<<endl;
				cin>>elemento;
				raiz=arbol.agregar(raiz,elemento);
				if(!raiz){
					arbol.setRaiz(raiz);		
				}
				break;
			case 'E':
				cout<<"El elemento eliminado es:"<<arbol.eliminar(raiz);			
				break;
			case 'p':
			case 'P':
				cout<<"la profundidad es: "<< arbol.profundidad(raiz);
				break;
			case 'M':
			case 'm':
				cout<<"Elementos en el arbol: "<<endl;
				cout<<"preorden\t";
				arbol.recorridoPreorden(raiz);
				cout<<endl<<"inorden\t\t";
				arbol.recorridoInorden(raiz);
				cout<<endl<<"posorden\t";	
				arbol.recorridoPostorden(raiz);					
				cout<<endl<<"posorden\t";	
				arbol.recorridoNiveles();
				break;
			case 'B':
			case 'b':
				cout<<"Porfavor, inserté un elemento para buscarlo"<<endl;
				cin>>elemento;
				encontrado=arbol.buscar(raiz,elemento);
				if(encontrado){
					cout<<"el elemento se encuentra en el arbol: referencia: "<<encontrado;
				}else{
					cout<<"el elemento no se encuentra en el arbol";	
				}
				break;
			case 'c':
			case 'C':
				cout<<"El numero de nodos es: "<<arbol.cantidadDeNodos( raiz );
				break;
			case 'H':
			case 'h':
				cout<<"El numero de hojas es: "<<arbol.cantidadDeHojas(raiz);
				break;
		}
			
	}while(opcion!='t' && opcion!='T');
		
	//cout<<endl<<"La raiz es: " << arbol.getRaiz()->elemento<<", la profundidad es: "<< arbol.profundidad(raiz);
	
	return 0;
}
