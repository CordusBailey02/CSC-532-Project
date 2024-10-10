/********************************************************************************
** Form generated from reading UI file 'communitiestab.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMMUNITIESTAB_H
#define UI_COMMUNITIESTAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_communitiesTab
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QListWidget *listWidget;

    void setupUi(QDialog *communitiesTab)
    {
        if (communitiesTab->objectName().isEmpty())
            communitiesTab->setObjectName("communitiesTab");
        communitiesTab->resize(400, 300);
        verticalLayout = new QVBoxLayout(communitiesTab);
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(communitiesTab);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        listWidget = new QListWidget(communitiesTab);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        listWidget->setObjectName("listWidget");

        verticalLayout->addWidget(listWidget);


        retranslateUi(communitiesTab);

        QMetaObject::connectSlotsByName(communitiesTab);
    } // setupUi

    void retranslateUi(QDialog *communitiesTab)
    {
        communitiesTab->setWindowTitle(QCoreApplication::translate("communitiesTab", "Communities", nullptr));
        label->setText(QCoreApplication::translate("communitiesTab", "Math", nullptr));

        const bool __sortingEnabled = listWidget->isSortingEnabled();
        listWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget->item(0);
        ___qlistwidgetitem->setText(QCoreApplication::translate("communitiesTab", "Prove 1=2", nullptr));
        QListWidgetItem *___qlistwidgetitem1 = listWidget->item(1);
        ___qlistwidgetitem1->setText(QCoreApplication::translate("communitiesTab", "Integral of ln(x)", nullptr));
        QListWidgetItem *___qlistwidgetitem2 = listWidget->item(2);
        ___qlistwidgetitem2->setText(QCoreApplication::translate("communitiesTab", "Volume of a sphere", nullptr));
        listWidget->setSortingEnabled(__sortingEnabled);

    } // retranslateUi

};

namespace Ui {
    class communitiesTab: public Ui_communitiesTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMMUNITIESTAB_H
