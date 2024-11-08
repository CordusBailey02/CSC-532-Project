/********************************************************************************
** Form generated from reading UI file 'comment_1.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMMENT_1_H
#define UI_COMMENT_1_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_comment_1
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_14;
    QLabel *label;
    QPlainTextEdit *plainTextEdit_commentText;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_upComment;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QLabel *label_upCountComment;
    QPushButton *pushButton_downComment;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_3;
    QLabel *label_downCountComment;
    QVBoxLayout *verticalLayout;
    QLabel *label_commentUserPic;
    QLabel *label_commentUsername;

    void setupUi(QDialog *comment_1)
    {
        if (comment_1->objectName().isEmpty())
            comment_1->setObjectName("comment_1");
        comment_1->resize(494, 335);
        gridLayout = new QGridLayout(comment_1);
        gridLayout->setObjectName("gridLayout");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        verticalLayout_14 = new QVBoxLayout();
        verticalLayout_14->setObjectName("verticalLayout_14");
        label = new QLabel(comment_1);
        label->setObjectName("label");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(15);
        label->setFont(font);

        verticalLayout_14->addWidget(label);

        plainTextEdit_commentText = new QPlainTextEdit(comment_1);
        plainTextEdit_commentText->setObjectName("plainTextEdit_commentText");
        plainTextEdit_commentText->setFont(font);

        verticalLayout_14->addWidget(plainTextEdit_commentText);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        pushButton_upComment = new QPushButton(comment_1);
        pushButton_upComment->setObjectName("pushButton_upComment");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton_upComment->sizePolicy().hasHeightForWidth());
        pushButton_upComment->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(pushButton_upComment);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        label_2 = new QLabel(comment_1);
        label_2->setObjectName("label_2");
        QFont font1;
        font1.setPointSize(12);
        label_2->setFont(font1);
        label_2->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(label_2);

        label_upCountComment = new QLabel(comment_1);
        label_upCountComment->setObjectName("label_upCountComment");
        label_upCountComment->setFont(font);
        label_upCountComment->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(label_upCountComment);


        horizontalLayout->addLayout(verticalLayout_2);

        pushButton_downComment = new QPushButton(comment_1);
        pushButton_downComment->setObjectName("pushButton_downComment");
        sizePolicy1.setHeightForWidth(pushButton_downComment->sizePolicy().hasHeightForWidth());
        pushButton_downComment->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(pushButton_downComment);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        label_3 = new QLabel(comment_1);
        label_3->setObjectName("label_3");
        label_3->setFont(font1);
        label_3->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_3->addWidget(label_3);

        label_downCountComment = new QLabel(comment_1);
        label_downCountComment->setObjectName("label_downCountComment");
        label_downCountComment->setFont(font);
        label_downCountComment->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_3->addWidget(label_downCountComment);


        horizontalLayout->addLayout(verticalLayout_3);


        verticalLayout_14->addLayout(horizontalLayout);


        horizontalLayout_3->addLayout(verticalLayout_14);


        gridLayout->addLayout(horizontalLayout_3, 0, 2, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label_commentUserPic = new QLabel(comment_1);
        label_commentUserPic->setObjectName("label_commentUserPic");
        label_commentUserPic->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(label_commentUserPic);

        label_commentUsername = new QLabel(comment_1);
        label_commentUsername->setObjectName("label_commentUsername");
        sizePolicy.setHeightForWidth(label_commentUsername->sizePolicy().hasHeightForWidth());
        label_commentUsername->setSizePolicy(sizePolicy);
        label_commentUsername->setFont(font);
        label_commentUsername->setAlignment(Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignTop);

        verticalLayout->addWidget(label_commentUsername);


        gridLayout->addLayout(verticalLayout, 0, 1, 1, 1);


        retranslateUi(comment_1);

        QMetaObject::connectSlotsByName(comment_1);
    } // setupUi

    void retranslateUi(QDialog *comment_1)
    {
        comment_1->setWindowTitle(QCoreApplication::translate("comment_1", "Comment", nullptr));
        label->setText(QCoreApplication::translate("comment_1", "Comment", nullptr));
        plainTextEdit_commentText->setPlainText(QCoreApplication::translate("comment_1", "Read only three", nullptr));
        pushButton_upComment->setText(QString());
        label_2->setText(QCoreApplication::translate("comment_1", "Upvotes", nullptr));
        label_upCountComment->setText(QCoreApplication::translate("comment_1", "0", nullptr));
        pushButton_downComment->setText(QString());
        label_3->setText(QCoreApplication::translate("comment_1", "Downvotes", nullptr));
        label_downCountComment->setText(QCoreApplication::translate("comment_1", "0", nullptr));
        label_commentUserPic->setText(QString());
        label_commentUsername->setText(QCoreApplication::translate("comment_1", "Username", nullptr));
    } // retranslateUi

};

namespace Ui {
    class comment_1: public Ui_comment_1 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMMENT_1_H
