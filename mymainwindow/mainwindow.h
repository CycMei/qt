#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public:
    void newFile();
    bool maybeSave();
    bool save();
    bool saveAs();
    bool saveFile(const QString &filename);

private slots:
    void on_action_N_triggered();

    void on_actionsave_S_triggered();

    void on_actionsaveAs_A_triggered();

private:
    bool isUntitled;
    QString curFile;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
