/********************************************************************************
** Form generated from reading UI file 'post_1.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POST_1_H
#define UI_POST_1_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Post_1
{
public:
    QFormLayout *formLayout;
    QListWidget *listWidget;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton;
    QVBoxLayout *verticalLayout_10;
    QHBoxLayout *horizontalLayout_12;
    QVBoxLayout *verticalLayout;
    QLabel *label_userPic;
    QLabel *label_username;
    QVBoxLayout *verticalLayout_2;
    QTextEdit *textEdit_postQ;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_upPost;
    QLabel *label_upPostCount;
    QPushButton *pushButton_downPost;
    QLabel *label_downPostCount;
    QLabel *label_3;

    void setupUi(QDialog *Post_1)
    {
        if (Post_1->objectName().isEmpty())
            Post_1->setObjectName("Post_1");
        Post_1->resize(400, 310);
        formLayout = new QFormLayout(Post_1);
        formLayout->setObjectName("formLayout");
        listWidget = new QListWidget(Post_1);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        listWidget->setObjectName("listWidget");

        formLayout->setWidget(3, QFormLayout::SpanningRole, listWidget);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        pushButton = new QPushButton(Post_1);
        pushButton->setObjectName("pushButton");

        horizontalLayout_2->addWidget(pushButton);


        formLayout->setLayout(4, QFormLayout::LabelRole, horizontalLayout_2);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName("verticalLayout_10");
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName("horizontalLayout_12");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label_userPic = new QLabel(Post_1);
        label_userPic->setObjectName("label_userPic");
        label_userPic->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(label_userPic);

        label_username = new QLabel(Post_1);
        label_username->setObjectName("label_username");
        label_username->setAlignment(Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignTop);

        verticalLayout->addWidget(label_username);


        horizontalLayout_12->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        textEdit_postQ = new QTextEdit(Post_1);
        textEdit_postQ->setObjectName("textEdit_postQ");

        verticalLayout_2->addWidget(textEdit_postQ);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        pushButton_upPost = new QPushButton(Post_1);
        pushButton_upPost->setObjectName("pushButton_upPost");

        horizontalLayout_3->addWidget(pushButton_upPost);

        label_upPostCount = new QLabel(Post_1);
        label_upPostCount->setObjectName("label_upPostCount");

        horizontalLayout_3->addWidget(label_upPostCount);

        pushButton_downPost = new QPushButton(Post_1);
        pushButton_downPost->setObjectName("pushButton_downPost");

        horizontalLayout_3->addWidget(pushButton_downPost);

        label_downPostCount = new QLabel(Post_1);
        label_downPostCount->setObjectName("label_downPostCount");

        horizontalLayout_3->addWidget(label_downPostCount);


        verticalLayout_2->addLayout(horizontalLayout_3);


        horizontalLayout_12->addLayout(verticalLayout_2);


        verticalLayout_10->addLayout(horizontalLayout_12);

        label_3 = new QLabel(Post_1);
        label_3->setObjectName("label_3");
        label_3->setAlignment(Qt::AlignmentFlag::AlignBottom|Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft);

        verticalLayout_10->addWidget(label_3);


        formLayout->setLayout(2, QFormLayout::SpanningRole, verticalLayout_10);


        retranslateUi(Post_1);

        QMetaObject::connectSlotsByName(Post_1);
    } // setupUi

    void retranslateUi(QDialog *Post_1)
    {
        Post_1->setWindowTitle(QCoreApplication::translate("Post_1", "Post", nullptr));

        const bool __sortingEnabled = listWidget->isSortingEnabled();
        listWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget->item(0);
        ___qlistwidgetitem->setText(QCoreApplication::translate("Post_1", "Answer 1", nullptr));
        QListWidgetItem *___qlistwidgetitem1 = listWidget->item(1);
        ___qlistwidgetitem1->setText(QCoreApplication::translate("Post_1", "Answer 2", nullptr));
        QListWidgetItem *___qlistwidgetitem2 = listWidget->item(2);
        ___qlistwidgetitem2->setText(QCoreApplication::translate("Post_1", "Answer 3", nullptr));
        QListWidgetItem *___qlistwidgetitem3 = listWidget->item(3);
        ___qlistwidgetitem3->setText(QCoreApplication::translate("Post_1", "Answer 4", nullptr));
        QListWidgetItem *___qlistwidgetitem4 = listWidget->item(4);
        ___qlistwidgetitem4->setText(QCoreApplication::translate("Post_1", "Answer 5", nullptr));
        listWidget->setSortingEnabled(__sortingEnabled);

        pushButton->setText(QCoreApplication::translate("Post_1", "Make a Comment", nullptr));
        label_userPic->setText(QString());
        label_username->setText(QCoreApplication::translate("Post_1", "Username", nullptr));
        textEdit_postQ->setHtml(QCoreApplication::translate("Post_1", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Read only</p></body></html>", nullptr));
        pushButton_upPost->setText(QString());
        label_upPostCount->setText(QCoreApplication::translate("Post_1", "0", nullptr));
        pushButton_downPost->setText(QString());
        label_downPostCount->setText(QCoreApplication::translate("Post_1", "0", nullptr));
        label_3->setText(QCoreApplication::translate("Post_1", "Answers", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Post_1: public Ui_Post_1 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POST_1_H
