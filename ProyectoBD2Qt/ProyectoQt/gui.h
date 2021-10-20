#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QWidget>
#include <QAbstractTableModel>
#include "Librerias.h"
#include "Record.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GUI; }
QT_END_NAMESPACE

class GUI : public QMainWindow
{
    Q_OBJECT

public:
    GUI(QWidget *parent = nullptr);
    ~GUI();

private:
    Ui::GUI *ui;
    QStandardItemModel *csvModel;

private slots:
    void setValueAt(int ix, int jx, const QString &value);
    void leyendoConsulta();
    void Insertar();
    void Remove();
    void RangeSearch();
    void Search();
    void llenarTabla(vector<RecordEdu> registros);
    void Hash(string indicacion);
    void Sequential(string indicacion, vector<RecordEdu> &registros);
};


#endif // GUI_H
