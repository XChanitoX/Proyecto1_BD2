#include "gui.h"
#include "./ui_gui.h"
#include <string>
#include <vector>
#include "ParserCSV.h"

GUI::GUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GUI)
{
    ui->setupUi(this);

    connect(ui->Enviar, SIGNAL(released()), this,
            SLOT(LlenarTabla()));
}

GUI::~GUI()
{
    delete ui;
}

void GUI::LlenarTabla(){

    QString consulta = ui->Consulta->toPlainText();
    std::string cadenaEntera = consulta.toStdString();
    std::string delimitador = "\n";
    std::vector<std::string> palabras{};

    size_t pos = 0;
    while ((pos = cadenaEntera.find(delimitador)) != std::string::npos) {
        palabras.push_back(cadenaEntera.substr(0, pos));
        cadenaEntera.erase(0, pos + delimitador.length());
    }
    palabras.push_back(cadenaEntera);


    std::string fileName = palabras[0];

    //Busco el parentesis de inicio del nombre del archivo
    int posicion = fileName.find("(");

    fileName = fileName.substr(posicion);

    fileName = fileName.substr(2, fileName.size()-4);


    /*
    ofstream file;
    file.open("../Hola.txt");
    file << "primera línea\n";
    file << "segunda línea\n";
    file << "tercera línea\n";
    file.close();*/

/*
    // Leer el archivo CSV
    ofstream Archivo;
    Archivo.open("../QtApp/archivo.dat",ios::app|ios::binary);

    if(!Archivo.is_open()){
        throw new exception;
    }

    vector<vector<string>> parseado;
    parseado = ParserCSV(fileName);

    for (auto & i : parseado) {
        for (auto & j : i) {
            Archivo << j << " ";
        }
        Archivo << '\n';
    }*/



    QList<QString> contactNames;
    QList<QString> contactPhoneNums;

    // Create some data that is tabular in nature:
    contactNames.append("Thomas");
    contactNames.append("Richard");
    contactNames.append("Harrison");
    contactPhoneNums.append("123-456-7890");
    contactPhoneNums.append("222-333-4444");
    contactPhoneNums.append("333-444-5555");

    // Create model:
    TestModel *PhoneBookModel = new TestModel(this);

    // Populate model with data:
    PhoneBookModel->populateData(contactNames,contactPhoneNums);

    // Connect model to table view:
    ui->Respuesta->setModel(PhoneBookModel);

    // Make table header visible and display table:
    ui->Respuesta->horizontalHeader()->setVisible(true);
    ui->Respuesta->show();

    ui->Consulta->setText("");
}


TestModel::TestModel(QObject *parent) : QAbstractTableModel(parent)
{
}

// Create a method to populate the model with data:
void TestModel::populateData(const QList<QString> &contactName,const QList<QString> &contactPhone)
{
    tm_contact_name.clear();
    tm_contact_name = contactName;
    tm_contact_phone.clear();
    tm_contact_phone = contactPhone;
    return;
}

int TestModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return tm_contact_name.length();
}

int TestModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 2;
}

QVariant TestModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole) {
        return QVariant();
    }
    if (index.column() == 0) {
        return tm_contact_name[index.row()];
    } else if (index.column() == 1) {
        return tm_contact_phone[index.row()];
    }
    return QVariant();
}

QVariant TestModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        if (section == 0) {
            return QString("Name");
        } else if (section == 1) {
            return QString("Phone");
        }
    }
    return QVariant();
}
