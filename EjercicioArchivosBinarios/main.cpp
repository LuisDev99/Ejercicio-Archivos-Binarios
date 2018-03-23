#include <fstream>
#include <iostream>

using namespace std;

struct Herramienta {

	int codigo;
	char nombre[30];
	int cantidad;
	float precio;

};


void deleteHerramienta();
void addHerramienta();
void updateHerramienta();
int getPosicion(int);
void printHerramienta();


int main() {

	int menu;

	do {
		cout << "1. Añadir herramienta\n2. Actualizar herramienta\n3. Borrar herramienta\n4. Imprimir Herramientas\n5. Salir\nIngrese lo que quiere hacer: ";
		cin >> menu;

		switch (menu)
		{
		case 1:
			addHerramienta();
			break;
		case 2:
			updateHerramienta();
			break;
		case 3:
			deleteHerramienta();
			break;
		case 4:
			printHerramienta();
			break;

		default:
			break;
		}


	} while (menu != 5);


}


void deleteHerramienta() {

	Herramienta h;

	ofstream writer("ferreteria.dat", ios::binary | ios::app);
	int code, posicion = 0;

	cout << "Ingrese el codigo de la herramienta: ";
	cin >> code;

	h.codigo = code;

	posicion = getPosicion(code);

	if (posicion == -1) {
		cout << "No se encontro ese codigo en ninguna herramienta!" << endl;
		return;
	}


	writer.seekp(0, ios::end);

	int bytesTotales = writer.tellp();

	int tam = sizeof Herramienta;

	int helper = tam * posicion;

	int	pointer = (helper != 0) ? bytesTotales / helper : 0;

	pointer *= tam;

	writer.seekp(pointer, ios::beg);

	h.cantidad = 0;
	h.precio = 0;
	h.codigo = -1;

	writer.write(reinterpret_cast<char *>(&h), sizeof Herramienta);

	cout << "Herramienta eliminada!" << endl;

	writer.close();


}

void addHerramienta() {


	Herramienta h;

	cout << "Ingrese el codigo, nombre, cantidad y precio (en orden todo, separado con espacio va): ";
	cin >> h.codigo >> h.nombre >> h.cantidad >> h.precio;

	ofstream writer("ferreteria.dat", ios::out | ios::binary | ios::app);

	writer.write(reinterpret_cast<char *>(&h), sizeof Herramienta);
	writer.close();

	cout << "Herramienta registrada!" << endl;

}

int getPosicion(int _codigo) {
	Herramienta h;
	ifstream reader("ferreteria.dat", ios::binary | ios::in);
	int posicion = 0;

	reader.read(reinterpret_cast<char *>(&h), sizeof Herramienta);

	while (!reader.eof()) {
		
		if (h.codigo == _codigo) {
			reader.close();
			return posicion;
		}
		reader.read(reinterpret_cast<char *>(&h), sizeof Herramienta);
		posicion++;
	}

	reader.close();
	return -1;
}

void updateHerramienta() {
	Herramienta h;

	ofstream writer("ferreteria.dat", ios::binary | ios::app);
	int code, posicion = 0;

	cout << "Ingrese el codigo de la herramienta: ";
	cin >> code;

	h.codigo = code;

	posicion = getPosicion(code);

	if (posicion == -1) {
		cout << "No se encontro ese codigo en ninguna herramienta!" << endl;
		return;
	}


	writer.seekp(0, ios::end);

	int bytesTotales = writer.tellp();

	int tam = sizeof Herramienta;

	int helper = tam * posicion;

    int	pointer =  (helper != 0) ? bytesTotales / helper : 0;

	pointer *= tam;

	writer.seekp(pointer, ios::beg);

	cout << "Ingrese el nuevo nombre: ";
	cin >> h.nombre;

	cout << "Ingrese la cantidad: ";
	cin >> h.cantidad;

	cout << "Ingrese el precio: ";
	cin >> h.precio;

	writer.write(reinterpret_cast<char *>(&h), sizeof Herramienta);

	cout << "Herramienta actualizada!" << endl;

	writer.close();
	
}

void printHerramienta() {

	Herramienta h;

	ifstream reader("ferreteria.dat", ios::binary | ios::in);

	reader.read(reinterpret_cast<char *>(&h), sizeof Herramienta);

	cout << "\n## IMPRIMIENDO HERRAMIENTAS DEL ARCHIVO ## \n";

	while (!reader.eof()) {
		cout << "Codigo: " << h.codigo << " Nombre: " << h.nombre << " Cantidad: " << h.cantidad << " Precio: " << h.precio << endl;
		reader.read(reinterpret_cast<char *>(&h), sizeof Herramienta);
	}

	cout << endl << endl;

	reader.close();

}