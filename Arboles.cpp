#include "iostream"

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
		int eliminar();
		int profundidad(Nodo*);
		void recorridoPreorden(Nodo *);
		void recorridoInorden(Nodo *);
		void recorridoPostorden(Nodo *);
		void recorridoNiveles();
		int cantidadDeNodos();
		int cantidadDeHojas();
		Nodo* buscar(int);
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
	Nodo *p;
	if(raiz){
		if(profundidad(raiz->izq)<profundidad(raiz->der))
			raiz->izq= agregar(raiz->izq, elemento);
		else
			raiz->der= agregar(raiz->der, elemento);
	}else{
		p = new Nodo;
		raiz=p;
		raiz->elemento=elemento;
		raiz->izq=NULL;
		raiz->der=NULL;
	}
	return raiz;
}		

int ArbolBinario::eliminar(){
	
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
		recorridoPreorden(raiz->izq);
		cout<<raiz->elemento<<" ";
		recorridoPreorden(raiz->der);
	}
}
void ArbolBinario::recorridoPostorden(Nodo *raiz){
	if(raiz){
		recorridoPreorden(raiz->izq);
		recorridoPreorden(raiz->der);
		cout<<raiz->elemento<<" ";
	}
}

void ArbolBinario::recorridoNiveles(){

}

int ArbolBinario::cantidadDeNodos(){
	
}

int ArbolBinario::cantidadDeHojas(){
	
}


int main(){
	ArbolBinario arbol;
	Nodo *raiz= arbol.getRaiz();
	raiz=arbol.agregar(raiz, 30);
	arbol.setRaiz(raiz);
		
	raiz=arbol.agregar(raiz, 70);	
	raiz=arbol.agregar(raiz, 10);
	raiz=arbol.agregar(raiz, 80);
	raiz=arbol.agregar(raiz, 81);
	raiz=arbol.agregar(raiz, 84);
	raiz=arbol.agregar(raiz, 87);
		
	cout<<"Elementos en el arbol: "<<endl;
	cout<<"preorden\t";
	arbol.recorridoPreorden(raiz);
	cout<<endl<<"inorden\t";	
	arbol.recorridoInorden(raiz);
	cout<<endl<<"posorden\t";	
	arbol.recorridoPostorden(raiz);	
	
	cout<<endl<<"La raiz es: " << arbol.getRaiz()->elemento<<", la profundidad es: "<< arbol.profundidad(raiz);	
	
	return 0;
}

