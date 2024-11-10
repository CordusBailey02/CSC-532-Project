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
#include <QtWidgets/QHBoxLayout>
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
    QListWidget *listWidget_defaultList;
    QLabel *label_2;
    QLabel *label_3;
    QListWidget *listWidget_favoriteList;
    QLabel *label;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_askAQuestion;
    QLineEdit *lineEdit_searchBar;
    QPushButton *pushButton_searchButton;
    QPushButton *pushButton_profileButton;
    QListWidget *listWidget_communitiesList;
    QLabel *label_4;
    QListWidget *listWidget_faveCommunitiesList;

    void setupUi(QDialog *SecDialog)
    {
        if (SecDialog->objectName().isEmpty())
            SecDialog->setObjectName("SecDialog");
        SecDialog->resize(1054, 682);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(100);
        sizePolicy.setHeightForWidth(SecDialog->sizePolicy().hasHeightForWidth());
        SecDialog->setSizePolicy(sizePolicy);
        SecDialog->setBaseSize(QSize(0, 100));
        verticalLayout = new QVBoxLayout(SecDialog);
        verticalLayout->setObjectName("verticalLayout");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
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
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(listWidget_defaultList->sizePolicy().hasHeightForWidth());
        listWidget_defaultList->setSizePolicy(sizePolicy1);
        QPalette palette;
        QBrush brush(QColor(146, 194, 242, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Highlight, brush);
        QBrush brush1(QColor(0, 0, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::HighlightedText, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Highlight, brush);
        palette.setBrush(QPalette::Inactive, QPalette::HighlightedText, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::HighlightedText, brush1);
        listWidget_defaultList->setPalette(palette);
        QFont font;
        font.setPointSize(15);
        listWidget_defaultList->setFont(font);

        gridLayout->addWidget(listWidget_defaultList, 6, 0, 1, 4);

        label_2 = new QLabel(SecDialog);
        label_2->setObjectName("label_2");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy2);
        QFont font1;
        font1.setPointSize(20);
        label_2->setFont(font1);

        gridLayout->addWidget(label_2, 3, 0, 1, 2);

        label_3 = new QLabel(SecDialog);
        label_3->setObjectName("label_3");
        sizePolicy2.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy2);
        label_3->setFont(font1);

        gridLayout->addWidget(label_3, 5, 0, 1, 2);

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
        sizePolicy1.setHeightForWidth(listWidget_favoriteList->sizePolicy().hasHeightForWidth());
        listWidget_favoriteList->setSizePolicy(sizePolicy1);
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::Highlight, brush);
        palette1.setBrush(QPalette::Active, QPalette::HighlightedText, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Highlight, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::HighlightedText, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::HighlightedText, brush1);
        listWidget_favoriteList->setPalette(palette1);
        listWidget_favoriteList->setFont(font);

        gridLayout->addWidget(listWidget_favoriteList, 4, 0, 1, 4);

        label = new QLabel(SecDialog);
        label->setObjectName("label");
        sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy2);
        label->setFont(font1);

        gridLayout->addWidget(label, 3, 4, 1, 2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        pushButton_askAQuestion = new QPushButton(SecDialog);
        pushButton_askAQuestion->setObjectName("pushButton_askAQuestion");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(pushButton_askAQuestion->sizePolicy().hasHeightForWidth());
        pushButton_askAQuestion->setSizePolicy(sizePolicy3);
        QPalette palette2;
        QBrush brush2(QColor(255, 190, 111, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::Button, brush2);
        palette2.setBrush(QPalette::Inactive, QPalette::Button, brush2);
        palette2.setBrush(QPalette::Disabled, QPalette::Button, brush2);
        pushButton_askAQuestion->setPalette(palette2);
        pushButton_askAQuestion->setFont(font1);

        horizontalLayout_3->addWidget(pushButton_askAQuestion);

        lineEdit_searchBar = new QLineEdit(SecDialog);
        lineEdit_searchBar->setObjectName("lineEdit_searchBar");
        sizePolicy3.setHeightForWidth(lineEdit_searchBar->sizePolicy().hasHeightForWidth());
        lineEdit_searchBar->setSizePolicy(sizePolicy3);
        lineEdit_searchBar->setFont(font1);

        horizontalLayout_3->addWidget(lineEdit_searchBar);

        pushButton_searchButton = new QPushButton(SecDialog);
        pushButton_searchButton->setObjectName("pushButton_searchButton");
        sizePolicy3.setHeightForWidth(pushButton_searchButton->sizePolicy().hasHeightForWidth());
        pushButton_searchButton->setSizePolicy(sizePolicy3);
        QPalette palette3;
        QBrush brush3(QColor(143, 240, 164, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette3.setBrush(QPalette::Active, QPalette::Button, brush3);
        palette3.setBrush(QPalette::Inactive, QPalette::Button, brush3);
        palette3.setBrush(QPalette::Disabled, QPalette::Button, brush3);
        pushButton_searchButton->setPalette(palette3);
        pushButton_searchButton->setFont(font1);

        horizontalLayout_3->addWidget(pushButton_searchButton);

        pushButton_profileButton = new QPushButton(SecDialog);
        pushButton_profileButton->setObjectName("pushButton_profileButton");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Maximum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(pushButton_profileButton->sizePolicy().hasHeightForWidth());
        pushButton_profileButton->setSizePolicy(sizePolicy4);
        pushButton_profileButton->setFont(font);

        horizontalLayout_3->addWidget(pushButton_profileButton);


        gridLayout->addLayout(horizontalLayout_3, 2, 0, 1, 6);

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
        listWidget_communitiesList->setObjectName("listWidget_communitiesList");
        sizePolicy1.setHeightForWidth(listWidget_communitiesList->sizePolicy().hasHeightForWidth());
        listWidget_communitiesList->setSizePolicy(sizePolicy1);
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::Highlight, brush);
        palette4.setBrush(QPalette::Active, QPalette::HighlightedText, brush1);
        palette4.setBrush(QPalette::Inactive, QPalette::Highlight, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::HighlightedText, brush1);
        palette4.setBrush(QPalette::Disabled, QPalette::HighlightedText, brush1);
        listWidget_communitiesList->setPalette(palette4);
        listWidget_communitiesList->setFont(font);

        gridLayout->addWidget(listWidget_communitiesList, 6, 4, 1, 2);

        label_4 = new QLabel(SecDialog);
        label_4->setObjectName("label_4");
        label_4->setFont(font1);

        gridLayout->addWidget(label_4, 5, 4, 1, 2);

        listWidget_faveCommunitiesList = new QListWidget(SecDialog);
        new QListWidgetItem(listWidget_faveCommunitiesList);
        new QListWidgetItem(listWidget_faveCommunitiesList);
        new QListWidgetItem(listWidget_faveCommunitiesList);
        new QListWidgetItem(listWidget_faveCommunitiesList);
        new QListWidgetItem(listWidget_faveCommunitiesList);
        new QListWidgetItem(listWidget_faveCommunitiesList);
        listWidget_faveCommunitiesList->setObjectName("listWidget_faveCommunitiesList");
        sizePolicy1.setHeightForWidth(listWidget_faveCommunitiesList->sizePolicy().hasHeightForWidth());
        listWidget_faveCommunitiesList->setSizePolicy(sizePolicy1);
        QPalette palette5;
        palette5.setBrush(QPalette::Active, QPalette::Highlight, brush);
        palette5.setBrush(QPalette::Active, QPalette::HighlightedText, brush1);
        palette5.setBrush(QPalette::Inactive, QPalette::Highlight, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::HighlightedText, brush1);
        palette5.setBrush(QPalette::Disabled, QPalette::HighlightedText, brush1);
        listWidget_faveCommunitiesList->setPalette(palette5);
        listWidget_faveCommunitiesList->setFont(font);

        gridLayout->addWidget(listWidget_faveCommunitiesList, 4, 4, 1, 2);


        verticalLayout->addLayout(gridLayout);


        retranslateUi(SecDialog);

        QMetaObject::connectSlotsByName(SecDialog);
    } // setupUi

    void retranslateUi(QDialog *SecDialog)
    {
        SecDialog->setWindowTitle(QCoreApplication::translate("SecDialog", "Main Window", nullptr));

        const bool __sortingEnabled = listWidget_defaultList->isSortingEnabled();
        listWidget_defaultList->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget_defaultList->item(0);
        ___qlistwidgetitem->setText(QCoreApplication::translate("SecDialog", "Who has \"decision-authority\" about paper content: First author or the co-author with the higher academic rank?", nullptr));
        QListWidgetItem *___qlistwidgetitem1 = listWidget_defaultList->item(1);
        ___qlistwidgetitem1->setText(QCoreApplication::translate("SecDialog", "How to discuss traumatic experiences that might sound fabricated or distorted in graduate school applications", nullptr));
        QListWidgetItem *___qlistwidgetitem2 = listWidget_defaultList->item(2);
        ___qlistwidgetitem2->setText(QCoreApplication::translate("SecDialog", "What is the position of Lebanon about the presence of the Hezbollah on its territory?", nullptr));
        QListWidgetItem *___qlistwidgetitem3 = listWidget_defaultList->item(3);
        ___qlistwidgetitem3->setText(QCoreApplication::translate("SecDialog", "Is there any evidence on whether \"Balrog\" from Street Fighter is named after the Balrogs in The Lord of the Rings?", nullptr));
        QListWidgetItem *___qlistwidgetitem4 = listWidget_defaultList->item(4);
        ___qlistwidgetitem4->setText(QCoreApplication::translate("SecDialog", "Does God the Son have Faith?", nullptr));
        QListWidgetItem *___qlistwidgetitem5 = listWidget_defaultList->item(5);
        ___qlistwidgetitem5->setText(QCoreApplication::translate("SecDialog", "Reference Request for global H\303\266lder continuity of solutions to elliptic PDEs", nullptr));
        QListWidgetItem *___qlistwidgetitem6 = listWidget_defaultList->item(6);
        ___qlistwidgetitem6->setText(QCoreApplication::translate("SecDialog", "Draw a string as a binary tree", nullptr));
        QListWidgetItem *___qlistwidgetitem7 = listWidget_defaultList->item(7);
        ___qlistwidgetitem7->setText(QCoreApplication::translate("SecDialog", "Disk-sound after mounting", nullptr));
        QListWidgetItem *___qlistwidgetitem8 = listWidget_defaultList->item(8);
        ___qlistwidgetitem8->setText(QCoreApplication::translate("SecDialog", "Is it possible to have two normally open circuits and use one switch to close one or the other (never both at once for my purposes)?", nullptr));
        QListWidgetItem *___qlistwidgetitem9 = listWidget_defaultList->item(9);
        ___qlistwidgetitem9->setText(QCoreApplication::translate("SecDialog", "Covering directions with rational circles", nullptr));
        QListWidgetItem *___qlistwidgetitem10 = listWidget_defaultList->item(10);
        ___qlistwidgetitem10->setText(QCoreApplication::translate("SecDialog", "How do I justify a society where people have two permanent homes: a summer home and a winter home?", nullptr));
        QListWidgetItem *___qlistwidgetitem11 = listWidget_defaultList->item(11);
        ___qlistwidgetitem11->setText(QCoreApplication::translate("SecDialog", "Why do communists claim that capitalism began at the Industrial Revolution?", nullptr));
        QListWidgetItem *___qlistwidgetitem12 = listWidget_defaultList->item(12);
        ___qlistwidgetitem12->setText(QCoreApplication::translate("SecDialog", "A short series of books in which the main character belongs to a race of beings who can create/reset the universe", nullptr));
        QListWidgetItem *___qlistwidgetitem13 = listWidget_defaultList->item(13);
        ___qlistwidgetitem13->setText(QCoreApplication::translate("SecDialog", "Why are sportsmen not desirous to have others of their persuasion move in?", nullptr));
        QListWidgetItem *___qlistwidgetitem14 = listWidget_defaultList->item(14);
        ___qlistwidgetitem14->setText(QCoreApplication::translate("SecDialog", "What do the Apollo crew mean by \"you're five square\"", nullptr));
        QListWidgetItem *___qlistwidgetitem15 = listWidget_defaultList->item(15);
        ___qlistwidgetitem15->setText(QCoreApplication::translate("SecDialog", "Prepping basement for drywall; how to deal with electrical wires running across joists?", nullptr));
        QListWidgetItem *___qlistwidgetitem16 = listWidget_defaultList->item(16);
        ___qlistwidgetitem16->setText(QCoreApplication::translate("SecDialog", "In a perfect vacuum, shouldn't every solid be above its sublimation point, since its vapor pressure must exceed the atmospheric pressure?", nullptr));
        listWidget_defaultList->setSortingEnabled(__sortingEnabled);

        label_2->setText(QCoreApplication::translate("SecDialog", "From Followed Communities", nullptr));
        label_3->setText(QCoreApplication::translate("SecDialog", "Recent Questions", nullptr));

        const bool __sortingEnabled1 = listWidget_favoriteList->isSortingEnabled();
        listWidget_favoriteList->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem17 = listWidget_favoriteList->item(0);
        ___qlistwidgetitem17->setText(QCoreApplication::translate("SecDialog", "[Coding] Draw a string as a binary tree", nullptr));
        QListWidgetItem *___qlistwidgetitem18 = listWidget_favoriteList->item(1);
        ___qlistwidgetitem18->setText(QCoreApplication::translate("SecDialog", "[Cryptography] Explain eliptic curve cryptography like I am five years old?", nullptr));
        QListWidgetItem *___qlistwidgetitem19 = listWidget_favoriteList->item(2);
        ___qlistwidgetitem19->setText(QCoreApplication::translate("SecDialog", "[Cryptography] What is symmetrical and assymetrical encryption?", nullptr));
        QListWidgetItem *___qlistwidgetitem20 = listWidget_favoriteList->item(3);
        ___qlistwidgetitem20->setText(QCoreApplication::translate("SecDialog", "[Math] Prove 1=2", nullptr));
        QListWidgetItem *___qlistwidgetitem21 = listWidget_favoriteList->item(4);
        ___qlistwidgetitem21->setText(QCoreApplication::translate("SecDialog", "[Politics] Why do communists claim that capitalism began at the Industrial Revolution?", nullptr));
        QListWidgetItem *___qlistwidgetitem22 = listWidget_favoriteList->item(5);
        ___qlistwidgetitem22->setText(QCoreApplication::translate("SecDialog", "[Religion] Does God the Son have faith?", nullptr));
        QListWidgetItem *___qlistwidgetitem23 = listWidget_favoriteList->item(6);
        ___qlistwidgetitem23->setText(QCoreApplication::translate("SecDialog", "[Science] In a perfect vacuum, shouldn't every solid be above its sublimation point, since its vapor pressure must exceed the atmospheric pressure?", nullptr));
        QListWidgetItem *___qlistwidgetitem24 = listWidget_favoriteList->item(7);
        ___qlistwidgetitem24->setText(QCoreApplication::translate("SecDialog", "[Science] Where does most of Earth's oxygen come from?", nullptr));
        listWidget_favoriteList->setSortingEnabled(__sortingEnabled1);

        label->setText(QCoreApplication::translate("SecDialog", "Followed Communities", nullptr));
        pushButton_askAQuestion->setText(QCoreApplication::translate("SecDialog", "Ask a Question", nullptr));
        pushButton_searchButton->setText(QCoreApplication::translate("SecDialog", "Search", nullptr));
        pushButton_profileButton->setText(QString());

        const bool __sortingEnabled2 = listWidget_communitiesList->isSortingEnabled();
        listWidget_communitiesList->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem25 = listWidget_communitiesList->item(0);
        ___qlistwidgetitem25->setText(QCoreApplication::translate("SecDialog", "Animals", nullptr));
        QListWidgetItem *___qlistwidgetitem26 = listWidget_communitiesList->item(1);
        ___qlistwidgetitem26->setText(QCoreApplication::translate("SecDialog", "Architecture", nullptr));
        QListWidgetItem *___qlistwidgetitem27 = listWidget_communitiesList->item(2);
        ___qlistwidgetitem27->setText(QCoreApplication::translate("SecDialog", "Astronomy", nullptr));
        QListWidgetItem *___qlistwidgetitem28 = listWidget_communitiesList->item(3);
        ___qlistwidgetitem28->setText(QCoreApplication::translate("SecDialog", "Computer Hardware", nullptr));
        QListWidgetItem *___qlistwidgetitem29 = listWidget_communitiesList->item(4);
        ___qlistwidgetitem29->setText(QCoreApplication::translate("SecDialog", "Computer Science", nullptr));
        QListWidgetItem *___qlistwidgetitem30 = listWidget_communitiesList->item(5);
        ___qlistwidgetitem30->setText(QCoreApplication::translate("SecDialog", "Cycling", nullptr));
        QListWidgetItem *___qlistwidgetitem31 = listWidget_communitiesList->item(6);
        ___qlistwidgetitem31->setText(QCoreApplication::translate("SecDialog", "Dating", nullptr));
        QListWidgetItem *___qlistwidgetitem32 = listWidget_communitiesList->item(7);
        ___qlistwidgetitem32->setText(QCoreApplication::translate("SecDialog", "Drinks", nullptr));
        QListWidgetItem *___qlistwidgetitem33 = listWidget_communitiesList->item(8);
        ___qlistwidgetitem33->setText(QCoreApplication::translate("SecDialog", "Economy", nullptr));
        QListWidgetItem *___qlistwidgetitem34 = listWidget_communitiesList->item(9);
        ___qlistwidgetitem34->setText(QCoreApplication::translate("SecDialog", "Engagement", nullptr));
        QListWidgetItem *___qlistwidgetitem35 = listWidget_communitiesList->item(10);
        ___qlistwidgetitem35->setText(QCoreApplication::translate("SecDialog", "Engineering", nullptr));
        QListWidgetItem *___qlistwidgetitem36 = listWidget_communitiesList->item(11);
        ___qlistwidgetitem36->setText(QCoreApplication::translate("SecDialog", "Finances", nullptr));
        QListWidgetItem *___qlistwidgetitem37 = listWidget_communitiesList->item(12);
        ___qlistwidgetitem37->setText(QCoreApplication::translate("SecDialog", "Food", nullptr));
        QListWidgetItem *___qlistwidgetitem38 = listWidget_communitiesList->item(13);
        ___qlistwidgetitem38->setText(QCoreApplication::translate("SecDialog", "Furniture", nullptr));
        QListWidgetItem *___qlistwidgetitem39 = listWidget_communitiesList->item(14);
        ___qlistwidgetitem39->setText(QCoreApplication::translate("SecDialog", "Housing", nullptr));
        QListWidgetItem *___qlistwidgetitem40 = listWidget_communitiesList->item(15);
        ___qlistwidgetitem40->setText(QCoreApplication::translate("SecDialog", "Jobs", nullptr));
        QListWidgetItem *___qlistwidgetitem41 = listWidget_communitiesList->item(16);
        ___qlistwidgetitem41->setText(QCoreApplication::translate("SecDialog", "Marriage", nullptr));
        QListWidgetItem *___qlistwidgetitem42 = listWidget_communitiesList->item(17);
        ___qlistwidgetitem42->setText(QCoreApplication::translate("SecDialog", "Parenting", nullptr));
        QListWidgetItem *___qlistwidgetitem43 = listWidget_communitiesList->item(18);
        ___qlistwidgetitem43->setText(QCoreApplication::translate("SecDialog", "Technology", nullptr));
        QListWidgetItem *___qlistwidgetitem44 = listWidget_communitiesList->item(19);
        ___qlistwidgetitem44->setText(QCoreApplication::translate("SecDialog", "Traveling", nullptr));
        QListWidgetItem *___qlistwidgetitem45 = listWidget_communitiesList->item(20);
        ___qlistwidgetitem45->setText(QCoreApplication::translate("SecDialog", "Psychology", nullptr));
        QListWidgetItem *___qlistwidgetitem46 = listWidget_communitiesList->item(21);
        ___qlistwidgetitem46->setText(QCoreApplication::translate("SecDialog", "Science", nullptr));
        listWidget_communitiesList->setSortingEnabled(__sortingEnabled2);

        label_4->setText(QCoreApplication::translate("SecDialog", "Other Communities", nullptr));

        const bool __sortingEnabled3 = listWidget_faveCommunitiesList->isSortingEnabled();
        listWidget_faveCommunitiesList->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem47 = listWidget_faveCommunitiesList->item(0);
        ___qlistwidgetitem47->setText(QCoreApplication::translate("SecDialog", "Coding", nullptr));
        QListWidgetItem *___qlistwidgetitem48 = listWidget_faveCommunitiesList->item(1);
        ___qlistwidgetitem48->setText(QCoreApplication::translate("SecDialog", "Cryptography", nullptr));
        QListWidgetItem *___qlistwidgetitem49 = listWidget_faveCommunitiesList->item(2);
        ___qlistwidgetitem49->setText(QCoreApplication::translate("SecDialog", "Math", nullptr));
        QListWidgetItem *___qlistwidgetitem50 = listWidget_faveCommunitiesList->item(3);
        ___qlistwidgetitem50->setText(QCoreApplication::translate("SecDialog", "Science", nullptr));
        QListWidgetItem *___qlistwidgetitem51 = listWidget_faveCommunitiesList->item(4);
        ___qlistwidgetitem51->setText(QCoreApplication::translate("SecDialog", "Politics", nullptr));
        QListWidgetItem *___qlistwidgetitem52 = listWidget_faveCommunitiesList->item(5);
        ___qlistwidgetitem52->setText(QCoreApplication::translate("SecDialog", "Religion", nullptr));
        listWidget_faveCommunitiesList->setSortingEnabled(__sortingEnabled3);

    } // retranslateUi

};

namespace Ui {
    class SecDialog: public Ui_SecDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SECDIALOG_H
