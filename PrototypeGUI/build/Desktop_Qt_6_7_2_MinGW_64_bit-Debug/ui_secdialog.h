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
    QLabel *label_2;
    QLabel *label;
    QLabel *label_3;

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

        label_2 = new QLabel(SecDialog);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 1, 0, 1, 2);

        label = new QLabel(SecDialog);
        label->setObjectName("label");

        gridLayout->addWidget(label, 1, 4, 1, 2);

        label_3 = new QLabel(SecDialog);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 3, 0, 1, 2);


        verticalLayout->addLayout(gridLayout);


        retranslateUi(SecDialog);

        QMetaObject::connectSlotsByName(SecDialog);
    } // setupUi

    void retranslateUi(QDialog *SecDialog)
    {
        SecDialog->setWindowTitle(QCoreApplication::translate("SecDialog", "Main Window", nullptr));
        pushButton_3->setText(QCoreApplication::translate("SecDialog", "Search", nullptr));

        const bool __sortingEnabled = listWidget_2->isSortingEnabled();
        listWidget_2->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget_2->item(0);
        ___qlistwidgetitem->setText(QCoreApplication::translate("SecDialog", "Animals", nullptr));
        QListWidgetItem *___qlistwidgetitem1 = listWidget_2->item(1);
        ___qlistwidgetitem1->setText(QCoreApplication::translate("SecDialog", "Architecture", nullptr));
        QListWidgetItem *___qlistwidgetitem2 = listWidget_2->item(2);
        ___qlistwidgetitem2->setText(QCoreApplication::translate("SecDialog", "Astronomy", nullptr));
        QListWidgetItem *___qlistwidgetitem3 = listWidget_2->item(3);
        ___qlistwidgetitem3->setText(QCoreApplication::translate("SecDialog", "Coding", nullptr));
        QListWidgetItem *___qlistwidgetitem4 = listWidget_2->item(4);
        ___qlistwidgetitem4->setText(QCoreApplication::translate("SecDialog", "Computer Hardware", nullptr));
        QListWidgetItem *___qlistwidgetitem5 = listWidget_2->item(5);
        ___qlistwidgetitem5->setText(QCoreApplication::translate("SecDialog", "Computer Science", nullptr));
        QListWidgetItem *___qlistwidgetitem6 = listWidget_2->item(6);
        ___qlistwidgetitem6->setText(QCoreApplication::translate("SecDialog", "Cryptography", nullptr));
        QListWidgetItem *___qlistwidgetitem7 = listWidget_2->item(7);
        ___qlistwidgetitem7->setText(QCoreApplication::translate("SecDialog", "Cycling", nullptr));
        QListWidgetItem *___qlistwidgetitem8 = listWidget_2->item(8);
        ___qlistwidgetitem8->setText(QCoreApplication::translate("SecDialog", "Dating", nullptr));
        QListWidgetItem *___qlistwidgetitem9 = listWidget_2->item(9);
        ___qlistwidgetitem9->setText(QCoreApplication::translate("SecDialog", "Drinks", nullptr));
        QListWidgetItem *___qlistwidgetitem10 = listWidget_2->item(10);
        ___qlistwidgetitem10->setText(QCoreApplication::translate("SecDialog", "Economy", nullptr));
        QListWidgetItem *___qlistwidgetitem11 = listWidget_2->item(11);
        ___qlistwidgetitem11->setText(QCoreApplication::translate("SecDialog", "Engagement", nullptr));
        QListWidgetItem *___qlistwidgetitem12 = listWidget_2->item(12);
        ___qlistwidgetitem12->setText(QCoreApplication::translate("SecDialog", "Engineering", nullptr));
        QListWidgetItem *___qlistwidgetitem13 = listWidget_2->item(13);
        ___qlistwidgetitem13->setText(QCoreApplication::translate("SecDialog", "Finances", nullptr));
        QListWidgetItem *___qlistwidgetitem14 = listWidget_2->item(14);
        ___qlistwidgetitem14->setText(QCoreApplication::translate("SecDialog", "Food", nullptr));
        QListWidgetItem *___qlistwidgetitem15 = listWidget_2->item(15);
        ___qlistwidgetitem15->setText(QCoreApplication::translate("SecDialog", "Furniture", nullptr));
        QListWidgetItem *___qlistwidgetitem16 = listWidget_2->item(16);
        ___qlistwidgetitem16->setText(QCoreApplication::translate("SecDialog", "Housing", nullptr));
        QListWidgetItem *___qlistwidgetitem17 = listWidget_2->item(17);
        ___qlistwidgetitem17->setText(QCoreApplication::translate("SecDialog", "Jobs", nullptr));
        QListWidgetItem *___qlistwidgetitem18 = listWidget_2->item(18);
        ___qlistwidgetitem18->setText(QCoreApplication::translate("SecDialog", "Marriage", nullptr));
        QListWidgetItem *___qlistwidgetitem19 = listWidget_2->item(19);
        ___qlistwidgetitem19->setText(QCoreApplication::translate("SecDialog", "Math", nullptr));
        QListWidgetItem *___qlistwidgetitem20 = listWidget_2->item(20);
        ___qlistwidgetitem20->setText(QCoreApplication::translate("SecDialog", "Parenting", nullptr));
        QListWidgetItem *___qlistwidgetitem21 = listWidget_2->item(21);
        ___qlistwidgetitem21->setText(QCoreApplication::translate("SecDialog", "Technology", nullptr));
        QListWidgetItem *___qlistwidgetitem22 = listWidget_2->item(22);
        ___qlistwidgetitem22->setText(QCoreApplication::translate("SecDialog", "Traveling", nullptr));
        QListWidgetItem *___qlistwidgetitem23 = listWidget_2->item(23);
        ___qlistwidgetitem23->setText(QCoreApplication::translate("SecDialog", "Politics", nullptr));
        QListWidgetItem *___qlistwidgetitem24 = listWidget_2->item(24);
        ___qlistwidgetitem24->setText(QCoreApplication::translate("SecDialog", "Psychology", nullptr));
        QListWidgetItem *___qlistwidgetitem25 = listWidget_2->item(25);
        ___qlistwidgetitem25->setText(QCoreApplication::translate("SecDialog", "Religion", nullptr));
        QListWidgetItem *___qlistwidgetitem26 = listWidget_2->item(26);
        ___qlistwidgetitem26->setText(QCoreApplication::translate("SecDialog", "Science", nullptr));
        listWidget_2->setSortingEnabled(__sortingEnabled);


        const bool __sortingEnabled1 = listWidget->isSortingEnabled();
        listWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem27 = listWidget->item(0);
        ___qlistwidgetitem27->setText(QCoreApplication::translate("SecDialog", "Who has \"decision-authority\" about paper content: First author or the co-author with the higher academic rank?", nullptr));
        QListWidgetItem *___qlistwidgetitem28 = listWidget->item(1);
        ___qlistwidgetitem28->setText(QCoreApplication::translate("SecDialog", "How to discuss traumatic experiences that might sound fabricated or distorted in graduate school applications", nullptr));
        QListWidgetItem *___qlistwidgetitem29 = listWidget->item(2);
        ___qlistwidgetitem29->setText(QCoreApplication::translate("SecDialog", "What is the position of Lebanon about the presence of the Hezbollah on its territory?", nullptr));
        QListWidgetItem *___qlistwidgetitem30 = listWidget->item(3);
        ___qlistwidgetitem30->setText(QCoreApplication::translate("SecDialog", "Is there any evidence on whether \"Balrog\" from Street Fighter is named after the Balrogs in The Lord of the Rings?", nullptr));
        QListWidgetItem *___qlistwidgetitem31 = listWidget->item(4);
        ___qlistwidgetitem31->setText(QCoreApplication::translate("SecDialog", "Does God the Son have Faith?", nullptr));
        QListWidgetItem *___qlistwidgetitem32 = listWidget->item(5);
        ___qlistwidgetitem32->setText(QCoreApplication::translate("SecDialog", "Reference Request for global H\303\266lder continuity of solutions to elliptic PDEs", nullptr));
        QListWidgetItem *___qlistwidgetitem33 = listWidget->item(6);
        ___qlistwidgetitem33->setText(QCoreApplication::translate("SecDialog", "Draw a string as a binary tree", nullptr));
        QListWidgetItem *___qlistwidgetitem34 = listWidget->item(7);
        ___qlistwidgetitem34->setText(QCoreApplication::translate("SecDialog", "Disk-sound after mounting", nullptr));
        QListWidgetItem *___qlistwidgetitem35 = listWidget->item(8);
        ___qlistwidgetitem35->setText(QCoreApplication::translate("SecDialog", "Is it possible to have two normally open circuits and use one switch to close one or the other (never both at once for my purposes)?", nullptr));
        QListWidgetItem *___qlistwidgetitem36 = listWidget->item(9);
        ___qlistwidgetitem36->setText(QCoreApplication::translate("SecDialog", "Covering directions with rational circles", nullptr));
        QListWidgetItem *___qlistwidgetitem37 = listWidget->item(10);
        ___qlistwidgetitem37->setText(QCoreApplication::translate("SecDialog", "How do I justify a society where people have two permanent homes: a summer home and a winter home?", nullptr));
        QListWidgetItem *___qlistwidgetitem38 = listWidget->item(11);
        ___qlistwidgetitem38->setText(QCoreApplication::translate("SecDialog", "Why do communists claim that capitalism began at the Industrial Revolution?", nullptr));
        QListWidgetItem *___qlistwidgetitem39 = listWidget->item(12);
        ___qlistwidgetitem39->setText(QCoreApplication::translate("SecDialog", "A short series of books in which the main character belongs to a race of beings who can create/reset the universe", nullptr));
        QListWidgetItem *___qlistwidgetitem40 = listWidget->item(13);
        ___qlistwidgetitem40->setText(QCoreApplication::translate("SecDialog", "Why are sportsmen not desirous to have others of their persuasion move in?", nullptr));
        QListWidgetItem *___qlistwidgetitem41 = listWidget->item(14);
        ___qlistwidgetitem41->setText(QCoreApplication::translate("SecDialog", "What do the Apollo crew mean by \"you're five square\"", nullptr));
        QListWidgetItem *___qlistwidgetitem42 = listWidget->item(15);
        ___qlistwidgetitem42->setText(QCoreApplication::translate("SecDialog", "Prepping basement for drywall; how to deal with electrical wires running across joists?", nullptr));
        QListWidgetItem *___qlistwidgetitem43 = listWidget->item(16);
        ___qlistwidgetitem43->setText(QCoreApplication::translate("SecDialog", "In a perfect vacuum, shouldn't every solid be above its sublimation point, since its vapor pressure must exceed the atmospheric pressure?", nullptr));
        listWidget->setSortingEnabled(__sortingEnabled1);

        pushButton_2->setText(QString());

        const bool __sortingEnabled2 = listWidget_3->isSortingEnabled();
        listWidget_3->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem44 = listWidget_3->item(0);
        ___qlistwidgetitem44->setText(QCoreApplication::translate("SecDialog", "[Coding] Draw a string as a binary tree", nullptr));
        QListWidgetItem *___qlistwidgetitem45 = listWidget_3->item(1);
        ___qlistwidgetitem45->setText(QCoreApplication::translate("SecDialog", "[Cryptography] Explain eliptic curve cryptography like I am five years old?", nullptr));
        QListWidgetItem *___qlistwidgetitem46 = listWidget_3->item(2);
        ___qlistwidgetitem46->setText(QCoreApplication::translate("SecDialog", "[Cryptography] What is symmetrical and assymetrical encryption?", nullptr));
        QListWidgetItem *___qlistwidgetitem47 = listWidget_3->item(3);
        ___qlistwidgetitem47->setText(QCoreApplication::translate("SecDialog", "[Math] Prove 1=2", nullptr));
        QListWidgetItem *___qlistwidgetitem48 = listWidget_3->item(4);
        ___qlistwidgetitem48->setText(QCoreApplication::translate("SecDialog", "[Science] Where does most of Earth's oxygen come from?", nullptr));
        QListWidgetItem *___qlistwidgetitem49 = listWidget_3->item(5);
        ___qlistwidgetitem49->setText(QCoreApplication::translate("SecDialog", "[Science] In a perfect vacuum, shouldn't every solid be above its sublimation point, since its vapor pressure must exceed the atmospheric pressure?", nullptr));
        QListWidgetItem *___qlistwidgetitem50 = listWidget_3->item(6);
        ___qlistwidgetitem50->setText(QCoreApplication::translate("SecDialog", "[Politics] Why do communists claim that capitalism began at the Industrial Revolution?", nullptr));
        QListWidgetItem *___qlistwidgetitem51 = listWidget_3->item(7);
        ___qlistwidgetitem51->setText(QCoreApplication::translate("SecDialog", "[Religion] Does God the Son have faith?", nullptr));
        listWidget_3->setSortingEnabled(__sortingEnabled2);

        pushButton->setText(QCoreApplication::translate("SecDialog", "Ask a Question", nullptr));
        label_2->setText(QCoreApplication::translate("SecDialog", "From Favorite Communities", nullptr));
        label->setText(QCoreApplication::translate("SecDialog", "Communities", nullptr));
        label_3->setText(QCoreApplication::translate("SecDialog", "You might be interested", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SecDialog: public Ui_SecDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SECDIALOG_H
