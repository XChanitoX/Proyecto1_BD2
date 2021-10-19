#include "gui.h"
#include "./ui_gui.h"
#include <string>
#include <vector>
#include "ParserCSV.h"
#include "Record.h"
#include "Sequential.h"
#include "Hash.h"

GUI::GUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GUI)
{
    ui->setupUi(this);

    connect(ui->Enviar, SIGNAL(released()), this,
            SLOT(leyendoConsulta()));
}

GUI::~GUI()
{
    delete ui;
}

//---------------------------------------
void GUI::leyendoConsulta(){

    QString consulta = ui->Consulta->toPlainText();
    string cadenaEntera = consulta.toStdString();
    string delimitador = "\n";
    vector<string> palabras{};

    size_t pos = 0;
    while ((pos = cadenaEntera.find(delimitador)) != string::npos) {
        palabras.push_back(cadenaEntera.substr(0, pos));
        cadenaEntera.erase(0, pos + delimitador.length());
    }
    palabras.push_back(cadenaEntera);


    string fileName = palabras[0];

    //Busco el parentesis de inicio del nombre del archivo
    int posicion = fileName.find("(");

    fileName = fileName.substr(posicion);

    fileName = fileName.substr(2, fileName.size()-4);


    //Escoger el metodo a utilizar
    /*
    if(palabras[1].substr(palabras[1].size()-5,palabras[1].size()-2) == "hash;"){
        Hash(palabras[2]);
    }else{
        Sequential(palabras[2]);
    }*/


    // Leer el archivo CSV
    ofstream Archivo;
    Archivo.open("../archivo.dat",ios::app|ios::binary);

    if(!Archivo.is_open()){
        throw new exception;
    }

    //Agarrando lo del Excel
    vector<vector<string>> parseado;
    vector<RecordEdu> registros;
    parseado = ParserCSV(fileName, ',');

    for (int i = 0; i < parseado.size(); i++) {
        for (int j = 0; j < parseado[0].size(); j++) {
            Archivo << parseado[i][j] << ' ';
        }
        Archivo << '\n';
    }

    Archivo.close();

    llenarTabla();
}

void GUI::llenarTabla(){
    csvModel = new QStandardItemModel(this);
    vector<vector<string>> datos;
    datos = ParserCSV("../archivo.dat", ' ');
    int cantidadColumnas = datos[0].size();
    int cantidadFilas = datos.size();

    QStringList lista;
    for (int i = 0; i < cantidadColumnas; i++) {
        lista.append(QString::fromStdString(datos[0][i]));
    }

    csvModel->setColumnCount(cantidadColumnas);
    csvModel->setHorizontalHeaderLabels(lista);
    QList<QStandardItem *> items;

    for (int i = 1; i < cantidadFilas; i++) {
        items.clear();

        for (int j = 0; j < cantidadColumnas; j++) {
            items.append(new QStandardItem(datos[i][j].c_str()));
        }

        csvModel->appendRow(items);
    }

    ui->Respuesta->setModel(csvModel);
}

void GUI::Hash(string indicacion){

}

void GUI::Sequential(string indicacion){

}
