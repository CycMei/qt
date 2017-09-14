#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QTextEdit>
#include <QCloseEvent>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QKeyEvent>

#include "finddialog.h"
#define DELETE_PTR(ptr) if (ptr) { delete ptr; ptr = nullptr; }

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    bool maybeSave();
    void newFile();
    bool save();
    bool saveAs();
    bool saveFile(const QString &filePath);
    void openFile();
    bool loadFile(const QString &filePath);
    bool closeFile();
    void exitMain();
    void closeEvent(QCloseEvent *event);
private slots:
    void cheXiao();
    void jianQie();
    void fuZhi();
    void zhanTie();
    void chaZhao();
public slots:
    void showFindText();
protected:
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void timerEvent(QTimerEvent *event);
private:
    FindDialog *findDlg;
private:
    QLabel *statusLabel;
    QLabel *permanent;
private:
    QTextEdit *textEdit;
    bool isUntitled;
    QString curFile;
private:
    QPushButton *mouseEvtBtn;
    int id1;
    int id2;
    int id3;
    QLabel *labId1;
    QLabel *labId2;
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
