/********************************************************************************
** Form generated from reading UI file 'secdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SECDIALOG_H
#define UI_SECDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SecDialog
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QPushButton *pushButton_3;
    QLineEdit *lineEdit;
    QListWidget *listWidget_2;
    QListWidget *listWidget;
    QPushButton *pushButton_2;
    QListWidget *listWidget_3;
    QPushButton *pushButton;
    QLabel *label_3;
    QLabel *label_2;
    QLabel *label;

    void setupUi(QDialog *SecDialog)
    {
        if (SecDialog->objectName().isEmpty())
            SecDialog->setObjectName("SecDialog");
        SecDialog->resize(535, 297);
        verticalLayout = new QVBoxLayout(SecDialog);
        verticalLayout->setObjectName("verticalLayout");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        pushButton_3 = new QPushButton(SecDialog);
        pushButton_3->setObjectName("pushButton_3");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButton_3, 0, 4, 1, 1);

        lineEdit = new QLineEdit(SecDialog);
        lineEdit->setObjectName("lineEdit");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(lineEdit, 0, 1, 1, 3);

        listWidget_2 = new QListWidget(SecDialog);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        new QListWidgetItem(listWidget_2);
        listWidget_2->setObjectName("listWidget_2");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(listWidget_2->sizePolicy().hasHeightForWidth());
        listWidget_2->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(listWidget_2, 2, 4, 3, 2);

        listWidget = new QListWidget(SecDialog);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        listWidget->setObjectName("listWidget");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Maximum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(listWidget->sizePolicy().hasHeightForWidth());
        listWidget->setSizePolicy(sizePolicy3);

        gridLayout->addWidget(listWidget, 4, 0, 1, 4);

        pushButton_2 = new QPushButton(SecDialog);
        pushButton_2->setObjectName("pushButton_2");
        sizePolicy.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButton_2, 0, 5, 1, 1);

        listWidget_3 = new QListWidget(SecDialog);
        new QListWidgetItem(listWidget_3);
        new QListWidgetItem(listWidget_3);
        new QListWidgetItem(listWidget_3);
        new QListWidgetItem(listWidget_3);
        new QListWidgetItem(listWidget_3);
        new QListWidgetItem(listWidget_3);
        new QListWidgetItem(listWidget_3);
        new QListWidgetItem(listWidget_3);
        new QListWidgetItem(listWidget_3);
        new QListWidgetItem(listWidget_3);
        new QListWidgetItem(listWidget_3);
        new QListWidgetItem(listWidget_3);
        new QListWidgetItem(listWidget_3);
        new QListWidgetItem(listWidget_3);
        new QListWidgetItem(listWidget_3);
        new QListWidgetItem(listWidget_3);
        new QListWidgetItem(listWidget_3);
        new QListWidgetItem(listWidget_3);
        new QListWidgetItem(listWidget_3);
        new QListWidgetItem(listWidget_3);
        listWidget_3->setObjectName("listWidget_3");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Maximum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(listWidget_3->sizePolicy().hasHeightForWidth());
        listWidget_3->setSizePolicy(sizePolicy4);

        gridLayout->addWidget(listWidget_3, 2, 0, 1, 4);

        pushButton = new QPushButton(SecDialog);
        pushButton->setObjectName("pushButton");
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButton, 0, 0, 1, 1);

        label_3 = new QLabel(SecDialog);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 3, 0, 1, 1);

        label_2 = new QLabel(SecDialog);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 1, 0, 1, 2);

        label = new QLabel(SecDialog);
        label->setObjectName("label");

        gridLayout->addWidget(label, 1, 4, 1, 2);


        verticalLayout->addLayout(gridLayout);


        retranslateUi(SecDialog);

        QMetaObject::connectSlotsByName(SecDialog);
    } // setupUi

    void retranslateUi(QDialog *SecDialog)
    {
        SecDialog->setWindowTitle(QCoreApplication::translate("SecDialog", "Dialog", nullptr));
        pushButton_3->setText(QCoreApplication::translate("SecDialog", "Search", nullptr));

        const bool __sortingEnabled = listWidget_2->isSortingEnabled();
        listWidget_2->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget_2->item(0);
        ___qlistwidgetitem->setText(QCoreApplication::translate("SecDialog", "1", nullptr));
        QListWidgetItem *___qlistwidgetitem1 = listWidget_2->item(1);
        ___qlistwidgetitem1->setText(QCoreApplication::translate("SecDialog", "2", nullptr));
        QListWidgetItem *___qlistwidgetitem2 = listWidget_2->item(2);
        ___qlistwidgetitem2->setText(QCoreApplication::translate("SecDialog", "3", nullptr));
        QListWidgetItem *___qlistwidgetitem3 = listWidget_2->item(3);
        ___qlistwidgetitem3->setText(QCoreApplication::translate("SecDialog", "4", nullptr));
        QListWidgetItem *___qlistwidgetitem4 = listWidget_2->item(4);
        ___qlistwidgetitem4->setText(QCoreApplication::translate("SecDialog", "5", nullptr));
        QListWidgetItem *___qlistwidgetitem5 = listWidget_2->item(5);
        ___qlistwidgetitem5->setText(QCoreApplication::translate("SecDialog", "6", nullptr));
        QListWidgetItem *___qlistwidgetitem6 = listWidget_2->item(6);
        ___qlistwidgetitem6->setText(QCoreApplication::translate("SecDialog", "7", nullptr));
        QListWidgetItem *___qlistwidgetitem7 = listWidget_2->item(7);
        ___qlistwidgetitem7->setText(QCoreApplication::translate("SecDialog", "8", nullptr));
        QListWidgetItem *___qlistwidgetitem8 = listWidget_2->item(8);
        ___qlistwidgetitem8->setText(QCoreApplication::translate("SecDialog", "9", nullptr));
        QListWidgetItem *___qlistwidgetitem9 = listWidget_2->item(9);
        ___qlistwidgetitem9->setText(QCoreApplication::translate("SecDialog", "1", nullptr));
        QListWidgetItem *___qlistwidgetitem10 = listWidget_2->item(10);
        ___qlistwidgetitem10->setText(QCoreApplication::translate("SecDialog", "2", nullptr));
        QListWidgetItem *___qlistwidgetitem11 = listWidget_2->item(11);
        ___qlistwidgetitem11->setText(QCoreApplication::translate("SecDialog", "3", nullptr));
        QListWidgetItem *___qlistwidgetitem12 = listWidget_2->item(12);
        ___qlistwidgetitem12->setText(QCoreApplication::translate("SecDialog", "4", nullptr));
        QListWidgetItem *___qlistwidgetitem13 = listWidget_2->item(13);
        ___qlistwidgetitem13->setText(QCoreApplication::translate("SecDialog", "5", nullptr));
        QListWidgetItem *___qlistwidgetitem14 = listWidget_2->item(14);
        ___qlistwidgetitem14->setText(QCoreApplication::translate("SecDialog", "6", nullptr));
        QListWidgetItem *___qlistwidgetitem15 = listWidget_2->item(15);
        ___qlistwidgetitem15->setText(QCoreApplication::translate("SecDialog", "7", nullptr));
        QListWidgetItem *___qlistwidgetitem16 = listWidget_2->item(16);
        ___qlistwidgetitem16->setText(QCoreApplication::translate("SecDialog", "8", nullptr));
        QListWidgetItem *___qlistwidgetitem17 = listWidget_2->item(17);
        ___qlistwidgetitem17->setText(QCoreApplication::translate("SecDialog", "9", nullptr));
        QListWidgetItem *___qlistwidgetitem18 = listWidget_2->item(18);
        ___qlistwidgetitem18->setText(QCoreApplication::translate("SecDialog", "1", nullptr));
        QListWidgetItem *___qlistwidgetitem19 = listWidget_2->item(19);
        ___qlistwidgetitem19->setText(QCoreApplication::translate("SecDialog", "2", nullptr));
        QListWidgetItem *___qlistwidgetitem20 = listWidget_2->item(20);
        ___qlistwidgetitem20->setText(QCoreApplication::translate("SecDialog", "3", nullptr));
        QListWidgetItem *___qlistwidgetitem21 = listWidget_2->item(21);
        ___qlistwidgetitem21->setText(QCoreApplication::translate("SecDialog", "4", nullptr));
        QListWidgetItem *___qlistwidgetitem22 = listWidget_2->item(22);
        ___qlistwidgetitem22->setText(QCoreApplication::translate("SecDialog", "5", nullptr));
        QListWidgetItem *___qlistwidgetitem23 = listWidget_2->item(23);
        ___qlistwidgetitem23->setText(QCoreApplication::translate("SecDialog", "6", nullptr));
        QListWidgetItem *___qlistwidgetitem24 = listWidget_2->item(24);
        ___qlistwidgetitem24->setText(QCoreApplication::translate("SecDialog", "7", nullptr));
        QListWidgetItem *___qlistwidgetitem25 = listWidget_2->item(25);
        ___qlistwidgetitem25->setText(QCoreApplication::translate("SecDialog", "8", nullptr));
        QListWidgetItem *___qlistwidgetitem26 = listWidget_2->item(26);
        ___qlistwidgetitem26->setText(QCoreApplication::translate("SecDialog", "9", nullptr));
        QListWidgetItem *___qlistwidgetitem27 = listWidget_2->item(27);
        ___qlistwidgetitem27->setText(QCoreApplication::translate("SecDialog", "1", nullptr));
        QListWidgetItem *___qlistwidgetitem28 = listWidget_2->item(28);
        ___qlistwidgetitem28->setText(QCoreApplication::translate("SecDialog", "2", nullptr));
        QListWidgetItem *___qlistwidgetitem29 = listWidget_2->item(29);
        ___qlistwidgetitem29->setText(QCoreApplication::translate("SecDialog", "3", nullptr));
        QListWidgetItem *___qlistwidgetitem30 = listWidget_2->item(30);
        ___qlistwidgetitem30->setText(QCoreApplication::translate("SecDialog", "4", nullptr));
        QListWidgetItem *___qlistwidgetitem31 = listWidget_2->item(31);
        ___qlistwidgetitem31->setText(QCoreApplication::translate("SecDialog", "5", nullptr));
        QListWidgetItem *___qlistwidgetitem32 = listWidget_2->item(32);
        ___qlistwidgetitem32->setText(QCoreApplication::translate("SecDialog", "6", nullptr));
        QListWidgetItem *___qlistwidgetitem33 = listWidget_2->item(33);
        ___qlistwidgetitem33->setText(QCoreApplication::translate("SecDialog", "7", nullptr));
        QListWidgetItem *___qlistwidgetitem34 = listWidget_2->item(34);
        ___qlistwidgetitem34->setText(QCoreApplication::translate("SecDialog", "8", nullptr));
        QListWidgetItem *___qlistwidgetitem35 = listWidget_2->item(35);
        ___qlistwidgetitem35->setText(QCoreApplication::translate("SecDialog", "9", nullptr));
        listWidget_2->setSortingEnabled(__sortingEnabled);


        const bool __sortingEnabled1 = listWidget->isSortingEnabled();
        listWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem36 = listWidget->item(0);
        ___qlistwidgetitem36->setText(QCoreApplication::translate("SecDialog", "Who has \"decision-authority\" about paper content: First author or the co-author with the higher academic rank?", nullptr));
        QListWidgetItem *___qlistwidgetitem37 = listWidget->item(1);
        ___qlistwidgetitem37->setText(QCoreApplication::translate("SecDialog", "How to discuss traumatic experiences that might sound fabricated or distorted in graduate school applications", nullptr));
        QListWidgetItem *___qlistwidgetitem38 = listWidget->item(2);
        ___qlistwidgetitem38->setText(QCoreApplication::translate("SecDialog", "What is the position of Lebanon about the presence of the Hezbollah on its territory?", nullptr));
        QListWidgetItem *___qlistwidgetitem39 = listWidget->item(3);
        ___qlistwidgetitem39->setText(QCoreApplication::translate("SecDialog", "Is there any evidence on whether \"Balrog\" from Street Fighter is named after the Balrogs in The Lord of the Rings?", nullptr));
        QListWidgetItem *___qlistwidgetitem40 = listWidget->item(4);
        ___qlistwidgetitem40->setText(QCoreApplication::translate("SecDialog", "Does God the Son have Faith?", nullptr));
        QListWidgetItem *___qlistwidgetitem41 = listWidget->item(5);
        ___qlistwidgetitem41->setText(QCoreApplication::translate("SecDialog", "Reference Request for global H\303\266lder continuity of solutions to elliptic PDEs", nullptr));
        QListWidgetItem *___qlistwidgetitem42 = listWidget->item(6);
        ___qlistwidgetitem42->setText(QCoreApplication::translate("SecDialog", "Draw a string as a binary tree", nullptr));
        QListWidgetItem *___qlistwidgetitem43 = listWidget->item(7);
        ___qlistwidgetitem43->setText(QCoreApplication::translate("SecDialog", "Disk-sound after mounting", nullptr));
        QListWidgetItem *___qlistwidgetitem44 = listWidget->item(8);
        ___qlistwidgetitem44->setText(QCoreApplication::translate("SecDialog", "Is it possible to have two normally open circuits and use one switch to close one or the other (never both at once for my purposes)?", nullptr));
        QListWidgetItem *___qlistwidgetitem45 = listWidget->item(9);
        ___qlistwidgetitem45->setText(QCoreApplication::translate("SecDialog", "Covering directions with rational circles", nullptr));
        QListWidgetItem *___qlistwidgetitem46 = listWidget->item(10);
        ___qlistwidgetitem46->setText(QCoreApplication::translate("SecDialog", "How do I justify a society where people have two permanent homes: a summer home and a winter home?", nullptr));
        QListWidgetItem *___qlistwidgetitem47 = listWidget->item(11);
        ___qlistwidgetitem47->setText(QCoreApplication::translate("SecDialog", "Why do communists claim that capitalism began at the Industrial Revolution?", nullptr));
        QListWidgetItem *___qlistwidgetitem48 = listWidget->item(12);
        ___qlistwidgetitem48->setText(QCoreApplication::translate("SecDialog", "A short series of books in which the main character belongs to a race of beings who can create/reset the universe", nullptr));
        QListWidgetItem *___qlistwidgetitem49 = listWidget->item(13);
        ___qlistwidgetitem49->setText(QCoreApplication::translate("SecDialog", "Why are sportsmen not desirous to have others of their persuasion move in?", nullptr));
        QListWidgetItem *___qlistwidgetitem50 = listWidget->item(14);
        ___qlistwidgetitem50->setText(QCoreApplication::translate("SecDialog", "What do the Apollo crew mean by \"you're five square\"", nullptr));
        QListWidgetItem *___qlistwidgetitem51 = listWidget->item(15);
        ___qlistwidgetitem51->setText(QCoreApplication::translate("SecDialog", "Prepping basement for drywall; how to deal with electrical wires running across joists?", nullptr));
        QListWidgetItem *___qlistwidgetitem52 = listWidget->item(16);
        ___qlistwidgetitem52->setText(QCoreApplication::translate("SecDialog", "In a perfect vacuum, shouldn't every solid be above its sublimation point, since its vapor pressure must exceed the atmospheric pressure?", nullptr));
        listWidget->setSortingEnabled(__sortingEnabled1);

        pushButton_2->setText(QString());

        const bool __sortingEnabled2 = listWidget_3->isSortingEnabled();
        listWidget_3->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem53 = listWidget_3->item(0);
        ___qlistwidgetitem53->setText(QCoreApplication::translate("SecDialog", "1", nullptr));
        QListWidgetItem *___qlistwidgetitem54 = listWidget_3->item(1);
        ___qlistwidgetitem54->setText(QCoreApplication::translate("SecDialog", "2", nullptr));
        QListWidgetItem *___qlistwidgetitem55 = listWidget_3->item(2);
        ___qlistwidgetitem55->setText(QCoreApplication::translate("SecDialog", "3", nullptr));
        QListWidgetItem *___qlistwidgetitem56 = listWidget_3->item(3);
        ___qlistwidgetitem56->setText(QCoreApplication::translate("SecDialog", "4", nullptr));
        QListWidgetItem *___qlistwidgetitem57 = listWidget_3->item(4);
        ___qlistwidgetitem57->setText(QCoreApplication::translate("SecDialog", "5", nullptr));
        QListWidgetItem *___qlistwidgetitem58 = listWidget_3->item(5);
        ___qlistwidgetitem58->setText(QCoreApplication::translate("SecDialog", "6", nullptr));
        QListWidgetItem *___qlistwidgetitem59 = listWidget_3->item(6);
        ___qlistwidgetitem59->setText(QCoreApplication::translate("SecDialog", "7", nullptr));
        QListWidgetItem *___qlistwidgetitem60 = listWidget_3->item(7);
        ___qlistwidgetitem60->setText(QCoreApplication::translate("SecDialog", "8", nullptr));
        QListWidgetItem *___qlistwidgetitem61 = listWidget_3->item(8);
        ___qlistwidgetitem61->setText(QCoreApplication::translate("SecDialog", "9", nullptr));
        QListWidgetItem *___qlistwidgetitem62 = listWidget_3->item(9);
        ___qlistwidgetitem62->setText(QCoreApplication::translate("SecDialog", "10", nullptr));
        QListWidgetItem *___qlistwidgetitem63 = listWidget_3->item(10);
        ___qlistwidgetitem63->setText(QCoreApplication::translate("SecDialog", "11", nullptr));
        QListWidgetItem *___qlistwidgetitem64 = listWidget_3->item(11);
        ___qlistwidgetitem64->setText(QCoreApplication::translate("SecDialog", "12", nullptr));
        QListWidgetItem *___qlistwidgetitem65 = listWidget_3->item(12);
        ___qlistwidgetitem65->setText(QCoreApplication::translate("SecDialog", "13", nullptr));
        QListWidgetItem *___qlistwidgetitem66 = listWidget_3->item(13);
        ___qlistwidgetitem66->setText(QCoreApplication::translate("SecDialog", "14", nullptr));
        QListWidgetItem *___qlistwidgetitem67 = listWidget_3->item(14);
        ___qlistwidgetitem67->setText(QCoreApplication::translate("SecDialog", "15", nullptr));
        QListWidgetItem *___qlistwidgetitem68 = listWidget_3->item(15);
        ___qlistwidgetitem68->setText(QCoreApplication::translate("SecDialog", "16", nullptr));
        QListWidgetItem *___qlistwidgetitem69 = listWidget_3->item(16);
        ___qlistwidgetitem69->setText(QCoreApplication::translate("SecDialog", "17", nullptr));
        QListWidgetItem *___qlistwidgetitem70 = listWidget_3->item(17);
        ___qlistwidgetitem70->setText(QCoreApplication::translate("SecDialog", "18", nullptr));
        QListWidgetItem *___qlistwidgetitem71 = listWidget_3->item(18);
        ___qlistwidgetitem71->setText(QCoreApplication::translate("SecDialog", "19", nullptr));
        QListWidgetItem *___qlistwidgetitem72 = listWidget_3->item(19);
        ___qlistwidgetitem72->setText(QCoreApplication::translate("SecDialog", "20", nullptr));
        listWidget_3->setSortingEnabled(__sortingEnabled2);

        pushButton->setText(QCoreApplication::translate("SecDialog", "Ask a Question", nullptr));
        label_3->setText(QCoreApplication::translate("SecDialog", "TextLabel", nullptr));
        label_2->setText(QCoreApplication::translate("SecDialog", "TextLabel", nullptr));
        label->setText(QCoreApplication::translate("SecDialog", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SecDialog: public Ui_SecDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SECDIALOG_H
