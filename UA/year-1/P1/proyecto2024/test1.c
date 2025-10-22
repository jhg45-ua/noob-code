#include <stdio.h>
#define KNOMBREAULA 21
#define KEVENTOS 20

typedef char TAula[KNOMBREAULA];

typedef struct {
    TAula    aula; // char aula[KNOMBREAULA];
    int      tipoSensor;
    long int tiempo;
    float    dato;
} TEvento;

typedef TEvento TListaEventos[KEVENTOS];

typedef struct {
    TListaEventos lista;
    int           numEventos;
} TGestor;

int menu()
{
    int opcion;

    // +++++++++++++++++++
    printf("0. Minima/maxima temperatura\n");
    printf("1. Nuevo evento\n");
    printf("2. Listar todos\n");
    printf("3. Listar tipo\n");
    printf("4. Diferencia tiempos");
    printf("5. Ordenar\n");
    printf("6. Salir\n");
    printf("Opcion: ");
    scanf("%d", &opcion);
    return opcion;
}

void altaEventoGestor(TGestor* gestor)
{
    TEvento nuevo;
    printf("Aula: ");
    scanf(" %s", nuevo.aula);
    printf("Tipo: ");
    scanf("%d", &nuevo.tipoSensor);
    printf("Tiempo: ");
    scanf("%ld", &nuevo.tiempo);
    printf("Valor: ");
    scanf("%f", &nuevo.dato);

    gestor->lista[gestor->numEventos] = nuevo;
    (gestor->numEventos)++;
}
void altaEvento(TListaEventos lista, int* numEventos)
{
    TEvento nuevo;
    printf("Aula: ");
    scanf(" %s", nuevo.aula);
    printf("Tipo: ");
    scanf("%d", &nuevo.tipoSensor);
    printf("Tiempo: ");
    scanf("%ld", &nuevo.tiempo);
    printf("Valor: ");
    scanf("%f", &nuevo.dato);

    lista[*numEventos] = nuevo;
    (*numEventos)++;
}

void imprimirEvento(TEvento evento)
{
    printf("%s,%d,%ld,%.2f",
           evento.aula,
           evento.tipoSensor,
           evento.tiempo,
           evento.dato);
}

void listarTodos(TListaEventos lista, int numEventos)
{
    if (numEventos == 0) {
        printf("Lista de eventos vacia\n");
    }
    else {
        for (int i = 0; i < numEventos; i++) {
            /*printf("%s,%d,%ld,%.2f",
                   lista[i].aula,
                   lista[i].tipoSensor,
                   lista[i].tiempo,
                   lista[i].dato);
            printf("\n");*/
            imprimirEvento(lista[i]); // TEvento
            printf("\n");
        }
    }
}

void listarTodosEventos(TGestor gestor)
{
    int stemperatura, spuerta, sventana;
    if (gestor.numEventos == 0) {
        printf("Lista de eventos vacia\n");
    }
    else {
        stemperatura = 0;
        spuerta      = 0;
        sventana     = 0;
        for (int i = 0; i < gestor.numEventos; i++) {
            printf("%s,%d,%ld,%.2f\n", gestor.lista[i].aula, gestor.lista[i].tipoSensor, gestor.lista[i].tiempo, gestor.lista[i].dato);
            switch (gestor.lista[i].tipoSensor) {
                case 0: // temperatura
                    stemperatura++;
                    break;
                case 1: // puerta
                    spuerta++;
                    break;
                case 2: // ventana
                    sventana++;
                    break;
            }
            // imprimirEvento(gestor.lista[i]);
        }
        //-----------------------------
        // *** DESPUES DE MOSTRAR TODOS LOS EVENTOS, SE MOSTRARAN
        // CUANTOS EVENTOS HAY DE CADA TIPO DE SENSOR
        // ----------------------------
        printf("Temperatura: %d\n", stemperatura);
        printf("Puerta: %d\n", spuerta);
        printf("Ventana: %d\n", sventana);
    }
}

void listarTodosEventosTipo(TGestor gestor)
{
    int tipoSensor;
    int encontrados;

    if (gestor.numEventos == 0) {
        printf("Lista de eventos vacia\n");
    }
    else {
        //--------------------------
        // *** COMPROBAR QUE EL TIPO ES CORRECTO, SI NO SE VUELVE A PEDIR.
        //--------------------------
        do {
            printf("Introduce el tipo de sensor: ");
            scanf("%d", &tipoSensor);
            if (tipoSensor < 0 || tipoSensor > 2) {
                printf("Error. El tipo de sensor debe ser (0)temperatura, (1)puerta o (2)ventana.");
            }
        } while (tipoSensor < 0 || tipoSensor > 2);
        encontrados = 0;
        for (int i = 0; i < gestor.numEventos; i++) {
            if (gestor.lista[i].tipoSensor == tipoSensor) {
                encontrados++;
                imprimirEvento(gestor.lista[i]);
                printf("\n");
            }
        }
        // -------------------------
        // *** SI NO SE HA ENCONTRADO SESNORES DE ESE TIPO SE MOSTRARA POR PANTALLA
        // NO SE AHN ENCONTRADO SENSORES DEL TIPO.
        // ------------------------
        if (encontrados == 0) {
            printf("No se han encontrado eventos del tipo ");
        }
        else {
            printf("Total de eventos encontrados es %d\n", encontrados);
        }
    }
}

void calcularDiferencia(TGestor gestor)
{
    // pedir dos sensores (posiciones en la lista)
    // mostrar la diferencia de tiempo entre esos dos sensores.
    int      sensor1, sensor2;
    long int diferencia;

    printf("Introduce la posicion de los dos sensores: ");
    scanf("%d %d", &sensor1, &sensor2);

    diferencia = gestor.lista[sensor2].tiempo -
                 gestor.lista[sensor1].tiempo;

    printf("La diferencia de tiempos es %ld\n", diferencia);
}

/// lo hace tu tia.
void ordenar(TGestor gestor)
{
}

// +++++++++++++++++++
// AÑADE LA OPCION TEMPERATURA MAXIMA/MINIMA DE LO SENSORES DE TEMPERATURA.
// Cuando se selecciona la opcion si:
//      - Si no  hay eventos: Se mostrara "NO EVENTOS"
//      - Si hay eventos pero no son de temperatura: Se mostrará "NO HAY EVENTOS DE TEMPERATURA".
//      - Si hay eventos de temperaura: Se mostrará "minima XX SSALA1, maxima YY SSALA2"
//          XX ES LA MINIMA, YY ES LA MAXIMA, SSALA1 ES AULA EL AULA DE LA  MINIMA Y SSALA2 EL DE LA MAXIMA
//      <PODEMOS SUPONER QUE NO HABRAN DOS EVENTOS CON LA MISMA TEMPERATURA>

void minMaxTemperaturasCool(TGestor gestor)
{
    int posMin, posMax;
    if (gestor.numEventos == 0) {
        printf("No hay eventos\n");
    }
    else {
        posMin = posMax = -1;
        for (int i = 0; i < gestor.numEventos && posMin == -1; i++) {
            if (gestor.lista[i].tipoSensor == 1) {
                posMin = posMax = i; // si encuenro uno para el bucle... y es el menor y el mayor de momento.
            }
        }
        if (posMin == -1) {
            printf("No hay ningun eventto de temperatura\n");
        }
        else {
            // empiezo desde el siguiente al primer sensor de temperatura que empece :)
            for (int i = posMin + 1; i < gestor.numEventos; i++) {
                if (gestor.lista[i].tipoSensor == 1) {
                    if (gestor.lista[i].dato > gestor.lista[posMax].dato) {
                        posMax = i;
                    }
                    if (gestor.lista[i].dato < gestor.lista[posMin].dato) {
                        posMin = i;
                    }
                }
            }
            printf("El menor esta en %s y la temperatura es %.2f\n", gestor.lista[posMin].aula, gestor.lista[posMin].dato);
            printf("El mayor esta en %s y la temperatura es %.2f\n", gestor.lista[posMax].aula, gestor.lista[posMax].dato);
        }
    }
}

int main()
{
    TGestor gestor = {{
                          {"a21", 2, 10, 13.1}, // gestor2.lista[0]
                          {"b21", 1, 10, 1},    // gestor2.lista[1]
                          {"c21", 1, 10, 1},    // gestor2.lista[2]
                          {"a21", 2, 10, 23.1}, // gestor2.lista[3]
                          {"a21", 1, 10, 3},    // gestor2.lista[4]
                          {"a21", 0, 10, 3},    // gestor2.lista[5]
                          {"b12", 1, 21, 34.2}  // gestor2.lista[6]
                      },
                      7}; // gestor.numEventos

    int opcion;

    // ----------------------------------------------------------------------------------
    // *** AÑADIREMOS LA OPCION BORRAR EVENTO
    //  DONDE SE MOSTRARÁN TODOS LOS EVENTOS, CON LA POSICION QUE OCUPAN EN EL VECTOR
    // EL USUARIO ELIGIARÁ LA POSICION DEL ELEMENTO A BORRAR (SI NO ES VALIDA SE VOLVERÁ
    // A PEDIR).
    // -----------------
    do {
        opcion = menu();
        switch (opcion) {
            case 0:
                minMaxTemperaturasCool(gestor);
                break;
            case 1:
                // altaEventoGestor(&gestor);
                altaEvento(gestor.lista, &gestor.numEventos);
                break;
            case 2:
                // listarTodos(gestor.lista, gestor.numEventos);
                listarTodosEventos(gestor);
                break;
            case 3:
                listarTodosEventosTipo(gestor);
                break;
            case 4:
                calcularDiferencia(gestor);
                break;
            case 5:
                calcularDiferencia(gestor);
                break;
            case 6:
                break;
            default:
                printf("error. opcion incorrecta\n");
        }
    } while (opcion != 6);
    return 0;
}
