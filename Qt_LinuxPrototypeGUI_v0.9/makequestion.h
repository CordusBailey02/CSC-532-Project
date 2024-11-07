#ifndef MAKEQUESTION_H
#define MAKEQUESTION_H

#include <QDialog>

namespace Ui {
class makeQuestion;
}

class makeQuestion : public QDialog
{
    Q_OBJECT

public:
    explicit makeQuestion(QWidget *parent = nullptr);
    ~makeQuestion();

private slots:
    void on_pushButton_cancel_clicked();

    void on_pushButton_postQuestion_clicked();

    void on_pushButton_uploadQuestionImage_clicked();

private:
    Ui::makeQuestion *ui;
};

#endif // MAKEQUESTION_H
