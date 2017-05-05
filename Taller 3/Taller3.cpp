/*	|_______________________________________________|
	|	  Carlos David Camacho Panche 20151020034	|
	|  	  Esteban Elias Romero Jaimes 20151020048	|
	|												|
	|Universidad Distrital Francisco jose de caldas	|
*/
#include "iostream"
#include <ctype.h>
#include <stdlib.h>
#include <conio.h>
#include <stack>
#include <queue>
using namespace std;
struct Nodo{
        int elemento;
        int bal;
        Nodo* izq;
        Nodo* der;      
};
 
class ArbolBinario{
    protected:
        Nodo* raiz;
    public:
        ArbolBinario();
        Nodo *getRaiz();
        void setRaiz(Nodo*);
        void agregar(int);
        Nodo *agregar(Nodo *, int);
        Nodo *eliminar(Nodo *);
        Nodo *buscar(Nodo*,int);
        int profundidad(Nodo*);
        void recorridoPreorden(Nodo *);
        void recorridoInorden(Nodo *);
        void recorridoPostorden(Nodo *);
        void recorridoNiveles();
        int cantidadDeNodos(Nodo *);
        int cantidadDeHojas(Nodo *);
        bool isComplete();
        void recorridoInorden();
};

void ArbolBinario::recorridoInorden(){
    stack<Nodo*> pila;
    Nodo *p = raiz;
    do{
        if(!pila.empty() && p == NULL){
            cout<<pila.top()->elemento<<" ";// si la pila tiene valores y p es nulo, imprimir el elemento de la cabeza
        } 
        if(p != NULL){
            pila.push(p);//agregamos el elemento a la pila
            p = p->izq;//recorrer hasta el elemento mas a la izquierda
        }else if(!pila.empty()){
            p = pila.top()->der;
            pila.pop();
        }
    }while(!pila.empty() || p != NULL);//Mientras la pila no este vacia o p tenga algun valor
};

ArbolBinario::ArbolBinario(){
    raiz=NULL;
}
Nodo* ArbolBinario::getRaiz(){
    return raiz;
}
void ArbolBinario::setRaiz(Nodo* raiz){
    this->raiz= raiz;
}
 
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
 
Nodo *ArbolBinario::eliminar(Nodo * r){
	if (raiz==NULL)
		return NULL;
	if((r->izq==NULL)&&(r->der==NULL)){
		if(r==raiz)
			raiz=NULL;
		delete r;
		return NULL;
	}
	else if(profundidad(r->izq)>profundidad(r->der)){
		r->izq = eliminar(r->izq);
	}
	else{
		r->der = eliminar(r->der);
	}
}
 
int ArbolBinario::profundidad(Nodo* r){
    if(r){
        int profIzq = profundidad(r->izq);
        int profDer = profundidad(r->der);
        if(profIzq > profDer){
            return profIzq + 1;
        }
        return profDer + 1;
    }
    else{
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
	if(raiz){
	 	Nodo *p;
		queue<Nodo *> c;
		c.push(raiz);
		while (!c.empty() ){
			p = c.front();
			c.pop();
			cout<< p->elemento<<" ";
			if(p->izq)
				c.push(p->izq);
			if(p->der)
				c.push(p->der);	
		 }
	}else{
		cout<<"the three is void ";
	}
}
 
int ArbolBinario::cantidadDeNodos(Nodo *raiz){
    if(raiz){
        return 1 + cantidadDeNodos(raiz->izq) + cantidadDeNodos(raiz->der);
    }
    else{
        return 0;
    }
}
 
int ArbolBinario::cantidadDeHojas(Nodo *raiz){
    if(raiz){
    	if ((raiz->izq==NULL)&&(raiz->der==NULL))
        	return 1 + cantidadDeHojas(raiz->izq) + cantidadDeHojas(raiz->der);
    	else
    		return 0 + cantidadDeHojas(raiz->izq) + cantidadDeHojas(raiz->der);
    }else{
    	return 0;  
	}		
}
		

Nodo* ArbolBinario::buscar(Nodo *p, int elemento){
    if(raiz){
        if(p->elemento==elemento){
        	return raiz;
		}
        buscar(p->izq, elemento);
        buscar(p->der, elemento);
    }	
}


bool ArbolBinario::isComplete(){
	stack<Nodo *> pila;
	int nHijos;
    Nodo *aux = raiz;
     do{
        if(aux != NULL){
        	nHijos=0;
            if(aux->der){
            	nHijos=nHijos+1;
			}
			if(aux->izq){
            	nHijos=nHijos+1;
			}
			if(nHijos!=0 && nHijos!=2){
        		return false;
			}			
            pila.push(aux);
            aux = aux->izq;
        }else if(!pila.empty()){
            aux = pila.top();
            pila.pop();
            aux = aux->der;
        }
    }while(!pila.empty() || aux != NULL);
    return true;
}

 ////////ARBOL ORDENADO////////////////////////////////////

class ArbolBinarioOrdenado : public ArbolBinario{
	public:
	Nodo *agregar(int);
	Nodo *buscar(int);
	Nodo *eliminar(Nodo*, int elemento);
	Nodo *encontrarSucesor(Nodo*);
};

Nodo *ArbolBinarioOrdenado::agregar(int elemento){
	if(raiz==NULL){
		raiz = new Nodo;
		raiz->elemento=elemento;
		raiz->der=NULL;
		raiz->izq=NULL;
		return raiz;
	}
	Nodo *R=raiz;
	Nodo *S;
	while(R){
		S=R;
		if(elemento<R->elemento)
			R=R->izq;
		else
		 	R=R->der;				
	}
	R=new Nodo;	
	R->elemento=elemento;
	R->der=NULL;
	R->izq=NULL;
	if(raiz){
		if(elemento < S->elemento)
			S->izq=R;
		else
		 	S->der=R;
		return raiz;
	}		
	return R;
}	

Nodo *ArbolBinarioOrdenado::buscar(int elemento){
	Nodo *R=raiz;
	while(R){
		if(R->elemento==elemento)
			return R;
		else if(elemento<R->elemento)
			R=R->izq;
		else
		 	R=R->der;				
	}
	return NULL;
}

Nodo * ArbolBinarioOrdenado::eliminar(Nodo * r, int elemento){
	if(r == NULL) 
		return r; 
	else if(elemento < r->elemento) 
		r->izq = eliminar(r->izq,elemento);
	else if (elemento > r->elemento) 
		r->der = eliminar(r->der,elemento);
	else{
		if((r->izq==NULL)&&(r->der==NULL)){
			if(r==raiz)
				raiz=NULL;
			delete r;
			r=NULL;
		}
		else if(r->izq==NULL){
			if(r==raiz)
				raiz=r->der;
			Nodo* q = r;
			r = r->der;
			delete q;
		}
		else if(r->der==NULL){
			if(r==raiz)
				raiz=r->izq;
			Nodo* q = r;
			r = r->izq;
			delete q;
		}
		else{
			Nodo* q = encontrarSucesor(r->der);
			r->elemento = q->elemento;
			r->der = eliminar(r->der,q->elemento);
		}
	}
	return r;
}

Nodo* ArbolBinarioOrdenado::encontrarSucesor(Nodo* r){
	Nodo * sucesor=r;
	while(sucesor->izq!=NULL){
		sucesor = r->izq; 
	}
	return sucesor;
}
 ////////ARBOL AVL////////////////////////////////////
 
class ArbolBinarioAVL:public ArbolBinarioOrdenado{
	public:
		int	agregar(int);
		void rotDer(Nodo*,Nodo*);
		void rotIzq(Nodo*,Nodo*);
		void rotDobleDer(Nodo*,Nodo**);
		void rotDobleIzq(Nodo*,Nodo**);
		Nodo *eliminar(Nodo*,int);
		Nodo *balancear(Nodo*);
		void actualizarBalance(Nodo *);
		void verBalance(Nodo *);
};
void ArbolBinarioAVL::rotDer(Nodo *p,Nodo *q){
	cout << p->elemento << "  rot " << q->elemento << endl;
 	p->bal=0;
 	q->bal=0;
	p->izq = q->der;
 	q->der=p;
 	if (p==raiz)
 		raiz = q;
 }
void ArbolBinarioAVL::rotIzq(Nodo *p,Nodo *q){
 	p->bal=0;
 	q->bal=0;
 	p->der = q->izq;
 	q->izq=p;
 	if (p==raiz)
 		raiz = q;
 }
 
void ArbolBinarioAVL::rotDobleDer(Nodo *p,Nodo **q){
	cout << "rotacion Doble Derecha"<<endl;
	if(raiz==p)
		raiz=(*q)->der;
	Nodo *r;
	r=(*q)->der;
	(*q)->der = r->izq;
	r->izq = *q;
	p->izq = r->der;
	r->der = p;
	actualizarBalance(raiz);
 }
 
void ArbolBinarioAVL::rotDobleIzq(Nodo *p,Nodo **q){
	cout << "rotacion Doble Izquierda"<<endl;
	if(raiz==p)
		raiz=(*q)->der;
	Nodo *r;
	r=(*q)->izq;
	(*q)->izq = r->der;
	r->der = *q;
	p->der = r->izq;
	r->izq = p;
	actualizarBalance(raiz);
 }
 
int ArbolBinarioAVL::agregar(int elemento){
	Nodo *nuevo,*p,*q,*s,*pivote,*pp;
	int llave, altura;
	nuevo = new Nodo;
	nuevo->elemento = elemento;
	nuevo->bal=0;
	nuevo->izq=nuevo->der=NULL;
	if(raiz==NULL){
	 	raiz=nuevo;
	 	return 1;
	}
	pp=q=NULL;
	pivote=raiz;
	p=raiz;
	llave=nuevo->elemento;
	while(p!=NULL){
		if(p->bal){
			pp=q;
			pivote=p;
		}
		if(llave==p->elemento){
			delete nuevo;
			return 2;
		}else{
			q=p;
			if(llave<p->elemento){
				p=p->izq;
			}else{
				p=p->der;
			}
		}
	}
	if(llave<q->elemento){
		q->izq=nuevo;
	}else{
		q->der=nuevo;
	}
	if(llave<pivote->elemento){
		s=pivote->izq;
		altura=1;
	} else{
		s=pivote->der;
		altura=-1;
	}
	p=s;
	while(p!=nuevo)
		if(llave<p->elemento){
			p->bal=1;
			p=p->izq;
		}else{
			p->bal=-1;
			p=p->der;
		}
	if(pivote->bal==0){
		pivote->bal=altura;
	}
	else if(pivote->bal+altura==0){
		pivote->bal=0;
	}else{
		if(altura==1){
			if(s->bal==1){
				rotDer(pivote,s);

			}else{
				rotDer(pivote,s);
			}
		}

		else if(s->bal==-1){
				rotIzq(pivote,s);
			}else{
				rotIzq(pivote,s);
		}

		if(pp==NULL){
			raiz=s;

		}
		else if(pp->izq==pivote){
			pp->izq=s;

		}else{
			pp->der=s;
		}
	}
	return 1;
}

Nodo * ArbolBinarioAVL::eliminar(Nodo * r, int elemento){
	if(r == NULL) 
		return r; 
	else if(elemento < r->elemento) 
		r->izq = eliminar(r->izq,elemento);
	else if (elemento > r->elemento) 
		r->der = eliminar(r->der,elemento);
	else{
		if((r->izq==NULL)&&(r->der==NULL)){
			if(r==raiz)
				raiz=NULL;
			delete r;
			r=NULL;
		}
		else if(r->izq==NULL){
			if(r==raiz)
				raiz=r->der;
			Nodo* q = r;
			r = r->der;
			delete q;
		}
		else if(r->der==NULL){
			if(r==raiz)
				raiz=r->izq;
			Nodo* q = r;
			r = r->izq;
			delete q;
		}
		else{
			Nodo* q = encontrarSucesor(r->der);
			r->elemento = q->elemento;
			r->der = eliminar(r->der,q->elemento);
		}
	}
	return r;
}

Nodo *  ArbolBinarioAVL::balancear(Nodo * r){
	if(raiz==NULL)
		return NULL;
    if (r->izq != NULL)
        r->izq = balancear(r->izq);
    if (r->der != NULL)
        r->der = balancear(r->der);
    ///balanceo
    if(profundidad(r->izq) - profundidad(r->der) >= 2)
    {
        if(profundidad(r->izq->der) > profundidad(r->izq->izq)){
        	rotDobleDer(r,&r->izq);
		}
        else{
        	rotDer(r,r->izq);
		}
    }
    else if(profundidad(r->der) - profundidad(r->izq) >= 2)
    {
        if(profundidad(r->der->izq) > profundidad(r->der->der)){
        	rotDobleIzq(r,&r->izq);
		}
		else{
			rotIzq(r,r->der);
		}
    }
    return r;
}

void ArbolBinarioAVL::verBalance(Nodo * q){
	if(q){
		cout << "balance de : "<<q->elemento<<"  es : "<<q->bal<<endl;
		verBalance(q->izq);
		verBalance(q->der);
	}
}

void  ArbolBinarioAVL::actualizarBalance(Nodo * q){
	if(q){
		actualizarBalance(q->izq);
		actualizarBalance(q->der);
		q->bal = profundidad(q->der)-profundidad(q->izq);
	}
}
/////////////MENU/////////////////////////
class Menu{
    private:
    	ArbolBinario arbol;
    	ArbolBinarioOrdenado arbolOrdenado;
        ArbolBinarioAVL arbolAVL;
    public:
        void principalMenu();
        void binarioMenu();
        void ordenadoMenu();
        void avlMenu();
        void showMenu(ArbolBinario);
        void countMenu(ArbolBinario);
        char opciones();
};
 /////////////////OPTION MENU//////////////////////////////////
char Menu::opciones(){
	char option;
	    cout << "\t\tWelcome"<<endl<<endl;
        cout << "\tChoose an option =D"<<endl<<endl;
        cout << "\t(A)dd"<<endl;
        cout << "\t(E)liminate"<< endl;
        cout << "\t(D)epth"<<endl;
        cout << "\t(S)how"<<endl;
        cout << "\t(F)ind"<<endl;
        cout << "\t(C)ount"<<endl;
    	cout << "\tC(O)mplete Tree"<<endl;
        cout << "\t(T)erminate"<<endl<<endl;
        cout << "Option : ";
        cin >> option;
	return option;
}
 /////////////////PRINCIPAL MENU//////////////////////////////////
void Menu::principalMenu(){
 	char option;
 	do{
 		system("cls");
        cout << "\t\tWelcome"<<endl<<endl;
        cout << "\tChoose an option =D"<<endl<<endl;
        cout << "\t(B)inary Tree"<<endl;
        cout << "\t(O)rdered Tree"<< endl;
        cout << "\t(A)Vl"<<endl;
        cout << "\t(E)nd"<<endl;   
    	cout << "Option : ";
        cin >> option;
        switch (tolower(option)){
        	case 'b':{
        		system("cls");
        		binarioMenu();
				break;
			}
			case 'o':{
				ordenadoMenu();
				system("cls");
				break;
			}
			case 'a':{
				system("cls");
				avlMenu();
				break;
			}
		}
	}while(tolower(option)!='e');
 }
 //////////////////BINARY///////////////////////////////////////
void Menu::binarioMenu(){
 	Nodo *raiz= arbol.getRaiz();
    int element;
    char option;
    do{
		system("cls");
    	option = opciones();
        switch (tolower(option)){
            case 'a': {
	                system("cls");
	                cout << "Enter a new element for the tree : ";
	                cin >> element;
	                if (arbol.cantidadDeNodos(raiz)==0){
	                    raiz=arbol.agregar(raiz, element);
	                    arbol.setRaiz(raiz);
	                }
	                else{
	                    raiz=arbol.agregar(raiz, element);
	                }
	                break;
                }
                case 'e':{
                    system("cls");
                    arbol.eliminar(arbol.getRaiz());
                    cout << "Most depth element eliminated, new order : " <<endl;
                    arbol.recorridoPreorden(arbol.getRaiz());
                    cout << endl;
                    system("pause");
                    break;
                }
                case 'd':{
                    system("cls");
                    cout << "The Depth of your tree is : ";
                    cout << arbol.profundidad(raiz)<<endl;
                    system("pause");
                    break;  
                }
                case 's':{
                    system("cls");
                    showMenu(arbol);
                    system("pause");
                    break;
                }
                case 'f':{
                    system("cls");
                    cout << "Enter the elemento you're looking for : "<<endl;
                    cin >> element;
                    if(arbol.buscar(raiz,element)){
                    	cout << "The element is in the tree "<<endl;
					}
					else{
						cout << "Such element is not in the tree"<<endl;
					}
                    system("pause");
                    break;
                }
                case 'c':{
                    system("cls");
                    countMenu(arbol);
                    system("pause");
                    break;
                }
				case 'o':{
					system("cls");
                    if(arbol.isComplete()){
                    	cout << "Yes!!! it's a complete Tree"<<endl;	
					}
					else{
						cout << "No!!! it's not a complete Tree, :c   "<<endl;
					}
                    system("pause");
					break;
				}  
            }
    }while(option!='t');
 }
 ///////////////////////ORDERED/////////////////////////////////////////////
 void Menu::ordenadoMenu(){
  	Nodo *raiz= arbolOrdenado.getRaiz();
  	int element;
    char option;
    do{system("cls");
    	option = opciones();
        switch (tolower(option)){
            case 'a': {
	                system("cls");
	                cout << "Enter a new element for the ordered tree : ";
	                cin >> element;
	            	arbolOrdenado.agregar(element);
	                system("pause");
					break;
            }
            case 'e':{
                    system("cls");
                    cout << "Enter the element you want to erase : ";
	                cin >> element;
                    arbolOrdenado.eliminar(arbolOrdenado.getRaiz(),element);
                    system("pause");
                    break;
            }
            case 'd':{
                    system("cls");
                    cout << "The Depth of your tree is : ";
                    cout << arbolOrdenado.profundidad(arbolOrdenado.getRaiz())<<endl;
                    system("pause");
                    break;  
            }
            case 's':{
                    system("cls");
                    showMenu(arbolOrdenado);
                    system("pause");
                    break;
            }
            case 'f':{
                    system("cls");
                    cout << "Enter the elemento you're looking for : ";
                    cin >> element;
                    if(arbolOrdenado.buscar(element)){
                    	cout << "The element is in the tree "<<endl;
					}
					else{
						cout << "Such element is not in the tree"<<endl;
					}
                    system("pause");
                    break;
            }
            case 'c':{
                    system("cls");
                    countMenu(arbolOrdenado);
                    system("pause");
                    break;
            }
			case 'o':{
					system("cls");
                    if(arbolOrdenado.isComplete()){
                    	cout << "Yes!!! it's a complete Tree"<<endl;	
					}
					else{
						cout << "No!!! it's not a complete Tree, :c   "<<endl;
					}
                    system("pause");
			}  
            }
     
    }while(option!='t');	
 }
///////////////////////AVL
void Menu::avlMenu(){
    Nodo *raiz= arbolAVL.getRaiz();
    int element;
    char option;
    do{
    	system("cls");
    	option = opciones();
        switch (tolower(option)){
            case 'a': {
                system("cls");
                cout << "Enter a new element for the tree : ";
                cin >> element;
                	arbolAVL.agregar(element);
                break;
                }
                case 'e':{
                    system("cls");
                	cout << "Enter the element to be erased : ";
                	cin >> element;
                    cout << "updating balance :v ...."<<endl;
                    arbolAVL.actualizarBalance(arbolAVL.getRaiz());
                    arbolAVL.eliminar(arbolAVL.getRaiz(),element);
                    arbolAVL.balancear(arbolAVL.getRaiz());
                    arbolAVL.actualizarBalance(arbolAVL.getRaiz());
                    arbolAVL.verBalance(arbolAVL.getRaiz());
                    cout <<endl<< "the element was erased and the tree is balanced ...."<<endl;
                    system("pause");
                    break;
                }
                case 'd':{
                    system("cls");
                    cout << "The Depth of your tree is : ";
                    cout << arbolAVL.profundidad(arbolAVL.getRaiz())<<endl;
                    system("pause");
                    break;  
                }
                case 's':{
                    system("cls");
                    showMenu(arbolAVL);
                    system("pause");
                    break;
                }
                case 'f':{
                    system("cls");
                    cout << "Enter the element you're looking for': ";
                	cin >> element;
                    if(arbolAVL.buscar(element))
						cout << "Elemento Encontrado"<<endl;
					else
						cout << "No Encontrado"<<endl;
                    system("pause");
                    break;
                }
                case 'c':{
                    system("cls");
                    countMenu(arbolAVL);
                    system("pause");
                    break;
                }
				case 'o':{
					system("cls");
                    if(arbolAVL.isComplete()){
                    	cout << "Yes!!! it's a complete Tree"<<endl;	
					}
					else{
						cout << "No!!! it's not a complete Tree, :c   "<<endl;
					}
                    system("pause");
				} 
            }
     
    }while(option!='t');
}
///////////////////SHOW
void Menu::showMenu(ArbolBinario arbol){
    char option;
    cout << "Welcome to the show Menu"<<endl<<endl;
    cout << "\t\tChoose an option =D"<<endl<<endl;
    cout << "\t(P)reOrden"<<endl;
    cout << "\t(I)norden"<< endl;
    cout << "\t(O)PostOrden"<<endl;
    cout << "\t(L)evels"<<endl;
    cout << "\tT(t)erative Inorden"<<endl;
    cout << "Option : ";
    cin >>  option;
    switch (tolower(option)){
        case 'p':{
            arbol.recorridoPreorden(arbol.getRaiz());
            break;
        }
        case 'i':{
            arbol.recorridoInorden(arbol.getRaiz());
            break;
        }
        case 'o':{
            arbol.recorridoPostorden(arbol.getRaiz());
            break;
        }
		case 'l':{
            arbol.recorridoNiveles();
            break;
        }
		case 't':{
			arbol.recorridoInorden();
			break;
		}
		       
    }
    cout <<endl;   
}
////////////////COUNT
void Menu::countMenu(ArbolBinario arbol){
	char option;
    cout << "\t\tWelcome to the show Menu"<<endl;
    cout << "\tChoose an option =D"<<endl<<endl;
    cout << "\t(N)odes"<<endl;
    cout << "\t(L)eaves"<< endl;
    cout << "Option : ";
    cin >>  option;
    switch (tolower(option)){
        case 'n':{
            cout << "The number of nodes in the tree is : "<<arbol.cantidadDeNodos(arbol.getRaiz())<<endl;
            break;
        }
        case 'l':{
             cout << "The number of leaves in the tree is : "<<arbol.cantidadDeHojas(arbol.getRaiz())<<endl;
            break;
        }    
    }
    cout <<endl;   
}
int main(){
    Menu arbolMenu;
    arbolMenu.principalMenu();
    return 0;
}

