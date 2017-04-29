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
        int eliminar();
        Nodo *buscar(Nodo*,int);
        int profundidad(Nodo*);
        void recorridoPreorden(Nodo *);
        void recorridoInorden(Nodo *);
        void recorridoPostorden(Nodo *);
        void recorridoNiveles();
        int cantidadDeNodos(Nodo *);
        int cantidadDeHojas(Nodo *);
        Nodo* buscar(int);
        bool isComplete();
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
    }  
}

Nodo* ArbolBinario::buscar(int elemento){
    if(raiz){
        if(raiz->elemento==elemento){
        	return raiz;
		}
        recorridoPreorden(raiz->izq);
        recorridoPreorden(raiz->der);
    }	
}

 ////////ARBOL ORDENADO////////////////////////////////////

class ArbolBinarioOrdenado : public ArbolBinario{
	public:
	Nodo *agregar(int);
	Nodo *buscar(int);
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



 ////////ARBOL AVL////////////////////////////////////
 
 
class ArbolBinarioAVL:public ArbolBinarioOrdenado{
	public:
		int	agregar(int);
		void rotDer(Nodo*,Nodo*);
		void rotIzq(Nodo*,Nodo*);
		void rotDobleDer(Nodo*,Nodo*);
};
 
void ArbolBinarioAVL::rotDer(Nodo *p,Nodo *q){
 	p->bal=0;
 	q->bal=0;
 	p->izq = q->der;
 	q->der=p;
 }
 
void ArbolBinarioAVL::rotIzq(Nodo *p,Nodo *q){
 	p->bal=0;
 	q->bal=0;
 	p->der = p->izq;
 	q->izq=p;
 }
 
void ArbolBinarioAVL::rotDobleDer(Nodo *p,Nodo *q){
	Nodo *r;
	r=q->der;
	q->der = r->der;
	r->izq = q;
	p->izq = r->der;
	r->der = p;
	switch(r->bal){
		case -1:
		{
			(q)->bal=1;
			p->bal=0;	
			break;
		}
		case 0:
		{
			(q)->bal=p->bal=0;	
			break;
		}
		case 1:
		{
			(q)->bal=0;
			p->bal=-1;	
			break;
		}
	}
 }
 
 
 
int ArbolBinarioAVL::agregar(int elemento){
	Nodo *nuevo,*p,*q,*s,*pivote,*pp;
	int llave, altura;
	nuevo = new Nodo;
	nuevo->elemento = elemento;
	nuevo->bal=0;
	nuevo->izq=nuevo->der=NULL;
	if(raiz==NULL){
		raiz = nuevo;
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
};
 
 
 
 
 
 /////////////////PRINCIPAL MENU//////////////////////////////////
void Menu::principalMenu(){
 	char option;
 	do{
 		system("cls");
        cout << "Welcome"<<endl<<endl;
        cout << "Choose an option =D"<<endl<<endl;
        cout << "(B)inary Tree"<<endl;
        cout << "(O)rdered Tree"<< endl;
        cout << "(A)Vl"<<endl;
        cout << "(E)nd"<<endl;   
    	cout << "Option : ";
        cin >> option;
        switch (tolower(option)){
        	case 'b':{
        		binarioMenu();
				break;
			}
			case 'o':{
				ordenadoMenu();
				break;
			}
			case 'a':{
				avlMenu();
				break;
			}
	}
	 }while(tolower(option)!='e');
 }
 
 
 
 
 //////////////////BINARY///////////////////////////////////////
void Menu::binarioMenu(){
 	Nodo *raiz= arbol.getRaiz();
    char option;
    int element;
    do{
        system("cls");
        cout << "Welcome"<<endl<<endl;
        cout << "Choose an option =D"<<endl<<endl;
        cout << "(A)dd"<<endl;
        cout << "(E)liminate"<< endl;
        cout << "(D)epth"<<endl;
        cout << "(S)how"<<endl;
        cout << "(F)ind"<<endl;
        cout << "(C)ount"<<endl;
    	cout << "C(O)mplete Tree"<<endl;
        cout << "(T)erminate"<<endl<<endl;
        cout << "Option : ";
        cin >> option;
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
                    cout << "Enter the elemento you're looking for : ";
                    cin >> element;
                    if(arbol.buscar(element)){
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
                    	cout<<"el arbol es completo";
					}else{
						cout<<"el arbol no es completo";
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
    char option;
    int element;
    do{
        system("cls");
        cout << "Welcome"<<endl<<endl;
        cout << "Choose an option =D"<<endl<<endl;
        cout << "(A)dd"<<endl;
        cout << "(E)liminate"<< endl;
        cout << "(D)epth"<<endl;
        cout << "(S)how"<<endl;
        cout << "(F)ind"<<endl;
        cout << "(C)ount"<<endl;
    	cout << "C(O)mplete Tree"<<endl;
        cout << "(T)erminate"<<endl<<endl;
        cout << "Option : ";
        cin >> option;
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
                    cout << " not yet"<<endl;
                    system("pause");
					break;
			}  
            }
     
    }while(option!='t');	
 }















///////////////////////AVL
void Menu::avlMenu(){
    Nodo *raiz= arbolAVL.getRaiz();
    char option;
    int element;
    do{
        system("cls");
        cout << "Welcome"<<endl<<endl;
        cout << "Choose an option =D"<<endl<<endl;
        cout << "(A)dd"<<endl;
        cout << "(E)liminate"<< endl;
        cout << "(S)how"<<endl;
        cout << "(F)ind"<<endl;
        cout << "(C)ount"<<endl;
        cout << "(D)epth"<<endl;
        cout << "C(O)mplete Tree"<<endl;
        cout << "(T)erminate"<<endl<<endl;
        cout << "Option : ";
        cin >> option;
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
                    cout << " not yet"<<endl;
                    system("pause");
					break;
				} 
            }
     
    }while(option!='t');
}



///////////////////SHOW
void Menu::showMenu(ArbolBinario arbol){
    char option;
    cout << "Welcome to the show Menu"<<endl<<endl;
    cout << "Choose an option =D"<<endl<<endl;
    cout << "(P)reOrden"<<endl;
    cout << "(I)norden"<< endl;
    cout << "(O)PostOrden"<<endl;
    cout << "(L)evels"<<endl;
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
		   
    }
    cout <<endl;   
}



////////////////COUNT
void Menu::countMenu(ArbolBinario arbol){
	char option;
    cout << "Welcome to the show Menu"<<endl<<endl;
    cout << "Choose an option =D"<<endl<<endl;
    cout << "(N)odes"<<endl;
    cout << "(L)eaves"<< endl;
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
