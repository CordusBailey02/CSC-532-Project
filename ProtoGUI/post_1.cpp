#include "post_1.h"
#include "ui_post_1.h"

Post_1::Post_1(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Post_1)
{
    ui->setupUi(this);
}

Post_1::~Post_1()
{
    delete ui;
}
