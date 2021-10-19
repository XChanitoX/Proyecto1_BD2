#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QWidget>
#include <QAbstractTableModel>
#include "Librerias.h"

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
    void leyendoConsulta();
    void llenarTabla();
    void Hash(string indicacion);
    void Sequential(string indicacion);
};


#endif // GUI_H
