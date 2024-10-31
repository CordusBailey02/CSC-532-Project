/********************************************************************************
** Form generated from reading UI file 'AccountCode.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ACCOUNTCODE_H
#define UI_ACCOUNTCODE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AccountCode
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *lineEdit_code;
    QPushButton *pushButton_submitCode;

    void setupUi(QDialog *AccountCode)
    {
        if (AccountCode->objectName().isEmpty())
            AccountCode->setObjectName("AccountCode");
        AccountCode->resize(300, 113);
        AccountCode->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        verticalLayout = new QVBoxLayout(AccountCode);
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(AccountCode);
        label->setObjectName("label");
        label->setAcceptDrops(false);
        label->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        label->setInputMethodHints(Qt::InputMethodHint::ImhNone);
        label->setTextFormat(Qt::TextFormat::AutoText);
        label->setScaledContents(false);
        label->setAlignment(Qt::AlignmentFlag::AlignBottom|Qt::AlignmentFlag::AlignHCenter);
        label->setWordWrap(true);

        verticalLayout->addWidget(label);

        lineEdit_code = new QLineEdit(AccountCode);
        lineEdit_code->setObjectName("lineEdit_code");

        verticalLayout->addWidget(lineEdit_code);

        pushButton_submitCode = new QPushButton(AccountCode);
        pushButton_submitCode->setObjectName("pushButton_submitCode");

        verticalLayout->addWidget(pushButton_submitCode);


        retranslateUi(AccountCode);

        QMetaObject::connectSlotsByName(AccountCode);
    } // setupUi

    void retranslateUi(QDialog *AccountCode)
    {
        AccountCode->setWindowTitle(QCoreApplication::translate("AccountCode", "Code Confirmation", nullptr));
        label->setText(QCoreApplication::translate("AccountCode", "Insert code below.\n"
"If code does not work, try reopening this window by clicking the \"I have a code\" button", nullptr));
        pushButton_submitCode->setText(QCoreApplication::translate("AccountCode", "Submit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AccountCode: public Ui_AccountCode {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACCOUNTCODE_H
