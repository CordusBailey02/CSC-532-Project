/********************************************************************************
** Form generated from reading UI file 'profile.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
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
    QPushButton *pushButton_viewIcon;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_4;
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
    QLabel *label_5;
    QVBoxLayout *verticalLayout_7;
    QLabel *label;
    QListWidget *listWidget_postsFromProfile;
    QLabel *label_3;
    QListWidget *listWidget_answersFromProfile;
    QLabel *label_2;
    QListWidget *listWidget_commentsFromProfile;

    void setupUi(QDialog *Profile)
    {
        if (Profile->objectName().isEmpty())
            Profile->setObjectName("Profile");
        Profile->resize(490, 383);
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
        QSizePolicy sizePolicy(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_profilePic->sizePolicy().hasHeightForWidth());
        pushButton_profilePic->setSizePolicy(sizePolicy);

        verticalLayout_4->addWidget(pushButton_profilePic);

        pushButton_viewIcon = new QPushButton(Profile);
        pushButton_viewIcon->setObjectName("pushButton_viewIcon");
        QFont font;
        font.setPointSize(15);
        pushButton_viewIcon->setFont(font);

        verticalLayout_4->addWidget(pushButton_viewIcon);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label_4 = new QLabel(Profile);
        label_4->setObjectName("label_4");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy1);
        label_4->setFont(font);

        horizontalLayout->addWidget(label_4);

        lineEdit_LinkedInLine = new QLineEdit(Profile);
        lineEdit_LinkedInLine->setObjectName("lineEdit_LinkedInLine");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lineEdit_LinkedInLine->sizePolicy().hasHeightForWidth());
        lineEdit_LinkedInLine->setSizePolicy(sizePolicy2);
        lineEdit_LinkedInLine->setFont(font);

        horizontalLayout->addWidget(lineEdit_LinkedInLine);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        pushButton_AddResume = new QPushButton(Profile);
        pushButton_AddResume->setObjectName("pushButton_AddResume");
        pushButton_AddResume->setFont(font);

        horizontalLayout_2->addWidget(pushButton_AddResume);

        pushButton_ViewResume = new QPushButton(Profile);
        pushButton_ViewResume->setObjectName("pushButton_ViewResume");
        pushButton_ViewResume->setFont(font);

        horizontalLayout_2->addWidget(pushButton_ViewResume);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        pushButton_AddDegree = new QPushButton(Profile);
        pushButton_AddDegree->setObjectName("pushButton_AddDegree");
        pushButton_AddDegree->setFont(font);

        horizontalLayout_3->addWidget(pushButton_AddDegree);

        pushButton_ViewDegree = new QPushButton(Profile);
        pushButton_ViewDegree->setObjectName("pushButton_ViewDegree");
        pushButton_ViewDegree->setFont(font);

        horizontalLayout_3->addWidget(pushButton_ViewDegree);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        pushButton_AddCertificates = new QPushButton(Profile);
        pushButton_AddCertificates->setObjectName("pushButton_AddCertificates");
        pushButton_AddCertificates->setFont(font);

        horizontalLayout_4->addWidget(pushButton_AddCertificates);

        pushButton_ViewCertificates = new QPushButton(Profile);
        pushButton_ViewCertificates->setObjectName("pushButton_ViewCertificates");
        pushButton_ViewCertificates->setFont(font);

        horizontalLayout_4->addWidget(pushButton_ViewCertificates);


        verticalLayout->addLayout(horizontalLayout_4);

        pushButton_AddDriverLicense = new QPushButton(Profile);
        pushButton_AddDriverLicense->setObjectName("pushButton_AddDriverLicense");
        pushButton_AddDriverLicense->setFont(font);

        verticalLayout->addWidget(pushButton_AddDriverLicense);

        label_5 = new QLabel(Profile);
        label_5->setObjectName("label_5");
        sizePolicy1.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy1);
        label_5->setFont(font);
        label_5->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(label_5);


        verticalLayout_4->addLayout(verticalLayout);


        verticalLayout_5->addLayout(verticalLayout_4);


        horizontalLayout_8->addLayout(verticalLayout_5);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName("verticalLayout_7");
        label = new QLabel(Profile);
        label->setObjectName("label");
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setFont(font);

        verticalLayout_7->addWidget(label);

        listWidget_postsFromProfile = new QListWidget(Profile);
        new QListWidgetItem(listWidget_postsFromProfile);
        new QListWidgetItem(listWidget_postsFromProfile);
        new QListWidgetItem(listWidget_postsFromProfile);
        listWidget_postsFromProfile->setObjectName("listWidget_postsFromProfile");
        listWidget_postsFromProfile->setFont(font);

        verticalLayout_7->addWidget(listWidget_postsFromProfile);

        label_3 = new QLabel(Profile);
        label_3->setObjectName("label_3");
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);
        label_3->setFont(font);

        verticalLayout_7->addWidget(label_3);

        listWidget_answersFromProfile = new QListWidget(Profile);
        new QListWidgetItem(listWidget_answersFromProfile);
        new QListWidgetItem(listWidget_answersFromProfile);
        new QListWidgetItem(listWidget_answersFromProfile);
        listWidget_answersFromProfile->setObjectName("listWidget_answersFromProfile");
        listWidget_answersFromProfile->setFont(font);

        verticalLayout_7->addWidget(listWidget_answersFromProfile);

        label_2 = new QLabel(Profile);
        label_2->setObjectName("label_2");
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);
        label_2->setFont(font);

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
        listWidget_commentsFromProfile->setFont(font);

        verticalLayout_7->addWidget(listWidget_commentsFromProfile);


        horizontalLayout_8->addLayout(verticalLayout_7);


        gridLayout->addLayout(horizontalLayout_8, 0, 0, 1, 1);


        retranslateUi(Profile);

        QMetaObject::connectSlotsByName(Profile);
    } // setupUi

    void retranslateUi(QDialog *Profile)
    {
        Profile->setWindowTitle(QCoreApplication::translate("Profile", "Profile", nullptr));
        pushButton_profilePic->setText(QString());
        pushButton_viewIcon->setText(QCoreApplication::translate("Profile", "Change Icon", nullptr));
        label_4->setText(QCoreApplication::translate("Profile", "LinkedIn", nullptr));
        pushButton_AddResume->setText(QCoreApplication::translate("Profile", "Add Resume", nullptr));
        pushButton_ViewResume->setText(QCoreApplication::translate("Profile", "View Resume", nullptr));
        pushButton_AddDegree->setText(QCoreApplication::translate("Profile", "Add Degree", nullptr));
        pushButton_ViewDegree->setText(QCoreApplication::translate("Profile", "View Degree", nullptr));
        pushButton_AddCertificates->setText(QCoreApplication::translate("Profile", "Add Certificates", nullptr));
        pushButton_ViewCertificates->setText(QCoreApplication::translate("Profile", "View Certificates", nullptr));
        pushButton_AddDriverLicense->setText(QCoreApplication::translate("Profile", "Add Driver's License", nullptr));
        label_5->setText(QCoreApplication::translate("Profile", "You are not verified", nullptr));
        label->setText(QCoreApplication::translate("Profile", "Questions", nullptr));

        const bool __sortingEnabled = listWidget_postsFromProfile->isSortingEnabled();
        listWidget_postsFromProfile->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget_postsFromProfile->item(0);
        ___qlistwidgetitem->setText(QCoreApplication::translate("Profile", "Question 1", nullptr));
        QListWidgetItem *___qlistwidgetitem1 = listWidget_postsFromProfile->item(1);
        ___qlistwidgetitem1->setText(QCoreApplication::translate("Profile", "Question 2", nullptr));
        QListWidgetItem *___qlistwidgetitem2 = listWidget_postsFromProfile->item(2);
        ___qlistwidgetitem2->setText(QCoreApplication::translate("Profile", "Question 3", nullptr));
        listWidget_postsFromProfile->setSortingEnabled(__sortingEnabled);

        label_3->setText(QCoreApplication::translate("Profile", "Answers", nullptr));

        const bool __sortingEnabled1 = listWidget_answersFromProfile->isSortingEnabled();
        listWidget_answersFromProfile->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem3 = listWidget_answersFromProfile->item(0);
        ___qlistwidgetitem3->setText(QCoreApplication::translate("Profile", "Answer 1", nullptr));
        QListWidgetItem *___qlistwidgetitem4 = listWidget_answersFromProfile->item(1);
        ___qlistwidgetitem4->setText(QCoreApplication::translate("Profile", "Answer 2", nullptr));
        QListWidgetItem *___qlistwidgetitem5 = listWidget_answersFromProfile->item(2);
        ___qlistwidgetitem5->setText(QCoreApplication::translate("Profile", "Answer 3", nullptr));
        listWidget_answersFromProfile->setSortingEnabled(__sortingEnabled1);

        label_2->setText(QCoreApplication::translate("Profile", "Comments", nullptr));

        const bool __sortingEnabled2 = listWidget_commentsFromProfile->isSortingEnabled();
        listWidget_commentsFromProfile->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem6 = listWidget_commentsFromProfile->item(0);
        ___qlistwidgetitem6->setText(QCoreApplication::translate("Profile", "Comment 1", nullptr));
        QListWidgetItem *___qlistwidgetitem7 = listWidget_commentsFromProfile->item(1);
        ___qlistwidgetitem7->setText(QCoreApplication::translate("Profile", "Comment 2", nullptr));
        QListWidgetItem *___qlistwidgetitem8 = listWidget_commentsFromProfile->item(2);
        ___qlistwidgetitem8->setText(QCoreApplication::translate("Profile", "Comment 3", nullptr));
        QListWidgetItem *___qlistwidgetitem9 = listWidget_commentsFromProfile->item(3);
        ___qlistwidgetitem9->setText(QCoreApplication::translate("Profile", "Comment 4", nullptr));
        QListWidgetItem *___qlistwidgetitem10 = listWidget_commentsFromProfile->item(4);
        ___qlistwidgetitem10->setText(QCoreApplication::translate("Profile", "Comment 5", nullptr));
        QListWidgetItem *___qlistwidgetitem11 = listWidget_commentsFromProfile->item(5);
        ___qlistwidgetitem11->setText(QCoreApplication::translate("Profile", "Comment 6", nullptr));
        QListWidgetItem *___qlistwidgetitem12 = listWidget_commentsFromProfile->item(6);
        ___qlistwidgetitem12->setText(QCoreApplication::translate("Profile", "Comment 7", nullptr));
        listWidget_commentsFromProfile->setSortingEnabled(__sortingEnabled2);

    } // retranslateUi

};

namespace Ui {
    class Profile: public Ui_Profile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROFILE_H
