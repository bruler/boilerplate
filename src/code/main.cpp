#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <boost/python.hpp>

#include "tensorflow-api.h"
#include "caffe-modules.h"
#include "theano-api.h"
#include "vision.h"


using namespace tf;  // tensorflow-api
using namespace cm;  // caffe-modules
using namespace th;  // theano-api
using namespace vision;  // openCV code

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
