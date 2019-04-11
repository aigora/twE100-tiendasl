/*

ESTE PROGRAMA SIMULA UN CONCESIONARIO EN EL QUE SE PUEDEN
REGISTRAR A DISTINTOS CLIENTES, CREAR DISTINTOS PRODUCTOS
Y QUE ESTOS CLIENTES COMPREN DICHOS PRODUCTOS, CUANDO UN 
PRODUCTO SE COMPRA SE ELIMINA. EL REGISTRO DE CLIENTES CON
SU RESPECTIVA INFORMACION SE ALMACENA EN FICHEROS LOS CUALES
SE ACTUALIZAN CADA VEZ QUE SE REALIZA UNA COMPRA.

EL TIPO DE DATO "DESCUENTO" Y SUS FUNCIONES NO SE UTILIZAN
pero se dejan implementadas por si en un futuro fueran 
necesarias. 

*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/********** enumeración tipos de vehiculos ************/
typedef enum{
  MOTO = 1,
  GASOLINA = 2,
  DIESEL = 3,
  HIBRIDO = 4
} TipoVehiculo; 

/********** enumeración tipos de descuentos ************/
typedef enum{
  GASTO,
  ECO,
  FIDELIDAD,
  ESPECIAL
} TipoDescuento; 


/************************ Declaración de estructuras *************************/
struct _Producto {
  char* nombre; /* nombre del producto*/
  float precio; /* precio del vehiculo */
  TipoVehiculo tipo; /* tipo de vehiculo */
};

typedef struct _Producto Producto;

struct _Cliente {
  char * nombre; /* nombre del cliente */
  double gasto; /* gasto total realizado por el cliente*/
  int fidelidad; /* años que lleva el cliente registrado*/
};

typedef struct _Cliente Cliente;

struct _Descuento {
  TipoDescuento tipo; /* tipo de descuento*/
  float rebaja; /* porcentaje de rebaja sobre un precio*/
};

typedef struct _Descuento Descuento;

struct _Tienda {
	Cliente ** clientes; /* array de clientes */
	Producto ** productos; /* productos disponibles */
	Descuento ** descuentos; /* descuentos existentes */
	int nClientes; /* numero de clientes */
	int nProductos; /* numero de productos*/
	int nDescuentos; /* numero de descuentos*/
	FILE ** fClientes; /* ficheros de clientes */
};

typedef struct _Tienda Tienda;



/************************ Declaración de funciones ***************************/

/* funciones de producto */
Producto * crearProducto();
void borrarProducto(Producto* p);
Producto* setNombreProducto(Producto* p, char* n);
char* getNombreProducto(Producto* p);
Producto* setPrecioProducto(Producto* p, float pre);
float getPrecioProducto(Producto* p);
Producto* setTipoProducto(Producto* p, TipoVehiculo t);
TipoVehiculo getTipoProducto(Producto* p);

/* funciones de cliente */
Cliente * crearCliente();
void borrarCliente (Cliente * c);
Cliente * setNombreCliente(Cliente* c, char* n);
char * getNombreCliente(Cliente* c);
Cliente * setGastoCliente(Cliente * c, double g);
double getGastoCliente(Cliente * c);
Cliente * setFidelidadCliente(Cliente * c, int f);
int getFidelidadCliente(Cliente * c);

/* funciones de descuento */
Descuento * crearDescuento(TipoDescuento t, float r);
void borrarDescuento (Descuento * c);
TipoDescuento getTipo(Descuento* d);
float getRebaja(Descuento* d);
/* funciones de tienda */

/*************************** IMPLEMENTACIÓN DE FUNCIONES *********************/

/* FUNCIONES DE DESCUENTOS */

Descuento * crearDescuento(TipoDescuento t, float r){
	Descuento* d = NULL;
	d = (Descuento*) malloc (sizeof(Descuento));
	if (d == NULL) {
		return NULL;
	}
	
	d->tipo = t;
	d->rebaja = r;
	return d;   
}

void borrarDescuento(Descuento* d){
	if (d == NULL) {
		return;
	}
	free(d);
}

TipoDescuento getTipo(Descuento* d){
	if (d == NULL){
		return -1;
	}
	return d->tipo;
}

float getRebaja(Descuento* d){
	if(d == NULL){
		return -1;
	}
	return d->rebaja;
}

/* FUNCIONES RELACIONADAS CON EL CLIENTE */

Cliente * crearCliente() {
	Cliente * c = NULL; 
	c = (Cliente*) malloc (sizeof (Cliente));
	if (c == NULL) {
		return NULL;
	}
	c->gasto = 0;
	c->fidelidad = 0;
	c->nombre = NULL;
	return c;   
}

void borrarCliente (Cliente * c){
	if (c == NULL) {
		return;
	}
	if (c->nombre != NULL) {
		free(c->nombre);
	}
	free(c);
}

Cliente * setNombreCliente(Cliente* c, char* n){
	if ((c == NULL) || (n == NULL)) {
		return NULL;
	}
	
	if  (c->nombre != NULL) {
		free(c->nombre);
	}
	
	c->nombre = (char*) malloc (sizeof(char) * (strlen(n) + 1));
	if (c->nombre == NULL) {
		return NULL;
	}
	strcpy(c->nombre, n);
	return c;
}

char * getNombreCliente(Cliente* c){
	if (c == NULL) {
		return NULL;
	}
	
	if  (c->nombre == NULL) {
		return NULL;
	}
	
	return c->nombre;
}

Cliente * setGastoCliente(Cliente * c, double g){
	if (c == NULL) {
		return NULL;
	}
	
	c->gasto = g;
	return c;
}

double getGastoCliente(Cliente * c){
	if (c == NULL) {
		return -1;
	}
	
	return c->gasto;
}

Cliente * setFidelidadCliente(Cliente * c, int f){
	if (c == NULL) {
		return NULL;
	}
	
	c->fidelidad = f;
	return c;
}

int getFidelidadCliente(Cliente * c){
	if (c == NULL) {
		return -1;
	}
	
	return c->fidelidad;
}



/* FUNCIONES RELACIONADAS CON EL PRODUCTO */

Producto * crearProducto() {
	Producto * p = NULL;
	p = (Producto*) malloc (sizeof (Producto));
	if (p == NULL) {
		return NULL;
	}
	p->nombre = NULL;
	p->precio = 0.0;
	p->tipo = -1;
	return p;   
}

void borrarProducto(Producto* p){
	if (p == NULL){
		return;
	}
	if (p->nombre != NULL){
		free(p->nombre);
	}
	free(p);
}

Producto* setNombreProducto(Producto * p, char* n){
	if ((p == NULL) || (n == NULL)) {
		return NULL;
	}
	
	if  (p->nombre != NULL) {
		free(p->nombre);
	}
	
	p->nombre = (char*) malloc (sizeof(char) * (strlen(n) + 1));
	if (p->nombre == NULL) {
		return NULL;
	}
	strcpy(p->nombre, n);
	return p;
}

char* getNombreProducto(Producto* p){
	if (p == NULL){
		return NULL;
	}
	if (p->nombre == NULL){
		return NULL;
	}
	
	return p->nombre;
}

Producto* setPrecioProducto(Producto* p, float pre){
	if (p == NULL) {
		return NULL;
	}
	p->precio = pre;
	return p;
}

float getPrecioProducto(Producto* p){
	if (p == NULL) {
		return -1;
	}
	return p->precio;
}

Producto* setTipoProducto(Producto* p, TipoVehiculo t){
	if (p == NULL){
		return NULL;
	}
	
	p->tipo = t;
	return p;
}

TipoVehiculo getTipoProducto(Producto* p){
	if (p ==NULL) {
		return -1;
	}
	
	return p->tipo;
}



/* funciones relacionadas con la tienda */


Tienda * crearTienda() {
	Tienda * t = NULL;  
	t = (Tienda*) malloc (sizeof (Tienda));
	if (t == NULL) {
		return NULL;
	}
	t->clientes = NULL;
	t->productos = NULL;
	t->descuentos = NULL;
	t->nClientes = 0;
	t->nProductos = 0;
	t->nDescuentos = 0;
	return t;   
}

void borrarTienda (Tienda *t){
	if (t == NULL) {
		return;
	}
	if (t->clientes != NULL) {
		free(t->clientes);
	}
	if (t->productos != NULL) {
		free(t->productos);
	}
	if (t->descuentos != NULL) {
		free(t->descuentos);
	}
	free(t);
}
