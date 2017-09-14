#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[]){
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engin;
    engin.load(QUrl(QStringLiteral("qrc:/abc/main.qml")));
    return app.exec();
}
