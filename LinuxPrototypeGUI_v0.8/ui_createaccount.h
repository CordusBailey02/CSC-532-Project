/********************************************************************************
** Form generated from reading UI file 'createaccount.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEACCOUNT_H
#define UI_CREATEACCOUNT_H

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

class Ui_createAccount
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit_accountNewEmail;
    QLineEdit *lineEdit_accountNewUsername;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *lineEdit_accountNewPassword;
    QLineEdit *lineEdit_accountNewPasswordConfirm;
    QLabel *label_6;
    QLabel *label_5;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_createConfirm;
    QPushButton *pushButton_createCancel;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_AccountCode;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *createAccount)
    {
        if (createAccount->objectName().isEmpty())
            createAccount->setObjectName("createAccount");
        createAccount->resize(446, 298);
        verticalLayout_2 = new QVBoxLayout(createAccount);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        formLayout->setFormAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);
        label = new QLabel(createAccount);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        label_2 = new QLabel(createAccount);
        label_2->setObjectName("label_2");

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        lineEdit_accountNewEmail = new QLineEdit(createAccount);
        lineEdit_accountNewEmail->setObjectName("lineEdit_accountNewEmail");

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEdit_accountNewEmail);

        lineEdit_accountNewUsername = new QLineEdit(createAccount);
        lineEdit_accountNewUsername->setObjectName("lineEdit_accountNewUsername");

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEdit_accountNewUsername);

        label_3 = new QLabel(createAccount);
        label_3->setObjectName("label_3");

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        label_4 = new QLabel(createAccount);
        label_4->setObjectName("label_4");

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);

        lineEdit_accountNewPassword = new QLineEdit(createAccount);
        lineEdit_accountNewPassword->setObjectName("lineEdit_accountNewPassword");
        lineEdit_accountNewPassword->setEchoMode(QLineEdit::EchoMode::Password);

        formLayout->setWidget(2, QFormLayout::FieldRole, lineEdit_accountNewPassword);

        lineEdit_accountNewPasswordConfirm = new QLineEdit(createAccount);
        lineEdit_accountNewPasswordConfirm->setObjectName("lineEdit_accountNewPasswordConfirm");
        lineEdit_accountNewPasswordConfirm->setEchoMode(QLineEdit::EchoMode::Password);

        formLayout->setWidget(3, QFormLayout::FieldRole, lineEdit_accountNewPasswordConfirm);


        verticalLayout->addLayout(formLayout);

        label_6 = new QLabel(createAccount);
        label_6->setObjectName("label_6");
        label_6->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(label_6);

        label_5 = new QLabel(createAccount);
        label_5->setObjectName("label_5");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);
        label_5->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(label_5);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        pushButton_createConfirm = new QPushButton(createAccount);
        pushButton_createConfirm->setObjectName("pushButton_createConfirm");
        pushButton_createConfirm->setFocusPolicy(Qt::FocusPolicy::NoFocus);

        horizontalLayout->addWidget(pushButton_createConfirm);

        pushButton_createCancel = new QPushButton(createAccount);
        pushButton_createCancel->setObjectName("pushButton_createCancel");
        pushButton_createCancel->setFocusPolicy(Qt::FocusPolicy::NoFocus);

        horizontalLayout->addWidget(pushButton_createCancel);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        pushButton_AccountCode = new QPushButton(createAccount);
        pushButton_AccountCode->setObjectName("pushButton_AccountCode");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton_AccountCode->sizePolicy().hasHeightForWidth());
        pushButton_AccountCode->setSizePolicy(sizePolicy1);
        pushButton_AccountCode->setFocusPolicy(Qt::FocusPolicy::NoFocus);

        horizontalLayout_2->addWidget(pushButton_AccountCode);


        verticalLayout_3->addLayout(horizontalLayout_2);


        verticalLayout->addLayout(verticalLayout_3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Maximum);

        verticalLayout->addItem(verticalSpacer);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(createAccount);

        QMetaObject::connectSlotsByName(createAccount);
    } // setupUi

    void retranslateUi(QDialog *createAccount)
    {
        createAccount->setWindowTitle(QCoreApplication::translate("createAccount", "Create Account Window", nullptr));
        label->setText(QCoreApplication::translate("createAccount", "Email", nullptr));
        label_2->setText(QCoreApplication::translate("createAccount", "Username", nullptr));
        label_3->setText(QCoreApplication::translate("createAccount", "Password", nullptr));
        label_4->setText(QCoreApplication::translate("createAccount", "Confirm Password", nullptr));
        label_6->setText(QCoreApplication::translate("createAccount", "Username must be at least 4 characters long", nullptr));
        label_5->setText(QCoreApplication::translate("createAccount", "Password must be 8 to 15 characters long", nullptr));
        pushButton_createConfirm->setText(QCoreApplication::translate("createAccount", "Confirm", nullptr));
        pushButton_createCancel->setText(QCoreApplication::translate("createAccount", "Cancel", nullptr));
        pushButton_AccountCode->setText(QCoreApplication::translate("createAccount", "I have a code", nullptr));
    } // retranslateUi

};

namespace Ui {
    class createAccount: public Ui_createAccount {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEACCOUNT_H
