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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AccountCode
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *lineEdit_code;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_submitCode;
    QPushButton *pushButton;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *AccountCode)
    {
        if (AccountCode->objectName().isEmpty())
            AccountCode->setObjectName("AccountCode");
        AccountCode->resize(428, 276);
        AccountCode->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        verticalLayout = new QVBoxLayout(AccountCode);
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(AccountCode);
        label->setObjectName("label");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(20);
        label->setFont(font);
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
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEdit_code->sizePolicy().hasHeightForWidth());
        lineEdit_code->setSizePolicy(sizePolicy1);
        lineEdit_code->setFont(font);

        verticalLayout->addWidget(lineEdit_code);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        pushButton_submitCode = new QPushButton(AccountCode);
        pushButton_submitCode->setObjectName("pushButton_submitCode");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButton_submitCode->sizePolicy().hasHeightForWidth());
        pushButton_submitCode->setSizePolicy(sizePolicy2);
        QPalette palette;
        QBrush brush(QColor(0, 255, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
        pushButton_submitCode->setPalette(palette);
        QFont font1;
        font1.setPointSize(30);
        pushButton_submitCode->setFont(font1);

        horizontalLayout->addWidget(pushButton_submitCode);

        pushButton = new QPushButton(AccountCode);
        pushButton->setObjectName("pushButton");
        sizePolicy2.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy2);
        QPalette palette1;
        QBrush brush1(QColor(255, 0, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        pushButton->setPalette(palette1);
        pushButton->setFont(font1);

        horizontalLayout->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(AccountCode);

        QMetaObject::connectSlotsByName(AccountCode);
    } // setupUi

    void retranslateUi(QDialog *AccountCode)
    {
        AccountCode->setWindowTitle(QCoreApplication::translate("AccountCode", "Code Confirmation", nullptr));
        label->setText(QCoreApplication::translate("AccountCode", "Insert code below.\n"
"If code does not work, try reopening this window by clicking the \"I have a code\" button", nullptr));
        pushButton_submitCode->setText(QCoreApplication::translate("AccountCode", "Submit", nullptr));
        pushButton->setText(QCoreApplication::translate("AccountCode", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AccountCode: public Ui_AccountCode {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACCOUNTCODE_H
