/********************************************************************************
** Form generated from reading UI file 'forgotpassword.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORGOTPASSWORD_H
#define UI_FORGOTPASSWORD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_forgotPassword
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *lineEdit_forgotPasswordEmail;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_forgotConfirm;
    QPushButton *pushButton_forgotCancel;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *forgotPassword)
    {
        if (forgotPassword->objectName().isEmpty())
            forgotPassword->setObjectName("forgotPassword");
        forgotPassword->resize(400, 300);
        verticalLayout_2 = new QVBoxLayout(forgotPassword);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        formLayout->setFormAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        label = new QLabel(forgotPassword);
        label->setObjectName("label");
        QFont font;
        font.setPointSize(30);
        label->setFont(font);

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        lineEdit_forgotPasswordEmail = new QLineEdit(forgotPassword);
        lineEdit_forgotPasswordEmail->setObjectName("lineEdit_forgotPasswordEmail");
        lineEdit_forgotPasswordEmail->setFont(font);

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEdit_forgotPasswordEmail);


        verticalLayout->addLayout(formLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        pushButton_forgotConfirm = new QPushButton(forgotPassword);
        pushButton_forgotConfirm->setObjectName("pushButton_forgotConfirm");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_forgotConfirm->sizePolicy().hasHeightForWidth());
        pushButton_forgotConfirm->setSizePolicy(sizePolicy);
        pushButton_forgotConfirm->setFont(font);

        horizontalLayout->addWidget(pushButton_forgotConfirm);

        pushButton_forgotCancel = new QPushButton(forgotPassword);
        pushButton_forgotCancel->setObjectName("pushButton_forgotCancel");
        sizePolicy.setHeightForWidth(pushButton_forgotCancel->sizePolicy().hasHeightForWidth());
        pushButton_forgotCancel->setSizePolicy(sizePolicy);
        pushButton_forgotCancel->setFont(font);

        horizontalLayout->addWidget(pushButton_forgotCancel);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Maximum);

        verticalLayout->addItem(verticalSpacer);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(forgotPassword);

        QMetaObject::connectSlotsByName(forgotPassword);
    } // setupUi

    void retranslateUi(QDialog *forgotPassword)
    {
        forgotPassword->setWindowTitle(QCoreApplication::translate("forgotPassword", "Forgot Password Window", nullptr));
        label->setText(QCoreApplication::translate("forgotPassword", "Email", nullptr));
        pushButton_forgotConfirm->setText(QCoreApplication::translate("forgotPassword", "Confirm", nullptr));
        pushButton_forgotCancel->setText(QCoreApplication::translate("forgotPassword", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class forgotPassword: public Ui_forgotPassword {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORGOTPASSWORD_H
