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
    cout << "Promedio: " << promedio << endl;
    ArchivoServicioMesa archivo("restaurant.dat");
    ServicioMesa registro;

   int i, cantidadRegistros = archivo.CantidadRegistros();
   cout << "********************" << endl << endl << endl;
   for(i = 0; i < cantidadRegistros; i++){
      registro = archivo.Leer(i);
      if(registro.getPuntajeObtenido() > promedio){

        cout << registro.toCSV() << endl;
      }
   }
   cout << "********************" << endl << endl << endl;

}


///punto 2

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
        float recaudacionPlatoActual = registro.getImporte() ;
        int numeroPlatoActual= registro.getIDPlato();
        bool yaProcesado = false;

        for (int x = 0; x< platosCalculados; x++ ){
            if(v[x] == registro.getIDPlato()){
                yaProcesado = true;
                break;
            }

        }
        if (yaProcesado) continue;

        for(int j = i+1; j<cantidadRegistros; j++){
            registro2 = archivo.Leer(j);
            if(numeroPlatoActual == registro2.getIDPlato() ){
                recaudacionPlatoActual += registro2.getImporte();
            }
        }

        v[platosCalculados] = numeroPlatoActual;
        platosCalculados++;

        if(recaudacionPlatoActual > recaudacionMayorXPlato){
            idPlatoMayor = registro.getIDPlato();
            recaudacionMayorXPlato = recaudacionPlatoActual;
        }
    }
    delete []v;
    cout << "El plato con mayor recaudacion es :" << idPlatoMayor<<endl;

}

void Examen::Punto3(){

}
