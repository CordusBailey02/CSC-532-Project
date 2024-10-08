/********************************************************************************
** Form generated from reading UI file 'post_1.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POST_1_H
#define UI_POST_1_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Post_1
{
public:
    QPushButton *pushButton;

    void setupUi(QDialog *Post_1)
    {
        if (Post_1->objectName().isEmpty())
            Post_1->setObjectName("Post_1");
        Post_1->resize(400, 300);
        pushButton = new QPushButton(Post_1);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(20, 20, 91, 31));

        retranslateUi(Post_1);
        QObject::connect(pushButton, &QPushButton::clicked, Post_1, qOverload<>(&QDialog::close));

        QMetaObject::connectSlotsByName(Post_1);
    } // setupUi

    void retranslateUi(QDialog *Post_1)
    {
        Post_1->setWindowTitle(QCoreApplication::translate("Post_1", "Dialog", nullptr));
        pushButton->setText(QCoreApplication::translate("Post_1", "Close post", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Post_1: public Ui_Post_1 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POST_1_H
