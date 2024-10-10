/********************************************************************************
** Form generated from reading UI file 'searchresults.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCHRESULTS_H
#define UI_SEARCHRESULTS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_searchResults
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QListWidget *listWidget_communitiesFromSearch;
    QLabel *label_2;
    QListWidget *listWidget_postsFromSearch;
    QLabel *label_3;
    QListWidget *listWidget_commentsFromSearch;

    void setupUi(QDialog *searchResults)
    {
        if (searchResults->objectName().isEmpty())
            searchResults->setObjectName("searchResults");
        searchResults->resize(400, 300);
        verticalLayout = new QVBoxLayout(searchResults);
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(searchResults);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        listWidget_communitiesFromSearch = new QListWidget(searchResults);
        new QListWidgetItem(listWidget_communitiesFromSearch);
        listWidget_communitiesFromSearch->setObjectName("listWidget_communitiesFromSearch");

        verticalLayout->addWidget(listWidget_communitiesFromSearch);

        label_2 = new QLabel(searchResults);
        label_2->setObjectName("label_2");

        verticalLayout->addWidget(label_2);

        listWidget_postsFromSearch = new QListWidget(searchResults);
        new QListWidgetItem(listWidget_postsFromSearch);
        listWidget_postsFromSearch->setObjectName("listWidget_postsFromSearch");

        verticalLayout->addWidget(listWidget_postsFromSearch);

        label_3 = new QLabel(searchResults);
        label_3->setObjectName("label_3");

        verticalLayout->addWidget(label_3);

        listWidget_commentsFromSearch = new QListWidget(searchResults);
        new QListWidgetItem(listWidget_commentsFromSearch);
        listWidget_commentsFromSearch->setObjectName("listWidget_commentsFromSearch");

        verticalLayout->addWidget(listWidget_commentsFromSearch);


        retranslateUi(searchResults);

        QMetaObject::connectSlotsByName(searchResults);
    } // setupUi

    void retranslateUi(QDialog *searchResults)
    {
        searchResults->setWindowTitle(QCoreApplication::translate("searchResults", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("searchResults", "Communities", nullptr));

        const bool __sortingEnabled = listWidget_communitiesFromSearch->isSortingEnabled();
        listWidget_communitiesFromSearch->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget_communitiesFromSearch->item(0);
        ___qlistwidgetitem->setText(QCoreApplication::translate("searchResults", "Community 1", nullptr));
        listWidget_communitiesFromSearch->setSortingEnabled(__sortingEnabled);

        label_2->setText(QCoreApplication::translate("searchResults", "Posts", nullptr));

        const bool __sortingEnabled1 = listWidget_postsFromSearch->isSortingEnabled();
        listWidget_postsFromSearch->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem1 = listWidget_postsFromSearch->item(0);
        ___qlistwidgetitem1->setText(QCoreApplication::translate("searchResults", "Post 1", nullptr));
        listWidget_postsFromSearch->setSortingEnabled(__sortingEnabled1);

        label_3->setText(QCoreApplication::translate("searchResults", "Comments", nullptr));

        const bool __sortingEnabled2 = listWidget_commentsFromSearch->isSortingEnabled();
        listWidget_commentsFromSearch->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem2 = listWidget_commentsFromSearch->item(0);
        ___qlistwidgetitem2->setText(QCoreApplication::translate("searchResults", "Comment 1", nullptr));
        listWidget_commentsFromSearch->setSortingEnabled(__sortingEnabled2);

    } // retranslateUi

};

namespace Ui {
    class searchResults: public Ui_searchResults {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHRESULTS_H
