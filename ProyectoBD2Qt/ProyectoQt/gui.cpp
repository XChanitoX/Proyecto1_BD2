#include "gui.h"
#include "./ui_gui.h"
#include "Librerias.h"
#include "ParserCSV.h"
#include "Record.h"
#include "Sequential.h"
#include "Hash.h"

vector<RecordEdu> registros;

GUI::GUI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GUI)
{
    ui->setupUi(this);

    auto model = new QStringListModel(this);

    QStringList list;
    QString tabla1 = "EduDataSet";
    QString tabla2 = "RealStateDataSet";
    list << tabla1 << tabla2;
    model->setStringList(list);
    ui->Tablas->setModel(model);

    connect(ui->Enviar, SIGNAL(released()), this,
            SLOT(leyendoConsulta()));
    connect(ui->Insert, SIGNAL(released()), this,
            SLOT(Insertar()));
    connect(ui->RangeSearch, SIGNAL(released()), this,
            SLOT(RangeSearch()));
    connect(ui->Search, SIGNAL(released()), this,
            SLOT(Search()));
    connect(ui->Remove, SIGNAL(released()), this,
            SLOT(Remove()));
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


    vector<vector<string>> parseado;

    parseado = ParserCSV(fileName, ',');

    vector<RecordEdu> registros;

    for (int i = 1; i < parseado.size(); i++) {
        RecordEdu record = RecordEdu(parseado[i][0],parseado[i][1],parseado[i][2],parseado[i][3],
                parseado[i][4],parseado[i][5],parseado[i][6],parseado[i][7],parseado[i][8],parseado[i][9],
                parseado[i][10],parseado[i][11],parseado[i][12],parseado[i][13],parseado[i][14],parseado[i][15],
                parseado[i][16],parseado[i][17]);
        registros.push_back(record);
    }

    if(palabras[1].substr(palabras[1].size()-5,palabras[1].size()-2) == "hash;"){
        metodo = "hash";
        Hash(palabras[2], registros);
    }else{
        metodo = "sequential";
        Sequential(palabras[2], registros);
    }

    llenarTabla(registros);
}

void GUI::llenarTabla(vector<RecordEdu> registros){

    csvModel = new QStandardItemModel(this);

    int ix = 0;
    while(ix != (int)registros.size()){
        csvModel->setRowCount(ix);
        auto line = registros[ix];

        vector <QString> values;

        QString ID = QString::fromStdString(line.ID);
        QString Gender = QString::fromStdString(line.Gender);
        QString Nacionalidad = QString::fromStdString(line.Nacionalidad);
        QString PlaceofBirth = QString::fromStdString(line.PlaceofBirth);
        QString StageID = QString::fromStdString(line.StageID);
        QString GradeID = QString::fromStdString(line.GradeID);
        QString SectionID = QString::fromStdString(line.SectionID);
        QString Topic = QString::fromStdString(line.Topic);
        QString Semester = QString::fromStdString(line.Semester);
        QString Relation = QString::fromStdString(line.Relation);
        QString raisedhands = QString::fromStdString(line.raisedhands);
        QString visitedResources = QString::fromStdString(line.visitedResources);
        QString announcements = QString::fromStdString(line.announcements);
        QString discussion = QString::fromStdString(line.discussion);
        QString parentAnswer = QString::fromStdString(line.parentAnswer);
        QString parentSchool = QString::fromStdString(line.parentSchool);
        QString studentAbsent = QString::fromStdString(line.studentAbsent);
        QString clase = QString::fromStdString(line.clase);

        values.push_back(ID);
        values.push_back(Gender);
        values.push_back(Nacionalidad);
        values.push_back(PlaceofBirth);
        values.push_back(StageID);
        values.push_back(GradeID);
        values.push_back(SectionID);
        values.push_back(Topic);
        values.push_back(Semester);
        values.push_back(Relation);
        values.push_back(raisedhands);
        values.push_back(visitedResources);
        values.push_back(announcements);
        values.push_back(discussion);
        values.push_back(parentAnswer);
        values.push_back(parentSchool);
        values.push_back(studentAbsent);
        values.push_back(clase);

        const int colCount = values.size();
        csvModel->setColumnCount(colCount);
        for (int jx = 0; jx < colCount; ++jx) {
            setValueAt(ix, jx, values.at(jx));
        }
        ix++;

        for (int i = 0; i < colCount; ++i) {
            values.pop_back();
        }
    }

    ui->Respuesta->setModel(csvModel);
}

void GUI::Insertar(){
    QString texto = ui->TextInsert->text();
    string cadenaEntera = texto.toStdString();
    string delimitador = ",";
    vector<string> palabras{};

    size_t pos = 0;
    while ((pos = cadenaEntera.find(delimitador)) != string::npos) {
        palabras.push_back(cadenaEntera.substr(0, pos));
        cadenaEntera.erase(0, pos + delimitador.length());
    }
    palabras.push_back(cadenaEntera);

    RecordEdu registro;
    registro = RecordEdu(palabras[0],palabras[1],palabras[2],palabras[3],palabras[4],palabras[5],palabras[6],
            palabras[7],palabras[8],palabras[9],palabras[10],palabras[11],palabras[12],palabras[13],palabras[14],
            palabras[15],palabras[16],palabras[17]);

    if(metodo == "hash"){
        auto hash = ExtendibleHash<RecordEdu,const char*,RecordEduHash>();
        hash.setIndexName("../index.dat");
        hash.setBucketName("../bucket.dat");
        hash.insert(registro);
        registros = hash.scanAll();
        llenarTabla(registros);

    }else{
        auto sequentialFile = SequentialFile<RecordEdu,const char*>("../datafile.dat","../auxfile.dat");
        sequentialFile.add_record(registro);
        registros = sequentialFile.load();
        llenarTabla(registros);
    }

}

void GUI::Remove(){
    QString texto = ui->TextDelete->text();
    string cadenaEntera = texto.toStdString();
    if(metodo == "hash"){
        auto hash = ExtendibleHash<RecordEdu,const char*,RecordEduHash>();
        hash.setIndexName("../index.dat");
        hash.setBucketName("../bucket.dat");
        hash.remove(cadenaEntera.c_str());
        registros = hash.scanAll();
        llenarTabla(registros);

    }else{
        auto sequentialFile = SequentialFile<RecordEdu,const char*>("../datafile.dat","../auxfile.dat");
        sequentialFile.remove_record(cadenaEntera.c_str());
        registros = sequentialFile.load();
        llenarTabla(registros);
    }

}

void GUI::RangeSearch(){
    QString texto = ui->TextRangeSearch->text();
    string cadenaEntera = texto.toStdString();
    string delimitador = ",";
    vector<string> palabras{};

    size_t pos = 0;
    while ((pos = cadenaEntera.find(delimitador)) != string::npos) {
        palabras.push_back(cadenaEntera.substr(0, pos));
        cadenaEntera.erase(0, pos + delimitador.length());
    }
    palabras.push_back(cadenaEntera);

    if(metodo == "hash"){
        auto hash = ExtendibleHash<RecordEdu,const char*,RecordEduHash>();
        hash.setIndexName("../index.dat");
        hash.setBucketName("../bucket.dat");
        hash.searchRange(palabras[0].c_str(),palabras[1].c_str());
        registros = hash.scanAll();
        llenarTabla(registros);

    }else{
        auto sequentialFile = SequentialFile<RecordEdu,const char*>("../datafile.dat","../auxfile.dat");
        sequentialFile.search_per_range(palabras[0].c_str(),palabras[1].c_str());
        registros = sequentialFile.load();
        llenarTabla(sequentialFile.search_per_range(palabras[0].c_str(),palabras[1].c_str()));
    }

}


void GUI::Search(){
    QString texto = ui->TextSearch->text();
    string cadenaEntera = texto.toStdString();

    if(metodo == "hash"){
        auto hash = ExtendibleHash<RecordEdu,const char*,RecordEduHash>();
        hash.setIndexName("../index.dat");
        hash.setBucketName("../bucket.dat");
        hash.search(cadenaEntera.c_str());
        registros = hash.scanAll();
        llenarTabla(registros);

    }else{
        auto sequentialFile = SequentialFile<RecordEdu,const char*>("../datafile.dat","../auxfile.dat");
        sequentialFile.search_record(cadenaEntera.c_str());
        registros = sequentialFile.load();
        llenarTabla(sequentialFile.search_record(cadenaEntera.c_str()));
    }

}

void GUI::Hash(string indicacion, vector<RecordEdu> &registros){
    auto hash = ExtendibleHash<RecordEdu,const char*,RecordEduHash>();
    hash.setIndexName("../index.dat");
    hash.setBucketName("../bucket.dat");
    hash.insertAll(registros);
    registros = hash.scanAll();
}

void GUI::Sequential(string indicacion, vector<RecordEdu> &registros){
    auto sequentialFile = SequentialFile<RecordEdu,const char*>("../datafile.dat","../auxfile.dat");
    sequentialFile.insert_all(registros);
    registros = sequentialFile.load();
}

void GUI::setValueAt(int ix, int jx, const QString &value)
{
    if(!csvModel->item(ix, jx)){
        csvModel->setItem(ix, jx, new QStandardItem(value));
    } else{
        csvModel->item(ix, jx)->setText(value);
    }
}


