#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QMessageBox>
#include <QPushButton>
#include <QFileDialog>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QAction *openAction = new QAction(tr("&Open"), this);
    QIcon icon(":/myimages/images/newFile.jpg");
    openAction->setIcon(icon);
    openAction->setShortcut(QKeySequence(tr("Ctrl+O")));
    ui->menu_F->addAction(openAction);

    QString strEdit = QString::fromLocal8Bit("编辑(&E)");
    QMenu *menu_E = ui->menuBar->addMenu(strEdit);
    QAction *findAction = new QAction(tr("&Find"), this);
    QIcon icon2(":/myimages/images/find.jpg");
    findAction->setIcon(icon2);
    findAction->setShortcut((QKeySequence(tr("Ctrl+F"))));
    menu_E->addAction(findAction);

    QPushButton *btn = new QPushButton(this);
    QLineEdit *le = new QLineEdit(this);
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(btn, 0, 0, 1, 1);
    layout->addWidget(le, 0, 1, 1, 2);
    layout->addWidget(ui->textEdit, 1, 0, 1, 3);
    ui->centralWidget->setLayout(layout);

    isUntitled = true;
    curFile = QString::fromLocal8Bit("未命名.txt");
    this->setWindowTitle(curFile);


}

void MainWindow::newFile() {
    if (maybeSave()){
        isUntitled = true;
        curFile = QString::fromLocal8Bit("未命名.txt");
        setWindowTitle(curFile);
        ui->textEdit->clear();
        ui->textEdit->setVisible(true);
    }
}

bool MainWindow::maybeSave() {
    if (ui->textEdit->document()->isModified()){
        QMessageBox box;
        box.setWindowTitle(QString::fromLocal8Bit("警告"));
        box.setIcon(QMessageBox::Warning);
        box.setText(curFile + QString::fromLocal8Bit("尚未保存，是否保存？"));
        QPushButton *yesBtn = box.addButton(QString::fromLocal8Bit("是(&Y)"),
                                            QMessageBox::YesRole);
        box.addButton(QString::fromLocal8Bit("否(&N)"), QMessageBox::NoRole);
        QPushButton *cancelBtn = box.addButton(QString::fromLocal8Bit("取消") ,
                                               QMessageBox::RejectRole);
        box.exec();
        if (box.clickedButton() == yesBtn){
            return save();
        }
        else if (box.clickedButton() == cancelBtn){
            return false;
        }

    }
    return true;
}


bool MainWindow::save() {
    if (isUntitled) {
        return saveAs();
    }
    else{
        return saveFile(curFile);
    }
}

bool MainWindow::saveAs() {
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    QString::fromLocal8Bit("另存为"),
                                                    curFile);

    if (fileName.isEmpty())
        return false;
    return saveFile(fileName);
}

bool MainWindow::saveFile(const QString &filename) {
    QFile file(filename);
    if (!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,
                             QString::fromLocal8Bit("多文档编辑器"),
                             QString::fromLocal8Bit("无法写入文件 %1: /n %2")
                             .arg(filename).arg(file.errorString()));
        return false;
    }
    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out<<ui->textEdit->toPlainText();
    QApplication::restoreOverrideCursor();
    isUntitled = false;
    curFile = QFileInfo(filename).canonicalFilePath();
    this->setWindowTitle(curFile);
    return true;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_N_triggered()
{
    newFile();
}

void MainWindow::on_actionsave_S_triggered()
{
    save();
}

void MainWindow::on_actionsaveAs_A_triggered()
{
    saveAs();
}
