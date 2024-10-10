/********************************************************************************
** Form generated from reading UI file 'comment_1.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_comment_1
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_14;
    QTextEdit *textEdit_commentQ;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_upComment;
    QLabel *label_upCountComment;
    QPushButton *pushButton_downComment;
    QLabel *label_downCountComment;
    QVBoxLayout *verticalLayout;
    QLabel *label_commentUserPic;
    QLabel *label_commentUsername;

    void setupUi(QDialog *comment_1)
    {
        if (comment_1->objectName().isEmpty())
            comment_1->setObjectName("comment_1");
        comment_1->resize(451, 323);
        gridLayout = new QGridLayout(comment_1);
        gridLayout->setObjectName("gridLayout");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        verticalLayout_14 = new QVBoxLayout();
        verticalLayout_14->setObjectName("verticalLayout_14");
        textEdit_commentQ = new QTextEdit(comment_1);
        textEdit_commentQ->setObjectName("textEdit_commentQ");

        verticalLayout_14->addWidget(textEdit_commentQ);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        pushButton_upComment = new QPushButton(comment_1);
        pushButton_upComment->setObjectName("pushButton_upComment");

        horizontalLayout->addWidget(pushButton_upComment);

        label_upCountComment = new QLabel(comment_1);
        label_upCountComment->setObjectName("label_upCountComment");

        horizontalLayout->addWidget(label_upCountComment);

        pushButton_downComment = new QPushButton(comment_1);
        pushButton_downComment->setObjectName("pushButton_downComment");

        horizontalLayout->addWidget(pushButton_downComment);

        label_downCountComment = new QLabel(comment_1);
        label_downCountComment->setObjectName("label_downCountComment");

        horizontalLayout->addWidget(label_downCountComment);


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
        label_commentUsername->setAlignment(Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignTop);

        verticalLayout->addWidget(label_commentUsername);


        gridLayout->addLayout(verticalLayout, 0, 1, 1, 1);


        retranslateUi(comment_1);

        QMetaObject::connectSlotsByName(comment_1);
    } // setupUi

    void retranslateUi(QDialog *comment_1)
    {
        comment_1->setWindowTitle(QCoreApplication::translate("comment_1", "Comment", nullptr));
        textEdit_commentQ->setHtml(QCoreApplication::translate("comment_1", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Read only too</p></body></html>", nullptr));
        pushButton_upComment->setText(QString());
        label_upCountComment->setText(QCoreApplication::translate("comment_1", "0", nullptr));
        pushButton_downComment->setText(QString());
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
