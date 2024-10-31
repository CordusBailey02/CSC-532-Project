#include "makecommentorpost.h"
#include "ui_makecommentorpost.h"

makeCommentOrPost::makeCommentOrPost(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::makeCommentOrPost)
{
    ui->setupUi(this);

    /*

    */
}

makeCommentOrPost::~makeCommentOrPost()
{
    delete ui;
}

void makeCommentOrPost::on_pushButton_clicked()
{
    QString postText = ui->textEdit->toPlainText();
    postText = postText.toLower();
    // Send postText to client to display in question, answer, or comment
}
