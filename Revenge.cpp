
#include <iostream>
#include <stdlib.h>
#include<vector>
using namespace std;

/*MENU PRINCIPAL*/
int menu(void){
  int option;
  cout << endl << endl << "REVENGE\n ---------- \n 1 - JUGAR \n 2 - ESTADÍSTICAS \n 3 - CRÉDITOS \n ---------- \n 0 - SALIR" << endl << endl ;
  cin >> option;

  return option;
  }

/*MENU LANZAR DADOS*/
int menuLanzarDados(void){
  int option;
  cout << endl << endl << "---------- \n 1 - LANZAR DADOS \n 0 - SALIR \n ----------" << endl << endl ;
  cin >> option;

  return option;
}

/*Dados Comaprtidos*/
vector<int> dadosCompartidos(){
  srand(time(0));
  vector<int> obtenerDadosComaprtidos{};

  for (int i = 0; i < 2; i++)
  {
    obtenerDadosComaprtidos.push_back(1 + rand()%(13 - 1));
  }
  

  return obtenerDadosComaprtidos;
}

/*Dados Seis Caras*/
vector<int> dadosSeisCaras(int dadosStock){
  srand(time(0));
  vector<int> dadosJugador{};
  for (int i = 0; i < dadosStock; i++)
  {
    dadosJugador.push_back(1 + rand()%(7 - 1));
  }
  
  return dadosJugador;
}

/*Mostrar dados*/
void showDados(vector<int> dados){
  for (int i = 0; i < dados.size(); i++)
  {
    cout << i+1 << " - Dado: " << dados[i] << endl;
  }

}

/*Puntaje*/
int puntaje(vector<int>dados, int sumaDados){
  int cantidadDados = dados.size();
  int sumaDadosElegidos = sumaDados;
  int puntos = cantidadDados * sumaDadosElegidos;

  return puntos;


}

/*LANZAMIENTO*/
vector<int> lanzamiento(int stockDadosJuegadorUno, int puntosJugadorUno, int option){
  vector<int> lanzarDadosCompartidos = dadosCompartidos();
  vector<int> lanzarDadosSeisCaras = dadosSeisCaras(stockDadosJuegadorUno);

  int sumaDadoCompartidos = 0;

  for (int i = 0; i < 2; i++)
  {
    cout << "dado compartido numero " << i+1 << " - " << lanzarDadosCompartidos[i] << endl;
    sumaDadoCompartidos += lanzarDadosCompartidos[i];
  }
  cout <<endl << endl <<  "--------------------------------";
  cout <<endl <<  "Total: " << sumaDadoCompartidos;
  cout <<endl <<  "--------------------------------" << endl << endl;


  /*Msotrar Dados*/
  showDados(lanzarDadosSeisCaras);


  /*Elegir dados*/
  int eleccion;
  int sumaDadosElegidos = 0;
  vector<int> DadosElegidos{};

  cout << endl << "Elija el primer dado y finalice colocando 30: ";
  cin >> eleccion;


  while(eleccion != 30){

    DadosElegidos.push_back(lanzarDadosSeisCaras[eleccion - 1]);
    sumaDadosElegidos += lanzarDadosSeisCaras[eleccion - 1];

    cout << "Elija el siguiente dado: ";
    cin >> eleccion;

  }

  cout <<endl << endl << "Dados elegidos" << endl << endl;

  /*Msotrar Dados*/
  showDados(DadosElegidos);

  cout << endl <<endl << "--------------------------" << endl;
  cout << "La suma de los dados elegidos es de: " << sumaDadosElegidos;
  cout << endl << "--------------------------" << endl << endl;

  if(sumaDadoCompartidos == sumaDadosElegidos){
    cout << endl << endl <<"La suma es correcta. Se elimina de su stock de dados " << DadosElegidos.size() << " dados";
    stockDadosJuegadorUno -= DadosElegidos.size();
    puntosJugadorUno+= puntaje(DadosElegidos, sumaDadosElegidos);
    cout << endl << "Suma " << puntosJugadorUno<< " puntos";
  } else {
    cout << "Se le agrega un dado a su stock. Sus puntos actuales son: " << puntosJugadorUno;
    stockDadosJuegadorUno += 1;
    DadosElegidos = {};
  }

  if(stockDadosJuegadorUno == 0){
    cout << endl << "Felicidades, ha ganado";
    puntosJugadorUno += 10000;
    option = 0;
  } else {
    option = menuLanzarDados();
  }

  int cantDados =  DadosElegidos.size();

  vector<int>jugada{stockDadosJuegadorUno, puntosJugadorUno, option, cantDados};

  return jugada;
}

/*MAIN*/
int main (void){

  int option = menu();
  int jugadas = 0;

  cout << endl << "Opcion elegida: " << option <<endl;

  int stockDadosJuegadorUno = 6;
  int stockDadosJuegadorDos = 6;
  int puntosJugadorUno = 0;
  int puntosJugadorDos = 0;

  while(option != 0 && jugadas != 5){

    /*NUMERO DE JUGADA*/
    jugadas++;
    cout << endl <<endl << "--------------------------" << endl;
    cout << "Ronda N: " << jugadas;
    cout << endl << "--------------------------" << endl;

    /*JUGADOR 1*/
    cout << endl <<endl << "--------------------------" << endl;
    cout << "Jugador 1";
    cout << endl << "--------------------------" << endl << endl;
    vector<int>jugadorUno = lanzamiento(stockDadosJuegadorUno, puntosJugadorUno, option);
    stockDadosJuegadorUno = jugadorUno[0];
    stockDadosJuegadorDos += jugadorUno[3];
    puntosJugadorUno = jugadorUno[1];
    option = jugadorUno[2];

    /*JUGADOR 2 */
    if(option != 0){
      cout << endl <<endl << "--------------------------" << endl;
      cout << "Jugador 2";
      cout << endl << "--------------------------" << endl << endl;
      vector<int>jugadorDos = lanzamiento(stockDadosJuegadorDos, puntosJugadorDos, option) ;
      stockDadosJuegadorDos = jugadorDos[0];
      stockDadosJuegadorUno+= jugadorDos[3];
      puntosJugadorDos = jugadorDos[1];
      option = jugadorDos[2];
    }
  }

    cout << endl <<endl << "--------------------------" << endl;
    cout << "Puntos Jugador 1: " << puntosJugadorUno<< endl;
    cout << "Puntos Jugador 2: " << puntosJugadorDos<< endl;
    cout << endl << "--------------------------" << endl << endl;

  return 0;
}

