/********************************************************************************
** Form generated from reading UI file 'makecommentorpost.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAKECOMMENTORPOST_H
#define UI_MAKECOMMENTORPOST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_makeCommentOrPost
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QTextEdit *textEdit;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *makeCommentOrPost)
    {
        if (makeCommentOrPost->objectName().isEmpty())
            makeCommentOrPost->setObjectName("makeCommentOrPost");
        makeCommentOrPost->resize(400, 300);
        verticalLayout = new QVBoxLayout(makeCommentOrPost);
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(makeCommentOrPost);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        textEdit = new QTextEdit(makeCommentOrPost);
        textEdit->setObjectName("textEdit");

        verticalLayout->addWidget(textEdit);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        pushButton = new QPushButton(makeCommentOrPost);
        pushButton->setObjectName("pushButton");

        horizontalLayout_2->addWidget(pushButton);

        pushButton_2 = new QPushButton(makeCommentOrPost);
        pushButton_2->setObjectName("pushButton_2");

        horizontalLayout_2->addWidget(pushButton_2);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(makeCommentOrPost);
        QObject::connect(pushButton_2, &QPushButton::clicked, makeCommentOrPost, qOverload<>(&QDialog::close));
        QObject::connect(pushButton, &QPushButton::clicked, makeCommentOrPost, qOverload<>(&QDialog::close));

        QMetaObject::connectSlotsByName(makeCommentOrPost);
    } // setupUi

    void retranslateUi(QDialog *makeCommentOrPost)
    {
        makeCommentOrPost->setWindowTitle(QCoreApplication::translate("makeCommentOrPost", "Making a Post or Comment", nullptr));
        label->setText(QCoreApplication::translate("makeCommentOrPost", "Text Editor", nullptr));
        pushButton->setText(QCoreApplication::translate("makeCommentOrPost", "Ok", nullptr));
        pushButton_2->setText(QCoreApplication::translate("makeCommentOrPost", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class makeCommentOrPost: public Ui_makeCommentOrPost {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAKECOMMENTORPOST_H
