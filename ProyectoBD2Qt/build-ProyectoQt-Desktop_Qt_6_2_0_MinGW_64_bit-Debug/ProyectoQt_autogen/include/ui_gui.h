/********************************************************************************
** Form generated from reading UI file 'gui.ui'
**
** Created by: Qt User Interface Compiler version 6.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GUI_H
#define UI_GUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GUI
{
public:
    QWidget *centralwidget;
    QTableView *Respuesta;
    QTextEdit *Consulta;
    QPushButton *Enviar;
    QLineEdit *lineEdit;
    QListView *Tablas;
    QScrollBar *verticalScrollBar;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *GUI)
    {
        if (GUI->objectName().isEmpty())
            GUI->setObjectName(QString::fromUtf8("GUI"));
        GUI->resize(800, 600);
        centralwidget = new QWidget(GUI);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        Respuesta = new QTableView(centralwidget);
        Respuesta->setObjectName(QString::fromUtf8("Respuesta"));
        Respuesta->setGeometry(QRect(20, 200, 751, 341));
        Consulta = new QTextEdit(centralwidget);
        Consulta->setObjectName(QString::fromUtf8("Consulta"));
        Consulta->setGeometry(QRect(283, 10, 501, 141));
        Enviar = new QPushButton(centralwidget);
        Enviar->setObjectName(QString::fromUtf8("Enviar"));
        Enviar->setGeometry(QRect(690, 150, 93, 28));
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(20, 10, 231, 31));
        lineEdit->setAlignment(Qt::AlignCenter);
        Tablas = new QListView(centralwidget);
        Tablas->setObjectName(QString::fromUtf8("Tablas"));
        Tablas->setGeometry(QRect(20, 40, 231, 111));
        verticalScrollBar = new QScrollBar(centralwidget);
        verticalScrollBar->setObjectName(QString::fromUtf8("verticalScrollBar"));
        verticalScrollBar->setGeometry(QRect(770, 200, 20, 341));
        verticalScrollBar->setOrientation(Qt::Vertical);
        GUI->setCentralWidget(centralwidget);
        menubar = new QMenuBar(GUI);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        GUI->setMenuBar(menubar);
        statusbar = new QStatusBar(GUI);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        GUI->setStatusBar(statusbar);

        retranslateUi(GUI);

        QMetaObject::connectSlotsByName(GUI);
    } // setupUi

    void retranslateUi(QMainWindow *GUI)
    {
        GUI->setWindowTitle(QCoreApplication::translate("GUI", "GUI", nullptr));
        Enviar->setText(QCoreApplication::translate("GUI", "Enviar", nullptr));
        lineEdit->setText(QCoreApplication::translate("GUI", "Tablas", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GUI: public Ui_GUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GUI_H
