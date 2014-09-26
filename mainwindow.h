#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "jugador.h"
#include "propiedad.h"
#include "propiedadnormal.h"
#include "communitychest.h"
#include "chance.h"
#include <vector>
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void llenarPropiedades();//llena el vector de propiedades
    void llenarChance(); //llena el vector de tarjetas chance
    void llenarChest(); //llena el vector de tarjetas de community chest
    void detectarPosicion(int); //detecta la posicion en el tablero
    void accionesChance(int); //funcion que realiza las acciones de las tarjetas de chance
    void accionesChest(char); //funcion que realiza las acciones de las tarjetas de Community Chest
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_comprarJugador1_clicked();

    void on_comprarJugador2_clicked();

    void on_pushButton_2_clicked();

    void on_pagar1_clicked();

    void on_subastar1_clicked();

    void on_pagar2_clicked();

    void on_subastar2_clicked();

    void on_propiedadesJugador2_clicked();

    void on_propiedadesJugador1_clicked();

    void on_pushButton_3_clicked();

    void on_hipotecar1_clicked();

    void on_hipotecar2_clicked();

    void on_construir1_clicked();

    void on_construir2_clicked();

private:
    Jugador* jugador1;
    Jugador* jugador2;
    vector<Propiedad*> propiedades;
    vector<Chance*> tarjetas_chance;
    vector<CommunityChest*> tarjetas_arca;
    vector<Propiedad*> propiedadesJugador1;
    vector<Propiedad*> propiedadesJugador2;
    bool bandera;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
