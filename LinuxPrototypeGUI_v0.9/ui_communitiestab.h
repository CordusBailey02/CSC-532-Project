/********************************************************************************
** Form generated from reading UI file 'communitiestab.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMMUNITIESTAB_H
#define UI_COMMUNITIESTAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_communitiesTab
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label;
    QCheckBox *checkBox;
    QListWidget *listWidget;

    void setupUi(QDialog *communitiesTab)
    {
        if (communitiesTab->objectName().isEmpty())
            communitiesTab->setObjectName("communitiesTab");
        communitiesTab->resize(400, 300);
        verticalLayout = new QVBoxLayout(communitiesTab);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label = new QLabel(communitiesTab);
        label->setObjectName("label");
        QFont font;
        font.setPointSize(17);
        label->setFont(font);

        horizontalLayout_5->addWidget(label);

        checkBox = new QCheckBox(communitiesTab);
        checkBox->setObjectName("checkBox");
        checkBox->setFont(font);

        horizontalLayout_5->addWidget(checkBox);


        verticalLayout->addLayout(horizontalLayout_5);

        listWidget = new QListWidget(communitiesTab);
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
        listWidget->setPalette(palette);
        listWidget->setFont(font);

        verticalLayout->addWidget(listWidget);


        retranslateUi(communitiesTab);

        QMetaObject::connectSlotsByName(communitiesTab);
    } // setupUi

    void retranslateUi(QDialog *communitiesTab)
    {
        communitiesTab->setWindowTitle(QCoreApplication::translate("communitiesTab", "Communities", nullptr));
        label->setText(QCoreApplication::translate("communitiesTab", "Math", nullptr));
        checkBox->setText(QCoreApplication::translate("communitiesTab", "Followed", nullptr));

        const bool __sortingEnabled = listWidget->isSortingEnabled();
        listWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget->item(0);
        ___qlistwidgetitem->setText(QCoreApplication::translate("communitiesTab", "Prove 1=2", nullptr));
        QListWidgetItem *___qlistwidgetitem1 = listWidget->item(1);
        ___qlistwidgetitem1->setText(QCoreApplication::translate("communitiesTab", "Integral of ln(x)", nullptr));
        QListWidgetItem *___qlistwidgetitem2 = listWidget->item(2);
        ___qlistwidgetitem2->setText(QCoreApplication::translate("communitiesTab", "Volume of a sphere", nullptr));
        QListWidgetItem *___qlistwidgetitem3 = listWidget->item(3);
        ___qlistwidgetitem3->setText(QCoreApplication::translate("communitiesTab", "Does math scare users?", nullptr));
        QListWidgetItem *___qlistwidgetitem4 = listWidget->item(4);
        ___qlistwidgetitem4->setText(QCoreApplication::translate("communitiesTab", "Can a math formula or math algorithm be patented?", nullptr));
        QListWidgetItem *___qlistwidgetitem5 = listWidget->item(5);
        ___qlistwidgetitem5->setText(QCoreApplication::translate("communitiesTab", "Publish math formulas on Blogger", nullptr));
        QListWidgetItem *___qlistwidgetitem6 = listWidget->item(6);
        ___qlistwidgetitem6->setText(QCoreApplication::translate("communitiesTab", "ThunderBird math equations", nullptr));
        QListWidgetItem *___qlistwidgetitem7 = listWidget->item(7);
        ___qlistwidgetitem7->setText(QCoreApplication::translate("communitiesTab", "Kotlin math vs math", nullptr));
        QListWidgetItem *___qlistwidgetitem8 = listWidget->item(8);
        ___qlistwidgetitem8->setText(QCoreApplication::translate("communitiesTab", "Math in Japanese", nullptr));
        QListWidgetItem *___qlistwidgetitem9 = listWidget->item(9);
        ___qlistwidgetitem9->setText(QCoreApplication::translate("communitiesTab", "Math exchange rates", nullptr));
        QListWidgetItem *___qlistwidgetitem10 = listWidget->item(10);
        ___qlistwidgetitem10->setText(QCoreApplication::translate("communitiesTab", "Proving the summability of a Sequence under Measure-Theoretic conditions", nullptr));
        QListWidgetItem *___qlistwidgetitem11 = listWidget->item(11);
        ___qlistwidgetitem11->setText(QCoreApplication::translate("communitiesTab", "The set of pairs in the image of a discrete function", nullptr));
        QListWidgetItem *___qlistwidgetitem12 = listWidget->item(12);
        ___qlistwidgetitem12->setText(QCoreApplication::translate("communitiesTab", "Help with uniqueness proof", nullptr));
        QListWidgetItem *___qlistwidgetitem13 = listWidget->item(13);
        ___qlistwidgetitem13->setText(QCoreApplication::translate("communitiesTab", "Linear deconvolution using FFT", nullptr));
        QListWidgetItem *___qlistwidgetitem14 = listWidget->item(14);
        ___qlistwidgetitem14->setText(QCoreApplication::translate("communitiesTab", "Derive relation between slopes of a quadrilateral with vertices on a parabola using analog of Laguerre formula?", nullptr));
        QListWidgetItem *___qlistwidgetitem15 = listWidget->item(15);
        ___qlistwidgetitem15->setText(QCoreApplication::translate("communitiesTab", "If gradient is bounded then absolute difference in images is bounded", nullptr));
        QListWidgetItem *___qlistwidgetitem16 = listWidget->item(16);
        ___qlistwidgetitem16->setText(QCoreApplication::translate("communitiesTab", "What is the number of events within an interval with Gamma-distributed waiting times?", nullptr));
        listWidget->setSortingEnabled(__sortingEnabled);

    } // retranslateUi

};

namespace Ui {
    class communitiesTab: public Ui_communitiesTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMMUNITIESTAB_H
