#include <iostream>
#include <string>

const int TAM_INICIAL = 50;

void inizializarArrays(int*&, float*&, std::string, int*&, std::string, int&);
void duplicarTamano(int*&, float*&, std::string, int*&, std::string, int&);
void encolarPaquete(int*&, float*&, std::string*&, int*&, std::string, int&, int&, int&,int&, int&);
void despacharPaquete(int*&, float*&, std::string*&, int*&, std::string, int&,int&,int&,int&);
void inspeccionar(int*, float*, std::string*, int, int, int);
void reporte(std::string*, float*, std::string*, int, int);
void liberarMemoria(int*&, float*&, std::string*&, int*&, std::string*&);


int main(){
    int *id = nullptr;
    float *peso = nullptr;
    std::string *destino = nullptr;
    int *prioridad = nullptr;
    std::string *estado = nullptr;

    int tam = TAM_INICIAL;
    int inicio = 0;
    int fin = 0;
    int total = 0;
    int contadorId = 100;
    
    std::cout << "--- Sistema de Despacho Logístico MegaEnvío (Modo Punteros) ---" << std::endl;
    inizializarArrays(id, peso, destino, prioridad, estado, tam);

    int opcion;
    do{
        std::cout << "Capacidad actual: 50. Paquetes en cola: 0. \n" << std::endl;
        std::cout << "Seleccione una operación:" << std::endl;
        std::cout << "1. Agregar Paquete (Encolar)" << std::endl;
        std::cout << "2. Despachar Paquete (Desencolar)" << std::endl;
        std::cout << "3. Inspeccionar Frente de Cola" << std::endl;
        std::cout << "4. Reporte por Destino" << std::endl;
        std::cout << "5. Salir (Liberar Memoria)" << std::endl;
        std::cin >> opcion;
        std::cin.ignore();
        
        switch(opcion){
            case 1: 
                encolarPaquete(id, peso, destino, prioridad, estado, tam, fin, total, contadorId);
                break;
            case 2:
                despacharPaquete(id, peso, destino, prioridad, estado, tam, total, inicio, fin);
                break;
            case 3: 
                inspeccionar(id, peso, destino, prioridad, estado, inicio, total, fin);              
                break;
            case 4:   
                reporte(destino, peso, estado, inicio, fin);   
                break;
            case 5:   
                liberarMemoria(id, peso, destino, prioridad, estado);
                std::cout << "Liberando" << tam << " bloques de memoria asignada..." <<std::endl;
                std::cout << "Sistema cerrado. ¡Memoria libre!" << std::endl;
                break;
        }
    }while(opcion != 5);
    return 0;
}

void inizializarArrays(int *&id, float *&peso, std::string *&destino, int *&prioridad, std::string *&estado, int &tam){
    id = new int[tam];
    peso = new float[tam];
    destino = new std::string[tam];
    prioridad = new int[tam];
    estado = new std::string[tam];

    for(int i = 0; i < tam; i++){
        id[i] = 0;
        peso[i] = 0.0;
        destino[i] = "";
        prioridad[i] = 0;
        estado[i] = "";
    }
    
    std::cout << "Inicializando sistema con capacidad para " << tam << " paquetes..."  << std::endl;   
}

void duplicarTamano(int *&id, float *&peso, std::string *&destino, int *&prioridad, std::string *&estado, int &tam){
    int nuevoTamano = tam *2;
    int *nId = new int[nuevoTamano];
    float *nPeso = new float[nuevoTamano];
    std::string *nDestino = new std::string[nuevoTamano];
    int *nPrioridad = new int[nuevoTamano];
    std::string *nEstado= new std::string[nuevoTamano];

    for(int i = 0; i < tam; i++){
        nId[i] = id[i];
        nPeso[i] = peso[i];
        nDestino[i] = destino[i];
        nPrioridad[i] = prioridad[i];
        nEstado[i] = estado[i];
            
    }
       
    for(int i = tam; i < nuevoTamano; i++){
        nId[i] = 0;
        nPeso[i] = 0.0;
        nDestino[i] = "";
        nPrioridad[i] = 0;
        nEstado[i] = "";
    }

    delete[] id;
    delete[] peso;
    delete[] destino;
    delete[] prioridad;
    delete[] estado;
    
    id = nId;
    peso = nPeso;
    destino = nDestino;
    prioridad = nPrioridad;
    estado = nEstado;
    tam = nuevoTamano;

    nId = nullptr;
    nPeso = nullptr;
    nDestino = nullptr;
    nPrioridad = nullptr;
    nEstado = nullptr;

    std::cout << " Capacidad actualizada a  " << nuevoTamano << " paquetes" << std::endl;
}

void encolarPaquete(int *&id, float *&peso, std::string *&destino, int *&prioridad, std::string *&estado, int &tam, int &totalCola, int &contadorId, int &fin, int &inicio){
    if(fin >= tam){
        duplicarTamano(id, peso, destino, prioridad,estado, tam);
    }
    
    float nuevoPeso;
    std::string nuevoDestino;
    int nuevaPrioridad;
    bool taBien = false;

    std::cout << "Peso: " << std::endl;
    std::cin >> nuevoPeso;
    std::cin.ignore();
    std::cout << "Destino: " << std::endl;
    std::getline(cin, nuevoDestino);
    do{
        std::cout << "Prioridad (1 = Alta, 2 = Media, 3 = Baja)" << std::endl;
        std::cin >> nuevaPrioridad;            
        cin.ignore();
    
        if(nuevaPrioridad == 1 || nuevaPrioridad == 2 || nuevaPrioridad ==3){
            taBien = true;
        } else {std::cout << "Opcion invalida" << std::endl;}
    } while(!taBien);

    int nuevoId = contadorId++;

    int posicion = fin; 
    
    for (int i = inicio; i < fin; i++) {
        if (estado[i] == "E" && prioridad[i] > nuevaPrioridad) {
            posicion = i;
            break;
        }
    }

    for (int i = fin; i > posicion; i--) {
        id[i] = id[i - 1];
        peso[i] = peso[i - 1];
        destino[i] = destino[i - 1];
        prioridad[i] = prioridad[i - 1];
        estado[i] = estado[i - 1];
    }

    id[fin] = nuevoId;
    peso[fin] = nuevoPeso;
    destino[fin] = nuevoDestino;
    prioridad[fin] = nuevaPrioridad;
    estado[fin] = "E";

    fin++;
    totalCola++;

    std::cout << "Paquete " << nuevoId << " encolado. Capacidad utilizada " << total << "/" << tam << std::endl;
}

void despacharPaquete(int *&id, float *&peso, std::string *&destino, int *&prioridad, std::string *&estado, int &tam, int &totalCola, int &inicio, int &fin){
    if (totaCola == 0l){
        std::cout << "No hay paquetes en cola." << std::endl;
        return;
    }

    int idDes = id[inicio];
    estado[inicio] = "D";
    
    std::cout << "Despachando paquete... " << std::endl;
    std::cout << "Paquete " << idDes << " Despachado con éxito. Estado: 'D'." << std::endl;

    inicio++;
    total--;
}

void inspeccionar(int *id, float *peso, std::string *destino, int *prioridad, std::string *estado, int inicio, int total, int fin){
    if(total == 0){
        std::cout << "Cola vacia" << std::endl;
        return;
    }

    int indice = -1;
    for(int i = inicio; i < fin; i++){
        if(estado[i] = "E"){
            indice = i;
            break;        
        }
    }

    if(indice == -1){
        std::cout << "No hay paquetes en espera" << std::endl;
        return;
    }
    
    std::cout << "Frente de la cola." << std::endl;
    std::cout << "Id: " << id[indice] << " | Peso: " << peso[indice] << " kg | Destino: " << destino[indice] << " | Prioridad: ";
    if (prioridad[indice] == 1) std::cout << "Alta";
    else if (prioridad[indice] == 2) std::cout << "Media";
    else std::cout << "Baja";
    std::cout << std::endl;
} 

void reporte(std::string *destino, float *peso, std::string *estado, int inicio, int fin){
    std::string buscando;
    std::cout << "Ingrese el destino del reporte: " << std::endl;
    getline(cin, buscando);
    
    int contadorPaquetes = 0;
    float suma = 0.0;
    
    for (int i = 0; i < fin, i++){
        if(estado[i] == "E" && destino[i] == buscando){
            contador++;
            suma+=peso[i];
        }
    }

    std::cout << "Reporte para destino '" <<  buscando << "':" << std::endl;
    std::cout << "  Paquetes En Cola: " << contador << std::endl;
    if(contador > 0){std::cout << "  Peso Promedio: " << (suma/contador) << "Kg" << std::endl;}
    else {std::cout << "  no hay paquetes"  << std::endl;}
}

void liberarMemoria(int *&id, float *&peso, std::string *&destino, int *&prioridad, std::string *&estado){
    delete[] id;
    delete[] peso; 
    delete[] destino;
    delete[] prioridad;
    delete[] estado;

    id = nullptr;
    peso = nullptr;
    destino = nullptr;
    prioridad = nullptr;
    estado = nullptr;
}
