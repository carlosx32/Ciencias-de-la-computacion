#include <iostream>

//definimos las estructuras
using namespace std;

typedef struct{
	int dia;
	int mes;
	int ano;
}Fecha;

struct confederacion{
	string region;
	int puestos;
};

struct pais{
	string nombre;
	confederacion *confe;
	string puesto;
};

struct entrenadores{
	string Nombres;
	string apellidos;
	pais *nacionalidad;
	pais *selecciones_dirigidas;
};
struct jugadores{
	string nombres;
	string npellidos;
	pais *nacionalidad;
	Fecha fechadeNacimiento;
	int Estatura;
	string Club;
	string poscicion;
	int golesanotados;
	int fechasdeSancion;
};
struct estadios{
	string nombre;
	int capacidad;
	string ciudad;
};
struct programacion{
	estadios *estadio;
	pais *equipo1;
	pais *equipo2;
	Fecha fecha;
};
struct resultado{
	programacion *prog;
	int goles90min1;
	int goles90min2;
	int golsup1;
	int golsup2;
	int golpen1;
	int golpen2;
};

class mundial{
	
};


int main(){
	

}	
