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
    QPushButton *pushButton_changeIcon;
    QPushButton *pushButton_requestVerification;
    QLabel *label_verifiedOrNot;
    QLabel *label_savedPath;
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
        Profile->resize(543, 448);
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

        pushButton_changeIcon = new QPushButton(Profile);
        pushButton_changeIcon->setObjectName("pushButton_changeIcon");
        QFont font;
        font.setPointSize(15);
        pushButton_changeIcon->setFont(font);

        verticalLayout_4->addWidget(pushButton_changeIcon);

        pushButton_requestVerification = new QPushButton(Profile);
        pushButton_requestVerification->setObjectName("pushButton_requestVerification");
        pushButton_requestVerification->setFont(font);

        verticalLayout_4->addWidget(pushButton_requestVerification);

        label_verifiedOrNot = new QLabel(Profile);
        label_verifiedOrNot->setObjectName("label_verifiedOrNot");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_verifiedOrNot->sizePolicy().hasHeightForWidth());
        label_verifiedOrNot->setSizePolicy(sizePolicy1);
        label_verifiedOrNot->setFont(font);
        label_verifiedOrNot->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_4->addWidget(label_verifiedOrNot);

        label_savedPath = new QLabel(Profile);
        label_savedPath->setObjectName("label_savedPath");
        sizePolicy.setHeightForWidth(label_savedPath->sizePolicy().hasHeightForWidth());
        label_savedPath->setSizePolicy(sizePolicy);
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(252, 252, 252, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        label_savedPath->setPalette(palette);
        QFont font1;
        font1.setPointSize(6);
        label_savedPath->setFont(font1);

        verticalLayout_4->addWidget(label_savedPath);


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
        QPalette palette1;
        QBrush brush2(QColor(146, 194, 242, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Highlight, brush2);
        QBrush brush3(QColor(0, 0, 0, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::HighlightedText, brush3);
        palette1.setBrush(QPalette::Inactive, QPalette::Highlight, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::HighlightedText, brush3);
        palette1.setBrush(QPalette::Disabled, QPalette::HighlightedText, brush3);
        listWidget_postsFromProfile->setPalette(palette1);
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
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::Highlight, brush2);
        palette2.setBrush(QPalette::Active, QPalette::HighlightedText, brush3);
        palette2.setBrush(QPalette::Inactive, QPalette::Highlight, brush2);
        palette2.setBrush(QPalette::Inactive, QPalette::HighlightedText, brush3);
        palette2.setBrush(QPalette::Disabled, QPalette::HighlightedText, brush3);
        listWidget_answersFromProfile->setPalette(palette2);
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
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::Highlight, brush2);
        palette3.setBrush(QPalette::Active, QPalette::HighlightedText, brush3);
        palette3.setBrush(QPalette::Inactive, QPalette::Highlight, brush2);
        palette3.setBrush(QPalette::Inactive, QPalette::HighlightedText, brush3);
        palette3.setBrush(QPalette::Disabled, QPalette::HighlightedText, brush3);
        listWidget_commentsFromProfile->setPalette(palette3);
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
        pushButton_changeIcon->setText(QCoreApplication::translate("Profile", "Change Icon", nullptr));
        pushButton_requestVerification->setText(QCoreApplication::translate("Profile", "Request Verification", nullptr));
        label_verifiedOrNot->setText(QCoreApplication::translate("Profile", "You are not verified", nullptr));
        label_savedPath->setText(QString());
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
