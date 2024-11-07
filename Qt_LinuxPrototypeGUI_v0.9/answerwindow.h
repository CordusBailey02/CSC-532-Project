#ifndef ANSWERWINDOW_H
#define ANSWERWINDOW_H

#include <QDialog>
#include <QtWidgets>

namespace Ui {
class answerWindow;
}

class answerWindow : public QDialog
{
    Q_OBJECT

public:
    explicit answerWindow(QWidget *parent = nullptr);
    ~answerWindow();

private slots:
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_pushButton_commentBtn_clicked();

    void on_pushButton_upAnswer_clicked();

    void on_pushButton_downAnswer_clicked();

private:
    Ui::answerWindow *ui;
};

#endif // ANSWERWINDOW_H
