#include <iostream>
using namespace std;

#include "Examen.h"
#include "ServicioMesa.h"
#include "ArchivoServicioMesa.h"

void Examen::EjemploDeListado(){
   ArchivoServicioMesa archivo("restaurant.dat");
   ServicioMesa registro;

   int i, cantidadRegistros = archivo.CantidadRegistros();
   for(i = 0; i < cantidadRegistros; i++){
      registro = archivo.Leer(i);
      cout << registro.toCSV() << endl;
   }
}


/*
1) Listar la cantidad de servicios de mesa que fueron valorados con un puntaje mayor al puntaje promedio

2) Listar el número de plato que recaudó mayor cantidad de dinero

3) Listar el número de mozo que recibió mayor cantidad total de propinas en el año 2024
*/

///punto 1
float PromedioPuntaje(){
    float puntaje = 0;
    ServicioMesa registro;
    ArchivoServicioMesa archivo("restaurant.dat");

    int i, cantidadRegistros = archivo.CantidadRegistros();
    for(i = 0; i < cantidadRegistros; i++){
      registro = archivo.Leer(i);
        puntaje += registro.getPuntajeObtenido();
      }
    float promedio = puntaje / cantidadRegistros;
    return promedio;
}

void Examen::Punto1(){
    float promedio = PromedioPuntaje();
    int cantidad = 0;
    if(promedio <= 0.0f){
        cout << "No se encuentran registros" << endl;
    }else{
        ArchivoServicioMesa archivo("restaurant.dat");
        ServicioMesa registro;
        int i, cantidadRegistros = archivo.CantidadRegistros();
        for(i = 0; i < cantidadRegistros; i++){
            registro = archivo.Leer(i);
            if(registro.getPuntajeObtenido() > promedio){
                cantidad++;
            }
        }

        cout << "********************" << endl;
        cout << "Promedio: " << promedio << endl;
        cout << "Cantidad de mesa con valoracion mayor al promedio: " << cantidad << endl;
        cout << "********************" << endl;
    }
}

///punto 2
bool ya_procesado(int *v , int tam, int id){

    for (int i = 0; i< tam; i++ ){
        if(v[i] == id){
            return true;
        }
    }
    return false;
}

void Examen::Punto2() {
    ArchivoServicioMesa archivo("restaurant.dat");
    ServicioMesa registro, registro2;
    int idPlatoMayor = -1;
    float recaudacionMayorXPlato=0;
    int i, cantidadRegistros = archivo.CantidadRegistros();
    int *v;
    v= new int [cantidadRegistros]{};
    int platosCalculados = 0;

    for(i = 0; i < cantidadRegistros; i++){
        registro = archivo.Leer(i);
        float recaudacionPlatoActual = 0 ;
        int numeroPlatoActual= registro.getIDPlato();

        if (ya_procesado(v, platosCalculados, numeroPlatoActual)) continue;

        for(int j = 0 ; j<cantidadRegistros; j++){
            registro2 = archivo.Leer(j);
            if(numeroPlatoActual == registro2.getIDPlato() ){
                recaudacionPlatoActual += registro2.getImporte();
            }
        }

        v[platosCalculados] = numeroPlatoActual;
        platosCalculados++;

        if(recaudacionPlatoActual > recaudacionMayorXPlato){
            idPlatoMayor = numeroPlatoActual;
            recaudacionMayorXPlato = recaudacionPlatoActual;
        }
    }
    delete []v;
    cout << "El plato con mayor recaudacion es :" << idPlatoMayor<<endl;
    cout << "********************" << endl;
}

///punto 3
void Examen::Punto3(){
     ArchivoServicioMesa archivo("restaurant.dat");
   ServicioMesa registro,registro2;

   int i, cantidadRegistros = archivo.CantidadRegistros();
   int idMozoMayorRecaudacionPropinas=-1;
   float propinasMaximas= -1;
   int *v;
   v = new int [cantidadRegistros]{};
   int mozosRegistrados=0;

   for(i = 0; i < cantidadRegistros; i++){
      registro = archivo.Leer(i);
      int idMozoActual = registro.getIDMozo();
      int anioRegistro = registro.getFecha().getAnio();
      float propinasMozoActual= 0;

      if( anioRegistro == 2024){
        if(ya_procesado(v,mozosRegistrados, idMozoActual)){
            continue;
        }else{
            for(int j = 0; j<cantidadRegistros; j++){
                registro2 = archivo.Leer(j);
                int idMozoActual2 = registro2.getIDMozo();
                int anioRegistro2 = registro2.getFecha().getAnio();
                if(idMozoActual == idMozoActual2 && anioRegistro2 == anioRegistro){
                    propinasMozoActual += registro2.getPropina();
                }
            }
        }
        v[mozosRegistrados] = idMozoActual;
        mozosRegistrados++;

        if(propinasMozoActual > propinasMaximas){
            propinasMaximas = propinasMozoActual;
            idMozoMayorRecaudacionPropinas = idMozoActual;
        }
      }
    }
    delete [] v;
    if(idMozoMayorRecaudacionPropinas == -1){
        cout << "No se encuentran registros en el 2024 " <<endl;
        cout << "********************" << endl;
    }else{
        cout << "El mozo con mayor recaudacion de propinas es : " << idMozoMayorRecaudacionPropinas << endl;
        cout << "********************" << endl;
    }
}
