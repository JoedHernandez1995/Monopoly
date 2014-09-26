#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "propiedad.h"
#include "propiedadnormal.h"
#include "servicio.h"
#include "railroad.h"
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <QMessageBox>
#include "chancedialog.h"
#include "communitychest.h"
#include "communitychestdialog.h"
#include "subastardialog.h"
#include <QInputDialog>
#include "propiedadesdialog.h"
#include "hipotecardialog.h"
#include "construirdialog.h"
#include <QTextStream>
#include <QFile>
#include <string>
#include <fstream>
#include <typeinfo>
using namespace std;

void detectarPosicion(int);
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    jugador1 = new Jugador("Jose",1);
    jugador2 = new Jugador("Jose2",1);
    bandera = true;
    ui->jugadorActual->setText("Jugador 1");
    llenarPropiedades();
    llenarChance();
    llenarChest();
}

MainWindow::~MainWindow(){
    delete ui;
    delete jugador1;
    delete jugador2;
    for(unsigned long i = 0; i < propiedades.size(); i++){
        delete propiedades[i];
    }
    for(unsigned long i = 0; i < tarjetas_chance.size(); i++){
        delete tarjetas_chance[i];
    }
    for(unsigned long i = 0; i < tarjetas_arca.size(); i++){
        delete tarjetas_arca[i];
    }
}


void MainWindow::on_pushButton_clicked() {
    ui->pushButton->setEnabled(false);
    for(int i = 0; i < propiedades.size(); i++){
        propiedades[i]->establecerRenta();
    }
    int low = 1;
    int high = 6;
    int one;
    int two;
    one = low + rand() / (RAND_MAX / (high - low + 1) + 1);
    two = low + rand() / (RAND_MAX / (high - low + 1) + 1);
    cout << one << endl << two << endl;
    int pos = one+two;
    if(one == 1){
        QPixmap foto1(":/dado1.png");
        ui->dice1->setPixmap(foto1);
    }else if(one == 2){
        QPixmap foto1(":/dado2.png");
        ui->dice1->setPixmap(foto1);
    }else if(one == 3){
        QPixmap foto1(":/dado3.png");
        ui->dice1->setPixmap(foto1);
    }else if(one == 4){
        QPixmap foto1(":/dado4.png");
        ui->dice1->setPixmap(foto1);
    }else if(one == 5){
        QPixmap foto1(":/dado5.png");
        ui->dice1->setPixmap(foto1);
    }else if(one == 6){
        QPixmap foto1(":/dado6.png");
        ui->dice1->setPixmap(foto1);
    }

    if(two == 1){
        QPixmap foto2(":/dado1.png");
        ui->dice2->setPixmap(foto2);
    }else if(two == 2){
        QPixmap foto2(":/dado2.png");
        ui->dice2->setPixmap(foto2);
    }else if(two == 3){
        QPixmap foto2(":/dado3.png");
        ui->dice2->setPixmap(foto2);
    }else if(two == 4){
        QPixmap foto2(":/dado4.png");
        ui->dice2->setPixmap(foto2);
    }else if(two == 5){
        QPixmap foto2(":/dado5.png");
        ui->dice2->setPixmap(foto2);
    }else if(two == 6){
        QPixmap foto2(":/dado6.png");
        ui->dice2->setPixmap(foto2);
    }

    if(bandera){
        jugador1->avanzar(pos);
        detectarPosicion(jugador1->getPosicion());
        for(unsigned long i = 0; i < propiedades.size(); i++){
            if(jugador1->getPosicion() == propiedades[i]->getPosicion()){
                ui->icon1->setGeometry(propiedades[i]->getX(),propiedades[i]->getY(),30,30);
                ui->labelFoto->setPixmap(propiedades[i]->getFoto());
                if(propiedades[i]->isHipotectado() && propiedades[i]->isPlayerOneOwner()){
                    QMessageBox m1;
                    m1.setText("Esta propiedad esta hipotecada por usted!");
                    m1.exec();
                    bandera = false;
                    QMessageBox m;
                    m.setText("Termino su turno Jugador 1");
                    m.exec();
                    ui->jugadorActual->setText("Jugador 2");
                    ui->comprarJugador1->setEnabled(false);
                    ui->propiedadesJugador1->setEnabled(false);
                    ui->subastar1->setEnabled(false);
                    ui->construir1->setEnabled(false);
                    ui->construir2->setEnabled(true);
                    ui->hipotecar1->setEnabled(false);
                    ui->hipotecar2->setEnabled(true);
                    ui->propiedadesJugador2->setEnabled(true);
                    ui->pushButton->setEnabled(true);
                } else if(propiedades[i]->isHipotectado() && propiedades[i]->isPlayerOneOwner()){
                    QMessageBox m1;
                    m1.setText("Esta propiedad esta hipotecada por el Jugador 2!");
                    m1.exec();
                    bandera = false;
                    QMessageBox m;
                    m.setText("Termino su turno Jugador 1");
                    m.exec();
                    ui->jugadorActual->setText("Jugador 2");
                    ui->comprarJugador1->setEnabled(false);
                    ui->propiedadesJugador1->setEnabled(false);
                    ui->subastar1->setEnabled(false);
                    ui->construir1->setEnabled(false);
                    ui->construir2->setEnabled(true);
                    ui->hipotecar1->setEnabled(false);
                    ui->hipotecar2->setEnabled(true);
                    ui->propiedadesJugador2->setEnabled(true);
                    ui->pushButton->setEnabled(true);
                }
                if(propiedades[i]->isEnVenta()){
                    ui->comprarJugador1->setEnabled(true);
                    ui->subastar1->setEnabled(true);
                } else if(!propiedades[i]->isEnVenta() && propiedades[i]->isPlayerTwoOwner()){
                    QMessageBox m;
                    if(typeid(*propiedades[i]) == typeid(PropiedadNormal)){
                        PropiedadNormal* property = dynamic_cast<PropiedadNormal*> (propiedades[i]);
                        m.setText("Tiene que pagar la renta al jugador 2! Valor: $"+QString::number(property->getRenta()));
                        m.exec();
                        ui->pagar1->setEnabled(true);
                    }
                    if(typeid(*propiedades[i]) == typeid(Railroad)){
                        Railroad* ferro = dynamic_cast<Railroad*>(propiedades[i]);
                        m.setText("Tiene que pagar la renta al jugador 2! Valor: $"+QString::number(ferro->getRenta()));
                        m.exec();
                        ui->pagar1->setEnabled(true);
                    }
                    if(typeid(*propiedades[i]) == typeid(Servicio)){
                        Servicio* service = dynamic_cast<Servicio*>(propiedades[i]);
                        m.setText("Tiene que pagar la renta al jugador 2! Valor: $"+QString::number(service->getRenta()));
                        m.exec();
                        ui->pagar1->setEnabled(true);
                    }
                }
            }
        }
    } else if(!bandera){
        jugador2->avanzar(pos);
        detectarPosicion(jugador2->getPosicion());
        for(unsigned long i = 0; i < propiedades.size(); i++){
            if(jugador2->getPosicion() == propiedades[i]->getPosicion()){
                ui->icon2->setGeometry(propiedades[i]->getX(),propiedades[i]->getY(),30,30);
                ui->labelFoto2->setPixmap(propiedades[i]->getFoto());
                if(propiedades[i]->isHipotectado() && propiedades[i]->isPlayerOneOwner()){
                    QMessageBox m1;
                    m1.setText("Esta propiedad esta hipotecada por el Jugador 1!");
                    m1.exec();
                    bandera = true;
                    QMessageBox m;
                    m.setText("Termino su turno Jugador 2");
                    m.exec();
                    ui->jugadorActual->setText("Jugador 1");
                    ui->comprarJugador2->setEnabled(false);
                    ui->propiedadesJugador2->setEnabled(false);
                    ui->subastar2->setEnabled(false);
                    ui->construir2->setEnabled(false);
                    ui->construir1->setEnabled(true);
                    ui->hipotecar2->setEnabled(false);
                    ui->hipotecar1->setEnabled(true);
                    ui->propiedadesJugador1->setEnabled(true);
                    ui->pushButton->setEnabled(true);
                } else if(propiedades[i]->isHipotectado() && propiedades[i]->isPlayerOneOwner()){
                    QMessageBox m1;
                    m1.setText("Esta propiedad esta hipotecada por usted!");
                    m1.exec();
                    bandera = false;
                    QMessageBox m;
                    m.setText("Termino su turno Jugador 2");
                    m.exec();
                    ui->jugadorActual->setText("Jugador 1");
                    ui->comprarJugador2->setEnabled(false);
                    ui->propiedadesJugador2->setEnabled(false);
                    ui->subastar2->setEnabled(false);
                    ui->construir2->setEnabled(false);
                    ui->construir1->setEnabled(true);
                    ui->hipotecar2->setEnabled(false);
                    ui->hipotecar1->setEnabled(true);
                    ui->propiedadesJugador1->setEnabled(true);
                    ui->pushButton->setEnabled(true);
                }
                if(propiedades[i]->isEnVenta()){
                    ui->comprarJugador2->setEnabled(true);
                    ui->subastar2->setEnabled(true);
                } else if(!propiedades[i]->isEnVenta() && propiedades[i]->isPlayerOneOwner()){
                    QMessageBox m;
                    if(typeid(*propiedades[i]) == typeid(PropiedadNormal)){
                        PropiedadNormal* property = dynamic_cast<PropiedadNormal*> (propiedades[i]);
                        m.setText("Tiene que pagar la renta al jugador 1! Valor: $"+QString::number(property->getRenta()));
                        m.exec();
                        ui->pagar2->setEnabled(true);
                    }
                    if(typeid(*propiedades[i]) == typeid(Railroad)){
                        Railroad* ferro = dynamic_cast<Railroad*>(propiedades[i]);
                        m.setText("Tiene que pagar la renta al jugador 1! Valor: $"+QString::number(ferro->getRenta()));
                        m.exec();
                        ui->pagar2->setEnabled(true);
                    }
                    if(typeid(*propiedades[i]) == typeid(Servicio)){
                        Servicio* service = dynamic_cast<Servicio*>(propiedades[i]);
                        m.setText("Tiene que pagar la renta al jugador 1! Valor: $"+QString::number(service->getRenta()));
                        m.exec();
                        ui->pagar2->setEnabled(true);
                    }
                }
            }
        }
    }
}

void MainWindow::on_comprarJugador1_clicked()
{
    for(unsigned long i = 0; i < propiedades.size(); i++){
        if(jugador1->getPosicion() == propiedades[i]->getPosicion() && propiedades[i]->isEnVenta()){
            if(jugador1->getDinero() < propiedades[i]->getPrecio()){
                QMessageBox m1;
                m1.setText("No tiene suficiente dinero para comprar esta propiedad! Hipoteque una de las suyas!");
                m1.exec();
            } else {
                jugador1->comprar(propiedades[i]->getPrecio());
                QMessageBox buy;
                buy.setText("Usted compro la siguiente propiedad: "+propiedades[i]->getNombre());
                buy.exec();
                propiedadesJugador1.push_back(propiedades[i]);
                propiedades[i]->setEnVenta(false);
                propiedades[i]->setPlayerOneOwner(true);
                bandera = false;
                QMessageBox m;
                m.setText("Termino su turno Jugador 1");
                m.exec();
                ui->jugadorActual->setText("Jugador 2");
                ui->comprarJugador1->setEnabled(false);
                ui->propiedadesJugador1->setEnabled(false);
                ui->subastar1->setEnabled(false);
                ui->construir1->setEnabled(false);
                ui->construir2->setEnabled(true);
                ui->hipotecar1->setEnabled(false);
                ui->hipotecar2->setEnabled(true);
                ui->propiedadesJugador2->setEnabled(true);
                ui->pushButton->setEnabled(true);
                ui->dinero1_LCD->display(jugador1->getDinero());
                break;
            }
        }
    }
}
void MainWindow::llenarPropiedades(){

    propiedades.push_back(new PropiedadNormal("Avenida Mediterraneo",2,false,true,30,60,530,520,false,false,"Cafe",2,10,30,90,160,250,50,50,0,false));
    propiedades.push_back(new PropiedadNormal("Avenida Baltica",4,false,true,30,60,400,520,false,false,"Cafe",4,20,60,180,320,540,50,50,0,false));
    propiedades.push_back(new Railroad("Ferrocarril Reading",6,false,true,100,200,310,520,false,false,25));
    propiedades.push_back(new PropiedadNormal("Avenida Oriental",7,false,true,50,100,260,520,false,false,"Celste",6,30,90,270,400,550,50,50,0,false));
    propiedades.push_back(new PropiedadNormal("Avenida Vermont",9,false,true,50,100,160,520,false,false,"Celeste",6,30,90,270,400,550,50,50,0,false));
    propiedades.push_back(new PropiedadNormal("Avenida Connecticut",10,false,true,60,120,100,520,false,false,"Celeste",8,40,100,300,450,600,50,50,0,false));
    propiedades.push_back(new PropiedadNormal("Plaza San Carlos",12,false,true,70,140,30,460,false,false,"Rosado",10,50,150,450,625,750,100,100,0,false));
    propiedades.push_back(new Servicio("Compañia Electrica",13,false,true,75,150,30,410,false,false,0));
    propiedades.push_back(new PropiedadNormal("Avenida Status",14,false,true,70,140,30,360,false,false,"Rosado",10,50,150,450,625,700,100,100,0,false));
    propiedades.push_back(new PropiedadNormal("Avenida Virginia",15,false,true,80,160,30,320,false,false,"Rosado",12,60,180,500,700,900,100,100,0,false));
    propiedades.push_back(new Railroad("Ferrocarril Pennsylvania",16,false,true,100,200,30,270,false,false,25));
    propiedades.push_back(new PropiedadNormal("Plaza St. James",17,false,true,90,180,30,220,false,false,"Naranja",14,70,200,550,750,950,100,100,0,false));
    propiedades.push_back(new PropiedadNormal("Avenida Tennessee",19,false,true,90,180,30,130,false,false,"Naranja",14,70,200,550,750,950,100,100,0,false));
    propiedades.push_back(new PropiedadNormal("Avenida Nueva York",20,false,true,100,200,30,80,false,false,"Narnja",16,80,220,600,800,1000,100,100,0,false));
    propiedades.push_back(new PropiedadNormal("Avenida Kentucky",22,false,true,110,220,100,20,false,false,"Rojo",18,90,250,700,875,1050,150,150,0,false));
    propiedades.push_back(new PropiedadNormal("Avenida Indiana",24,false,true,110,220,210,20,false,false,"Rojo",18,90,250,700,875,1050,150,150,0,false));
    propiedades.push_back(new PropiedadNormal("Avenida Illinois",25,false,true,120,240,260,20,false,false,"Rojo",20,100,300,750,925,1100,150,150,0,false));
    propiedades.push_back(new Railroad("Ferrocarril B & O",26,false,true,100,200,310,20,false,false,25));
    propiedades.push_back(new PropiedadNormal("Avenida Atlantico",27,false,true,130,260,360,20,false,false,"Amarillo",22,110,330,800,975,1150,150,150,0,false));
    propiedades.push_back(new PropiedadNormal("Avenida Ventnor",28,false,true,130,260,400,20,false,false,"Amarillo",22,110,330,800,975,1150,150,150,0,false));
    propiedades.push_back(new Servicio("Compañia de Agua",29,false,true,75,150,460,20,false,false,0));
    propiedades.push_back(new PropiedadNormal("Jardines Marvin",30,false,true,140,280,530,20,false,false,"Amarillo",24,120,360,850,1025,1200,150,150,0,false));
    propiedades.push_back(new PropiedadNormal("Avenida Pacifico",32,false,true,150,300,620,80,false,false,"Verde",26,130,390,900,1100,1275,150,150,0,false));
    propiedades.push_back(new PropiedadNormal("Avenida Carolina del Norte",33,false,true,150,300,620,130,false,false,"Verde",26,130,390,900,1100,1275,200,200,0,false));
    propiedades.push_back(new PropiedadNormal("Avenida Pennsylvania",35,false,true,160,320,620,220,false,false,"Verde",28,150,450,1000,1200,1400,200,200,0,false));
    propiedades.push_back(new Railroad("Ferrocarril Via Rapida",36,false,true,100,200,620,270,false,false,25));
    propiedades.push_back(new PropiedadNormal("Plaza Park",38,false,true,175,350,620,360,false,false,"Azul",35,175,500,1100,1300,1500,200,200,0,false));
    propiedades.push_back(new PropiedadNormal("El Muelle",40,false,true,200,400,620,460,false,false,"Azul",50,200,600,1400,1700,2000,200,200,0,false));

    QPixmap foto1(":/Mediterranean Avenue.png");
    QPixmap foto2(":/Baltic Avenue.png");
    QPixmap foto3(":/Oriental Avenue.png");
    QPixmap foto4(":/Vermont Avenue.png");
    QPixmap foto5(":/Connecticut Avenue.png");
    QPixmap foto6(":/St. Charles Place.png");
    QPixmap foto7(":/States Avenue.png");
    QPixmap foto8(":/Virginia Avenue.png");
    QPixmap foto9(":/St. James Place.png");
    QPixmap foto10(":/Tennesse Avenue.png");
    QPixmap foto11(":/New York Avenue.png");
    QPixmap foto12(":/Kentucky Avenue.png");
    QPixmap foto13(":/Indiana Avenue.png");
    QPixmap foto14(":/Illinois Avenue.png");
    QPixmap foto15(":/Atlantic Avenue.png");
    QPixmap foto16(":/Ventnor Avenue.png");
    QPixmap foto17(":/Marvin Gardens.png");
    QPixmap foto18(":/Pacific Avenue.png");
    QPixmap foto19(":/North Carolina Avenue.png");
    QPixmap foto20(":/Pensylvania Avenue.png");
    QPixmap foto21(":/Park Place.png");
    QPixmap foto22(":/Boardwalk.png");
    QPixmap foto23(":Electric Company.jpg");
    QPixmap foto24(":/Water Works.jpg");
    QPixmap foto25(":/Reading Railroad.png");
    QPixmap foto26(":/Pennsylvania Railroad.png");
    QPixmap foto27(":/B & O Railroad.png");
    QPixmap foto28(":/Short Line Railroad");

    propiedades[0]->setFoto(foto1);
    propiedades[1]->setFoto(foto2);
    propiedades[2]->setFoto(foto25);
    propiedades[3]->setFoto(foto3);
    propiedades[4]->setFoto(foto4);
    propiedades[5]->setFoto(foto5);
    propiedades[6]->setFoto(foto6);
    propiedades[7]->setFoto(foto23);
    propiedades[8]->setFoto(foto7);
    propiedades[9]->setFoto(foto8);
    propiedades[10]->setFoto(foto26);
    propiedades[11]->setFoto(foto9);
    propiedades[12]->setFoto(foto10);
    propiedades[13]->setFoto(foto11);
    propiedades[14]->setFoto(foto12);
    propiedades[15]->setFoto(foto13);
    propiedades[16]->setFoto(foto14);
    propiedades[17]->setFoto(foto27);
    propiedades[18]->setFoto(foto15);
    propiedades[19]->setFoto(foto16);
    propiedades[20]->setFoto(foto24);
    propiedades[21]->setFoto(foto17);
    propiedades[22]->setFoto(foto18);
    propiedades[23]->setFoto(foto19);
    propiedades[24]->setFoto(foto20);
    propiedades[25]->setFoto(foto28);
    propiedades[26]->setFoto(foto21);
    propiedades[27]->setFoto(foto22);
}

void MainWindow::detectarPosicion(int position){
    if(bandera){
        if(position == 1){
            ui->icon1->setGeometry(620,520,30,30);
            jugador1->recolectar(200);
            ui->dinero1_LCD->display(jugador1->getDinero());
            ui->pushButton->setEnabled(true);
            bandera = false;
            ui->propiedadesJugador1->setEnabled(false);
            ui->propiedadesJugador2->setEnabled(true);
            ui->construir1->setEnabled(false);
            ui->construir2->setEnabled(true);
            ui->hipotecar1->setEnabled(false);
            ui->hipotecar2->setEnabled(true);
            QMessageBox m;
            m.setText("Termino su turno Jugador 1");
        }
        if(position == 5){
            ui->icon1->setGeometry(360,520,30,30);
            QMessageBox m;
            m.setText("Le toca pagar un impuesto sobre ingresos!");
            m.exec();
            jugador1->pagar(200);
            ui->dinero1_LCD->display(jugador1->getDinero());
            ui->pushButton->setEnabled(true);
            bandera = false;
            ui->propiedadesJugador1->setEnabled(false);
            ui->propiedadesJugador2->setEnabled(true);
            ui->construir1->setEnabled(false);
            ui->construir2->setEnabled(true);
            ui->hipotecar1->setEnabled(false);
            ui->hipotecar2->setEnabled(true);
            QMessageBox m2;
            m2.setText("Termino su turno Jugador 1");
            m2.exec();
        }
        if(position == 11){
            ui->icon1->setGeometry(30,520,30,30);
            QMessageBox m;
            m.setText("Usted cayo en la carcel pero solo de visita!");
            m.exec();
            ui->pushButton->setEnabled(true);
            bandera = false;
            ui->propiedadesJugador1->setEnabled(false);
            ui->propiedadesJugador2->setEnabled(true);
            ui->construir1->setEnabled(false);
            ui->construir2->setEnabled(true);
            ui->hipotecar1->setEnabled(false);
            ui->hipotecar2->setEnabled(true);
            QMessageBox m2;
            m2.setText("Termino su turno Jugador 1");
            m2.exec();
        }
        if(position == 21){
            ui->icon1->setGeometry(30,20,30,30);
            QMessageBox m;
            m.setText("PARADA LIBRE!");
            m.exec();
            ui->pushButton->setEnabled(true);
            bandera = false;
            ui->propiedadesJugador1->setEnabled(false);
            ui->propiedadesJugador2->setEnabled(true);
            ui->construir1->setEnabled(false);
            ui->construir2->setEnabled(true);
            ui->hipotecar1->setEnabled(false);
            ui->hipotecar2->setEnabled(true);
            QMessageBox m2;
            m2.setText("Termino su turno Jugador 1");
            m2.exec();
        }
        if(position == 31){
            ui->icon1->setGeometry(620,20,30,30);
            QMessageBox m;
            m.setText("Vayase directamente a la carcel! Pierde tres turnos");
            m.exec();
            jugador1->setPosicion(11);
            ui->pushButton->setEnabled(true);
            jugador1->setEnCarcel(true);
            bandera = false;
            ui->propiedadesJugador1->setEnabled(false);
            ui->propiedadesJugador2->setEnabled(true);
            ui->construir1->setEnabled(false);
            ui->construir2->setEnabled(true);
            ui->hipotecar1->setEnabled(false);
            ui->hipotecar2->setEnabled(true);
            QMessageBox m2;
            m2.setText("Termino su turno Jugador 1");
            m2.exec();
            ui->icon1->setGeometry(30,520,30,30);
        }
        if(position == 39){
            ui->icon1->setGeometry(620,410,30,30);
            QMessageBox m;
            m.setText("Debe pagar un impuesto sobre lujos");
            m.exec();
            jugador1->pagar(75);
            ui->dinero1_LCD->display(jugador1->getDinero());
            ui->pushButton->setEnabled(true);
            ui->propiedadesJugador1->setEnabled(false);
            ui->propiedadesJugador2->setEnabled(true);
            ui->construir1->setEnabled(false);
            ui->construir2->setEnabled(true);
            ui->hipotecar1->setEnabled(false);
            ui->hipotecar2->setEnabled(true);
            bandera = false;
            QMessageBox m2;
            m2.setText("Termino su turno Jugador 1");
            m2.exec();
        }
        if(position == 8 || position == 23 || position == 37){
            QPixmap p(":/chance.gif");
            ui->labelFoto->setPixmap(p);
            if(position == 8){
                ui->icon1->setGeometry(210,520,30,30);
            } else if (position == 23){
                ui->icon1->setGeometry(160,20,30,30);
            } else if(position == 37){
                ui->icon1->setGeometry(620,320,30,30);
            }

            int low = 0;
            int high = 15;
            int num = low + rand() / (RAND_MAX / (high - low + 1) + 1);
            cout<<num<<endl<<endl;
            const QString info = tarjetas_chance[num]->getDescripcion();
            ChanceDialog m(this, info);
            m.setModal(true);
            m.exec();
            accionesChance(tarjetas_chance[num]->getCode());
        }
        if(position == 3 || position == 18|| position == 34){
            QPixmap p(":/chest.gif");
            ui->labelFoto->setPixmap(p);
            if(position == 3){
                ui->icon1->setGeometry(460,520,30,30);
            } else if (position == 18){
                ui->icon1->setGeometry(30,180,30,30);
            } else if(position == 34){
                ui->icon1->setGeometry(620,180,30,30);
            }
            int low = 0;
            int high = 15;
            int num2 = low + rand() / (RAND_MAX / (high - low + 1) + 1);
            cout<<num2<<endl<<endl;
            const QString n = tarjetas_arca[num2]->getDescripcion();
            CommunityChestDialog m(this,n);
            m.setModal(true);
            m.exec();
            accionesChest(tarjetas_arca[num2]->getCodigo());
        }
    } else {
        if(position == 1){
            ui->icon2->setGeometry(620,520,30,30);
            jugador2->recolectar(200);
            ui->dinero2_LCD->display(jugador2->getDinero());
            ui->pushButton->setEnabled(true);
            ui->propiedadesJugador1->setEnabled(true);
            ui->propiedadesJugador2->setEnabled(false);
            ui->construir1->setEnabled(true);
            ui->construir2->setEnabled(false);
            ui->hipotecar1->setEnabled(true);
            ui->hipotecar2->setEnabled(false);
            QMessageBox m;
            m.setText("Termino su turno Jugador 2");
            m.exec();
            bandera = true;
        }
        if(position == 5){
            ui->icon2->setGeometry(360,520,30,30);
            QMessageBox m;
            m.setText("Debe pagar un impuesto sobre ingresos!");
            m.exec();
            jugador2->pagar(200);
            ui->dinero2_LCD->display(jugador2->getDinero());
            ui->pushButton->setEnabled(true);
            ui->propiedadesJugador1->setEnabled(true);
            ui->propiedadesJugador2->setEnabled(false);
            ui->construir1->setEnabled(true);
            ui->construir2->setEnabled(false);
            ui->hipotecar1->setEnabled(true);
            ui->hipotecar2->setEnabled(false);
            bandera = true;
            QMessageBox m1;
            m1.setText("Termino su turno Jugador 2");
            m1.exec();
        }
        if(position == 11){
            ui->icon2->setGeometry(30,520,30,30);
            QMessageBox m;
            m.setText("Cayo en la carcel pero solo de visita!");
            m.exec();
            ui->pushButton->setEnabled(true);
            ui->propiedadesJugador1->setEnabled(true);
            ui->propiedadesJugador2->setEnabled(false);
            ui->construir1->setEnabled(true);
            ui->construir2->setEnabled(false);
            ui->hipotecar1->setEnabled(true);
            ui->hipotecar2->setEnabled(false);
            bandera = true;
            QMessageBox m1;
            m1.setText("Termino su turno Jugador 2");
            m1.exec();
        }
        if(position == 21){
            ui->icon2->setGeometry(30,20,30,30);
            QMessageBox m;
            m.setText("PARADA LIBRE!");
            m.exec();
            ui->pushButton->setEnabled(true);
            ui->propiedadesJugador1->setEnabled(true);
            ui->propiedadesJugador2->setEnabled(false);
            ui->construir1->setEnabled(true);
            ui->construir2->setEnabled(false);
            ui->hipotecar1->setEnabled(true);
            ui->hipotecar2->setEnabled(false);
            bandera = true;
            QMessageBox m1;
            m1.setText("Termino su turno Jugador 2");
            m1.exec();
        }
        if(position == 31){
            ui->icon2->setGeometry(620,20,30,30);
            QMessageBox m;
            m.setText("Vayase directamente a la Carcel! Pierde tres turnos");
            m.exec();
            jugador2->setPosicion(11);
            ui->pushButton->setEnabled(true);
            bandera = true;
            ui->propiedadesJugador1->setEnabled(true);
            ui->propiedadesJugador2->setEnabled(false);
            ui->construir1->setEnabled(true);
            ui->construir2->setEnabled(false);
            ui->hipotecar1->setEnabled(true);
            ui->hipotecar2->setEnabled(false);
            QMessageBox m1;
            m1.setText("Termino su turno Jugador 2");
            m1.exec();
            ui->icon2->setGeometry(30,540,30,30);
        }
        if(position == 39){
            ui->icon2->setGeometry(620,410,30,30);
            QMessageBox m;
            m.setText("Debe pagar un impuesto sobre Lujos! 75$");
            m.exec();
            jugador2->pagar(75);
            ui->dinero2_LCD->display(jugador2->getDinero());
            ui->pushButton->setEnabled(true);
            ui->propiedadesJugador1->setEnabled(true);
            ui->propiedadesJugador2->setEnabled(false);
            ui->construir1->setEnabled(true);
            ui->construir2->setEnabled(false);
            ui->hipotecar1->setEnabled(true);
            ui->hipotecar2->setEnabled(false);
            bandera = true;
            QMessageBox m1;
            m1.setText("Termino su turno Jugador 2");
            m1.exec();
        }

        if(position == 8 || position == 23 || position == 37){
            QPixmap p(":/chance.gif");
            ui->labelFoto2->setPixmap(p);
            if(position == 8){
                ui->icon2->setGeometry(210,520,30,30);
            } else if (position == 23){
                ui->icon2->setGeometry(160,20,30,30);
            } else if(position == 37){
                ui->icon2->setGeometry(620,320,30,30);
            }
            int low = 0;
            int high = 15;
            int num3 = low + rand() / (RAND_MAX / (high - low + 1) + 1);
            cout<<num3<<endl<<endl;
            const QString info2 = tarjetas_chance[num3]->getDescripcion();
            ChanceDialog m2(this, info2);
            m2.setModal(true);
            m2.exec();
            accionesChance(tarjetas_chance[num3]->getCode());
        }
    }
    if(position == 3 || position == 18|| position == 34){
        QPixmap p(":/chest.gif");
        ui->labelFoto->setPixmap(p);
        if(position == 3){
            ui->icon2->setGeometry(460,520,30,30);
        } else if (position == 18){
            ui->icon2->setGeometry(30,180,30,30);
        } else if(position == 34){
            ui->icon2->setGeometry(620,180,30,30);
        }
        int low = 0;
        int high = 15;
        int num4 = low + rand() / (RAND_MAX / (high - low + 1) + 1);
        cout<<num4<<endl<<endl;
        const QString n = tarjetas_arca[num4]->getDescripcion();
        CommunityChestDialog m(this,n);
        m.setModal(true);
        m.exec();
        accionesChest(tarjetas_arca[num4]->getCodigo());
    }
}

void MainWindow::llenarChance(){
    tarjetas_chance.push_back(new Chance(1,"AVANCE AL FERROCARRIL MAS CERCANO. Si esta a LA VENTA, puede comprarselo al banco. Si esta VENDIDO, debera pagar al dueñoel doble de la renta marcada en la tarjeta."));
    tarjetas_chance.push_back(new Chance(2,"AVANCE AL FERROCARRIL MAS CERCANO. Si esta a LA VENTA, puede comprarselo al banco. Si esta VENDIDO, debera pagar al dueñoel doble de la renta marcada en la tarjeta."));
    tarjetas_chance.push_back(new Chance(3,"PAGUE MULTA POR EXCESO DE VELOCIDAD $15."));
    tarjetas_chance.push_back(new Chance(4,"RETROCEDA TRES ESPACIOS"));
    tarjetas_chance.push_back(new Chance(5,"LE HAN ELEGIDO PRESIDENTE DE LA MESA DIRECTIVA. PAGUE $50 A CADA JUGADOR"));
    tarjetas_chance.push_back(new Chance(6,"AVANCE A PLAZA ST.JAMES. SI PASA POR LA SALIDA COBRE $200"));
    tarjetas_chance.push_back(new Chance(7,"SALGA DE LA CARCEL GRATIS. Puede guardar esta tarjeta hasta que la necesite o puede negociarla"));
    tarjetas_chance.push_back(new Chance(8,"HACES REPARACIONES EN TODAS SUS PROPIEDADES: POR CADA CASA PAGUE $25, POR CADA HOTEL PAGUE $100"));
    tarjetas_chance.push_back(new Chance(9,"EL BANCO LE PAGA UN DIVIDENDO POR $50"));
    tarjetas_chance.push_back(new Chance(10,"AVANCE A LA SALIDA(COBRE $200)"));
    tarjetas_chance.push_back(new Chance(11,"VAYASE DIRECTAMENTE A LA CARCEL SIN PASAR POR LA SALIDA Y SIN COBRAR $200"));
    tarjetas_chance.push_back(new Chance(12,"AVANCE AL SERVICIO MAS CERCANO. Si esta a LA VENTA, puede comprarselo al Banco. Si esta VENDIDO, debera pagar al dueño el doble de la renta marcada en la tarjeta"));
    tarjetas_chance.push_back(new Chance(13,"AVANCE A AVENIDA ILLINOIS. SI PASAS POR LA SALIDA COBRE $200"));
    tarjetas_chance.push_back(new Chance(14,"LIQUIDA SU PRESTAMO PARA CONSTRUCCION. COBRE $150"));
    tarjetas_chance.push_back(new Chance(15,"HACE UN VIAJE AL FERROCARRIL READING. SI PASA POR LA SALIDA COBRE $200"));
    tarjetas_chance.push_back(new Chance(16,"AVANCE A EL MUELLE"));
}

void MainWindow::llenarChest(){
    tarjetas_arca.push_back(new CommunityChest('A',"GANO EL SEGUNDO PREMIO EN UN CONCURSO DE BELLEZA. COBRE $10."));
    tarjetas_arca.push_back(new CommunityChest('B',"SALGA DE LA CARCEL GRATIS. Puede guardar esta tarjeta hasta que la necesite o puede negociarla."));
    tarjetas_arca.push_back(new CommunityChest('C',"CUOTAS MEDICAS. PAGUE $50"));
    tarjetas_arca.push_back(new CommunityChest('D',"LE PAGAN PRIMA VACACIONAL. COBRE $100"));
    tarjetas_arca.push_back(new CommunityChest('E',"LE PAGAN SEGURO DE VIDA. COBRE $100"));
    tarjetas_arca.push_back(new CommunityChest('F',"PAGUE CUOTAS DE ESCUELA POR $50."));
    tarjetas_arca.push_back(new CommunityChest('G',"DEVOLUCION DE IMPUESTOS. COBRE $20"));
    tarjetas_arca.push_back(new CommunityChest('H',"PAGUE CUOTAS DE HOSPITAL POR $100"));
    tarjetas_arca.push_back(new CommunityChest('I',"VAYASE DIRECTAMENTE A LA CARCEL. SIN PASAR POR LA SALIDA Y SIN COBRAR $200"));
    tarjetas_arca.push_back(new CommunityChest('J',"RECIBE $25 POR SERVICIOS DE ASESORIA"));
    tarjetas_arca.push_back(new CommunityChest('K',"ES SU CUMPLEAÑOS. CADA JUGADOR LE DA $10"));
    tarjetas_arca.push_back(new CommunityChest('L',"HEREDA $100"));
    tarjetas_arca.push_back(new CommunityChest('M',"POR VENTA DE ACCIONES GANE $50"));
    tarjetas_arca.push_back(new CommunityChest('N',"A PAGAR IMPUESTOS POR LA REPARACION DE CALLES: $40 POR CADA CASA, $115 POR CADA HOTEL"));
    tarjetas_arca.push_back(new CommunityChest('O',"AVANCE A LA SALIDA(COBRE $200)"));
    tarjetas_arca.push_back(new CommunityChest('P',"ERROR BANCARIO A SU FAVOR. COBRE $200"));
}

void MainWindow::on_comprarJugador2_clicked()
{  
    if(!bandera){
        for(unsigned long i = 0; i < propiedades.size(); i++){
            if(jugador2->getPosicion() == propiedades[i]->getPosicion() && propiedades[i]->isEnVenta()){
                if(jugador2->getDinero() < propiedades[i]->getPrecio()){
                    QMessageBox m;
                    m.setText("No tiene suficiente dinero para comprar esta propiedad");
                    m.exec();
                } else {
                    jugador2->comprar(propiedades[i]->getPrecio());
                    QMessageBox m;
                    m.setText("Has comprado la propiedad: "+propiedades[i]->getNombre());
                    m.exec();
                    propiedadesJugador2.push_back(propiedades[i]);
                    propiedades[i]->setEnVenta(false);
                    propiedades[i]->setPlayerTwoOwner(true);
                    bandera = true;
                    QMessageBox m1;
                    m1.setText("Termino su Turno Jugador 2");
                    m1.exec();
                    ui->jugadorActual->setText("Jugador 1");
                    ui->comprarJugador2->setEnabled(false);
                    ui->propiedadesJugador2->setEnabled(false);
                    ui->subastar2->setEnabled(false);
                    ui->propiedadesJugador1->setEnabled(true);
                    ui->pushButton->setEnabled(true);
                    ui->construir1->setEnabled(true);
                    ui->construir2->setEnabled(false);
                    ui->hipotecar1->setEnabled(true);
                    ui->hipotecar2->setEnabled(false);
                    ui->dinero2_LCD->display(jugador2->getDinero());
                    break;
                }
            }
        }
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    QFile file;
    file.setFileName("partida.txt");

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;

        QTextStream out(&file);

    //Para el Jugador1
    QString nombre1 = jugador1->getNombre();
    nombre1.toStdString();
    QString money1 = QString::number(jugador1->getDinero());
    money1.toStdString();
    QString position1 = QString::number(jugador1->getPosicion());
    position1.toStdString();

    //Para el jugador2
    QString nombre2 = jugador2->getNombre();
    nombre2.toStdString();
    QString money2 = QString::number(jugador2->getDinero());
    money2.toStdString();
    QString position2 = QString::number(jugador2->getPosicion());
    position2.toStdString();

    out << nombre1<<","<<money1<<","<<position1<<"\n";
    out << nombre2<<","<<money2<<","<<position2<<"\n";
    file.close();
    QMessageBox m;
    m.setText("Partida Guardada Exitosamente");
    m.exec();

    file.close();
}

void MainWindow::accionesChest(char code){
    QMessageBox m;
    int houses = 0;
    int hotels = 0;
    int sub1 = 0;
    int sub2 = 0;
    int total = 0;
    if(bandera){
        switch(code){
        case 'A':
            jugador1->recolectar(10);
            ui->dinero1_LCD->display(jugador1->getDinero());
            ui->propiedadesJugador2->setEnabled(true);
            ui->propiedadesJugador1->setEnabled(false);
            ui->construir1->setEnabled(false);
            ui->construir2->setEnabled(true);
            ui->hipotecar1->setEnabled(false);
            ui->hipotecar2->setEnabled(true);
            ui->pushButton->setEnabled(true);
            bandera = false;
            ui->jugadorActual->setText("Jugador 2");
            m.setText("Termino su turno Jugador 1");
            m.exec();
            break;
        case 'B':
            jugador1->setJailFree(true);
            ui->propiedadesJugador1->setEnabled(false);
            ui->propiedadesJugador2->setEnabled(true);
            ui->construir1->setEnabled(false);
            ui->construir2->setEnabled(true);
            ui->hipotecar1->setEnabled(false);
            ui->hipotecar2->setEnabled(true);
            ui->jugadorActual->setText("Jugador 2");
            m.setText("Termino su turno Jugador 1");
            m.exec();
            bandera = false;
            break;
        case 'C':
            jugador1->pagar(50);
            ui->dinero1_LCD->display(jugador1->getDinero());
            ui->propiedadesJugador2->setEnabled(true);
            ui->propiedadesJugador1->setEnabled(false);
            ui->construir1->setEnabled(false);
            ui->construir2->setEnabled(true);
            ui->hipotecar1->setEnabled(false);
            ui->hipotecar2->setEnabled(true);
            ui->pushButton->setEnabled(true);
            ui->jugadorActual->setText("Jugador 2");
            bandera = false;
            m.setText("Termino su turno Jugador 1");
            m.exec();
            break;
        case 'D':
            jugador1->recolectar(100);
            ui->dinero1_LCD->display(jugador1->getDinero());
            ui->propiedadesJugador2->setEnabled(true);
            ui->propiedadesJugador1->setEnabled(false);
            ui->construir1->setEnabled(false);
            ui->construir2->setEnabled(true);
            ui->hipotecar1->setEnabled(false);
            ui->hipotecar2->setEnabled(true);
            ui->pushButton->setEnabled(true);
            ui->jugadorActual->setText("Jugador 2");
            bandera = false;
            m.setText("Termino su turno Jugador 1");
            m.exec();
            break;
        case 'E':
            jugador1->recolectar(100);
            ui->dinero1_LCD->display(jugador1->getDinero());
            ui->propiedadesJugador2->setEnabled(true);
            ui->propiedadesJugador1->setEnabled(false);
            ui->construir1->setEnabled(false);
            ui->construir2->setEnabled(true);
            ui->hipotecar1->setEnabled(false);
            ui->hipotecar2->setEnabled(true);
            ui->pushButton->setEnabled(true);
            ui->jugadorActual->setText("Jugador 2");
            bandera = false;
            m.setText("Termino su turno Jugador 1");
            m.exec();
            break;
        case 'F':
            jugador1->pagar(50);
            ui->dinero1_LCD->display(jugador1->getDinero());
            ui->propiedadesJugador2->setEnabled(true);
            ui->propiedadesJugador1->setEnabled(false);
            ui->construir1->setEnabled(false);
            ui->construir2->setEnabled(true);
            ui->hipotecar1->setEnabled(false);
            ui->hipotecar2->setEnabled(true);
            ui->pushButton->setEnabled(true);
            ui->jugadorActual->setText("Jugador 2");
            bandera = false;
            m.setText("Termino su turno Jugador 1");
            m.exec();
            break;
        case 'G':
            jugador1->recolectar(20);
            ui->dinero1_LCD->display(jugador1->getDinero());
            ui->propiedadesJugador2->setEnabled(true);
            ui->propiedadesJugador1->setEnabled(false);
            ui->construir1->setEnabled(false);
            ui->construir2->setEnabled(true);
            ui->hipotecar1->setEnabled(false);
            ui->hipotecar2->setEnabled(true);
            ui->pushButton->setEnabled(true);
            ui->jugadorActual->setText("Jugador 2");
            bandera = false;
            m.setText("Termino su turno Jugador 1");
            m.exec();
            break;
        case 'H':
            jugador1->pagar(100);
            ui->dinero1_LCD->display(jugador1->getDinero());
            ui->propiedadesJugador2->setEnabled(true);
            ui->propiedadesJugador1->setEnabled(false);
            ui->construir1->setEnabled(false);
            ui->construir2->setEnabled(true);
            ui->pushButton->setEnabled(true);
            ui->hipotecar1->setEnabled(false);
            ui->hipotecar2->setEnabled(true);
            ui->jugadorActual->setText("Jugador 2");
            bandera = false;
            m.setText("Termino su turno Jugador 1");
            m.exec();
            break;
        case 'I':
            if(jugador1->isJailFree()){
                QMessageBox m2;
                m2.setText("Tiene una Tarjeta para salir de la carcel!");
                m2.exec();
                jugador1->setJailFree(false);
                bandera = false;
                ui->propiedadesJugador1->setEnabled(false);
                ui->propiedadesJugador2->setEnabled(true);
                ui->construir1->setEnabled(false);
                ui->construir2->setEnabled(true);
                ui->hipotecar1->setEnabled(false);
                ui->hipotecar2->setEnabled(true);
                ui->pushButton->setEnabled(true);
                ui->jugadorActual->setText("Jugador 2");
                m.setText("Termino su turno Jugador 1");
                m.exec();
            }else{
                jugador1->setEnCarcel(true);
                jugador1->setPosicion(11);
                ui->icon1->setGeometry(30,520,30,30);
                bandera = false;
                ui->propiedadesJugador1->setEnabled(false);
                ui->propiedadesJugador2->setEnabled(true);
                ui->construir1->setEnabled(false);
                ui->construir2->setEnabled(true);
                ui->hipotecar1->setEnabled(false);
                ui->hipotecar2->setEnabled(true);
                ui->pushButton->setEnabled(true);
                ui->jugadorActual->setText("Jugador 2");
                m.setText("Termino su turno Jugador 1");
                m.exec();
            }
            break;
        case 'J':
            jugador1->recolectar(25);
            ui->dinero1_LCD->display(jugador1->getDinero());
            ui->propiedadesJugador2->setEnabled(true);
            ui->propiedadesJugador1->setEnabled(false);
            ui->construir1->setEnabled(false);
            ui->construir2->setEnabled(true);
            ui->hipotecar1->setEnabled(false);
            ui->hipotecar2->setEnabled(true);
            ui->pushButton->setEnabled(true);
            ui->jugadorActual->setText("Jugador 2");
            bandera = false;
            m.setText("Termino su turno Jugador 1");
            m.exec();
            break;
        case 'K':
            jugador1->recolectar(10);
            ui->dinero1_LCD->display(jugador1->getDinero());
            ui->propiedadesJugador2->setEnabled(true);
            ui->propiedadesJugador1->setEnabled(false);
            ui->construir1->setEnabled(false);
            ui->construir2->setEnabled(true);
            ui->hipotecar1->setEnabled(false);
            ui->hipotecar2->setEnabled(true);
            ui->pushButton->setEnabled(true);
            ui->jugadorActual->setText("Jugador 2");
            bandera = false;
            m.setText("Termino su turno Jugador 1");
            m.exec();
            break;
        case 'L':
            jugador1->recolectar(100);
            ui->dinero1_LCD->display(jugador1->getDinero());
            ui->propiedadesJugador2->setEnabled(true);
            ui->propiedadesJugador1->setEnabled(false);
            ui->construir1->setEnabled(false);
            ui->construir2->setEnabled(true);
            ui->hipotecar1->setEnabled(false);
            ui->hipotecar2->setEnabled(true);
            ui->pushButton->setEnabled(true);
            ui->jugadorActual->setText("Jugador 2");
            bandera = false;
            m.setText("Termino su turno Jugador 1");
            m.exec();
            break;
        case 'M':
            jugador1->recolectar(50);
            ui->dinero1_LCD->display(jugador1->getDinero());
            ui->propiedadesJugador2->setEnabled(true);
            ui->propiedadesJugador1->setEnabled(false);
            ui->construir1->setEnabled(false);
            ui->construir2->setEnabled(true);
            ui->hipotecar1->setEnabled(false);
            ui->hipotecar2->setEnabled(true);
            ui->pushButton->setEnabled(true);
            ui->jugadorActual->setText("Jugador 2");
            bandera = false;
            m.setText("Termino su turno Jugador 1");
            m.exec();
            break;
        case 'N':
            for(int i = 0; i < propiedades.size(); i++){
                if(typeid(*propiedades[i]) == typeid(PropiedadNormal)){
                    PropiedadNormal* prop = dynamic_cast<PropiedadNormal*>(propiedades[i]);
                    houses += prop->getTotalCasitas();
                    if(prop->hasHotel()){
                        hotels++;
                    }
                }
            }
            sub1 = houses * 25;
            sub2 = hotels * 100;
            total = sub1+sub2;
            jugador1->pagar(total);
            ui->dinero1_LCD->display(jugador1->getDinero());
            bandera = false;
            ui->propiedadesJugador1->setEnabled(false);
            ui->propiedadesJugador2->setEnabled(true);
            ui->construir1->setEnabled(false);
            ui->construir2->setEnabled(true);
            ui->hipotecar1->setEnabled(false);
            ui->hipotecar2->setEnabled(true);
            ui->pushButton->setEnabled(true);
            ui->jugadorActual->setText("Jugador 2");
            m.setText("Termino su turno Jugador 1");
            m.exec();
            break;
        case 'O':
            jugador1->setPosicion(1);
            jugador1->recolectar(200);
            ui->dinero1_LCD->display(jugador1->getDinero());
            ui->icon1->setGeometry(620,520,30,30);
            bandera = false;
            ui->propiedadesJugador2->setEnabled(true);
            ui->propiedadesJugador1->setEnabled(false);
            ui->construir1->setEnabled(false);
            ui->construir2->setEnabled(true);
            ui->hipotecar1->setEnabled(false);
            ui->hipotecar2->setEnabled(true);
            ui->pushButton->setEnabled(true);
            ui->jugadorActual->setText("Jugador 2");
            break;
            m.setText("Termino su turno Jugador 1");
            m.exec();
        case 'P':
            jugador1->recolectar(200);
            ui->dinero1_LCD->display(jugador1->getDinero());
            ui->propiedadesJugador2->setEnabled(true);
            ui->propiedadesJugador1->setEnabled(false);
            ui->construir1->setEnabled(false);
            ui->construir2->setEnabled(true);
            ui->hipotecar1->setEnabled(false);
            ui->hipotecar2->setEnabled(true);
            ui->pushButton->setEnabled(true);
            ui->jugadorActual->setText("Jugador 2");
            bandera = false;
            m.setText("Termino su turno Jugador 1");
            m.exec();
            break;
        }
    } else {
        switch(code){
        case 'A':
            jugador2->recolectar(10);
            ui->dinero2_LCD->display(jugador2->getDinero());
            ui->propiedadesJugador1->setEnabled(true);
            ui->propiedadesJugador2->setEnabled(false);
            ui->construir1->setEnabled(true);
            ui->construir2->setEnabled(false);
            ui->hipotecar1->setEnabled(true);
            ui->hipotecar2->setEnabled(false);
            ui->pushButton->setEnabled(true);
            bandera = true;
            ui->jugadorActual->setText("Jugador 1");
            m.setText("Termino su turno Jugador 2");
            m.exec();
            break;
        case 'B':
            jugador1->setJailFree(true);
            ui->propiedadesJugador2->setEnabled(false);
            ui->propiedadesJugador1->setEnabled(true);
            ui->construir2->setEnabled(false);
            ui->construir1->setEnabled(true);
            ui->hipotecar2->setEnabled(false);
            ui->hipotecar1->setEnabled(true);
            ui->jugadorActual->setText("Jugador 1");
            m.setText("Termino su turno Jugador 2");
            m.exec();
            ui->jugadorActual->setText("Jugador 1");
            bandera = true;
            break;
        case 'C':
            jugador2->pagar(50);
            ui->dinero2_LCD->display(jugador2->getDinero());
            ui->propiedadesJugador1->setEnabled(true);
            ui->propiedadesJugador2->setEnabled(false);
            ui->construir1->setEnabled(true);
            ui->construir2->setEnabled(false);
            ui->hipotecar1->setEnabled(true);
            ui->hipotecar2->setEnabled(false);
            ui->pushButton->setEnabled(true);
            bandera = true;
            ui->jugadorActual->setText("Jugador 1");
            m.setText("Termino su turno Jugador 2");
            m.exec();
            break;
        case 'D':
            jugador2->recolectar(100);
            ui->dinero2_LCD->display(jugador2->getDinero());
            ui->propiedadesJugador1->setEnabled(true);
            ui->propiedadesJugador2->setEnabled(false);
            ui->construir1->setEnabled(true);
            ui->construir2->setEnabled(false);
            ui->hipotecar1->setEnabled(true);
            ui->hipotecar2->setEnabled(false);
            ui->pushButton->setEnabled(true);
            bandera = true;
            ui->jugadorActual->setText("Jugador 1");
            m.setText("Termino su turno Jugador 2");
            m.exec();
            break;
        case 'E':
            jugador2->recolectar(100);
            ui->dinero2_LCD->display(jugador2->getDinero());
            ui->propiedadesJugador1->setEnabled(true);
            ui->propiedadesJugador2->setEnabled(false);
            ui->construir1->setEnabled(true);
            ui->construir2->setEnabled(false);
            ui->hipotecar1->setEnabled(true);
            ui->hipotecar2->setEnabled(false);
            ui->pushButton->setEnabled(true);
            bandera = true;
            ui->jugadorActual->setText("Jugador 1");
            m.setText("Termino su turno Jugador 2");
            m.exec();
            break;
        case 'F':
            jugador2->pagar(50);
            ui->dinero2_LCD->display(jugador2->getDinero());
            ui->propiedadesJugador1->setEnabled(true);
            ui->propiedadesJugador2->setEnabled(false);
            ui->construir1->setEnabled(true);
            ui->construir2->setEnabled(false);
            ui->hipotecar1->setEnabled(true);
            ui->hipotecar2->setEnabled(false);
            ui->pushButton->setEnabled(true);
            bandera = true;
            ui->jugadorActual->setText("Jugador 1");
            m.setText("Termino su turno Jugador 2");
            m.exec();
            break;
        case 'G':
            jugador2->recolectar(20);
            ui->dinero2_LCD->display(jugador2->getDinero());
            ui->propiedadesJugador1->setEnabled(true);
            ui->propiedadesJugador2->setEnabled(false);
            ui->construir1->setEnabled(true);
            ui->construir2->setEnabled(false);
            ui->hipotecar1->setEnabled(true);
            ui->hipotecar2->setEnabled(false);
            ui->pushButton->setEnabled(true);
            bandera = true;
            ui->jugadorActual->setText("Jugador 1");
            m.setText("Termino su turno Jugador 2");
            m.exec();
            break;
        case 'H':
            jugador2->pagar(100);
            ui->dinero2_LCD->display(jugador2->getDinero());
            ui->propiedadesJugador1->setEnabled(true);
            ui->propiedadesJugador2->setEnabled(false);
            ui->construir1->setEnabled(true);
            ui->construir2->setEnabled(false);
            ui->hipotecar1->setEnabled(true);
            ui->hipotecar2->setEnabled(false);
            ui->pushButton->setEnabled(true);
            bandera = true;
            ui->jugadorActual->setText("Jugador 1");
            m.setText("Termino su turno Jugador 2");
            m.exec();
            break;
        case 'I':
            if(jugador2->isJailFree()){
                QMessageBox m2;
                m2.setText("Tiene una Tarjeta para salir de la carcel!");
                m2.exec();
                jugador2->setJailFree(false);
                bandera = true;
                ui->propiedadesJugador2->setEnabled(false);
                ui->propiedadesJugador1->setEnabled(true);
                ui->construir2->setEnabled(false);
                ui->construir1->setEnabled(true);
                ui->hipotecar2->setEnabled(false);
                ui->hipotecar1->setEnabled(true);
                ui->pushButton->setEnabled(true);
                ui->jugadorActual->setText("Jugador 1");
                m.setText("Termino su turno Jugador 2");
                m.exec();
            }else{
                jugador1->setEnCarcel(true);
                jugador1->setPosicion(11);
                ui->icon1->setGeometry(30,520,30,30);
                bandera = true;
                ui->propiedadesJugador1->setEnabled(false);
                ui->propiedadesJugador2->setEnabled(true);
                ui->construir1->setEnabled(false);
                ui->construir2->setEnabled(true);
                ui->hipotecar1->setEnabled(false);
                ui->hipotecar2->setEnabled(true);
                ui->pushButton->setEnabled(true);
                ui->jugadorActual->setText("Jugador 2");
                m.setText("Termino su turno Jugador 1");
                m.exec();
            }
            break;
        case 'J':
            jugador2->recolectar(25);
            ui->dinero2_LCD->display(jugador2->getDinero());
            ui->propiedadesJugador1->setEnabled(true);
            ui->propiedadesJugador2->setEnabled(false);
            ui->construir1->setEnabled(true);
            ui->construir2->setEnabled(false);
            ui->hipotecar1->setEnabled(true);
            ui->hipotecar2->setEnabled(false);
            ui->pushButton->setEnabled(true);
            bandera = true;
            ui->jugadorActual->setText("Jugador 1");
            m.setText("Termino su turno Jugador 2");
            m.exec();
            break;
        case 'K':
            jugador2->recolectar(10);
            ui->dinero2_LCD->display(jugador2->getDinero());
            ui->propiedadesJugador1->setEnabled(true);
            ui->propiedadesJugador2->setEnabled(false);
            ui->construir1->setEnabled(true);
            ui->construir2->setEnabled(false);
            ui->hipotecar1->setEnabled(true);
            ui->hipotecar2->setEnabled(false);
            ui->pushButton->setEnabled(true);
            bandera = true;
            ui->jugadorActual->setText("Jugador 1");
            m.setText("Termino su turno Jugador 2");
            m.exec();
            break;
        case 'L':
            jugador2->recolectar(100);
            ui->dinero2_LCD->display(jugador2->getDinero());
            ui->propiedadesJugador1->setEnabled(true);
            ui->propiedadesJugador2->setEnabled(false);
            ui->construir1->setEnabled(true);
            ui->construir2->setEnabled(false);
            ui->hipotecar1->setEnabled(true);
            ui->hipotecar2->setEnabled(false);
            ui->pushButton->setEnabled(true);
            bandera = true;
            ui->jugadorActual->setText("Jugador 1");
            m.setText("Termino su turno Jugador 2");
            m.exec();
            break;
        case 'M':
            jugador2->recolectar(50);
            ui->dinero2_LCD->display(jugador2->getDinero());
            ui->propiedadesJugador1->setEnabled(true);
            ui->propiedadesJugador2->setEnabled(false);
            ui->construir1->setEnabled(true);
            ui->construir2->setEnabled(false);
            ui->hipotecar1->setEnabled(true);
            ui->hipotecar2->setEnabled(false);
            ui->pushButton->setEnabled(true);
            bandera = true;
            ui->jugadorActual->setText("Jugador 1");
            m.setText("Termino su turno Jugador 2");
            m.exec();
            break;
        case 'N':
            for(int i = 0; i < propiedades.size(); i++){
                if(typeid(*propiedades[i]) == typeid(PropiedadNormal)){
                    PropiedadNormal* prop = dynamic_cast<PropiedadNormal*>(propiedades[i]);
                    houses += prop->getTotalCasitas();
                    if(prop->hasHotel()){
                        hotels++;
                    }
                }
            }
            sub1 = houses * 25;
            sub2 = hotels * 100;
            total = sub1+sub2;
            jugador2->pagar(total);
            ui->dinero2_LCD->display(jugador1->getDinero());
            bandera = true;
            ui->propiedadesJugador2->setEnabled(false);
            ui->propiedadesJugador1->setEnabled(true);
            ui->construir2->setEnabled(false);
            ui->construir1->setEnabled(true);
            ui->hipotecar2->setEnabled(false);
            ui->hipotecar1->setEnabled(true);
            ui->pushButton->setEnabled(true);
            ui->jugadorActual->setText("Jugador 1");
            m.setText("Termino su turno Jugador 2");
            m.exec();
            break;
        case 'O':
            jugador2->setPosicion(1);
            jugador2->recolectar(200);
            ui->dinero2_LCD->display(jugador1->getDinero());
            ui->icon2->setGeometry(620,520,30,30);
            bandera = true;
            ui->propiedadesJugador1->setEnabled(true);
            ui->propiedadesJugador2->setEnabled(false);
            ui->construir1->setEnabled(true);
            ui->construir2->setEnabled(false);
            ui->hipotecar1->setEnabled(true);
            ui->hipotecar2->setEnabled(false);
            ui->pushButton->setEnabled(true);
            ui->jugadorActual->setText("Jugador 1");
            m.setText("Termino su turno Jugador 2");
            m.exec();
            break;
        case 'P':
            jugador2->recolectar(200);
            ui->dinero2_LCD->display(jugador2->getDinero());
            ui->propiedadesJugador1->setEnabled(true);
            ui->propiedadesJugador2->setEnabled(false);
            ui->construir1->setEnabled(true);
            ui->construir2->setEnabled(false);
            ui->hipotecar1->setEnabled(true);
            ui->hipotecar2->setEnabled(false);
            ui->pushButton->setEnabled(true);
            bandera = true;
            m.setText("Termino su turno Jugador 2");
            m.exec();
            break;
        }
    }
}

void MainWindow::accionesChance(int codigo){
    QMessageBox m;
    int n = 0,n1 = 0,n2 = 0,n3 = 0,n4 = 0;
    int dist1 = 0,dist2 = 0,dist3 = 0,dist4 = 0;
    int houses = 0;
    int hotels = 0;
    int sub1 = 0;
    int sub2 = 0;
    int total = 0;
    if(bandera){
        switch(codigo){
        case 1:
            n = jugador1->getPosicion();
            for(unsigned long i = 0; i < propiedades.size(); i++){
                if(propiedades[i]->getNombre() == "Ferrocarril Reading"){
                    n1 = propiedades[i]->getPosicion();
                }
            }
            for(unsigned long i = 0; i < propiedades.size(); i++){
                if(propiedades[i]->getNombre() == "Ferrocarril Pennsylvania"){
                    n2 = propiedades[i]->getPosicion();
                }
            }
            for(unsigned long  i = 0; i < propiedades.size(); i++){
                if(propiedades[i]->getNombre() == "Ferrocarril B & O"){
                    n3 = propiedades[i]->getPosicion();
                }
            }
            for(unsigned long  i = 0; i < propiedades.size(); i++){
                if(propiedades[i]->getNombre() == "Ferrocarril Via Rapida"){
                    n4 = propiedades[i]->getPosicion();
                }
            }
            dist1 = n1 - n;
            dist2 = n2 - n;
            dist3 = n3 - n;
            dist4 = n4 - n;
            if(dist1 < dist2 && dist1 < dist3 && dist1 < dist4){
                for(unsigned long  i = 0; i < propiedades.size(); i++){
                    if(propiedades[i]->getNombre() == "Ferrocarril Reading"){
                        jugador1->setPosicion(propiedades[i]->getPosicion());
                        ui->icon1->setGeometry(propiedades[i]->getX(),propiedades[i]->getY(),30,30);
                        if(propiedades[i]->isEnVenta()){
                            ui->comprarJugador1->setEnabled(true);
                        } else if (!propiedades[i]->isEnVenta() && propiedades[i]->isPlayerTwoOwner()){
                            ui->pagar1->setEnabled(true);
                        }
                    }
                }
            } else if(dist2 < dist1 && dist2 < dist3 && dist2 < dist4){
                for(unsigned long  i = 0; i < propiedades.size(); i++){
                    if(propiedades[i]->getNombre() == "Ferrocarril Pennsylvania"){
                        jugador1->setPosicion(propiedades[i]->getPosicion());
                        ui->icon1->setGeometry(propiedades[i]->getX(),propiedades[i]->getY(),30,30);
                        if(propiedades[i]->isEnVenta()){
                            ui->comprarJugador1->setEnabled(true);
                        } else if (!propiedades[i]->isEnVenta() && propiedades[i]->isPlayerTwoOwner()){
                            ui->pagar1->setEnabled(true);
                        }
                    }
                }
            } else if (dist3 < dist1 && dist3 < dist2 && dist3 < dist4){
                for(unsigned long  i = 0; i < propiedades.size(); i++){
                    if(propiedades[i]->getNombre() == "Ferrocarril B & O"){
                        jugador1->setPosicion(propiedades[i]->getPosicion());
                        ui->icon1->setGeometry(propiedades[i]->getX(),propiedades[i]->getY(),30,30);
                        if(propiedades[i]->isEnVenta()){
                            ui->comprarJugador1->setEnabled(true);
                        } else if (!propiedades[i]->isEnVenta() && propiedades[i]->isPlayerTwoOwner()){
                            ui->pagar1->setEnabled(true);
                        }
                    }
                }
            } else if (dist4 < dist1 && dist4 < dist2 && dist4 < dist3){
                for(unsigned long  i = 0; i < propiedades.size(); i++){
                    if(propiedades[i]->getNombre() == "Ferrocarril Via Rapida"){
                        jugador1->setPosicion(propiedades[i]->getPosicion());
                        ui->icon1->setGeometry(propiedades[i]->getX(),propiedades[i]->getY(),30,30);
                        if(propiedades[i]->isEnVenta()){
                            ui->comprarJugador1->setEnabled(true);
                        } else if (!propiedades[i]->isEnVenta() && propiedades[i]->isPlayerTwoOwner()){
                            ui->pagar1->setEnabled(true);
                        }
                    }
                }
            }
            break;
        case 2:
            n = jugador1->getPosicion();
            for(unsigned long  i = 0; i < propiedades.size(); i++){
                if(propiedades[i]->getNombre() == "Ferrocarril Reading"){
                    n1 = propiedades[i]->getPosicion();
                }
            }
            for(unsigned long  i = 0; i < propiedades.size(); i++){
                if(propiedades[i]->getNombre() == "Ferrocarril Pennsylvania"){
                    n2 = propiedades[i]->getPosicion();
                }
            }
            for(unsigned long  i = 0; i < propiedades.size(); i++){
                if(propiedades[i]->getNombre() == "Ferrocarril B & O"){
                    n3 = propiedades[i]->getPosicion();
                }
            }
            for(unsigned long  i = 0; i < propiedades.size(); i++){
                if(propiedades[i]->getNombre() == "Ferrocarril Via Rapida"){
                    n4 = propiedades[i]->getPosicion();
                }
            }
            dist1 = n1 - n;
            dist2 = n2 - n;
            dist3 = n3 - n;
            dist4 = n4 - n;
            if(dist1 < dist2 && dist1 < dist3 && dist1 < dist4){
                for(unsigned long  i = 0; i < propiedades.size(); i++){
                    if(propiedades[i]->getNombre() == "Ferrocarril Reading"){
                        jugador1->setPosicion(propiedades[i]->getPosicion());
                        ui->icon1->setGeometry(propiedades[i]->getX(),propiedades[i]->getY(),30,30);
                        if(propiedades[i]->isEnVenta()){
                            ui->comprarJugador1->setEnabled(true);
                        } else if (!propiedades[i]->isEnVenta() && propiedades[i]->isPlayerTwoOwner()){
                            ui->pagar1->setEnabled(true);
                        }
                    }
                }
            } else if(dist2 < dist1 && dist2 < dist3 && dist2 < dist4){
                for(unsigned long  i = 0; i < propiedades.size(); i++){
                    if(propiedades[i]->getNombre() == "Ferrocarril Pennsylvania"){
                        jugador1->setPosicion(propiedades[i]->getPosicion());
                        ui->icon1->setGeometry(propiedades[i]->getX(),propiedades[i]->getY(),30,30);
                        if(propiedades[i]->isEnVenta()){
                            ui->comprarJugador1->setEnabled(true);
                        } else if (!propiedades[i]->isEnVenta() && propiedades[i]->isPlayerTwoOwner()){
                            ui->pagar1->setEnabled(true);
                        }
                    }
                }
            } else if (dist3 < dist1 && dist3 < dist2 && dist3 < dist4){
                for(unsigned long  i = 0; i < propiedades.size(); i++){
                    if(propiedades[i]->getNombre() == "Ferrocarril B & O"){
                        jugador1->setPosicion(propiedades[i]->getPosicion());
                        ui->icon1->setGeometry(propiedades[i]->getX(),propiedades[i]->getY(),30,30);
                        if(propiedades[i]->isEnVenta()){
                            ui->comprarJugador1->setEnabled(true);
                        } else if (!propiedades[i]->isEnVenta() && propiedades[i]->isPlayerTwoOwner()){
                            ui->pagar1->setEnabled(true);
                        }
                    }
                }
            } else if (dist4 < dist1 && dist4 < dist2 && dist4 < dist3){
                for(unsigned long  i = 0; i < propiedades.size(); i++){
                    if(propiedades[i]->getNombre() == "Ferrocarril Via Rapida"){
                        jugador1->setPosicion(propiedades[i]->getPosicion());
                        ui->icon1->setGeometry(propiedades[i]->getX(),propiedades[i]->getY(),30,30);
                        if(propiedades[i]->isEnVenta()){
                            ui->comprarJugador1->setEnabled(true);
                        } else if (!propiedades[i]->isEnVenta() && propiedades[i]->isPlayerTwoOwner()){
                            ui->pagar1->setEnabled(true);
                        }
                    }
                }
            }
            break;
        case 3:
            jugador1->pagar(15);
            ui->dinero1_LCD->display(jugador1->getDinero());
            bandera = false;
            ui->propiedadesJugador1->setEnabled(false);
            ui->propiedadesJugador2->setEnabled(true);
            ui->construir1->setEnabled(false);
            ui->construir2->setEnabled(true);
            ui->hipotecar1->setEnabled(false);
            ui->hipotecar2->setEnabled(true);
            ui->pushButton->setEnabled(true);
            ui->jugadorActual->setText("Jugador 2");
            m.setText("Termino su turno Jugador 1");
            m.exec();
            break;
        case 4:
            jugador1->avanzar(-3);
            for(unsigned long  i = 0; i < propiedades.size(); i++){
                if(jugador1->getPosicion() == propiedades[i]->getPosicion()){
                    ui->icon1->setGeometry(propiedades[i]->getX(),propiedades[i]->getY(),30,30);
                    break;
                }
            }
            bandera = false;
            ui->propiedadesJugador1->setEnabled(false);
            ui->propiedadesJugador2->setEnabled(true);
            ui->construir1->setEnabled(false);
            ui->construir2->setEnabled(true);
            ui->hipotecar1->setEnabled(false);
            ui->hipotecar2->setEnabled(true);
            ui->pushButton->setEnabled(true);
            ui->jugadorActual->setText("Jugador 2");
            m.setText("Termino su turno Jugador 1");
            m.exec();
            break;
        case 5:
            jugador1->pagar(50);
            jugador2->recolectar(50);
            ui->dinero1_LCD->display(jugador1->getDinero());
            ui->dinero2_LCD->display(jugador2->getDinero());
            bandera = false;
            ui->propiedadesJugador1->setEnabled(false);
            ui->propiedadesJugador2->setEnabled(true);
            ui->construir1->setEnabled(false);
            ui->construir2->setEnabled(true);
            ui->hipotecar1->setEnabled(false);
            ui->hipotecar2->setEnabled(true);
            ui->pushButton->setEnabled(true);
            ui->jugadorActual->setText("Jugador 2");
            m.setText("Termino su turno Jugador 1");
            m.exec();
            break;
        case 6:
            for(unsigned long  i = 0; i < propiedades.size(); i++){
                if(propiedades[i]->getNombre() == "Plaza St. James"){
                    jugador1->setPosicion(propiedades[i]->getPosicion());
                    ui->icon1->setGeometry(propiedades[i]->getX(),propiedades[i]->getY(),30,30);
                }
            }
            bandera = false;
            ui->propiedadesJugador1->setEnabled(false);
            ui->propiedadesJugador2->setEnabled(true);
            ui->comprarJugador1->setEnabled(false);
            ui->subastar1->setEnabled(false);
            ui->construir1->setEnabled(false);
            ui->construir2->setEnabled(true);
            ui->hipotecar1->setEnabled(false);
            ui->hipotecar2->setEnabled(true);
            ui->pushButton->setEnabled(true);
            ui->jugadorActual->setText("Jugador 2");
            m.setText("Termino su turno Jugador 1");
            m.exec();
            break;
        case 7:
            jugador1->setJailFree(true);
            bandera = false;
            ui->propiedadesJugador1->setEnabled(false);
            ui->propiedadesJugador2->setEnabled(true);
            ui->construir1->setEnabled(false);
            ui->construir2->setEnabled(true);
            ui->hipotecar1->setEnabled(false);
            ui->hipotecar2->setEnabled(true);
            ui->jugadorActual->setText("Jugador 2");
            m.setText("Termino su turno Jugador 1");
            m.exec();
            break;
        case 8:
            for(int i = 0; i < propiedades.size(); i++){
                if(typeid(*propiedades[i]) == typeid(PropiedadNormal)){
                    PropiedadNormal* prop = dynamic_cast<PropiedadNormal*>(propiedades[i]);
                    houses += prop->getTotalCasitas();
                    if(prop->hasHotel()){
                        hotels++;
                    }
                }
            }
            sub1 = houses * 25;
            sub2 = hotels * 100;
            total = sub1+sub2;
            jugador1->pagar(total);
            ui->dinero1_LCD->display(jugador1->getDinero());
            bandera = false;
            ui->propiedadesJugador1->setEnabled(false);
            ui->propiedadesJugador2->setEnabled(true);
            ui->construir1->setEnabled(false);
            ui->construir2->setEnabled(true);
            ui->hipotecar1->setEnabled(false);
            ui->hipotecar2->setEnabled(true);
            ui->pushButton->setEnabled(true);
            ui->jugadorActual->setText("Jugador 2");
            m.setText("Termino su turno Jugador 1");
            m.exec();
            break;
        case 9:
            jugador1->recolectar(50);
            bandera = false;
            ui->dinero1_LCD->display(jugador1->getDinero());
            ui->propiedadesJugador1->setEnabled(false);
            ui->propiedadesJugador2->setEnabled(true);
            ui->construir1->setEnabled(false);
            ui->construir2->setEnabled(true);
            ui->hipotecar1->setEnabled(false);
            ui->hipotecar2->setEnabled(true);
            ui->pushButton->setEnabled(true);
            ui->jugadorActual->setText("Jugador 2");
            m.setText("Termino su turno Jugador 1");
            m.exec();
            break;
        case 10:
            jugador1->setPosicion(1);
            jugador1->recolectar(200);
            ui->dinero1_LCD->display(jugador1->getDinero());
            ui->icon1->setGeometry(620,520,30,30);
            bandera = false;
            ui->propiedadesJugador1->setEnabled(false);
            ui->propiedadesJugador2->setEnabled(true);
            ui->construir1->setEnabled(false);
            ui->construir2->setEnabled(true);
            ui->hipotecar1->setEnabled(false);
            ui->hipotecar2->setEnabled(true);
            ui->pushButton->setEnabled(true);
            ui->jugadorActual->setText("Jugador 2");
            m.setText("Termino su turno Jugador 1");
            m.exec();
            break;
        case 11:
            if(jugador1->isJailFree()){
                QMessageBox m2;
                m2.setText("Tiene una Tarjeta para salir de la carcel!");
                m2.exec();
                jugador1->setJailFree(false);
                bandera = false;
                ui->propiedadesJugador1->setEnabled(false);
                ui->propiedadesJugador2->setEnabled(true);
                ui->construir1->setEnabled(false);
                ui->construir2->setEnabled(true);
                ui->hipotecar1->setEnabled(false);
                ui->hipotecar2->setEnabled(true);
                ui->pushButton->setEnabled(true);
                ui->jugadorActual->setText("Jugador 2");
                m.setText("Termino su turno Jugador 1");
                m.exec();
            }else{
                jugador1->setEnCarcel(true);
                jugador1->setPosicion(11);
                ui->icon1->setGeometry(30,520,30,30);
                bandera = false;
                ui->propiedadesJugador1->setEnabled(false);
                ui->propiedadesJugador2->setEnabled(true);
                ui->construir1->setEnabled(false);
                ui->construir2->setEnabled(true);
                ui->hipotecar1->setEnabled(false);
                ui->hipotecar2->setEnabled(true);
                ui->pushButton->setEnabled(true);
                ui->jugadorActual->setText("Jugador 2");
                m.setText("Termino su turno Jugador 1");
                m.exec();
            }
            break;
        case 12:
            n = jugador1->getPosicion();
            for(unsigned long  i = 0; i < propiedades.size(); i++){
                if(propiedades[i]->getNombre() == "Compañia Electrica"){
                    n1 = propiedades[i]->getPosicion();
                }
            }
            for(unsigned long  i = 0; i < propiedades.size(); i++){
                if(propiedades[i]->getNombre() == "Compañia de Agua"){
                    n2 = propiedades[i]->getPosicion();
                }
            }
            dist1 = n1 - n;
            dist2 = n2 - n;
            if(dist1 < dist2){
                for(unsigned long  i = 0; i < propiedades.size(); i++){
                    if(propiedades[i]->getNombre() == "Compañia Electrica"){
                        jugador1->setPosicion(propiedades[i]->getPosicion());
                        ui->icon1->setGeometry(propiedades[i]->getX(),propiedades[i]->getY(),30,30);
                        if(propiedades[i]->isEnVenta()){
                            ui->comprarJugador1->setEnabled(true);
                        } else if (!propiedades[i]->isEnVenta() && propiedades[i]->isPlayerTwoOwner()){
                            ui->pagar1->setEnabled(true);
                        }
                    }
                }
            } else if (dist2 < dist1){
                for(unsigned long  i = 0; i < propiedades.size(); i++){
                    if(propiedades[i]->getNombre() == "Compañia de Agua"){
                        jugador1->setPosicion(propiedades[i]->getPosicion());
                        ui->icon1->setGeometry(propiedades[i]->getX(),propiedades[i]->getY(),30,30);
                        if(propiedades[i]->isEnVenta()){
                            ui->comprarJugador1->setEnabled(true);
                        } else if (!propiedades[i]->isEnVenta() && propiedades[i]->isPlayerTwoOwner()){
                            ui->pagar1->setEnabled(true);
                        }
                    }
                }
            }
            break;
        case 13:
            for(unsigned long  i = 0; i < propiedades.size(); i++){
                if(propiedades[i]->getNombre() == "Avenida Illinois"){
                    jugador1->setPosicion(propiedades[i]->getPosicion());
                    ui->icon1->setGeometry(propiedades[i]->getX(),propiedades[i]->getY(),30,30);
                }
            }
            bandera = false;
            ui->propiedadesJugador1->setEnabled(false);
            ui->propiedadesJugador2->setEnabled(true);
            ui->construir1->setEnabled(false);
            ui->construir2->setEnabled(true);
            ui->hipotecar1->setEnabled(false);
            ui->hipotecar2->setEnabled(true);
            ui->pushButton->setEnabled(true);
            ui->jugadorActual->setText("Jugador 2");
            m.setText("Termino su turno Jugador 1");
            m.exec();
            break;
        case 14:
            jugador1->recolectar(150);
            ui->dinero1_LCD->display(jugador1->getDinero());
            bandera = false;
            ui->propiedadesJugador1->setEnabled(false);
            ui->propiedadesJugador2->setEnabled(true);
            ui->construir1->setEnabled(false);
            ui->construir2->setEnabled(true);
            ui->hipotecar1->setEnabled(false);
            ui->hipotecar2->setEnabled(true);
            ui->pushButton->setEnabled(true);
            ui->jugadorActual->setText("Jugador 2");
            m.setText("Termino su turno Jugador 1");
            m.exec();
            break;
        case 15:
            for(unsigned long  i = 0; i < propiedades.size(); i++){
                if(propiedades[i]->getNombre() == "Ferrocarril Reading"){
                    jugador1->setPosicion(propiedades[i]->getPosicion());
                    ui->icon1->setGeometry(propiedades[i]->getX(),propiedades[i]->getY(),30,30);
                }
            }
            bandera = false;
            ui->propiedadesJugador1->setEnabled(false);
            ui->propiedadesJugador2->setEnabled(true);
            ui->pushButton->setEnabled(true);
            ui->construir1->setEnabled(false);
            ui->construir2->setEnabled(true);
            ui->hipotecar1->setEnabled(false);
            ui->hipotecar2->setEnabled(true);
            ui->jugadorActual->setText("Jugador 2");
            m.setText("Termino su turno Jugador 1");
            m.exec();
            break;
        case 16:
            for(unsigned long  i = 0; i < propiedades.size(); i++){
                if(propiedades[i]->getNombre() == "El Muelle"){
                    jugador1->setPosicion(propiedades[i]->getPosicion());
                    ui->icon1->setGeometry(propiedades[i]->getX(),propiedades[i]->getY(),30,30);
                }
            }
            bandera = false;
            ui->propiedadesJugador1->setEnabled(false);
            ui->propiedadesJugador2->setEnabled(true);
            ui->construir1->setEnabled(false);
            ui->construir2->setEnabled(true);
            ui->hipotecar1->setEnabled(false);
            ui->hipotecar2->setEnabled(true);
            ui->pushButton->setEnabled(true);
            ui->jugadorActual->setText("Jugador 2");
            m.setText("Termino su turno Jugador 1");
            m.exec();
            break;
        }
    }else{
        switch(codigo){
        case 1:
            n = jugador2->getPosicion();
            for(unsigned long  i = 0; i < propiedades.size(); i++){
                if(propiedades[i]->getNombre() == "Ferrocarril Reading"){
                    n1 = propiedades[i]->getPosicion();
                }
            }
            for(unsigned long  i = 0; i < propiedades.size(); i++){
                if(propiedades[i]->getNombre() == "Ferrocarril Pennsylvania"){
                    n2 = propiedades[i]->getPosicion();
                }
            }
            for(unsigned long  i = 0; i < propiedades.size(); i++){
                if(propiedades[i]->getNombre() == "Ferrocarril B & O"){
                    n3 = propiedades[i]->getPosicion();
                }
            }
            for(unsigned long  i = 0; i < propiedades.size(); i++){
                if(propiedades[i]->getNombre() == "Ferrocarril Via Rapida"){
                    n4 = propiedades[i]->getPosicion();
                }
            }
            dist1 = n1 - n;
            dist2 = n2 - n;
            dist3 = n3 - n;
            dist4 = n4 - n;
            if(dist1 < dist2 && dist1 < dist3 && dist1 < dist4){
                for(unsigned long  i = 0; i < propiedades.size(); i++){
                    if(propiedades[i]->getNombre() == "Ferrocarril Reading"){
                        jugador2->setPosicion(propiedades[i]->getPosicion());
                        ui->icon2->setGeometry(propiedades[i]->getX(),propiedades[i]->getY(),30,30);
                        if(propiedades[i]->isEnVenta()){
                            ui->comprarJugador2->setEnabled(true);
                        } else if (!propiedades[i]->isEnVenta() && propiedades[i]->isPlayerOneOwner()){
                            ui->pagar2->setEnabled(true);
                        }
                    }
                }
            } else if(dist2 < dist1 && dist2 < dist3 && dist2 < dist4){
                for(unsigned long  i = 0; i < propiedades.size(); i++){
                    if(propiedades[i]->getNombre() == "Ferrocarril Pennsylvania"){
                        jugador2->setPosicion(propiedades[i]->getPosicion());
                        ui->icon2->setGeometry(propiedades[i]->getX(),propiedades[i]->getY(),30,30);
                        if(propiedades[i]->isEnVenta()){
                            ui->comprarJugador2->setEnabled(true);
                        } else if (!propiedades[i]->isEnVenta() && propiedades[i]->isPlayerOneOwner()){
                            ui->pagar2->setEnabled(true);
                        }
                    }
                }
            } else if (dist3 < dist1 && dist3 < dist2 && dist3 < dist4){
                for(unsigned long  i = 0; i < propiedades.size(); i++){
                    if(propiedades[i]->getNombre() == "Ferrocarril B & O"){
                        jugador2->setPosicion(propiedades[i]->getPosicion());
                        ui->icon2->setGeometry(propiedades[i]->getX(),propiedades[i]->getY(),30,30);
                        if(propiedades[i]->isEnVenta()){
                            ui->comprarJugador2->setEnabled(true);
                        } else if (!propiedades[i]->isEnVenta() && propiedades[i]->isPlayerOneOwner()){
                            ui->pagar2->setEnabled(true);
                        }
                    }
                }
            } else if (dist4 < dist1 && dist4 < dist2 && dist4 < dist3){
                for(unsigned long  i = 0; i < propiedades.size(); i++){
                    if(propiedades[i]->getNombre() == "Ferrocarril Via Rapida"){
                        jugador2->setPosicion(propiedades[i]->getPosicion());
                        ui->icon2->setGeometry(propiedades[i]->getX(),propiedades[i]->getY(),30,30);
                        if(propiedades[i]->isEnVenta()){
                            ui->comprarJugador2->setEnabled(true);
                        } else if (!propiedades[i]->isEnVenta() && propiedades[i]->isPlayerOneOwner()){
                            ui->pagar2->setEnabled(true);
                        }
                    }
                }
            }
            break;
        case 2:
            n = jugador2->getPosicion();
            for(unsigned long  i = 0; i < propiedades.size(); i++){
                if(propiedades[i]->getNombre() == "Ferrocarril Reading"){
                    n1 = propiedades[i]->getPosicion();
                }
            }
            for(unsigned long  i = 0; i < propiedades.size(); i++){
                if(propiedades[i]->getNombre() == "Ferrocarril Pennsylvania"){
                    n2 = propiedades[i]->getPosicion();
                }
            }
            for(unsigned long  i = 0; i < propiedades.size(); i++){
                if(propiedades[i]->getNombre() == "Ferrocarril B & O"){
                    n3 = propiedades[i]->getPosicion();
                }
            }
            for(unsigned long  i = 0; i < propiedades.size(); i++){
                if(propiedades[i]->getNombre() == "Ferrocarril Via Rapida"){
                    n4 = propiedades[i]->getPosicion();
                }
            }
            dist1 = n1 - n;
            dist2 = n2 - n;
            dist3 = n3 - n;
            dist4 = n4 - n;
            if(dist1 < dist2 && dist1 < dist3 && dist1 < dist4){
                for(unsigned long  i = 0; i < propiedades.size(); i++){
                    if(propiedades[i]->getNombre() == "Ferrocarril Reading"){
                        jugador2->setPosicion(propiedades[i]->getPosicion());
                        ui->icon2->setGeometry(propiedades[i]->getX(),propiedades[i]->getY(),30,30);
                        if(propiedades[i]->isEnVenta()){
                            ui->comprarJugador2->setEnabled(true);
                        } else if (!propiedades[i]->isEnVenta() && propiedades[i]->isPlayerOneOwner()){
                            ui->pagar2->setEnabled(true);
                        }
                    }
                }
            } else if(dist2 < dist1 && dist2 < dist3 && dist2 < dist4){
                for(unsigned long  i = 0; i < propiedades.size(); i++){
                    if(propiedades[i]->getNombre() == "Ferrocarril Pennsylvania"){
                        jugador2->setPosicion(propiedades[i]->getPosicion());
                        ui->icon2->setGeometry(propiedades[i]->getX(),propiedades[i]->getY(),30,30);
                        if(propiedades[i]->isEnVenta()){
                            ui->comprarJugador2->setEnabled(true);
                        } else if (!propiedades[i]->isEnVenta() && propiedades[i]->isPlayerOneOwner()){
                            ui->pagar2->setEnabled(true);
                        }
                    }
                }
            } else if (dist3 < dist1 && dist3 < dist2 && dist3 < dist4){
                for(unsigned long  i = 0; i < propiedades.size(); i++){
                    if(propiedades[i]->getNombre() == "Ferrocarril B & O"){
                        jugador2->setPosicion(propiedades[i]->getPosicion());
                        ui->icon2->setGeometry(propiedades[i]->getX(),propiedades[i]->getY(),30,30);
                        if(propiedades[i]->isEnVenta()){
                            ui->comprarJugador2->setEnabled(true);
                        } else if (!propiedades[i]->isEnVenta() && propiedades[i]->isPlayerOneOwner()){
                            ui->pagar2->setEnabled(true);
                        }
                    }
                }
            } else if (dist4 < dist1 && dist4 < dist2 && dist4 < dist3){
                for(unsigned long  i = 0; i < propiedades.size(); i++){
                    if(propiedades[i]->getNombre() == "Ferrocarril Via Rapida"){
                        jugador2->setPosicion(propiedades[i]->getPosicion());
                        ui->icon2->setGeometry(propiedades[i]->getX(),propiedades[i]->getY(),30,30);
                        if(propiedades[i]->isEnVenta()){
                            ui->comprarJugador2->setEnabled(true);
                        } else if (!propiedades[i]->isEnVenta() && propiedades[i]->isPlayerOneOwner()){
                            ui->pagar2->setEnabled(true);
                        }
                    }
                }
            }
            break;
        case 3:
            jugador2->pagar(15);
            ui->dinero2_LCD->display(jugador2->getDinero());
            bandera = true;
            ui->propiedadesJugador2->setEnabled(false);
            ui->propiedadesJugador1->setEnabled(true);
            ui->construir1->setEnabled(true);
            ui->construir2->setEnabled(false);
            ui->hipotecar1->setEnabled(true);
            ui->hipotecar2->setEnabled(false);
            ui->pushButton->setEnabled(true);
            ui->jugadorActual->setText("Jugador 1");
            m.setText("Termino su turno Jugador 2");
            m.exec();
            break;
        case 4:
            jugador2->avanzar(-3);
            for(unsigned long  i = 0; i < propiedades.size(); i++){
                if(jugador2->getPosicion() == propiedades[i]->getPosicion()){
                    ui->icon2->setGeometry(propiedades[i]->getX(),propiedades[i]->getY(),30,30);
                }
            }
            bandera = true;
            ui->propiedadesJugador2->setEnabled(false);
            ui->propiedadesJugador1->setEnabled(true);
            ui->construir1->setEnabled(true);
            ui->construir2->setEnabled(false);
            ui->hipotecar1->setEnabled(true);
            ui->hipotecar2->setEnabled(false);
            ui->pushButton->setEnabled(true);
            ui->jugadorActual->setText("Jugador 1");
            m.setText("Termino su turno Jugador 2");
            m.exec();
            break;
        case 5:
            jugador2->pagar(50);
            jugador1->recolectar(50);
            ui->dinero2_LCD->display(jugador2->getDinero());
            ui->dinero1_LCD->display(jugador1->getDinero());
            bandera = true;
            ui->propiedadesJugador2->setEnabled(false);
            ui->propiedadesJugador1->setEnabled(true);
            ui->construir1->setEnabled(true);
            ui->construir2->setEnabled(false);
            ui->hipotecar1->setEnabled(true);
            ui->hipotecar2->setEnabled(false);
            ui->pushButton->setEnabled(true);
            ui->jugadorActual->setText("Jugador 1");
            m.setText("Termino su turno Jugador 2");
            m.exec();
            break;
        case 6:
            for(unsigned long  i = 0; i < propiedades.size(); i++){
                if(propiedades[i]->getNombre() == "Plaza St. James"){
                    jugador2->setPosicion(propiedades[i]->getPosicion());
                    ui->icon2->setGeometry(propiedades[i]->getX(),propiedades[i]->getY(),30,30);
                }
            }
            bandera = true;
            ui->propiedadesJugador2->setEnabled(false);
            ui->propiedadesJugador1->setEnabled(true);
            ui->comprarJugador2->setEnabled(false);
            ui->subastar2->setEnabled(false);
            ui->construir1->setEnabled(true);
            ui->construir2->setEnabled(false);
            ui->hipotecar1->setEnabled(true);
            ui->hipotecar2->setEnabled(false);
            ui->pushButton->setEnabled(true);
            ui->jugadorActual->setText("Jugador 1");
            m.setText("Termino su turno Jugador 2");
            m.exec();
            break;
        case 7:
            jugador2->setJailFree(true);
            bandera = true;
            ui->propiedadesJugador2->setEnabled(false);
            ui->propiedadesJugador1->setEnabled(true);
            ui->construir2->setEnabled(false);
            ui->construir1->setEnabled(true);
            ui->hipotecar2->setEnabled(false);
            ui->hipotecar1->setEnabled(true);
            ui->jugadorActual->setText("Jugador 1");
            m.setText("Termino su turno Jugador 2");
            m.exec();
            break;
        case 8:
            for(int i = 0; i < propiedades.size(); i++){
                if(typeid(*propiedades[i]) == typeid(PropiedadNormal)){
                    PropiedadNormal* prop = dynamic_cast<PropiedadNormal*>(propiedades[i]);
                    houses += prop->getTotalCasitas();
                    if(prop->hasHotel()){
                        hotels++;
                    }
                }
            }
            sub1 = houses * 25;
            sub2 = hotels * 100;
            total = sub1+sub2;
            jugador2->pagar(total);
            ui->dinero2_LCD->display(jugador2->getDinero());
            bandera = true;
            ui->propiedadesJugador2->setEnabled(false);
            ui->propiedadesJugador1->setEnabled(true);
            ui->construir2->setEnabled(false);
            ui->construir1->setEnabled(true);
            ui->hipotecar2->setEnabled(false);
            ui->hipotecar1->setEnabled(true);
            ui->pushButton->setEnabled(true);
            ui->jugadorActual->setText("Jugador 1");
            m.setText("Termino su turno Jugador 2");
            m.exec();
            break;
        case 9:
            jugador2->recolectar(50);
            ui->dinero2_LCD->display(jugador2->getDinero());
            bandera = true;
            ui->propiedadesJugador2->setEnabled(false);
            ui->propiedadesJugador1->setEnabled(true);
            ui->construir1->setEnabled(true);
            ui->construir2->setEnabled(false);
            ui->hipotecar1->setEnabled(true);
            ui->hipotecar2->setEnabled(false);
            ui->pushButton->setEnabled(true);
            ui->jugadorActual->setText("Jugador 1");
            m.setText("Termino su turno Jugador 2");
            m.exec();
            break;
        case 10:
            jugador2->setPosicion(1);
            jugador2->recolectar(200);
            ui->dinero2_LCD->display(jugador2->getDinero());
            ui->icon2->setGeometry(620,520,30,30);
            bandera = true;
            ui->propiedadesJugador2->setEnabled(false);
            ui->propiedadesJugador1->setEnabled(true);
            ui->construir1->setEnabled(true);
            ui->construir2->setEnabled(false);
            ui->hipotecar1->setEnabled(true);
            ui->hipotecar2->setEnabled(false);
            ui->pushButton->setEnabled(true);
            ui->jugadorActual->setText("Jugador 1");
            m.setText("Termino su turno Jugador 2");
            m.exec();
            break;
        case 11:
            if(jugador2->isJailFree()){
                QMessageBox m2;
                m2.setText("Tiene una Tarjeta para salir de la carcel!");
                m2.exec();
                jugador2->setJailFree(false);
                bandera = true;
                ui->propiedadesJugador2->setEnabled(false);
                ui->propiedadesJugador1->setEnabled(true);
                ui->construir2->setEnabled(false);
                ui->construir1->setEnabled(true);
                ui->hipotecar2->setEnabled(false);
                ui->hipotecar1->setEnabled(true);
                ui->pushButton->setEnabled(true);
                ui->jugadorActual->setText("Jugador 1");
                m.setText("Termino su turno Jugador 2");
                m.exec();
            }else{
                jugador2->setEnCarcel(true);
                jugador2->setPosicion(11);
                ui->icon2->setGeometry(30,520,30,30);
                bandera = true;
                ui->propiedadesJugador2->setEnabled(false);
                ui->propiedadesJugador1->setEnabled(true);
                ui->construir2->setEnabled(false);
                ui->construir1->setEnabled(true);
                ui->hipotecar2->setEnabled(false);
                ui->hipotecar1->setEnabled(true);
                ui->pushButton->setEnabled(true);
                ui->jugadorActual->setText("Jugador 1");
                m.setText("Termino su turno Jugador 2");
                m.exec();
            }
            break;
        case 12:
            n = jugador2->getPosicion();
            for(unsigned long  i = 0; i < propiedades.size(); i++){
                if(propiedades[i]->getNombre() == "Compañia Electrica"){
                    n1 = propiedades[i]->getPosicion();
                }
            }
            for(unsigned long  i = 0; i < propiedades.size(); i++){
                if(propiedades[i]->getNombre() == "Compañia de Agua"){
                    n2 = propiedades[i]->getPosicion();
                }
            }
            dist1 = n1 - n;
            dist2 = n2 - n;
            if(dist1 < dist2){
                for(unsigned long  i = 0; i < propiedades.size(); i++){
                    if(propiedades[i]->getNombre() == "Compañia Electrica"){
                        jugador2->setPosicion(propiedades[i]->getPosicion());
                        ui->icon2->setGeometry(propiedades[i]->getX(),propiedades[i]->getY(),30,30);
                        if(propiedades[i]->isEnVenta()){
                            ui->comprarJugador2->setEnabled(true);
                        } else if (!propiedades[i]->isEnVenta() && propiedades[i]->isPlayerOneOwner()){
                            ui->pagar2->setEnabled(true);
                        }
                    }
                }
            } else if (dist2 < dist1){
                for(unsigned long  i = 0; i < propiedades.size(); i++){
                    if(propiedades[i]->getNombre() == "Compañia de Agua"){
                        jugador2->setPosicion(propiedades[i]->getPosicion());
                        ui->icon2->setGeometry(propiedades[i]->getX(),propiedades[i]->getY(),30,30);
                        if(propiedades[i]->isEnVenta()){
                            ui->comprarJugador2->setEnabled(true);
                        } else if (!propiedades[i]->isEnVenta() && propiedades[i]->isPlayerOneOwner()){
                            ui->pagar2->setEnabled(true);
                        }
                    }
                }
            }
            break;
        case 13:
            for(unsigned long  i = 0; i < propiedades.size(); i++){
                if(propiedades[i]->getNombre() == "Avenida Illinois"){
                    jugador2->setPosicion(propiedades[i]->getPosicion());
                    ui->icon2->setGeometry(propiedades[i]->getX(),propiedades[i]->getY(),30,30);
                }
            }
            bandera = true;
            ui->propiedadesJugador2->setEnabled(false);
            ui->propiedadesJugador1->setEnabled(true);
            ui->construir1->setEnabled(true);
            ui->construir2->setEnabled(false);
            ui->hipotecar1->setEnabled(true);
            ui->hipotecar2->setEnabled(false);
            ui->pushButton->setEnabled(true);
            ui->jugadorActual->setText("Jugador 1");
            m.setText("Termino su turno Jugador 2");
            m.exec();
            break;
        case 14:
            jugador2->recolectar(150);
            ui->dinero2_LCD->display(jugador2->getDinero());
            bandera = true;
            ui->propiedadesJugador2->setEnabled(false);
            ui->propiedadesJugador1->setEnabled(true);
            ui->construir1->setEnabled(true);
            ui->construir2->setEnabled(false);
            ui->hipotecar1->setEnabled(true);
            ui->hipotecar2->setEnabled(false);
            ui->pushButton->setEnabled(true);
            ui->jugadorActual->setText("Jugador 1");
            m.setText("Termino su turno Jugador 2");
            m.exec();
            break;
        case 15:
            for(unsigned long  i = 0; i < propiedades.size(); i++){
                if(propiedades[i]->getNombre() == "Ferrocarril Reading"){
                    jugador2->setPosicion(propiedades[i]->getPosicion());
                    ui->icon2->setGeometry(propiedades[i]->getX(),propiedades[i]->getY(),30,30);
                }
            }
            bandera = true;
            ui->propiedadesJugador2->setEnabled(false);
            ui->propiedadesJugador1->setEnabled(true);
            ui->construir1->setEnabled(true);
            ui->construir2->setEnabled(false);
            ui->hipotecar1->setEnabled(true);
            ui->hipotecar2->setEnabled(false);
            ui->pushButton->setEnabled(true);
            ui->jugadorActual->setText("Jugador 1");
            m.setText("Termino su turno Jugador 2");
            m.exec();
            break;
        case 16:
            for(unsigned long  i = 0; i < propiedades.size(); i++){
                if(propiedades[i]->getNombre() == "El Muelle"){
                    jugador2->setPosicion(propiedades[i]->getPosicion());
                    ui->icon2->setGeometry(propiedades[i]->getX(),propiedades[i]->getY(),30,30);
                }
            }
            bandera = true;
            ui->propiedadesJugador2->setEnabled(false);
            ui->propiedadesJugador1->setEnabled(true);
            ui->construir1->setEnabled(true);
            ui->construir2->setEnabled(false);
            ui->hipotecar1->setEnabled(true);
            ui->hipotecar2->setEnabled(false);
            ui->pushButton->setEnabled(true);
            ui->jugadorActual->setText("Jugador 1");
            m.setText("Termino su turno Jugador 2");
            m.exec();
            break;
        }
    }
}

void MainWindow::on_pagar1_clicked()
{
    if(bandera){
        for(unsigned long i = 0; i < propiedades.size(); i++){
            if(jugador1->getPosicion() == propiedades[i]->getPosicion()){
                if(!propiedades[i]->isEnVenta() && propiedades[i]->isPlayerTwoOwner()){
                    if(typeid(*propiedades[i]) == typeid(PropiedadNormal)){
                        PropiedadNormal* property = dynamic_cast<PropiedadNormal*>(propiedades[i]);
                        jugador1->pagar(property->getRenta());
                        jugador2->recolectar(property->getRenta());
                    }
                    if(typeid(*propiedades[i]) == typeid(Railroad)){
                        Railroad* ferro = dynamic_cast<Railroad*>(propiedades[i]);
                        jugador1->pagar(ferro->getRenta());
                        jugador2->recolectar(ferro->getRenta());
                    }
                    if(typeid(*propiedades[i]) == typeid(Servicio)){
                        Servicio* service = dynamic_cast<Servicio*>(propiedades[i]);
                        jugador1->pagar(service->getRenta());
                        jugador2->recolectar(service->getRenta());
                    }
                    ui->dinero1_LCD->display(jugador1->getDinero());
                    ui->dinero2_LCD->display(jugador2->getDinero());
                    QMessageBox m;
                    m.setText("El jugador 2 le agredece por el pago!");
                    m.exec();
                    bandera = false;
                    QMessageBox m1;
                    m1.setText("Termino su turno Jugador 1");
                    m1.exec();
                    ui->pushButton->setEnabled(true);
                    ui->pagar1->setEnabled(false);
                    ui->construir1->setEnabled(false);
                    ui->construir2->setEnabled(true);
                    ui->hipotecar1->setEnabled(false);
                    ui->hipotecar2->setEnabled(true);
                    ui->propiedadesJugador1->setEnabled(false);
                    ui->propiedadesJugador2->setEnabled(true);
                }
            }
        }
    }
}

void MainWindow::on_subastar1_clicked()
{
    if(bandera){
        for(unsigned long i = 0; i < propiedades.size(); i++){
            if(jugador1->getPosicion() == propiedades[i]->getPosicion()){
                QMessageBox m;
                m.setText("Esta propiedad va a ser subastada al Jugador 2");
                m.exec();
                SubastarDialog subasta(this,QString::number(propiedades[i]->getPrecio()));
                subasta.setModal(true);
                subasta.setVisible(true);
                subasta.exec();
                int newValue = subasta.getNuevoPrecio();
                if(newValue > jugador2->getDinero()){
                    QMessageBox u;
                    u.setText("Jugador 2 no tiene suficiente dinero para comprar la propiedad. La propiedad queda en venta nuevamente.");
                    u.exec();
                    QMessageBox m2;
                    m2.setText("Termino su turno Jugador 1");
                    m2.exec();
                    bandera = false;
                    ui->pushButton->setEnabled(true);
                    ui->comprarJugador1->setEnabled(false);
                    ui->subastar1->setEnabled(false);
                    ui->construir1->setEnabled(false);
                    ui->propiedadesJugador2->setEnabled(true);
                    ui->hipotecar1->setEnabled(false);
                    ui->hipotecar2->setEnabled(true);
                    ui->construir2->setEnabled(true);
                    ui->jugadorActual->setText("Jugador 2");
                    break;
                } else {
                    jugador2->pagar(newValue);
                    ui->dinero2_LCD->display(jugador2->getDinero());
                    propiedades[i]->setPlayerTwoOwner(true);
                    propiedades[i]->setEnVenta(false);
                    propiedadesJugador2.push_back(propiedades[i]);
                    QMessageBox m1;
                    m1.setText("Gracias por Comprar la propiedad Jugador 2");
                    m1.exec();
                    QMessageBox m2;
                    m2.setText("Termino su turno Jugador 1");
                    m2.exec();
                    bandera = false;
                    ui->pushButton->setEnabled(true);
                    ui->comprarJugador1->setEnabled(false);
                    ui->subastar1->setEnabled(false);
                    ui->construir1->setEnabled(false);
                    ui->propiedadesJugador2->setEnabled(true);
                    ui->construir2->setEnabled(true);
                    ui->hipotecar1->setEnabled(false);
                    ui->hipotecar2->setEnabled(true);
                    ui->jugadorActual->setText("Jugador 2");
                    break;
                }
            }
        }
    }
}

void MainWindow::on_pagar2_clicked()
{
    if(!bandera){
        for(unsigned long i = 0; i < propiedades.size(); i++){
            if(jugador2->getPosicion() == propiedades[i]->getPosicion()){
                if(!propiedades[i]->isEnVenta() && propiedades[i]->isPlayerOneOwner()){
                    if(typeid(*propiedades[i]) == typeid(PropiedadNormal)){
                        PropiedadNormal* property = dynamic_cast<PropiedadNormal*>(propiedades[i]);
                        jugador2->pagar(property->getRenta());
                        jugador1->recolectar(property->getRenta());
                    }
                    if(typeid(*propiedades[i]) == typeid(Railroad)){
                        Railroad* ferro = dynamic_cast<Railroad*>(propiedades[i]);
                        jugador2->pagar(ferro->getRenta());
                        jugador1->recolectar(ferro->getRenta());
                    }
                    if(typeid(*propiedades[i]) == typeid(Servicio)){
                        Servicio* service = dynamic_cast<Servicio*>(propiedades[i]);
                        jugador2->pagar(service->getRenta());
                        jugador1->recolectar(service->getRenta());
                    }
                    ui->dinero1_LCD->display(jugador1->getDinero());
                    ui->dinero2_LCD->display(jugador2->getDinero());
                    QMessageBox m;
                    m.setText("El jugador 1 le agredece por el pago!");
                    m.exec();
                    QMessageBox m1;
                    m1.setText("Termino su turno Jugador 2");
                    m.exec();
                    bandera = true;
                    ui->pushButton->setEnabled(true);
                    ui->pagar2->setEnabled(false);
                    ui->hipotecar1->setEnabled(true);
                    ui->hipotecar2->setEnabled(false);
                    ui->propiedadesJugador2->setEnabled(false);
                    ui->propiedadesJugador1->setEnabled(true);
                }
            }
        }
    }
}

void MainWindow::on_subastar2_clicked()
{
    if(!bandera){
        for(unsigned long i = 0; i < propiedades.size(); i++){
            if(jugador2->getPosicion() == propiedades[i]->getPosicion()){
                QMessageBox m;
                m.setText("Esta propiedad va a ser subastada al Jugador 1");
                m.exec();
                SubastarDialog subasta(this,QString::number(propiedades[i]->getPrecio()));
                subasta.setModal(true);
                subasta.setVisible(true);
                subasta.exec();
                int newValue = subasta.getNuevoPrecio();
                if(newValue > jugador1->getDinero()){
                    QMessageBox u;
                    u.setText("Jugador 1 no tiene suficiente dinero para comprar la propiedad. La propiedad queda en venta nuevamente");
                    u.exec();
                    bandera = true;
                    ui->pushButton->setEnabled(true);
                    ui->comprarJugador2->setEnabled(false);
                    ui->construir1->setEnabled(true);
                    ui->construir2->setEnabled(false);
                    ui->subastar2->setEnabled(false);
                    ui->hipotecar1->setEnabled(true);
                    ui->hipotecar2->setEnabled(false);
                    ui->propiedadesJugador1->setEnabled(true);
                    ui->propiedadesJugador2->setEnabled(false);
                    QMessageBox m2;
                    m2.setText("Termino su turno Jugador 2");
                    m2.exec();
                    ui->jugadorActual->setText("Jugador 1");
                    break;
                } else {
                    jugador1->pagar(newValue);
                    ui->dinero1_LCD->display(jugador1->getDinero());
                    propiedades[i]->setPlayerOneOwner(true);
                    propiedades[i]->setEnVenta(false);
                    propiedadesJugador1.push_back(propiedades[i]);
                    QMessageBox m1;
                    m1.setText("Gracias por Comprar la propiedad Jugador 1");
                    m1.exec();
                    QMessageBox m2;
                    m2.setText("Termino su turno Jugador 2");
                    m2.exec();
                    bandera = true;
                    ui->pushButton->setEnabled(true);
                    ui->comprarJugador2->setEnabled(false);
                    ui->construir1->setEnabled(true);
                    ui->construir2->setEnabled(false);
                    ui->subastar2->setEnabled(false);
                    ui->hipotecar1->setEnabled(true);
                    ui->hipotecar2->setEnabled(false);
                    ui->propiedadesJugador1->setEnabled(true);
                    ui->propiedadesJugador2->setEnabled(false);
                    ui->jugadorActual->setText("Jugador 1");
                    break;
                }
            }
        }
    }
}

void MainWindow::on_propiedadesJugador2_clicked()
{
    PropiedadesDialog dialog(propiedadesJugador2,this,"Jugador 2");
    dialog.setVisible(true);
    dialog.setModal(true);
    dialog.exec();
}

void MainWindow::on_propiedadesJugador1_clicked()
{
    PropiedadesDialog dialog(propiedadesJugador1,this,"Jugador1");
    dialog.setVisible(true);
    dialog.setModal(true);
    dialog.exec();
}

void MainWindow::on_pushButton_3_clicked()
{
    /*ifstream infile;
    infile.open(":/partida.txt");
    //Check for an error
    if(infile.fail()){
        cerr << "Error al tratar de abrir el archivo";
    }
    int x,y;
    infile >> x >> y;
    cout << "Number 1: "<<x;
    cout << "Number 2: "<<y;*/

    bool llena1=true;

    QFile file("partida.txt");
       if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
           return;

       QTextStream in(&file);
       while (!in.atEnd()) {

           if(llena1==false){
               QString line = in.readLine();
               QList<QString> array=line.split(",");
               jugador2->setNombre(array[0]);
               jugador2->setDinero(array[1].toDouble());
               jugador2->setPosicion(array[2].toInt());
               for(int i = 0; i < propiedades.size(); i++){
                   if(jugador2->getPosicion() == propiedades[i]->getPosicion()){
                       ui->icon2->setGeometry(propiedades[i]->getX(),propiedades[i]->getY(),30,30);
                       ui->labelFoto2->setPixmap(propiedades[i]->getFoto());
                   }
               }
           }

           if(llena1){
               QString line = in.readLine();
               QList<QString> array=line.split(",");
               jugador1->setNombre(array[0]);
               jugador1->setDinero(array[1].toDouble());
               jugador1->setPosicion(array[2].toInt());
               for(int i = 0; i < propiedades.size(); i++){
                   if(jugador1->getPosicion() == propiedades[i]->getPosicion()){
                       ui->icon1->setGeometry(propiedades[i]->getX(),propiedades[i]->getY(),30,30);
                       ui->labelFoto->setPixmap(propiedades[i]->getFoto());
                   }
               }
               llena1=false;
           }


       }

       ui->dinero1_LCD->display(jugador1->getDinero());
       ui->dinero2_LCD->display(jugador2->getDinero());

       ui->label->setText(jugador1->getNombre());
       ui->label_4->setText(jugador2->getNombre());
}

void MainWindow::on_hipotecar1_clicked()
{
    HipotecarDialog hipoteca(jugador1->getDinero(),bandera,propiedades,this);
    hipoteca.setVisible(true);
    hipoteca.setModal(true);
    hipoteca.exec();
    propiedades = hipoteca.getPropiedades();
    jugador1->setDinero(hipoteca.getDinero());
    ui->dinero1_LCD->display(jugador1->getDinero());
}

void MainWindow::on_hipotecar2_clicked()
{
    HipotecarDialog hipoteca(jugador2->getDinero(),bandera,propiedades,this);
    hipoteca.setVisible(true);
    hipoteca.setModal(true);
    hipoteca.exec();
    propiedades = hipoteca.getPropiedades();
    jugador2->setDinero(hipoteca.getDinero());
    ui->dinero2_LCD->display(jugador2->getDinero());
}

void MainWindow::on_construir1_clicked()
{
    ConstruirDialog construir(jugador1->getDinero(),bandera,propiedades,this);
    construir.setVisible(true);
    construir.setModal(true);
    construir.exec();
}

void MainWindow::on_construir2_clicked()
{
    ConstruirDialog construir(jugador2->getDinero(),bandera,propiedades,this);
    construir.setVisible(true);
    construir.setModal(true);
    construir.exec();
}
