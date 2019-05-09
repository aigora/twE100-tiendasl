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

int inicializarFichero (Cliente *c){
	FILE *fp = NULL;    
	char cadena[512];
	char nombre[20];
	if (c == NULL) {
		return -1;
	}
	sprintf((char*) cadena, "Nombre=%s\nGasto=%lf\nFidelidad=%d", c->nombre, c->gasto, c->fidelidad);
	sprintf((char*) nombre, "%s.txt", c->nombre);

	fp = (FILE*) malloc (sizeof(FILE));

	fp = fopen (nombre, "w" );
	fwrite( cadena, sizeof(char), strlen(cadena), fp );
	fclose ( fp );
	
	return 0;
}

Cliente ** anyadirClientePorNombre(Tienda * t, Cliente * c){
	int i;
	Cliente ** CAux = NULL;
	if (t == NULL || c == NULL) {
		return NULL;
	}

	if (t->clientes == NULL || t->nClientes == 0) {
		t->clientes = (Cliente **) malloc (sizeof (Cliente*));
		t->clientes[t->nClientes] = c;

		inicializarFichero(c);
		t->clientes = (Cliente **) realloc (t->clientes, (sizeof(t->clientes) + sizeof(Cliente *)));
		t->clientes[t->nClientes] = c;
		t->nClientes++;
		return t->clientes;
	}


	for (i = 0; i < t->nClientes; i++) {
		if (strcmp(getNombreCliente(t->clientes[i]), c->nombre) == 0) {
			printf("ya existe un cliente con este nombre\n");
			borrarCliente(c);
			return t->clientes;
		}
	}



	inicializarFichero(c);

	t->clientes = (Cliente **) realloc (t->clientes, (sizeof(t->clientes) + sizeof(Cliente *)));
	t->clientes[t->nClientes] = c;
	t->nClientes++;
	return t->clientes;
}

Producto ** anyadirProducto(Tienda * t, Producto *p){
	if (t == NULL || p == NULL) {
		return NULL;
	}

	if (t->productos == NULL || t->nProductos == 0) {
		t->productos = (Producto **) malloc (sizeof (Producto *));
		t->productos[t->nProductos] = p;
		t->nProductos++;
		return t->productos;
	}

	t->productos = (Producto **) realloc (t->productos, (sizeof(t->productos) + sizeof(Producto *)));
	t->productos[t->nProductos] = p;
	t->nProductos++;
	return t->productos;
}

Descuento ** anyadirDescuento(Tienda * t, Descuento* d){
	if (t == NULL || d == NULL) {
		return NULL;
	}

	if (t->descuentos == NULL || t->nDescuentos == 0) {
		t->descuentos = (Descuento **) malloc (sizeof (Descuento *));
		t->descuentos[t->nDescuentos] = d;
		t->nDescuentos++;
		return t->descuentos;
	}

	t->descuentos = (Descuento **) realloc (t->descuentos, (sizeof(t->descuentos) + sizeof(Descuento *)));
	t->descuentos[t->nDescuentos] = d;
	t->nDescuentos++;
	return t->descuentos;
}

Cliente ** getClientes(Tienda * t){
	if (t == NULL) {
		return NULL;
	}

	return t->clientes;
}

Producto ** getProductos(Tienda * t){
	if (t == NULL) {
		return NULL;
	}

	return t->productos;
}

Descuento ** getDescuentos(Tienda * t){
	if (t == NULL) {
		return NULL;
	}

	return t->descuentos;
}

/* dado el nombre de un producto lo elimina */

Producto ** eliminarProductoPorNombre(Tienda * t, char * nombre) {
	int i, j, k;
	Producto ** pAux = NULL;

	if (t == NULL || nombre == NULL) {
		return NULL;
	}

	if (t->productos == NULL) {
		printf("no hay ningun producto ahora mismo, no se puede eliminar\n");
		return NULL;
	}

	for (i = 0; i < t->nProductos; i++) {
		if (strcmp(getNombreProducto(t->productos[i]), nombre) == 0) {
			borrarProducto(t->productos[i]);
			t->productos[i] = NULL;
			/*pAux = (Producto **) realloc (t->productos, (sizeof(t->productos) - sizeof(Producto *)));*/
			pAux = (Producto **) malloc(sizeof(Producto*) * (t->nProductos - 1));
			k = 0;
			for (j = 0; j < t->nProductos; j++) {
				if (t->productos[j] != NULL) {
					printf("siii\n");
					pAux[j] = t->productos[j];
					printf("2\n");
					k++;
				}
			}

			free(t->productos);
			t->productos = pAux;
			t->nProductos--;
			return t->productos;
		}
	}

	printf("NO SE HA ENCONTRADO EL PRODUCTO\n");
	return t->productos;
}
/* dada la tienda el cliente y el producto compra el producto, sumando su
precio al gasto del cliente y eliminando el producto */
int comprarProducto(Tienda *t, Cliente *c, Producto*p){
	int i;
	if ( t == NULL || c == NULL || p == NULL) {
		return -1;
	}

	for (i = 0; i < t->nProductos; i++) {
		if (strcmp(getNombreProducto(t->productos[i]), p->nombre) == 0) {
			c->gasto += p->precio;
			inicializarFichero(c);
			eliminarProductoPorNombre(t, p->nombre);
			return 0;
		}
	}

	printf("no se encuentra ese producto en la lista\n");
	return -1;
}

/*devuelve un cliente dado su nombre*/
Cliente * getClientePorNombre(Tienda * t, char* nombre){
	int i;
	if (t == NULL || nombre == NULL) {
		return NULL;
	}

	if (t->clientes == NULL || t->nClientes == 0) {
		printf("NO HAY CLIENTES REGISTRADOS\n");
		return NULL;
	}


	for (i = 0; i < t->nClientes; i++) {
		if (strcmp(getNombreCliente(t->clientes[i]), nombre) == 0) {
			return t->clientes[i];
		}
	}



	printf("NO SE HA ENCONTRADO NINGÚN CLIENTE CON ESE NOMBRE\n");
	return NULL;
}

/*devuelve un cliente dado su nombre*/
Producto * getProductoPorNombre(Tienda * t, char* nombre){
	int i;
	if (t == NULL || nombre == NULL) {
		return NULL;
	}

	if (t->productos == NULL || t->nProductos == 0) {
		printf("NO HAY PRODUCTOS REGISTRADOS\n");
		return NULL;
	}


	for (i = 0; i < t->nProductos; i++) {
		if (strcmp(getNombreProducto(t->productos[i]), nombre) == 0) {
			return t->productos[i];
		}
	}



	printf("NO SE HA ENCONTRADO NINGÚN PRODUCTO CON ESE NOMBRE\n");
	return NULL;
}


 /* función de prueba creando clientes y productos y comprando*/
int prueba(){
	Tienda *t = NULL;
	Cliente *c1 = NULL;
	Cliente *c2 = NULL;
	Producto * p1 = NULL;

	t = crearTienda();
	c1 = crearCliente();
	c2 = crearCliente();
	p1 = crearProducto();


	setNombreCliente(c1, "pepe");
	setGastoCliente(c1, 999);
	setFidelidadCliente(c1, 2);
	anyadirClientePorNombre(t, c1);
	printf("%s\n", getNombreCliente(c1));

	setNombreCliente(c2, "Jose");
	setGastoCliente(c2, 100);
	setFidelidadCliente(c2, 15);
	anyadirClientePorNombre(t, c2);
	printf("%s\n", getNombreCliente(c2));


	setNombreProducto(p1, "cochazo");
	setTipoProducto(p1, GASOLINA);
	setPrecioProducto(p1, 1000);
	anyadirProducto(t, p1);

	comprarProducto(t, c1, p1);
	comprarProducto(t, c2, p1); /* o deberia permitirlo ya que alguien ya ha comprado el producto*/

	/*borrarProducto(p1);*/ 
	borrarCliente(c1);
	borrarCliente(c2);
	borrarTienda(t);

	return 0;
}
/* función principal con un bucle con 5 opciones*/
int main(int argc, char const *argv[])
{
	int opcion = 0;
	Tienda *t = NULL;
	t = crearTienda();

	while(opcion != 5){
		printf("\nPosibles comandos (introduzca el numero de comando):\n Nuevo cliente (1)\n Nuevo producto (2)\n Comprar producto (3)\n Ejecucion de prueba (4)\n Salir (5)");
	
	int f = 0;
	double g = 0;
	Cliente * c1 = NULL;
	Producto * p1 = NULL;
	char n[20];
	char np[20];

	scanf( "%d", &opcion );

		switch ( opcion )
		{
			case 1: 
					c1 = crearCliente();

					printf( "\n   Introduzca el nombre: ");
					scanf( "%s", n);
					setNombreCliente(c1, n);


					printf( "\n   Introduzca fidelidad (numero de años): ");
					scanf( "%d", &f );
					setFidelidadCliente(c1, f);

					printf( "\n   Introduzca el gasto realizado hasta la fecha (euros): ");
					scanf( "%lf", &g );
					setGastoCliente(c1, g);

					anyadirClientePorNombre(t, c1);
					break;

			case 2: 
					p1 = crearProducto();

					printf( "\n   Introduzca el nombre del producto: ");
					scanf( "%s", np);
					setNombreProducto(p1, np);


					printf( "\n   Introduzca el tipo de vehículo (MOTO = 1, GASOLINA = 2, DIESEL = 3, HIBRIDO = 4): ");
					scanf( "%d", &f );
					setTipoProducto(p1, f);

					printf( "\n   Introduzca el precio del producto (euros): ");
					scanf( "%lf", &g );
					setPrecioProducto(p1, g);

					anyadirProducto(t, p1);
					break;

			case 3: 
					printf( "\n   Introduzca el nombre del cliente que va a realizar la compra: " );
					scanf( "%s", n);
					c1 = getClientePorNombre(t, n);
					if (c1 == NULL) break;

					printf( "\n   Introduzca el nombre del producto a comprar: " );
					scanf( "%s", np);
					p1 = getProductoPorNombre(t, np);
					if (p1 == NULL) break;

					comprarProducto(t, c1, p1);
					break;

			case 4: 
					prueba();
		}
	}
	return 0;
}
