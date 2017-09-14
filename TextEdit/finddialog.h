#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

namespace Ui {
class FindDialog;
}

class FindDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FindDialog(QWidget *parent = 0);
    ~FindDialog();
    const QString getLineEditText() const;
private:
    QLineEdit *findLineEdit;
private:
    Ui::FindDialog *ui;
};

#endif // FINDDIALOG_H
