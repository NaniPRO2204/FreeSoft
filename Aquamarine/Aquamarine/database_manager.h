#pragma once

#include "inventario.h"

#include <QString>
#include <QtSql/QSqlDatabase>
#include <QStringList>
#include <map>
#include <vector>

// DatabaseManager encapsula todo el acceso a SQLite.
// La idea es que el resto de la aplicacion no tenga que escribir SQL por todos lados.
class DatabaseManager
{
private:
    // Conexion abierta a SQLite.
    QSqlDatabase database;

    // Nombre interno de la conexion dentro de Qt.
    QString connectionName;

    // Ruta fisica del archivo .sqlite.
    QString databasePath;

    // Ultimo error legible para mostrar en la UI.
    QString lastErrorText;

    // Crea las tablas si todavia no existen.
    bool createTables();
    bool ensureProductSchema();

public:
    DatabaseManager();
    ~DatabaseManager();

    bool initialize(const QString& path);
    bool isAvailable() const;
    QString lastError() const;
    QString path() const;

    // Guarda TODO el estado en la base.
    bool saveAll(const Inventario& inventario);

    // Carga TODO el estado desde la base.
    bool loadAll(std::map<QString, Producto>& productos,
                 std::vector<Venta>& ventas,
                 std::vector<Reparacion>& reparaciones);

    // Utilidades del panel admin oculto.
    bool executeSelect(const QString& sql, QStringList& headers, std::vector<QStringList>& rows);
    bool executeStatement(const QString& sql, int& affectedRows);
    bool resetDatabase();
};
