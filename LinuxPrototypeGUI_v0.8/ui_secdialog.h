/********************************************************************************
** Form generated from reading UI file 'secdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
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
    QPushButton *pushButton_searchButton;
    QLineEdit *lineEdit_searchBar;
    QListWidget *listWidget_communitiesList;
    QListWidget *listWidget_defaultList;
    QPushButton *pushButton_profileButton;
    QListWidget *listWidget_favoriteList;
    QPushButton *pushButton_askAQuestion;
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
        pushButton_searchButton = new QPushButton(SecDialog);
        pushButton_searchButton->setObjectName("pushButton_searchButton");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_searchButton->sizePolicy().hasHeightForWidth());
        pushButton_searchButton->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButton_searchButton, 0, 4, 1, 1);

        lineEdit_searchBar = new QLineEdit(SecDialog);
        lineEdit_searchBar->setObjectName("lineEdit_searchBar");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEdit_searchBar->sizePolicy().hasHeightForWidth());
        lineEdit_searchBar->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(lineEdit_searchBar, 0, 1, 1, 3);

        listWidget_communitiesList = new QListWidget(SecDialog);
        new QListWidgetItem(listWidget_communitiesList);
        new QListWidgetItem(listWidget_communitiesList);
        new QListWidgetItem(listWidget_communitiesList);
        new QListWidgetItem(listWidget_communitiesList);
        new QListWidgetItem(listWidget_communitiesList);
        new QListWidgetItem(listWidget_communitiesList);
        new QListWidgetItem(listWidget_communitiesList);
        new QListWidgetItem(listWidget_communitiesList);
        new QListWidgetItem(listWidget_communitiesList);
        new QListWidgetItem(listWidget_communitiesList);
        new QListWidgetItem(listWidget_communitiesList);
        new QListWidgetItem(listWidget_communitiesList);
        new QListWidgetItem(listWidget_communitiesList);
        new QListWidgetItem(listWidget_communitiesList);
        new QListWidgetItem(listWidget_communitiesList);
        new QListWidgetItem(listWidget_communitiesList);
        new QListWidgetItem(listWidget_communitiesList);
        new QListWidgetItem(listWidget_communitiesList);
        new QListWidgetItem(listWidget_communitiesList);
        new QListWidgetItem(listWidget_communitiesList);
        new QListWidgetItem(listWidget_communitiesList);
        new QListWidgetItem(listWidget_communitiesList);
        new QListWidgetItem(listWidget_communitiesList);
        new QListWidgetItem(listWidget_communitiesList);
        new QListWidgetItem(listWidget_communitiesList);
        new QListWidgetItem(listWidget_communitiesList);
        new QListWidgetItem(listWidget_communitiesList);
        listWidget_communitiesList->setObjectName("listWidget_communitiesList");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(listWidget_communitiesList->sizePolicy().hasHeightForWidth());
        listWidget_communitiesList->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(listWidget_communitiesList, 2, 4, 3, 2);

        listWidget_defaultList = new QListWidget(SecDialog);
        new QListWidgetItem(listWidget_defaultList);
        new QListWidgetItem(listWidget_defaultList);
        new QListWidgetItem(listWidget_defaultList);
        new QListWidgetItem(listWidget_defaultList);
        new QListWidgetItem(listWidget_defaultList);
        new QListWidgetItem(listWidget_defaultList);
        new QListWidgetItem(listWidget_defaultList);
        new QListWidgetItem(listWidget_defaultList);
        new QListWidgetItem(listWidget_defaultList);
        new QListWidgetItem(listWidget_defaultList);
        new QListWidgetItem(listWidget_defaultList);
        new QListWidgetItem(listWidget_defaultList);
        new QListWidgetItem(listWidget_defaultList);
        new QListWidgetItem(listWidget_defaultList);
        new QListWidgetItem(listWidget_defaultList);
        new QListWidgetItem(listWidget_defaultList);
        new QListWidgetItem(listWidget_defaultList);
        listWidget_defaultList->setObjectName("listWidget_defaultList");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Maximum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(listWidget_defaultList->sizePolicy().hasHeightForWidth());
        listWidget_defaultList->setSizePolicy(sizePolicy3);

        gridLayout->addWidget(listWidget_defaultList, 4, 0, 1, 4);

        pushButton_profileButton = new QPushButton(SecDialog);
        pushButton_profileButton->setObjectName("pushButton_profileButton");
        sizePolicy.setHeightForWidth(pushButton_profileButton->sizePolicy().hasHeightForWidth());
        pushButton_profileButton->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButton_profileButton, 0, 5, 1, 1);

        listWidget_favoriteList = new QListWidget(SecDialog);
        new QListWidgetItem(listWidget_favoriteList);
        new QListWidgetItem(listWidget_favoriteList);
        new QListWidgetItem(listWidget_favoriteList);
        new QListWidgetItem(listWidget_favoriteList);
        new QListWidgetItem(listWidget_favoriteList);
        new QListWidgetItem(listWidget_favoriteList);
        new QListWidgetItem(listWidget_favoriteList);
        new QListWidgetItem(listWidget_favoriteList);
        listWidget_favoriteList->setObjectName("listWidget_favoriteList");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Maximum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(listWidget_favoriteList->sizePolicy().hasHeightForWidth());
        listWidget_favoriteList->setSizePolicy(sizePolicy4);

        gridLayout->addWidget(listWidget_favoriteList, 2, 0, 1, 4);

        pushButton_askAQuestion = new QPushButton(SecDialog);
        pushButton_askAQuestion->setObjectName("pushButton_askAQuestion");
        sizePolicy.setHeightForWidth(pushButton_askAQuestion->sizePolicy().hasHeightForWidth());
        pushButton_askAQuestion->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButton_askAQuestion, 0, 0, 1, 1);

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
        pushButton_searchButton->setText(QCoreApplication::translate("SecDialog", "Search", nullptr));

        const bool __sortingEnabled = listWidget_communitiesList->isSortingEnabled();
        listWidget_communitiesList->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget_communitiesList->item(0);
        ___qlistwidgetitem->setText(QCoreApplication::translate("SecDialog", "Animals", nullptr));
        QListWidgetItem *___qlistwidgetitem1 = listWidget_communitiesList->item(1);
        ___qlistwidgetitem1->setText(QCoreApplication::translate("SecDialog", "Architecture", nullptr));
        QListWidgetItem *___qlistwidgetitem2 = listWidget_communitiesList->item(2);
        ___qlistwidgetitem2->setText(QCoreApplication::translate("SecDialog", "Astronomy", nullptr));
        QListWidgetItem *___qlistwidgetitem3 = listWidget_communitiesList->item(3);
        ___qlistwidgetitem3->setText(QCoreApplication::translate("SecDialog", "Coding", nullptr));
        QListWidgetItem *___qlistwidgetitem4 = listWidget_communitiesList->item(4);
        ___qlistwidgetitem4->setText(QCoreApplication::translate("SecDialog", "Computer Hardware", nullptr));
        QListWidgetItem *___qlistwidgetitem5 = listWidget_communitiesList->item(5);
        ___qlistwidgetitem5->setText(QCoreApplication::translate("SecDialog", "Computer Science", nullptr));
        QListWidgetItem *___qlistwidgetitem6 = listWidget_communitiesList->item(6);
        ___qlistwidgetitem6->setText(QCoreApplication::translate("SecDialog", "Cryptography", nullptr));
        QListWidgetItem *___qlistwidgetitem7 = listWidget_communitiesList->item(7);
        ___qlistwidgetitem7->setText(QCoreApplication::translate("SecDialog", "Cycling", nullptr));
        QListWidgetItem *___qlistwidgetitem8 = listWidget_communitiesList->item(8);
        ___qlistwidgetitem8->setText(QCoreApplication::translate("SecDialog", "Dating", nullptr));
        QListWidgetItem *___qlistwidgetitem9 = listWidget_communitiesList->item(9);
        ___qlistwidgetitem9->setText(QCoreApplication::translate("SecDialog", "Drinks", nullptr));
        QListWidgetItem *___qlistwidgetitem10 = listWidget_communitiesList->item(10);
        ___qlistwidgetitem10->setText(QCoreApplication::translate("SecDialog", "Economy", nullptr));
        QListWidgetItem *___qlistwidgetitem11 = listWidget_communitiesList->item(11);
        ___qlistwidgetitem11->setText(QCoreApplication::translate("SecDialog", "Engagement", nullptr));
        QListWidgetItem *___qlistwidgetitem12 = listWidget_communitiesList->item(12);
        ___qlistwidgetitem12->setText(QCoreApplication::translate("SecDialog", "Engineering", nullptr));
        QListWidgetItem *___qlistwidgetitem13 = listWidget_communitiesList->item(13);
        ___qlistwidgetitem13->setText(QCoreApplication::translate("SecDialog", "Finances", nullptr));
        QListWidgetItem *___qlistwidgetitem14 = listWidget_communitiesList->item(14);
        ___qlistwidgetitem14->setText(QCoreApplication::translate("SecDialog", "Food", nullptr));
        QListWidgetItem *___qlistwidgetitem15 = listWidget_communitiesList->item(15);
        ___qlistwidgetitem15->setText(QCoreApplication::translate("SecDialog", "Furniture", nullptr));
        QListWidgetItem *___qlistwidgetitem16 = listWidget_communitiesList->item(16);
        ___qlistwidgetitem16->setText(QCoreApplication::translate("SecDialog", "Housing", nullptr));
        QListWidgetItem *___qlistwidgetitem17 = listWidget_communitiesList->item(17);
        ___qlistwidgetitem17->setText(QCoreApplication::translate("SecDialog", "Jobs", nullptr));
        QListWidgetItem *___qlistwidgetitem18 = listWidget_communitiesList->item(18);
        ___qlistwidgetitem18->setText(QCoreApplication::translate("SecDialog", "Marriage", nullptr));
        QListWidgetItem *___qlistwidgetitem19 = listWidget_communitiesList->item(19);
        ___qlistwidgetitem19->setText(QCoreApplication::translate("SecDialog", "Math", nullptr));
        QListWidgetItem *___qlistwidgetitem20 = listWidget_communitiesList->item(20);
        ___qlistwidgetitem20->setText(QCoreApplication::translate("SecDialog", "Parenting", nullptr));
        QListWidgetItem *___qlistwidgetitem21 = listWidget_communitiesList->item(21);
        ___qlistwidgetitem21->setText(QCoreApplication::translate("SecDialog", "Technology", nullptr));
        QListWidgetItem *___qlistwidgetitem22 = listWidget_communitiesList->item(22);
        ___qlistwidgetitem22->setText(QCoreApplication::translate("SecDialog", "Traveling", nullptr));
        QListWidgetItem *___qlistwidgetitem23 = listWidget_communitiesList->item(23);
        ___qlistwidgetitem23->setText(QCoreApplication::translate("SecDialog", "Politics", nullptr));
        QListWidgetItem *___qlistwidgetitem24 = listWidget_communitiesList->item(24);
        ___qlistwidgetitem24->setText(QCoreApplication::translate("SecDialog", "Psychology", nullptr));
        QListWidgetItem *___qlistwidgetitem25 = listWidget_communitiesList->item(25);
        ___qlistwidgetitem25->setText(QCoreApplication::translate("SecDialog", "Religion", nullptr));
        QListWidgetItem *___qlistwidgetitem26 = listWidget_communitiesList->item(26);
        ___qlistwidgetitem26->setText(QCoreApplication::translate("SecDialog", "Science", nullptr));
        listWidget_communitiesList->setSortingEnabled(__sortingEnabled);


        const bool __sortingEnabled1 = listWidget_defaultList->isSortingEnabled();
        listWidget_defaultList->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem27 = listWidget_defaultList->item(0);
        ___qlistwidgetitem27->setText(QCoreApplication::translate("SecDialog", "Who has \"decision-authority\" about paper content: First author or the co-author with the higher academic rank?", nullptr));
        QListWidgetItem *___qlistwidgetitem28 = listWidget_defaultList->item(1);
        ___qlistwidgetitem28->setText(QCoreApplication::translate("SecDialog", "How to discuss traumatic experiences that might sound fabricated or distorted in graduate school applications", nullptr));
        QListWidgetItem *___qlistwidgetitem29 = listWidget_defaultList->item(2);
        ___qlistwidgetitem29->setText(QCoreApplication::translate("SecDialog", "What is the position of Lebanon about the presence of the Hezbollah on its territory?", nullptr));
        QListWidgetItem *___qlistwidgetitem30 = listWidget_defaultList->item(3);
        ___qlistwidgetitem30->setText(QCoreApplication::translate("SecDialog", "Is there any evidence on whether \"Balrog\" from Street Fighter is named after the Balrogs in The Lord of the Rings?", nullptr));
        QListWidgetItem *___qlistwidgetitem31 = listWidget_defaultList->item(4);
        ___qlistwidgetitem31->setText(QCoreApplication::translate("SecDialog", "Does God the Son have Faith?", nullptr));
        QListWidgetItem *___qlistwidgetitem32 = listWidget_defaultList->item(5);
        ___qlistwidgetitem32->setText(QCoreApplication::translate("SecDialog", "Reference Request for global H\303\266lder continuity of solutions to elliptic PDEs", nullptr));
        QListWidgetItem *___qlistwidgetitem33 = listWidget_defaultList->item(6);
        ___qlistwidgetitem33->setText(QCoreApplication::translate("SecDialog", "Draw a string as a binary tree", nullptr));
        QListWidgetItem *___qlistwidgetitem34 = listWidget_defaultList->item(7);
        ___qlistwidgetitem34->setText(QCoreApplication::translate("SecDialog", "Disk-sound after mounting", nullptr));
        QListWidgetItem *___qlistwidgetitem35 = listWidget_defaultList->item(8);
        ___qlistwidgetitem35->setText(QCoreApplication::translate("SecDialog", "Is it possible to have two normally open circuits and use one switch to close one or the other (never both at once for my purposes)?", nullptr));
        QListWidgetItem *___qlistwidgetitem36 = listWidget_defaultList->item(9);
        ___qlistwidgetitem36->setText(QCoreApplication::translate("SecDialog", "Covering directions with rational circles", nullptr));
        QListWidgetItem *___qlistwidgetitem37 = listWidget_defaultList->item(10);
        ___qlistwidgetitem37->setText(QCoreApplication::translate("SecDialog", "How do I justify a society where people have two permanent homes: a summer home and a winter home?", nullptr));
        QListWidgetItem *___qlistwidgetitem38 = listWidget_defaultList->item(11);
        ___qlistwidgetitem38->setText(QCoreApplication::translate("SecDialog", "Why do communists claim that capitalism began at the Industrial Revolution?", nullptr));
        QListWidgetItem *___qlistwidgetitem39 = listWidget_defaultList->item(12);
        ___qlistwidgetitem39->setText(QCoreApplication::translate("SecDialog", "A short series of books in which the main character belongs to a race of beings who can create/reset the universe", nullptr));
        QListWidgetItem *___qlistwidgetitem40 = listWidget_defaultList->item(13);
        ___qlistwidgetitem40->setText(QCoreApplication::translate("SecDialog", "Why are sportsmen not desirous to have others of their persuasion move in?", nullptr));
        QListWidgetItem *___qlistwidgetitem41 = listWidget_defaultList->item(14);
        ___qlistwidgetitem41->setText(QCoreApplication::translate("SecDialog", "What do the Apollo crew mean by \"you're five square\"", nullptr));
        QListWidgetItem *___qlistwidgetitem42 = listWidget_defaultList->item(15);
        ___qlistwidgetitem42->setText(QCoreApplication::translate("SecDialog", "Prepping basement for drywall; how to deal with electrical wires running across joists?", nullptr));
        QListWidgetItem *___qlistwidgetitem43 = listWidget_defaultList->item(16);
        ___qlistwidgetitem43->setText(QCoreApplication::translate("SecDialog", "In a perfect vacuum, shouldn't every solid be above its sublimation point, since its vapor pressure must exceed the atmospheric pressure?", nullptr));
        listWidget_defaultList->setSortingEnabled(__sortingEnabled1);

        pushButton_profileButton->setText(QString());

        const bool __sortingEnabled2 = listWidget_favoriteList->isSortingEnabled();
        listWidget_favoriteList->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem44 = listWidget_favoriteList->item(0);
        ___qlistwidgetitem44->setText(QCoreApplication::translate("SecDialog", "[Coding] Draw a string as a binary tree", nullptr));
        QListWidgetItem *___qlistwidgetitem45 = listWidget_favoriteList->item(1);
        ___qlistwidgetitem45->setText(QCoreApplication::translate("SecDialog", "[Cryptography] Explain eliptic curve cryptography like I am five years old?", nullptr));
        QListWidgetItem *___qlistwidgetitem46 = listWidget_favoriteList->item(2);
        ___qlistwidgetitem46->setText(QCoreApplication::translate("SecDialog", "[Cryptography] What is symmetrical and assymetrical encryption?", nullptr));
        QListWidgetItem *___qlistwidgetitem47 = listWidget_favoriteList->item(3);
        ___qlistwidgetitem47->setText(QCoreApplication::translate("SecDialog", "[Math] Prove 1=2", nullptr));
        QListWidgetItem *___qlistwidgetitem48 = listWidget_favoriteList->item(4);
        ___qlistwidgetitem48->setText(QCoreApplication::translate("SecDialog", "[Science] Where does most of Earth's oxygen come from?", nullptr));
        QListWidgetItem *___qlistwidgetitem49 = listWidget_favoriteList->item(5);
        ___qlistwidgetitem49->setText(QCoreApplication::translate("SecDialog", "[Science] In a perfect vacuum, shouldn't every solid be above its sublimation point, since its vapor pressure must exceed the atmospheric pressure?", nullptr));
        QListWidgetItem *___qlistwidgetitem50 = listWidget_favoriteList->item(6);
        ___qlistwidgetitem50->setText(QCoreApplication::translate("SecDialog", "[Politics] Why do communists claim that capitalism began at the Industrial Revolution?", nullptr));
        QListWidgetItem *___qlistwidgetitem51 = listWidget_favoriteList->item(7);
        ___qlistwidgetitem51->setText(QCoreApplication::translate("SecDialog", "[Religion] Does God the Son have faith?", nullptr));
        listWidget_favoriteList->setSortingEnabled(__sortingEnabled2);

        pushButton_askAQuestion->setText(QCoreApplication::translate("SecDialog", "Ask a Question", nullptr));
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
