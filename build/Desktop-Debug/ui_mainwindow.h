/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QTextEdit *textEdit_Message;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *comboBox_type;
    QLabel *label_2;
    QComboBox *comboBox_list;
    QPushButton *pushButton_send;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(543, 521);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        textEdit_Message = new QTextEdit(centralwidget);
        textEdit_Message->setObjectName("textEdit_Message");

        gridLayout->addWidget(textEdit_Message, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(centralwidget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        comboBox_type = new QComboBox(centralwidget);
        comboBox_type->addItem(QString());
        comboBox_type->addItem(QString());
        comboBox_type->setObjectName("comboBox_type");

        horizontalLayout->addWidget(comboBox_type);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");

        horizontalLayout->addWidget(label_2);

        comboBox_list = new QComboBox(centralwidget);
        comboBox_list->setObjectName("comboBox_list");

        horizontalLayout->addWidget(comboBox_list);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);

        pushButton_send = new QPushButton(centralwidget);
        pushButton_send->setObjectName("pushButton_send");

        gridLayout->addWidget(pushButton_send, 2, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 543, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Transfer Type:", nullptr));
        comboBox_type->setItemText(0, QCoreApplication::translate("MainWindow", "Broadcast", nullptr));
        comboBox_type->setItemText(1, QCoreApplication::translate("MainWindow", "Receiver", nullptr));

        label_2->setText(QCoreApplication::translate("MainWindow", "Client List:", nullptr));
        pushButton_send->setText(QCoreApplication::translate("MainWindow", "Send", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
