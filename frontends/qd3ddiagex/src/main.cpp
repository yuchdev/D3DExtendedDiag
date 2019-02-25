#include <QApplication>
#include <QPushButton>

#include <qd3ddiagex/qd3ddiagex_application.h>


int main(int argc, char **argv)
{
    setlocale(LC_ALL, "en-US");

    QApplication::setApplicationName("qD3DExtended Diag");

    // TODO: replace the dumb code with actual application code
    QApplication app (argc, argv);
    QPushButton hello( "Hello D3D Extended Diag", 0 );
    hello.resize( 100, 30 );
    app.setMainWidget( &hello );
    hello.show();
    return app.exec();
}
