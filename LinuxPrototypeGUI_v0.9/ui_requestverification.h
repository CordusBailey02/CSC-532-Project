/********************************************************************************
** Form generated from reading UI file 'requestverification.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REQUESTVERIFICATION_H
#define UI_REQUESTVERIFICATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_requestVerification
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *comboBox_occupations;
    QLabel *label_2;
    QLineEdit *lineEdit_linkedInLine;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_addResume;
    QLabel *label_resumeFilePath;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton_addDegree;
    QLabel *label_degreeFilePath;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *pushButton_addCertificate;
    QLabel *label_certificateFilePath;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *pushButton_addDriverLicense;
    QLabel *label_driverLicenseFilePath;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *pushButton_submitVerificationRequest;
    QPushButton *pushButton_cancelVerificationRequest;

    void setupUi(QDialog *requestVerification)
    {
        if (requestVerification->objectName().isEmpty())
            requestVerification->setObjectName("requestVerification");
        requestVerification->resize(1088, 468);
        verticalLayout = new QVBoxLayout(requestVerification);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(requestVerification);
        label->setObjectName("label");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(20);
        label->setFont(font);

        horizontalLayout->addWidget(label);

        comboBox_occupations = new QComboBox(requestVerification);
        comboBox_occupations->addItem(QString());
        comboBox_occupations->addItem(QString());
        comboBox_occupations->addItem(QString());
        comboBox_occupations->addItem(QString());
        comboBox_occupations->addItem(QString());
        comboBox_occupations->addItem(QString());
        comboBox_occupations->addItem(QString());
        comboBox_occupations->addItem(QString());
        comboBox_occupations->setObjectName("comboBox_occupations");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(comboBox_occupations->sizePolicy().hasHeightForWidth());
        comboBox_occupations->setSizePolicy(sizePolicy1);
        comboBox_occupations->setFont(font);

        horizontalLayout->addWidget(comboBox_occupations);

        label_2 = new QLabel(requestVerification);
        label_2->setObjectName("label_2");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy2);
        label_2->setFont(font);

        horizontalLayout->addWidget(label_2);

        lineEdit_linkedInLine = new QLineEdit(requestVerification);
        lineEdit_linkedInLine->setObjectName("lineEdit_linkedInLine");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(4);
        sizePolicy3.setHeightForWidth(lineEdit_linkedInLine->sizePolicy().hasHeightForWidth());
        lineEdit_linkedInLine->setSizePolicy(sizePolicy3);
        lineEdit_linkedInLine->setFont(font);

        horizontalLayout->addWidget(lineEdit_linkedInLine);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        pushButton_addResume = new QPushButton(requestVerification);
        pushButton_addResume->setObjectName("pushButton_addResume");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(pushButton_addResume->sizePolicy().hasHeightForWidth());
        pushButton_addResume->setSizePolicy(sizePolicy4);
        pushButton_addResume->setFont(font);

        horizontalLayout_3->addWidget(pushButton_addResume);

        label_resumeFilePath = new QLabel(requestVerification);
        label_resumeFilePath->setObjectName("label_resumeFilePath");
        QSizePolicy sizePolicy5(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(label_resumeFilePath->sizePolicy().hasHeightForWidth());
        label_resumeFilePath->setSizePolicy(sizePolicy5);
        QFont font1;
        font1.setPointSize(15);
        label_resumeFilePath->setFont(font1);

        horizontalLayout_3->addWidget(label_resumeFilePath);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        pushButton_addDegree = new QPushButton(requestVerification);
        pushButton_addDegree->setObjectName("pushButton_addDegree");
        sizePolicy4.setHeightForWidth(pushButton_addDegree->sizePolicy().hasHeightForWidth());
        pushButton_addDegree->setSizePolicy(sizePolicy4);
        pushButton_addDegree->setFont(font);

        horizontalLayout_4->addWidget(pushButton_addDegree);

        label_degreeFilePath = new QLabel(requestVerification);
        label_degreeFilePath->setObjectName("label_degreeFilePath");
        sizePolicy5.setHeightForWidth(label_degreeFilePath->sizePolicy().hasHeightForWidth());
        label_degreeFilePath->setSizePolicy(sizePolicy5);
        label_degreeFilePath->setFont(font1);

        horizontalLayout_4->addWidget(label_degreeFilePath);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        pushButton_addCertificate = new QPushButton(requestVerification);
        pushButton_addCertificate->setObjectName("pushButton_addCertificate");
        sizePolicy4.setHeightForWidth(pushButton_addCertificate->sizePolicy().hasHeightForWidth());
        pushButton_addCertificate->setSizePolicy(sizePolicy4);
        pushButton_addCertificate->setFont(font);

        horizontalLayout_5->addWidget(pushButton_addCertificate);

        label_certificateFilePath = new QLabel(requestVerification);
        label_certificateFilePath->setObjectName("label_certificateFilePath");
        sizePolicy5.setHeightForWidth(label_certificateFilePath->sizePolicy().hasHeightForWidth());
        label_certificateFilePath->setSizePolicy(sizePolicy5);
        label_certificateFilePath->setFont(font1);

        horizontalLayout_5->addWidget(label_certificateFilePath);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        pushButton_addDriverLicense = new QPushButton(requestVerification);
        pushButton_addDriverLicense->setObjectName("pushButton_addDriverLicense");
        sizePolicy4.setHeightForWidth(pushButton_addDriverLicense->sizePolicy().hasHeightForWidth());
        pushButton_addDriverLicense->setSizePolicy(sizePolicy4);
        pushButton_addDriverLicense->setFont(font);

        horizontalLayout_6->addWidget(pushButton_addDriverLicense);

        label_driverLicenseFilePath = new QLabel(requestVerification);
        label_driverLicenseFilePath->setObjectName("label_driverLicenseFilePath");
        sizePolicy5.setHeightForWidth(label_driverLicenseFilePath->sizePolicy().hasHeightForWidth());
        label_driverLicenseFilePath->setSizePolicy(sizePolicy5);
        label_driverLicenseFilePath->setFont(font1);

        horizontalLayout_6->addWidget(label_driverLicenseFilePath);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        pushButton_submitVerificationRequest = new QPushButton(requestVerification);
        pushButton_submitVerificationRequest->setObjectName("pushButton_submitVerificationRequest");
        sizePolicy4.setHeightForWidth(pushButton_submitVerificationRequest->sizePolicy().hasHeightForWidth());
        pushButton_submitVerificationRequest->setSizePolicy(sizePolicy4);
        QPalette palette;
        QBrush brush(QColor(0, 255, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
        pushButton_submitVerificationRequest->setPalette(palette);
        pushButton_submitVerificationRequest->setFont(font);

        horizontalLayout_7->addWidget(pushButton_submitVerificationRequest);

        pushButton_cancelVerificationRequest = new QPushButton(requestVerification);
        pushButton_cancelVerificationRequest->setObjectName("pushButton_cancelVerificationRequest");
        sizePolicy4.setHeightForWidth(pushButton_cancelVerificationRequest->sizePolicy().hasHeightForWidth());
        pushButton_cancelVerificationRequest->setSizePolicy(sizePolicy4);
        QPalette palette1;
        QBrush brush1(QColor(255, 0, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        pushButton_cancelVerificationRequest->setPalette(palette1);
        pushButton_cancelVerificationRequest->setFont(font);

        horizontalLayout_7->addWidget(pushButton_cancelVerificationRequest);


        verticalLayout->addLayout(horizontalLayout_7);


        retranslateUi(requestVerification);

        QMetaObject::connectSlotsByName(requestVerification);
    } // setupUi

    void retranslateUi(QDialog *requestVerification)
    {
        requestVerification->setWindowTitle(QCoreApplication::translate("requestVerification", "Request Verification Window", nullptr));
        label->setText(QCoreApplication::translate("requestVerification", "Requesting verification for the occupation of:", nullptr));
        comboBox_occupations->setItemText(0, QString());
        comboBox_occupations->setItemText(1, QCoreApplication::translate("requestVerification", "Programmer", nullptr));
        comboBox_occupations->setItemText(2, QCoreApplication::translate("requestVerification", "Lawyer", nullptr));
        comboBox_occupations->setItemText(3, QCoreApplication::translate("requestVerification", "Politician", nullptr));
        comboBox_occupations->setItemText(4, QCoreApplication::translate("requestVerification", "Mathematician", nullptr));
        comboBox_occupations->setItemText(5, QCoreApplication::translate("requestVerification", "Physician", nullptr));
        comboBox_occupations->setItemText(6, QCoreApplication::translate("requestVerification", "Retail Store Manager", nullptr));
        comboBox_occupations->setItemText(7, QCoreApplication::translate("requestVerification", "Dentist", nullptr));

        label_2->setText(QCoreApplication::translate("requestVerification", "LinkedIn:", nullptr));
        pushButton_addResume->setText(QCoreApplication::translate("requestVerification", "Add Resume", nullptr));
        label_resumeFilePath->setText(QCoreApplication::translate("requestVerification", "No file selected", nullptr));
        pushButton_addDegree->setText(QCoreApplication::translate("requestVerification", "Add Degree", nullptr));
        label_degreeFilePath->setText(QCoreApplication::translate("requestVerification", "No file selected", nullptr));
        pushButton_addCertificate->setText(QCoreApplication::translate("requestVerification", "Add a Certificate", nullptr));
        label_certificateFilePath->setText(QCoreApplication::translate("requestVerification", "No file selected", nullptr));
        pushButton_addDriverLicense->setText(QCoreApplication::translate("requestVerification", "Add Driver's License", nullptr));
        label_driverLicenseFilePath->setText(QCoreApplication::translate("requestVerification", "No file selected", nullptr));
        pushButton_submitVerificationRequest->setText(QCoreApplication::translate("requestVerification", "Submit", nullptr));
        pushButton_cancelVerificationRequest->setText(QCoreApplication::translate("requestVerification", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class requestVerification: public Ui_requestVerification {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REQUESTVERIFICATION_H
