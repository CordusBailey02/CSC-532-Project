/********************************************************************************
** Form generated from reading UI file 'searchresults.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
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
    QLabel *label_4;
    QListWidget *listWidget_answersFromSearch;
    QLabel *label_3;
    QListWidget *listWidget_commentsFromSearch;

    void setupUi(QDialog *searchResults)
    {
        if (searchResults->objectName().isEmpty())
            searchResults->setObjectName("searchResults");
        searchResults->resize(445, 452);
        verticalLayout = new QVBoxLayout(searchResults);
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(searchResults);
        label->setObjectName("label");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(17);
        label->setFont(font);

        verticalLayout->addWidget(label);

        listWidget_communitiesFromSearch = new QListWidget(searchResults);
        new QListWidgetItem(listWidget_communitiesFromSearch);
        listWidget_communitiesFromSearch->setObjectName("listWidget_communitiesFromSearch");
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
        listWidget_communitiesFromSearch->setPalette(palette);
        listWidget_communitiesFromSearch->setFont(font);

        verticalLayout->addWidget(listWidget_communitiesFromSearch);

        label_2 = new QLabel(searchResults);
        label_2->setObjectName("label_2");
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setFont(font);

        verticalLayout->addWidget(label_2);

        listWidget_postsFromSearch = new QListWidget(searchResults);
        new QListWidgetItem(listWidget_postsFromSearch);
        listWidget_postsFromSearch->setObjectName("listWidget_postsFromSearch");
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::Highlight, brush);
        palette1.setBrush(QPalette::Active, QPalette::HighlightedText, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Highlight, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::HighlightedText, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::HighlightedText, brush1);
        listWidget_postsFromSearch->setPalette(palette1);
        listWidget_postsFromSearch->setFont(font);

        verticalLayout->addWidget(listWidget_postsFromSearch);

        label_4 = new QLabel(searchResults);
        label_4->setObjectName("label_4");
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);
        label_4->setFont(font);

        verticalLayout->addWidget(label_4);

        listWidget_answersFromSearch = new QListWidget(searchResults);
        new QListWidgetItem(listWidget_answersFromSearch);
        listWidget_answersFromSearch->setObjectName("listWidget_answersFromSearch");
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::Highlight, brush);
        palette2.setBrush(QPalette::Active, QPalette::HighlightedText, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Highlight, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::HighlightedText, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::HighlightedText, brush1);
        listWidget_answersFromSearch->setPalette(palette2);
        listWidget_answersFromSearch->setFont(font);

        verticalLayout->addWidget(listWidget_answersFromSearch);

        label_3 = new QLabel(searchResults);
        label_3->setObjectName("label_3");
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        label_3->setFont(font);

        verticalLayout->addWidget(label_3);

        listWidget_commentsFromSearch = new QListWidget(searchResults);
        new QListWidgetItem(listWidget_commentsFromSearch);
        listWidget_commentsFromSearch->setObjectName("listWidget_commentsFromSearch");
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::Highlight, brush);
        palette3.setBrush(QPalette::Active, QPalette::HighlightedText, brush1);
        palette3.setBrush(QPalette::Inactive, QPalette::Highlight, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::HighlightedText, brush1);
        palette3.setBrush(QPalette::Disabled, QPalette::HighlightedText, brush1);
        listWidget_commentsFromSearch->setPalette(palette3);
        listWidget_commentsFromSearch->setFont(font);

        verticalLayout->addWidget(listWidget_commentsFromSearch);


        retranslateUi(searchResults);

        QMetaObject::connectSlotsByName(searchResults);
    } // setupUi

    void retranslateUi(QDialog *searchResults)
    {
        searchResults->setWindowTitle(QCoreApplication::translate("searchResults", "Search Results", nullptr));
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

        label_4->setText(QCoreApplication::translate("searchResults", "Answers", nullptr));

        const bool __sortingEnabled2 = listWidget_answersFromSearch->isSortingEnabled();
        listWidget_answersFromSearch->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem2 = listWidget_answersFromSearch->item(0);
        ___qlistwidgetitem2->setText(QCoreApplication::translate("searchResults", "Answer 1", nullptr));
        listWidget_answersFromSearch->setSortingEnabled(__sortingEnabled2);

        label_3->setText(QCoreApplication::translate("searchResults", "Comments", nullptr));

        const bool __sortingEnabled3 = listWidget_commentsFromSearch->isSortingEnabled();
        listWidget_commentsFromSearch->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem3 = listWidget_commentsFromSearch->item(0);
        ___qlistwidgetitem3->setText(QCoreApplication::translate("searchResults", "Comment 1", nullptr));
        listWidget_commentsFromSearch->setSortingEnabled(__sortingEnabled3);

    } // retranslateUi

};

namespace Ui {
    class searchResults: public Ui_searchResults {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHRESULTS_H
