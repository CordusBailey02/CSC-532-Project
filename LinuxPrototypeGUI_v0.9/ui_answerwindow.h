/********************************************************************************
** Form generated from reading UI file 'answerwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANSWERWINDOW_H
#define UI_ANSWERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_answerWindow
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label_answerPic;
    QLabel *label_answerUser;
    QLabel *label_3;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QListWidget *listWidget;
    QPushButton *pushButton_commentBtn;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QPlainTextEdit *plainTextEdit_answerText;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_upAnswer;
    QLabel *label_upAnswerCount;
    QPushButton *pushButton_downAnswer;
    QLabel *label_downAnswerCount;

    void setupUi(QDialog *answerWindow)
    {
        if (answerWindow->objectName().isEmpty())
            answerWindow->setObjectName("answerWindow");
        answerWindow->resize(400, 300);
        gridLayout = new QGridLayout(answerWindow);
        gridLayout->setObjectName("gridLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label_answerPic = new QLabel(answerWindow);
        label_answerPic->setObjectName("label_answerPic");
        label_answerPic->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(label_answerPic);

        label_answerUser = new QLabel(answerWindow);
        label_answerUser->setObjectName("label_answerUser");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_answerUser->sizePolicy().hasHeightForWidth());
        label_answerUser->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(15);
        label_answerUser->setFont(font);
        label_answerUser->setAlignment(Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignTop);

        verticalLayout->addWidget(label_answerUser);

        label_3 = new QLabel(answerWindow);
        label_3->setObjectName("label_3");
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        label_3->setFont(font);
        label_3->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(label_3);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        label = new QLabel(answerWindow);
        label->setObjectName("label");
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setFont(font);

        verticalLayout_3->addWidget(label);

        listWidget = new QListWidget(answerWindow);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        listWidget->setObjectName("listWidget");
        listWidget->setFont(font);

        verticalLayout_3->addWidget(listWidget);

        pushButton_commentBtn = new QPushButton(answerWindow);
        pushButton_commentBtn->setObjectName("pushButton_commentBtn");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton_commentBtn->sizePolicy().hasHeightForWidth());
        pushButton_commentBtn->setSizePolicy(sizePolicy1);
        pushButton_commentBtn->setFont(font);

        verticalLayout_3->addWidget(pushButton_commentBtn);


        gridLayout->addLayout(verticalLayout_3, 1, 0, 1, 2);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        label_2 = new QLabel(answerWindow);
        label_2->setObjectName("label_2");
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setFont(font);

        verticalLayout_2->addWidget(label_2);

        plainTextEdit_answerText = new QPlainTextEdit(answerWindow);
        plainTextEdit_answerText->setObjectName("plainTextEdit_answerText");
        plainTextEdit_answerText->setFont(font);

        verticalLayout_2->addWidget(plainTextEdit_answerText);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        pushButton_upAnswer = new QPushButton(answerWindow);
        pushButton_upAnswer->setObjectName("pushButton_upAnswer");

        horizontalLayout->addWidget(pushButton_upAnswer);

        label_upAnswerCount = new QLabel(answerWindow);
        label_upAnswerCount->setObjectName("label_upAnswerCount");
        label_upAnswerCount->setFont(font);

        horizontalLayout->addWidget(label_upAnswerCount);

        pushButton_downAnswer = new QPushButton(answerWindow);
        pushButton_downAnswer->setObjectName("pushButton_downAnswer");

        horizontalLayout->addWidget(pushButton_downAnswer);

        label_downAnswerCount = new QLabel(answerWindow);
        label_downAnswerCount->setObjectName("label_downAnswerCount");
        label_downAnswerCount->setFont(font);

        horizontalLayout->addWidget(label_downAnswerCount);


        verticalLayout_2->addLayout(horizontalLayout);


        gridLayout->addLayout(verticalLayout_2, 0, 1, 1, 1);


        retranslateUi(answerWindow);

        QMetaObject::connectSlotsByName(answerWindow);
    } // setupUi

    void retranslateUi(QDialog *answerWindow)
    {
        answerWindow->setWindowTitle(QCoreApplication::translate("answerWindow", "Answer Window", nullptr));
        label_answerPic->setText(QString());
        label_answerUser->setText(QCoreApplication::translate("answerWindow", "Username", nullptr));
        label_3->setText(QCoreApplication::translate("answerWindow", "Verified", nullptr));
        label->setText(QCoreApplication::translate("answerWindow", "Comments", nullptr));

        const bool __sortingEnabled = listWidget->isSortingEnabled();
        listWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget->item(0);
        ___qlistwidgetitem->setText(QCoreApplication::translate("answerWindow", "Comment 1", nullptr));
        QListWidgetItem *___qlistwidgetitem1 = listWidget->item(1);
        ___qlistwidgetitem1->setText(QCoreApplication::translate("answerWindow", "Comment 2", nullptr));
        QListWidgetItem *___qlistwidgetitem2 = listWidget->item(2);
        ___qlistwidgetitem2->setText(QCoreApplication::translate("answerWindow", "Comment 3", nullptr));
        listWidget->setSortingEnabled(__sortingEnabled);

        pushButton_commentBtn->setText(QCoreApplication::translate("answerWindow", "Make a Comment", nullptr));
        label_2->setText(QCoreApplication::translate("answerWindow", "Answer", nullptr));
        plainTextEdit_answerText->setPlainText(QCoreApplication::translate("answerWindow", "Read only too", nullptr));
        pushButton_upAnswer->setText(QString());
        label_upAnswerCount->setText(QCoreApplication::translate("answerWindow", "0", nullptr));
        pushButton_downAnswer->setText(QString());
        label_downAnswerCount->setText(QCoreApplication::translate("answerWindow", "0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class answerWindow: public Ui_answerWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANSWERWINDOW_H
