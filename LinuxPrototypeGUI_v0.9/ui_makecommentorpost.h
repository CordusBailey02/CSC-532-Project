/********************************************************************************
** Form generated from reading UI file 'makecommentorpost.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
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
        QSizePolicy sizePolicy(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(15);
        label->setFont(font);

        verticalLayout->addWidget(label);

        textEdit = new QTextEdit(makeCommentOrPost);
        textEdit->setObjectName("textEdit");
        textEdit->setFont(font);

        verticalLayout->addWidget(textEdit);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        pushButton = new QPushButton(makeCommentOrPost);
        pushButton->setObjectName("pushButton");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy1);
        QPalette palette;
        QBrush brush(QColor(0, 255, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
        pushButton->setPalette(palette);
        pushButton->setFont(font);

        horizontalLayout_2->addWidget(pushButton);

        pushButton_2 = new QPushButton(makeCommentOrPost);
        pushButton_2->setObjectName("pushButton_2");
        sizePolicy1.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy1);
        QPalette palette1;
        QBrush brush1(QColor(255, 0, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        pushButton_2->setPalette(palette1);
        pushButton_2->setFont(font);

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
