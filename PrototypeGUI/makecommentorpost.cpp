#include "makecommentorpost.h"
#include "ui_makecommentorpost.h"

makeCommentOrPost::makeCommentOrPost(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::makeCommentOrPost)
{
    ui->setupUi(this);
}

makeCommentOrPost::~makeCommentOrPost()
{
    delete ui;
}
