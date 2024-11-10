#ifndef REQUESTVERIFICATION_H
#define REQUESTVERIFICATION_H

#include <QDialog>

namespace Ui {
class requestVerification;
}

class requestVerification : public QDialog
{
    Q_OBJECT

public:
    explicit requestVerification(QWidget *parent = nullptr);
    ~requestVerification();

private slots:
    void on_pushButton_addResume_clicked();

    void on_pushButton_addDegree_clicked();

    void on_pushButton_addCertificate_clicked();

    void on_pushButton_addDriverLicense_clicked();

    void on_pushButton_submitVerificationRequest_clicked();

    void on_pushButton_cancelVerificationRequest_clicked();

private:
    Ui::requestVerification *ui;
};

#endif // REQUESTVERIFICATION_H
