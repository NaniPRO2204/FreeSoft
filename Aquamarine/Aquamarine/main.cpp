#include "ProyectoAquamarine.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    // Punto de entrada de la app:
    // 1. Qt inicializa el bucle de eventos.
    // 2. Se crea la ventana principal.
    // 3. show() la hace visible y exec() mantiene viva la interfaz.
    QApplication app(argc, argv);
    ProyectoAquamarine window;
    window.show();
    return app.exec();
}
