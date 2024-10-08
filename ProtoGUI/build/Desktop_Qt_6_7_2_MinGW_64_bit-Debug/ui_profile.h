/********************************************************************************
** Form generated from reading UI file 'profile.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROFILE_H
#define UI_PROFILE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Profile
{
public:
    QGridLayout *gridLayout;
    QPushButton *pushButton_profilePic;
    QPushButton *pushButton_closeProfile;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_LinkedInBtn;
    QLineEdit *lineEdit_LinkedInLine;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_AddResume;
    QPushButton *pushButton_ViewResume;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_AddDegree;
    QPushButton *pushButton_ViewDegree;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton_AddCertificates;
    QPushButton *pushButton_ViewCertificates;
    QPushButton *pushButton_AddDriverLicense;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer;

    void setupUi(QDialog *Profile)
    {
        if (Profile->objectName().isEmpty())
            Profile->setObjectName("Profile");
        Profile->resize(400, 300);
        gridLayout = new QGridLayout(Profile);
        gridLayout->setObjectName("gridLayout");
        pushButton_profilePic = new QPushButton(Profile);
        pushButton_profilePic->setObjectName("pushButton_profilePic");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_profilePic->sizePolicy().hasHeightForWidth());
        pushButton_profilePic->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButton_profilePic, 2, 0, 1, 1);

        pushButton_closeProfile = new QPushButton(Profile);
        pushButton_closeProfile->setObjectName("pushButton_closeProfile");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton_closeProfile->sizePolicy().hasHeightForWidth());
        pushButton_closeProfile->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(pushButton_closeProfile, 0, 2, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        pushButton_LinkedInBtn = new QPushButton(Profile);
        pushButton_LinkedInBtn->setObjectName("pushButton_LinkedInBtn");
        sizePolicy1.setHeightForWidth(pushButton_LinkedInBtn->sizePolicy().hasHeightForWidth());
        pushButton_LinkedInBtn->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(pushButton_LinkedInBtn);

        lineEdit_LinkedInLine = new QLineEdit(Profile);
        lineEdit_LinkedInLine->setObjectName("lineEdit_LinkedInLine");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lineEdit_LinkedInLine->sizePolicy().hasHeightForWidth());
        lineEdit_LinkedInLine->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(lineEdit_LinkedInLine);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        pushButton_AddResume = new QPushButton(Profile);
        pushButton_AddResume->setObjectName("pushButton_AddResume");

        horizontalLayout_2->addWidget(pushButton_AddResume);

        pushButton_ViewResume = new QPushButton(Profile);
        pushButton_ViewResume->setObjectName("pushButton_ViewResume");

        horizontalLayout_2->addWidget(pushButton_ViewResume);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        pushButton_AddDegree = new QPushButton(Profile);
        pushButton_AddDegree->setObjectName("pushButton_AddDegree");

        horizontalLayout_3->addWidget(pushButton_AddDegree);

        pushButton_ViewDegree = new QPushButton(Profile);
        pushButton_ViewDegree->setObjectName("pushButton_ViewDegree");

        horizontalLayout_3->addWidget(pushButton_ViewDegree);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        pushButton_AddCertificates = new QPushButton(Profile);
        pushButton_AddCertificates->setObjectName("pushButton_AddCertificates");

        horizontalLayout_4->addWidget(pushButton_AddCertificates);

        pushButton_ViewCertificates = new QPushButton(Profile);
        pushButton_ViewCertificates->setObjectName("pushButton_ViewCertificates");

        horizontalLayout_4->addWidget(pushButton_ViewCertificates);


        verticalLayout->addLayout(horizontalLayout_4);

        pushButton_AddDriverLicense = new QPushButton(Profile);
        pushButton_AddDriverLicense->setObjectName("pushButton_AddDriverLicense");

        verticalLayout->addWidget(pushButton_AddDriverLicense);


        gridLayout->addLayout(verticalLayout, 4, 0, 1, 1);

        pushButton = new QPushButton(Profile);
        pushButton->setObjectName("pushButton");

        gridLayout->addWidget(pushButton, 3, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 1, 3, 1);


        retranslateUi(Profile);
        QObject::connect(pushButton_closeProfile, &QPushButton::clicked, Profile, qOverload<>(&QDialog::close));

        QMetaObject::connectSlotsByName(Profile);
    } // setupUi

    void retranslateUi(QDialog *Profile)
    {
        Profile->setWindowTitle(QCoreApplication::translate("Profile", "Dialog", nullptr));
        pushButton_profilePic->setText(QString());
        pushButton_closeProfile->setText(QCoreApplication::translate("Profile", "X", nullptr));
        pushButton_LinkedInBtn->setText(QCoreApplication::translate("Profile", "LinkedIn", nullptr));
        pushButton_AddResume->setText(QCoreApplication::translate("Profile", "Add Resume", nullptr));
        pushButton_ViewResume->setText(QCoreApplication::translate("Profile", "View Resume", nullptr));
        pushButton_AddDegree->setText(QCoreApplication::translate("Profile", "Add Degree", nullptr));
        pushButton_ViewDegree->setText(QCoreApplication::translate("Profile", "View Degree", nullptr));
        pushButton_AddCertificates->setText(QCoreApplication::translate("Profile", "Add Certificates", nullptr));
        pushButton_ViewCertificates->setText(QCoreApplication::translate("Profile", "View Certificates", nullptr));
        pushButton_AddDriverLicense->setText(QCoreApplication::translate("Profile", "Add Driver's License", nullptr));
        pushButton->setText(QCoreApplication::translate("Profile", "Change Icon", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Profile: public Ui_Profile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROFILE_H
