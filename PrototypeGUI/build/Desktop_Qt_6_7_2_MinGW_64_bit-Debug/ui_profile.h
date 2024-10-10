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
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Profile
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_8;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout_4;
    QPushButton *pushButton_profilePic;
    QPushButton *pushButton;
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
    QVBoxLayout *verticalLayout_7;
    QLabel *label;
    QListWidget *listWidget_postsFromProfile;
    QLabel *label_2;
    QListWidget *listWidget_commentsFromProfile;

    void setupUi(QDialog *Profile)
    {
        if (Profile->objectName().isEmpty())
            Profile->setObjectName("Profile");
        Profile->resize(400, 300);
        gridLayout = new QGridLayout(Profile);
        gridLayout->setObjectName("gridLayout");
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        pushButton_profilePic = new QPushButton(Profile);
        pushButton_profilePic->setObjectName("pushButton_profilePic");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_profilePic->sizePolicy().hasHeightForWidth());
        pushButton_profilePic->setSizePolicy(sizePolicy);

        verticalLayout_4->addWidget(pushButton_profilePic);

        pushButton = new QPushButton(Profile);
        pushButton->setObjectName("pushButton");

        verticalLayout_4->addWidget(pushButton);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        pushButton_LinkedInBtn = new QPushButton(Profile);
        pushButton_LinkedInBtn->setObjectName("pushButton_LinkedInBtn");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
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


        verticalLayout_4->addLayout(verticalLayout);


        verticalLayout_5->addLayout(verticalLayout_4);


        horizontalLayout_8->addLayout(verticalLayout_5);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName("verticalLayout_7");
        label = new QLabel(Profile);
        label->setObjectName("label");

        verticalLayout_7->addWidget(label);

        listWidget_postsFromProfile = new QListWidget(Profile);
        new QListWidgetItem(listWidget_postsFromProfile);
        new QListWidgetItem(listWidget_postsFromProfile);
        new QListWidgetItem(listWidget_postsFromProfile);
        new QListWidgetItem(listWidget_postsFromProfile);
        new QListWidgetItem(listWidget_postsFromProfile);
        new QListWidgetItem(listWidget_postsFromProfile);
        new QListWidgetItem(listWidget_postsFromProfile);
        listWidget_postsFromProfile->setObjectName("listWidget_postsFromProfile");

        verticalLayout_7->addWidget(listWidget_postsFromProfile);

        label_2 = new QLabel(Profile);
        label_2->setObjectName("label_2");

        verticalLayout_7->addWidget(label_2);

        listWidget_commentsFromProfile = new QListWidget(Profile);
        new QListWidgetItem(listWidget_commentsFromProfile);
        new QListWidgetItem(listWidget_commentsFromProfile);
        new QListWidgetItem(listWidget_commentsFromProfile);
        new QListWidgetItem(listWidget_commentsFromProfile);
        new QListWidgetItem(listWidget_commentsFromProfile);
        new QListWidgetItem(listWidget_commentsFromProfile);
        new QListWidgetItem(listWidget_commentsFromProfile);
        listWidget_commentsFromProfile->setObjectName("listWidget_commentsFromProfile");

        verticalLayout_7->addWidget(listWidget_commentsFromProfile);


        horizontalLayout_8->addLayout(verticalLayout_7);


        gridLayout->addLayout(horizontalLayout_8, 1, 0, 1, 1);


        retranslateUi(Profile);

        QMetaObject::connectSlotsByName(Profile);
    } // setupUi

    void retranslateUi(QDialog *Profile)
    {
        Profile->setWindowTitle(QCoreApplication::translate("Profile", "Profile", nullptr));
        pushButton_profilePic->setText(QString());
        pushButton->setText(QCoreApplication::translate("Profile", "Change Icon", nullptr));
        pushButton_LinkedInBtn->setText(QCoreApplication::translate("Profile", "LinkedIn", nullptr));
        pushButton_AddResume->setText(QCoreApplication::translate("Profile", "Add Resume", nullptr));
        pushButton_ViewResume->setText(QCoreApplication::translate("Profile", "View Resume", nullptr));
        pushButton_AddDegree->setText(QCoreApplication::translate("Profile", "Add Degree", nullptr));
        pushButton_ViewDegree->setText(QCoreApplication::translate("Profile", "View Degree", nullptr));
        pushButton_AddCertificates->setText(QCoreApplication::translate("Profile", "Add Certificates", nullptr));
        pushButton_ViewCertificates->setText(QCoreApplication::translate("Profile", "View Certificates", nullptr));
        pushButton_AddDriverLicense->setText(QCoreApplication::translate("Profile", "Add Driver's License", nullptr));
        label->setText(QCoreApplication::translate("Profile", "Posts", nullptr));

        const bool __sortingEnabled = listWidget_postsFromProfile->isSortingEnabled();
        listWidget_postsFromProfile->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget_postsFromProfile->item(0);
        ___qlistwidgetitem->setText(QCoreApplication::translate("Profile", "Post 1", nullptr));
        QListWidgetItem *___qlistwidgetitem1 = listWidget_postsFromProfile->item(1);
        ___qlistwidgetitem1->setText(QCoreApplication::translate("Profile", "Post 2", nullptr));
        QListWidgetItem *___qlistwidgetitem2 = listWidget_postsFromProfile->item(2);
        ___qlistwidgetitem2->setText(QCoreApplication::translate("Profile", "Post 3", nullptr));
        QListWidgetItem *___qlistwidgetitem3 = listWidget_postsFromProfile->item(3);
        ___qlistwidgetitem3->setText(QCoreApplication::translate("Profile", "Post 4", nullptr));
        QListWidgetItem *___qlistwidgetitem4 = listWidget_postsFromProfile->item(4);
        ___qlistwidgetitem4->setText(QCoreApplication::translate("Profile", "Post 5", nullptr));
        QListWidgetItem *___qlistwidgetitem5 = listWidget_postsFromProfile->item(5);
        ___qlistwidgetitem5->setText(QCoreApplication::translate("Profile", "Post 6", nullptr));
        QListWidgetItem *___qlistwidgetitem6 = listWidget_postsFromProfile->item(6);
        ___qlistwidgetitem6->setText(QCoreApplication::translate("Profile", "Post 7", nullptr));
        listWidget_postsFromProfile->setSortingEnabled(__sortingEnabled);

        label_2->setText(QCoreApplication::translate("Profile", "Comments", nullptr));

        const bool __sortingEnabled1 = listWidget_commentsFromProfile->isSortingEnabled();
        listWidget_commentsFromProfile->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem7 = listWidget_commentsFromProfile->item(0);
        ___qlistwidgetitem7->setText(QCoreApplication::translate("Profile", "Comment 1", nullptr));
        QListWidgetItem *___qlistwidgetitem8 = listWidget_commentsFromProfile->item(1);
        ___qlistwidgetitem8->setText(QCoreApplication::translate("Profile", "Comment 2", nullptr));
        QListWidgetItem *___qlistwidgetitem9 = listWidget_commentsFromProfile->item(2);
        ___qlistwidgetitem9->setText(QCoreApplication::translate("Profile", "Comment 3", nullptr));
        QListWidgetItem *___qlistwidgetitem10 = listWidget_commentsFromProfile->item(3);
        ___qlistwidgetitem10->setText(QCoreApplication::translate("Profile", "Comment 4", nullptr));
        QListWidgetItem *___qlistwidgetitem11 = listWidget_commentsFromProfile->item(4);
        ___qlistwidgetitem11->setText(QCoreApplication::translate("Profile", "Comment 5", nullptr));
        QListWidgetItem *___qlistwidgetitem12 = listWidget_commentsFromProfile->item(5);
        ___qlistwidgetitem12->setText(QCoreApplication::translate("Profile", "Comment 6", nullptr));
        QListWidgetItem *___qlistwidgetitem13 = listWidget_commentsFromProfile->item(6);
        ___qlistwidgetitem13->setText(QCoreApplication::translate("Profile", "Comment 7", nullptr));
        listWidget_commentsFromProfile->setSortingEnabled(__sortingEnabled1);

    } // retranslateUi

};

namespace Ui {
    class Profile: public Ui_Profile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROFILE_H
