/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *photo_verticalLayout;
    QLabel *photo_label;
    QPushButton *pushButton;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *code_verticalLayout;
    QLabel *logo;
    QLabel *welcome_text;
    QLineEdit *lineEdit;
    QPushButton *pushButton_2;
    QPushButton *sendMessage_bt;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QPushButton *bt_connexion;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(426, 340);
        MainWindow->setMinimumSize(QSize(426, 340));
        MainWindow->setMaximumSize(QSize(426, 340));
        MainWindow->setAutoFillBackground(true);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(9, 9, 241, 291));
        photo_verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        photo_verticalLayout->setSpacing(6);
        photo_verticalLayout->setContentsMargins(11, 11, 11, 11);
        photo_verticalLayout->setObjectName(QStringLiteral("photo_verticalLayout"));
        photo_verticalLayout->setContentsMargins(0, 0, 0, 0);
        photo_label = new QLabel(verticalLayoutWidget);
        photo_label->setObjectName(QStringLiteral("photo_label"));

        photo_verticalLayout->addWidget(photo_label);

        pushButton = new QPushButton(verticalLayoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        photo_verticalLayout->addWidget(pushButton);

        verticalLayoutWidget_2 = new QWidget(centralWidget);
        verticalLayoutWidget_2->setObjectName(QStringLiteral("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(250, 10, 171, 291));
        code_verticalLayout = new QVBoxLayout(verticalLayoutWidget_2);
        code_verticalLayout->setSpacing(6);
        code_verticalLayout->setContentsMargins(11, 11, 11, 11);
        code_verticalLayout->setObjectName(QStringLiteral("code_verticalLayout"));
        code_verticalLayout->setContentsMargins(0, 0, 0, 0);
        logo = new QLabel(verticalLayoutWidget_2);
        logo->setObjectName(QStringLiteral("logo"));

        code_verticalLayout->addWidget(logo);

        welcome_text = new QLabel(verticalLayoutWidget_2);
        welcome_text->setObjectName(QStringLiteral("welcome_text"));

        code_verticalLayout->addWidget(welcome_text);

        lineEdit = new QLineEdit(verticalLayoutWidget_2);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        code_verticalLayout->addWidget(lineEdit);

        pushButton_2 = new QPushButton(verticalLayoutWidget_2);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        code_verticalLayout->addWidget(pushButton_2);

        sendMessage_bt = new QPushButton(verticalLayoutWidget_2);
        sendMessage_bt->setObjectName(QStringLiteral("sendMessage_bt"));

        code_verticalLayout->addWidget(sendMessage_bt);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(verticalLayoutWidget_2);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        bt_connexion = new QPushButton(verticalLayoutWidget_2);
        bt_connexion->setObjectName(QStringLiteral("bt_connexion"));

        horizontalLayout->addWidget(bt_connexion);


        code_verticalLayout->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Visual vision", 0));
        photo_label->setText(QApplication::translate("MainWindow", "Photo about to be taken", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Take picture (5 sec preview)", 0));
        logo->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        welcome_text->setText(QApplication::translate("MainWindow", "Hello, please enter the code", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "Open I/O Device", 0));
        sendMessage_bt->setText(QApplication::translate("MainWindow", "SEND", 0));
        label->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        bt_connexion->setText(QApplication::translate("MainWindow", "Connect", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
