#include <iostream>
#include <list>
#include <math.h>//para usar pow (potencia)

using namespace std;

struct monomio {//estructura para almacenar los coeficientes de un monomio y su exponente
    double coeficiente;//coeficiente
    int exponente;//exponente
    monomio(double pcoef, int pexp) {//constructor
        coeficiente = pcoef;//asigna el coeficiente
        exponente = pexp;//asigna el exponente
    }
};

//prototipos de funciones
list<monomio> agregarPolinomio();

void verPolinomios(list<list<monomio>> polinomios);

void sumarPolinomios(list<list<monomio>> polinomios);

void restarPolinomios(list<list<monomio>> polinomios);

void evaluarPolinomio(list<list<monomio>> polinomios);

list<monomio> sumaPuraPolinomios(list<monomio> polinomio1, list<monomio> polinomio2, int sizePolinomio1, int sizePolinomio2);

void multiplicarPolinomios(list<list<monomio>> polinomios);

monomio multiplicarMonomios(monomio &monomio1, monomio &monomio2);

void menu() {//funcion para mostrar el menu
    list<list<monomio>> polinomios;//lista de listas de polinomios, un polinomio es una lista de coeficientes y exponentes (monomios)
    list<monomio> polinomio1;//se va a crear un polinomio
    polinomio1.push_back({1, 0});
    polinomio1.push_back({4, 1});
    polinomio1.push_back({2, 2});
    list<monomio> polinomio2;//se va a crear un polinomio
    polinomio2.push_back({2, 0});
    polinomio2.push_back({5, 1});
    polinomio2.push_back({-4, 2});
    polinomio2.push_back({-2, 3});
    polinomio2.push_back({5, 4});
    polinomios.push_back(polinomio1);//se agrega el polinomio1 a la lista de polinomios
    polinomios.push_back(polinomio2);//se agrega el polinomio2 a la lista de polinomios
    while (true) {//ciclo infinito, se sale con el break

        string opcion;

        cout << "\n1. Ingresar polinomio" << endl;
        cout << "2. Mostrar polinomios" << endl;
        cout << "3. Sumar polinomios" << endl;
        cout << "4. Restar polinomios" << endl;
        cout << "5. Multiplicar polinomios" << endl;
        cout << "6. Evaluar polinomio en x" << endl;
        cout << "7. Salir" << endl;

        cout << "\nIngrese una opcion: ";

        cin >> opcion;

        if (opcion == "1") {

            list<monomio> polinomio = agregarPolinomio();//llama a la funcion para ingresar un polinomio, retorna una lista de coeficientes y exponentes (monomios)
            polinomios.push_front(polinomio);//agrega el monomio a la lista de polinomios
        } else if (opcion == "2") {
            verPolinomios(polinomios);//llama a la funcion para mostrar los polinomios
        } else if (opcion == "3") {
            sumarPolinomios(polinomios);//llama a la funcion para sumar los polinomios
        } else if (opcion == "4") {
            restarPolinomios(polinomios);//llama a la funcion para restar los polinomios
        } else if (opcion == "5") {
            multiplicarPolinomios(polinomios);//llama a la funcion para multiplicar los polinomios
        } else if (opcion == "6") {
            evaluarPolinomio(polinomios);//llama a la funcion para evaluar polinomio en x
        } else if (opcion == "7") {
            break;//sale del ciclo infinito
        } else {
            cout << "\nOpcion no valida" << endl;
        }
    }

}

void multiplicarPolinomios(list<list<monomio>> polinomios) {
    int posPolinomio1, posPolinomio2;
    list<monomio> polinomio1, polinomio2;

    verPolinomios(polinomios);
    cout << "\nIngrese el numero del primer polinomio a multiplicar: ";
    cin >> posPolinomio1;
    cout << "\nIngrese el numero del segundo polinomio a multiplicar: ";
    cin >> posPolinomio2;

    posPolinomio1 -= 1;
    posPolinomio2 -= 1;//se resta 1 para que el numero ingresado sea el correcto con respecto a la lista (indice)

    list<list<monomio>>::iterator it = polinomios.begin();//iterador para recorrer la lista de polinomios
    list<monomio>::iterator it2;//iterador para recorrer la lista de coeficientes y exponentes (monomios)
    list<monomio>::iterator it3;//iterador para recorrer la lista de coeficientes y exponentes (monomios)

    advance(it, posPolinomio1);//avanza el iterador hasta la posicion del polinomio1
    polinomio1 = *it;//asigna el polinomio1 a la lista de coeficientes y exponentes (monomios)
    it = polinomios.begin();//reinicia el iterador
    advance(it, posPolinomio2);//avanza el iterador hasta la posicion del polinomio2
    polinomio2 = *it;//asigna el polinomio2 a la lista de coeficientes y exponentes (monomios)
    list<monomio> polinomioFinal;//lista de coeficientes y exponentes (monomios) del tercer polinomio resultante de la resta

    int cont=0;//contador para saber cuantos terminos van, hay que completar al inicio con 0s para sumar
    for(it2 = polinomio1.begin(); it2 != polinomio1.end(); it2++){//recorre la lista de coeficientes y exponentes (monomios) del polinomio1
        list<monomio> polinomioMultiplicado;//lista de coeficientes y exponentes (monomios) del monomio multiplicado
        if(cont!=0){//si el contador es distinto de 0, se completan los terminos con 0s
            for(int i=0; i<cont; i++){
                polinomioMultiplicado.push_back({0,i});//se completa exponente con i que es exponente en posicion
            }
        }
        for(it3 = polinomio2.begin(); it3 != polinomio2.end(); it3++){//recorre la lista de coeficientes y exponentes (monomios) del polinomio2
            monomio monomioResultante = multiplicarMonomios(*it2, *it3);//llama a la funcion para multiplicar los monomios
            polinomioMultiplicado.push_back(monomioResultante);//agrega el monomio resultante a la lista de coeficientes y exponentes (monomios) del polinomio final
        }
        if(cont==0){//si el contador es 0, se agrega el primer termino
            polinomioFinal=polinomioMultiplicado;
        }else{//si el contador es distinto de 0, se suman los terminos
            polinomioFinal = sumaPuraPolinomios(polinomioFinal, polinomioMultiplicado, polinomioFinal.size(), polinomioMultiplicado.size());
        }

        cont++;//aumenta el contador
    }

    cout << "\nEl polinomio multiplicado es: ";
    list<list<monomio>> imprimirPolinomio; //lista de polinomios a imprimir
    imprimirPolinomio.push_back(polinomioFinal);//agrega el polinomio final a la lista de polinomios a imprimir
    verPolinomios(imprimirPolinomio);//llama a la funcion para imprimir los polinomios
}

monomio multiplicarMonomios(monomio &monomio1, monomio &monomio2) {
    monomio monomioResultante={0,0};//monomio resultante de la multiplicacion de los monomios
    monomioResultante.coeficiente = monomio1.coeficiente * monomio2.coeficiente;//multiplica los coeficientes
    monomioResultante.exponente = monomio1.exponente + monomio2.exponente;//suma los exponentes
    return monomioResultante;//retorna el monomio resultante
}

void evaluarPolinomio(list<list<monomio>> polinomios) {//funcion para evaluar un polinomio en x
    double x;
    int posPolinomio;
    double resultado = 0;

    verPolinomios(polinomios);//muestra los polinomios
    cout << "\nIngrese el numero del polinomio a evaluar: ";
    cin >> posPolinomio;
    posPolinomio -= 1;//se resta 1 para que el numero ingresado sea el correcto con respecto a la lista (indice)
    cout << "\nIngrese el valor de x: ";
    cin >> x;

    list<list<monomio>>::iterator it = polinomios.begin();//iterador para recorrer la lista de polinomios
    list<monomio>::iterator it2;//iterador para recorrer la lista de coeficientes y exponentes (monomios)
    advance(it, posPolinomio);//avanza el iterador hasta la posicion del polinomio1

    for (it2 = it->begin(); it2 != it->end(); it2++) {//recorre la lista de coeficientes y exponentes (monomios) del polinomio1
        resultado += it2->coeficiente * pow(x, it2->exponente);//calcula el valor del polinomio1 en x, pow(x, y) = x^y
    }

    list<list<monomio>> polinomios2;//para imprimir
    polinomios2.push_back(*it);//agrega el polinomio1 a la lista de polinomios

    cout << "\nPolinomio: " << endl;
    verPolinomios(polinomios2);//muestra el polinomio1
    cout << "\nEl resultado de evaluar el polinomio en x es: " << resultado << endl;

}

void restarPolinomios(list<list<monomio>> polinomios) {
    int posPolinomio1, posPolinomio2;
    list<monomio> polinomio1, polinomio2;

    verPolinomios(polinomios);
    cout << "\nIngrese el numero del primer polinomio a restar: ";
    cin >> posPolinomio1;
    cout << "\nIngrese el numero del segundo polinomio a restar: ";
    cin >> posPolinomio2;

    posPolinomio1 -= 1;
    posPolinomio2 -= 1;//se resta 1 para que el numero ingresado sea el correcto con respecto a la lista (indice)

    list<list<monomio>>::iterator it = polinomios.begin();//iterador para recorrer la lista de polinomios
    list<monomio>::iterator it2;//iterador para recorrer la lista de coeficientes y exponentes (monomios)
    list<monomio>::iterator it3;//iterador para recorrer la lista de coeficientes y exponentes (monomios)

    advance(it, posPolinomio1);//avanza el iterador hasta la posicion del polinomio1
    polinomio1 = *it;//asigna el polinomio1 a la lista de coeficientes y exponentes (monomios)
    it = polinomios.begin();//reinicia el iterador
    advance(it, posPolinomio2);//avanza el iterador hasta la posicion del polinomio2
    polinomio2 = *it;//asigna el polinomio2 a la lista de coeficientes y exponentes (monomios)

    int sizePolinomio1 = polinomio1.size();//tamaño de la lista de coeficientes y exponentes (monomios) del primer polinomio
    int sizePolinomio2 = polinomio2.size();//tamaño de la lista de coeficientes y exponentes (monomios) del segundo polinomio

    list<monomio> polinomio3;//lista de coeficientes y exponentes (monomios) del tercer polinomio resultante de la resta

    if (sizePolinomio1 == sizePolinomio2) {//CASO 1 los polinomios tienen el mismo grado
        int cont = 0;//contador para acceder a indice de polinomios
        for (it2 = polinomio1.begin(); it2 !=
                                       polinomio1.end(); it2++) {//recorre la lista de coeficientes y exponentes (monomios) del primer polinomio
            monomio monomio1 = *it2;//asigna el monomio a una variable
            it3 = polinomio2.begin();//reinicia el iterador
            advance(it3, cont);//avanza el iterador hasta el indice del monomio
            monomio monomio2 = *it3;//asigna el monomio a una variable
            monomio monomio3(monomio1.coeficiente - monomio2.coeficiente,
                             monomio1.exponente);//crea un nuevo monomio con el coeficiente y exponente de los monomios
            polinomio3.push_back(
                    monomio3);//agrega el nuevo monomio a la lista de coeficientes y exponentes (monomios) del tercer polinomio
            cont++;//incrementa el contador
        }
    } else {
        list<monomio> polinomioMayor, polinomioMenor;//listas de coeficientes y exponentes (monomios) del polinomio mas grande y pequieño respectivamente
        int menor; //guarda el tamaño del polinomio mas pequeño
        bool invertidos = false;//bandera para saber si los polinomios fueron invertidos, si es true los polinomios fueron invertidos
        if (sizePolinomio1 > sizePolinomio2) {//si el tamaño del polinomio1 es mayor al tamaño del polinomio2
            polinomioMayor = polinomio1;//se asigna polinomioq como mayor
            polinomioMenor = polinomio2;//se asigna polinomio2 como menor
            menor = sizePolinomio2;
        } else {
            polinomioMayor = polinomio2;//se asigna polinomio2 como mayor
            polinomioMenor = polinomio1;//se asigna polinomio1 como menor
            menor = sizePolinomio1;
            invertidos = true;//se cambia la bandera, esto para manejar bien los signos, no es lo mismo 10-8 que 8-10
        }

        int cont = 0;//contador para acceder a indice de polinomios
        for (it2 = polinomioMayor.begin(); it2 !=
                                           polinomioMayor.end(); it2++) {//recorre la lista de coeficientes y exponentes (monomios) del primer polinomio

            if (cont <
                menor) {//si el contador es menor al tamaño del polinomio menor, se restan los 2 monomios porque son del mismo grado
                monomio monomio1 = *it2;//asigna el monomio a una variable
                it3 = polinomioMenor.begin();//reinicia el iterador
                advance(it3, cont);//avanza el iterador hasta el indice del monomio
                monomio monomio2 = *it3;//asigna el monomio a una variable
                monomio monomio3 = {0, 0};//crea un nuevo monomio
                if (invertidos) {//si fue invertido el monomio1 y el monomio2, se cambian los signos
                    monomio3.coeficiente = monomio2.coeficiente - monomio1.coeficiente;
                    monomio3.exponente = monomio2.exponente;
                } else {
                    monomio3.coeficiente = monomio1.coeficiente - monomio2.coeficiente;
                    monomio3.exponente = monomio2.exponente;
                }
                polinomio3.push_back(
                        monomio3);//agrega el nuevo monomio a la lista de coeficientes y exponentes (monomios) del tercer polinomio
                cont++;//incrementa el contador
            } else {//si el contador es mayor al tamaño del polinomio menor, se suma solo el monomio del polinomio mayor
                monomio monomio1 = {0, 0};//asigna el monomio a una variable
                if (invertidos) monomio1.coeficiente = it2->coeficiente * -1;//se cambia el signo del coeficiente
                else monomio1.coeficiente = it2->coeficiente;
                monomio1.exponente = it2->exponente;//se asigna el exponente
                polinomio3.push_back(
                        monomio1);//agrega el nuevo monomio a la lista de coeficientes y exponentes (monomios) del tercer polinomio
                cont++;//incrementa el contador
            }
        }

    }

    cout << "El polinomio resultante de la resta es: ";
    list<list<monomio>> polinomiosResultado;//lista de polinomios resultante de la suma
    polinomiosResultado.push_back(
            polinomio3);//agrega el tercer polinomio a la lista de polinomios resultante de la suma, esto solo para  mandar a imprimir
    verPolinomios(polinomiosResultado);//muestra el polinomio resultante de la suma

}

list<monomio> sumaPuraPolinomios(list<monomio> polinomio1, list<monomio> polinomio2, int sizePolinomio1, int sizePolinomio2) {
    list < monomio > polinomio3;//lista de coeficientes y exponentes (monomios) del tercer polinomio
    list<monomio>::iterator it2;//iterador para recorrer la lista de coeficientes y exponentes (monomios)
    list<monomio>::iterator it3;//iterador para recorrer la lista de coeficientes y exponentes (monomios)
    if(sizePolinomio1==sizePolinomio2){//CASO 1 los polinomios tienen el mismo grado
        int cont = 0;//contador para acceder a indice de polinomios
        for(it2 = polinomio1.begin();it2!=polinomio1.end();it2++){//recorre la lista de coeficientes y exponentes (monomios) del primer polinomio
            monomio monomio1 = *it2;//asigna el monomio a una variable
            it3 = polinomio2.begin();//reinicia el iterador
            advance(it3, cont);//avanza el iterador hasta el indice del monomio
            monomio monomio2 = *it3;//asigna el monomio a una variable
            monomio monomio3(monomio1.coeficiente + monomio2.coeficiente,
                             monomio1.exponente);//crea un nuevo monomio con el coeficiente y exponente de los monomios
            polinomio3.push_back(monomio3);//agrega el nuevo monomio a la lista de coeficientes y exponentes (monomios) del tercer polinomio
            cont++;//incrementa el contador
        }
    } else{
        list<monomio> polinomioMayor, polinomioMenor;//listas de coeficientes y exponentes (monomios) del polinomio mas grande y pequieño respectivamente
        int menor; //guarda el tamaño del polinomio mas pequeño
        if(sizePolinomio1>sizePolinomio2){//si el tamaño del polinomio1 es mayor al tamaño del polinomio2
            polinomioMayor = polinomio1;//se asigna polinomioq como mayor
            polinomioMenor = polinomio2;//se asigna polinomio2 como menor
            menor = sizePolinomio2;
        } else{
            polinomioMayor = polinomio2;//se asigna polinomio2 como mayor
            polinomioMenor = polinomio1;//se asigna polinomio1 como menor
            menor = sizePolinomio1;
        }

        int cont = 0;//contador para acceder a indice de polinomios
        for(it2 = polinomioMayor.begin();it2!=polinomioMayor.end();it2++){//recorre la lista de coeficientes y exponentes (monomios) del primer polinomio

            if(cont<menor) {//si el contador es menor al tamaño del polinomio menor, se suman los 2 monomios porque son del mismo grado
                monomio monomio1 = *it2;//asigna el monomio a una variable
                it3 = polinomioMenor.begin();//reinicia el iterador
                advance(it3, cont);//avanza el iterador hasta el indice del monomio
                monomio monomio2 = *it3;//asigna el monomio a una variable
                monomio monomio3(monomio1.coeficiente + monomio2.coeficiente,
                                 monomio1.exponente);//crea un nuevo monomio con el coeficiente y exponente de los monomios
                polinomio3.push_back(
                        monomio3);//agrega el nuevo monomio a la lista de coeficientes y exponentes (monomios) del tercer polinomio
                cont++;//incrementa el contador
            } else{//si el contador es mayor al tamaño del polinomio menor, se suma solo el monomio del polinomio mayor
                monomio monomio1 = *it2;//asigna el monomio a una variable
                polinomio3.push_back(monomio1);//agrega el nuevo monomio a la lista de coeficientes y exponentes (monomios) del tercer polinomio
                cont++;//incrementa el contador
            }
        }

    }
    return polinomio3;
}

void sumarPolinomios(list<list<monomio>> polinomios) {
    int posPolinomio1, posPolinomio2;
    list < monomio > polinomio1, polinomio2;

    verPolinomios(polinomios);
    cout << "\nIngrese el numero del primer polinomio a sumar: ";
    cin >> posPolinomio1;
    cout << "\nIngrese el numero del segundo polinomio a sumar: ";
    cin >> posPolinomio2;

    posPolinomio1 -= 1;
    posPolinomio2 -= 1;//se resta 1 para que el numero ingresado sea el correcto con respecto a la lista (indice)

    list<list<monomio>>::iterator it = polinomios.begin();//iterador para recorrer la lista de polinomios
    list<monomio>::iterator it2;//iterador para recorrer la lista de coeficientes y exponentes (monomios)
    list<monomio>::iterator it3;//iterador para recorrer la lista de coeficientes y exponentes (monomios)

    advance(it, posPolinomio1);//avanza el iterador hasta la posicion del polinomio1
    polinomio1 = *it;//asigna el polinomio1 a la lista de coeficientes y exponentes (monomios)
    it = polinomios.begin();//reinicia el iterador
    advance(it, posPolinomio2);//avanza el iterador hasta la posicion del polinomio2
    polinomio2 = *it;//asigna el polinomio2 a la lista de coeficientes y exponentes (monomios)

    int sizePolinomio1 = polinomio1.size();//tamaño de la lista de coeficientes y exponentes (monomios) del primer polinomio
    int sizePolinomio2 = polinomio2.size();//tamaño de la lista de coeficientes y exponentes (monomios) del segundo polinomio

    list <monomio> polinomio3 = sumaPuraPolinomios(polinomio1, polinomio2, sizePolinomio1,
                                                   sizePolinomio2);//llama a la funcion que suma los polinomios
    //lista de coeficientes y exponentes (monomios) del tercer polinomio resultante de la suma



    cout << "El polinomio resultante de la suma es: " << endl;
    list < list < monomio >> polinomiosResultado;//lista de polinomios resultante de la suma
    polinomiosResultado.push_back(
            polinomio3);//agrega el tercer polinomio a la lista de polinomios resultante de la suma, esto solo para  mandar a imprimir
    verPolinomios(polinomiosResultado);//muestra el polinomio resultante de la suma

}


void verPolinomios(list<list<monomio>> polinomios) {//funcion para mostrar los polinomios

    list<list<monomio>>::iterator it;//iterador para recorrer la lista de polinomios
    list<monomio>::iterator it2;//iterador para recorrer la lista de coeficientes y exponentes (monomios)

    int cont = 1;//contador para saber el numero de polinomios
    for (it = polinomios.begin(); it != polinomios.end(); it++) {//recorre la lista de polinomios
        cout << "\n" << cont << ". ";//imprime el numero de polinomio
        cont++;//incrementa el contador
        for (it2 = it->begin(); it2 != it->end(); it2++) {//recorre la lista de coeficientes y exponentes

            if (it2->coeficiente == 0)continue;//si el coeficiente es 0, no se muestra

            if (it2 == it->begin() &&
                it2->coeficiente > 0) {//si es el primer monomio de la lista, se muestra el coeficiente
                cout << it2->coeficiente;
                continue;
            } else if (it2 == it->begin() && it2->coeficiente < 0) {//si el exponente es 0, se muestra el coeficiente
                cout << it2->coeficiente;
                continue;
            }
            if (it2->exponente == 1 && it2->coeficiente >
                                       0) {//si el exponente es 1, y coeficiente >0 se muestra el coeficiente positivo y el simbolo de x
                cout << "+" << it2->coeficiente << "x";
                continue;
            } else if (it2->exponente == 1 && it2->coeficiente <
                                              0) {//si el exponente es 1, y coeficiente <0 se muestra el coeficiente y el simbolo de x
                cout << it2->coeficiente << "x";
                continue;
            }
            if (it2->coeficiente > 0) {//si el coeficiente es mayor que 0, se muestra el coeficiente
                cout << "+" << it2->coeficiente << "x^" << it2->exponente;
            } else {//si el coeficiente es menor que 0, se muestra el coeficiente
                cout << it2->coeficiente << "x^" << it2->exponente;
            }
        }
    }
    cout << "\n";
}


list<monomio> agregarPolinomio() {//funcion para agregar un monomio

    list < monomio > polinomio;//lista de coeficientes y exponentes (monomios)
    double coeficiente;//coeficiente
    int grado;//grado del monomio

    cout << "\nIngrese el grado del polinomio: ";
    cin >> grado;
    int contadorGrado = 0;

    while (contadorGrado <= grado) {//ciclo para ingresar los coeficientes y exponentes
        cout << "\nIngrese el coeficiente del exponente " << contadorGrado << ": ";
        cin >> coeficiente;
        struct monomio p(coeficiente, contadorGrado);//crea un termino/monomio con los datos ingresados
        polinomio.push_back(p);//agrega el grado a la lista de polinomios
        contadorGrado++;
    }
    return polinomio;//retorna la lista de polinomios
}


int main() {
    cout<< "\n\t\tBienvenido al programa de operaciones con polinomios--\n" << endl;

    menu();//llama al menu

    return 0;
}