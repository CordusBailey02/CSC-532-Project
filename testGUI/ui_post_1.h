/********************************************************************************
** Form generated from reading UI file 'post_1.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POST_1_H
#define UI_POST_1_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Post_1
{
public:
    QFormLayout *formLayout;
    QListWidget *listWidget;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton;
    QVBoxLayout *verticalLayout_10;
    QHBoxLayout *horizontalLayout_12;
    QVBoxLayout *verticalLayout;
    QLabel *label_userPic;
    QLabel *label_username;
    QPushButton *pushButton_2;
    QVBoxLayout *verticalLayout_2;
    QPlainTextEdit *plainTextEdit_questionText;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_upPost;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QLabel *label_upPostCount;
    QPushButton *pushButton_downPost;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_2;
    QLabel *label_downPostCount;
    QLabel *label_3;

    void setupUi(QDialog *Post_1)
    {
        if (Post_1->objectName().isEmpty())
            Post_1->setObjectName("Post_1");
        Post_1->resize(622, 480);
        formLayout = new QFormLayout(Post_1);
        formLayout->setObjectName("formLayout");
        listWidget = new QListWidget(Post_1);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        listWidget->setObjectName("listWidget");
        QPalette palette;
        QBrush brush(QColor(146, 194, 242, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Highlight, brush);
        QBrush brush1(QColor(0, 0, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::HighlightedText, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Highlight, brush);
        palette.setBrush(QPalette::Inactive, QPalette::HighlightedText, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::HighlightedText, brush1);
        listWidget->setPalette(palette);
        QFont font;
        font.setPointSize(15);
        listWidget->setFont(font);

        formLayout->setWidget(3, QFormLayout::SpanningRole, listWidget);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        pushButton = new QPushButton(Post_1);
        pushButton->setObjectName("pushButton");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::Button, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush);
        pushButton->setPalette(palette1);
        pushButton->setFont(font);

        horizontalLayout_2->addWidget(pushButton);


        formLayout->setLayout(4, QFormLayout::LabelRole, horizontalLayout_2);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setObjectName("verticalLayout_10");
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName("horizontalLayout_12");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label_userPic = new QLabel(Post_1);
        label_userPic->setObjectName("label_userPic");
        label_userPic->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(label_userPic);

        label_username = new QLabel(Post_1);
        label_username->setObjectName("label_username");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_username->sizePolicy().hasHeightForWidth());
        label_username->setSizePolicy(sizePolicy1);
        label_username->setFont(font);
        label_username->setAlignment(Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignTop);

        verticalLayout->addWidget(label_username);

        pushButton_2 = new QPushButton(Post_1);
        pushButton_2->setObjectName("pushButton_2");
        sizePolicy1.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy1);
        pushButton_2->setFont(font);

        verticalLayout->addWidget(pushButton_2);


        horizontalLayout_12->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        plainTextEdit_questionText = new QPlainTextEdit(Post_1);
        plainTextEdit_questionText->setObjectName("plainTextEdit_questionText");
        plainTextEdit_questionText->setFont(font);

        verticalLayout_2->addWidget(plainTextEdit_questionText);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        pushButton_upPost = new QPushButton(Post_1);
        pushButton_upPost->setObjectName("pushButton_upPost");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButton_upPost->sizePolicy().hasHeightForWidth());
        pushButton_upPost->setSizePolicy(sizePolicy2);
        QPalette palette2;
        QBrush brush2(QColor(252, 252, 252, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::Dark, brush2);
        palette2.setBrush(QPalette::Active, QPalette::AlternateBase, brush2);
        palette2.setBrush(QPalette::Inactive, QPalette::Dark, brush2);
        palette2.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush2);
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette2.setBrush(QPalette::Disabled, QPalette::Dark, brush2);
        palette2.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        palette2.setBrush(QPalette::Disabled, QPalette::ButtonText, brush2);
        palette2.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush2);
        pushButton_upPost->setPalette(palette2);

        horizontalLayout_3->addWidget(pushButton_upPost);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        label = new QLabel(Post_1);
        label->setObjectName("label");
        QFont font1;
        font1.setPointSize(12);
        label->setFont(font1);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_3->addWidget(label);

        label_upPostCount = new QLabel(Post_1);
        label_upPostCount->setObjectName("label_upPostCount");
        label_upPostCount->setFont(font);
        label_upPostCount->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_3->addWidget(label_upPostCount);


        horizontalLayout_3->addLayout(verticalLayout_3);

        pushButton_downPost = new QPushButton(Post_1);
        pushButton_downPost->setObjectName("pushButton_downPost");
        sizePolicy2.setHeightForWidth(pushButton_downPost->sizePolicy().hasHeightForWidth());
        pushButton_downPost->setSizePolicy(sizePolicy2);
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::Dark, brush2);
        palette3.setBrush(QPalette::Active, QPalette::AlternateBase, brush2);
        palette3.setBrush(QPalette::Inactive, QPalette::Dark, brush2);
        palette3.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush2);
        palette3.setBrush(QPalette::Disabled, QPalette::WindowText, brush2);
        palette3.setBrush(QPalette::Disabled, QPalette::Dark, brush2);
        palette3.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        palette3.setBrush(QPalette::Disabled, QPalette::ButtonText, brush2);
        palette3.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush2);
        pushButton_downPost->setPalette(palette3);

        horizontalLayout_3->addWidget(pushButton_downPost);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName("verticalLayout_4");
        label_2 = new QLabel(Post_1);
        label_2->setObjectName("label_2");
        label_2->setFont(font1);
        label_2->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_4->addWidget(label_2);

        label_downPostCount = new QLabel(Post_1);
        label_downPostCount->setObjectName("label_downPostCount");
        label_downPostCount->setFont(font);
        label_downPostCount->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_4->addWidget(label_downPostCount);


        horizontalLayout_3->addLayout(verticalLayout_4);


        verticalLayout_2->addLayout(horizontalLayout_3);


        horizontalLayout_12->addLayout(verticalLayout_2);


        verticalLayout_10->addLayout(horizontalLayout_12);

        label_3 = new QLabel(Post_1);
        label_3->setObjectName("label_3");
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);
        label_3->setFont(font);
        label_3->setAlignment(Qt::AlignmentFlag::AlignBottom|Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft);

        verticalLayout_10->addWidget(label_3);


        formLayout->setLayout(2, QFormLayout::SpanningRole, verticalLayout_10);


        retranslateUi(Post_1);

        QMetaObject::connectSlotsByName(Post_1);
    } // setupUi

    void retranslateUi(QDialog *Post_1)
    {
        Post_1->setWindowTitle(QCoreApplication::translate("Post_1", "Post", nullptr));

        const bool __sortingEnabled = listWidget->isSortingEnabled();
        listWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget->item(0);
        ___qlistwidgetitem->setText(QCoreApplication::translate("Post_1", "Answer 1", nullptr));
        QListWidgetItem *___qlistwidgetitem1 = listWidget->item(1);
        ___qlistwidgetitem1->setText(QCoreApplication::translate("Post_1", "Answer 2", nullptr));
        QListWidgetItem *___qlistwidgetitem2 = listWidget->item(2);
        ___qlistwidgetitem2->setText(QCoreApplication::translate("Post_1", "Answer 3", nullptr));
        QListWidgetItem *___qlistwidgetitem3 = listWidget->item(3);
        ___qlistwidgetitem3->setText(QCoreApplication::translate("Post_1", "Answer 4", nullptr));
        QListWidgetItem *___qlistwidgetitem4 = listWidget->item(4);
        ___qlistwidgetitem4->setText(QCoreApplication::translate("Post_1", "Answer 5", nullptr));
        listWidget->setSortingEnabled(__sortingEnabled);

        pushButton->setText(QCoreApplication::translate("Post_1", "Answer Question", nullptr));
        label_userPic->setText(QString());
        label_username->setText(QCoreApplication::translate("Post_1", "Username", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Post_1", "View File", nullptr));
        plainTextEdit_questionText->setPlainText(QCoreApplication::translate("Post_1", "Read only", nullptr));
        pushButton_upPost->setText(QString());
        label->setText(QCoreApplication::translate("Post_1", "Upvotes", nullptr));
        label_upPostCount->setText(QCoreApplication::translate("Post_1", "0", nullptr));
        pushButton_downPost->setText(QString());
        label_2->setText(QCoreApplication::translate("Post_1", "Downvotes", nullptr));
        label_downPostCount->setText(QCoreApplication::translate("Post_1", "0", nullptr));
        label_3->setText(QCoreApplication::translate("Post_1", "Answers", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Post_1: public Ui_Post_1 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POST_1_H
