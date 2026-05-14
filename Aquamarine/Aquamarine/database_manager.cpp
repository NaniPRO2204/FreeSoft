#include "database_manager.h"

#include <QVariant>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>

// El nombre de conexion sirve para que Qt pueda identificarla internamente.
DatabaseManager::DatabaseManager()
    : connectionName("CRMServiceManagerSqlite")
{
}

DatabaseManager::~DatabaseManager()
{
    // Cerramos y removemos la conexion para no dejar recursos abiertos.
    if (database.isValid()) {
        database.close();
    }

    if (!connectionName.isEmpty() && QSqlDatabase::contains(connectionName)) {
        database = QSqlDatabase();
        QSqlDatabase::removeDatabase(connectionName);
    }
}

bool DatabaseManager::initialize(const QString& path)
{
    // Guardamos la ruta elegida para poder mostrarla luego en la UI.
    databasePath = path;

    if (QSqlDatabase::contains(connectionName)) {
        database = QSqlDatabase::database(connectionName);
    } else {
        database = QSqlDatabase::addDatabase("QSQLITE", connectionName);
    }

    database.setDatabaseName(databasePath);

    // Si el archivo no existe, SQLite lo crea al abrirlo.
    if (!database.open()) {
        lastErrorText = database.lastError().text();
        return false;
    }

    return createTables();
}

bool DatabaseManager::isAvailable() const
{
    return database.isValid() && database.isOpen();
}

QString DatabaseManager::lastError() const
{
    return lastErrorText;
}

QString DatabaseManager::path() const
{
    return databasePath;
}

bool DatabaseManager::createTables()
{
    // CREATE TABLE IF NOT EXISTS crea la tabla solo si todavia no esta.
    QSqlQuery query(database);

    const bool productsCreated = query.exec(
        "CREATE TABLE IF NOT EXISTS productos ("
        "sku TEXT PRIMARY KEY,"
        "codigo_barras TEXT,"
        "nombre TEXT NOT NULL,"
        "descripcion TEXT,"
        "modelo TEXT,"
        "marca TEXT,"
        "modelo_comp TEXT,"
        "observaciones TEXT,"
        "stock INTEGER NOT NULL,"
        "precio REAL NOT NULL)");

    if (!productsCreated) {
        lastErrorText = query.lastError().text();
        return false;
    }

    const bool salesCreated = query.exec(
        "CREATE TABLE IF NOT EXISTS ventas ("
        "id INTEGER PRIMARY KEY,"
        "fecha_hora TEXT NOT NULL,"
        "cliente TEXT NOT NULL,"
        "sku TEXT NOT NULL,"
        "cantidad INTEGER NOT NULL,"
        "precio_unitario REAL NOT NULL,"
        "precio_ml REAL NOT NULL,"
        "forma_pago TEXT NOT NULL,"
        "envio TEXT NOT NULL,"
        "observaciones TEXT,"
        "pagada_proveedor INTEGER NOT NULL DEFAULT 0,"
        "fecha_pago_proveedor TEXT,"
        "monto_pago_proveedor REAL NOT NULL DEFAULT 0)");

    if (!salesCreated) {
        lastErrorText = query.lastError().text();
        return false;
    }

    const bool repairsCreated = query.exec(
        "CREATE TABLE IF NOT EXISTS reparaciones ("
        "id INTEGER PRIMARY KEY,"
        "fecha_ingreso TEXT NOT NULL,"
        "cliente TEXT NOT NULL,"
        "tipo_reparacion TEXT NOT NULL,"
        "modelo_dispositivo TEXT NOT NULL,"
        "detalle_reparacion TEXT NOT NULL,"
        "mano_obra REAL NOT NULL,"
        "tiempo_trabajo TEXT NOT NULL,"
        "observaciones TEXT NOT NULL,"
        "estado TEXT NOT NULL)");

    if (!repairsCreated) {
        lastErrorText = query.lastError().text();
        return false;
    }

    if (!ensureProductSchema()) {
        return false;
    }

    lastErrorText.clear();
    return true;
}

bool DatabaseManager::ensureProductSchema()
{
    QSqlQuery query(database);
    if (!query.exec("PRAGMA table_info(productos)")) {
        lastErrorText = query.lastError().text();
        return false;
    }

    bool hasBarcodeColumn = false;
    while (query.next()) {
        if (query.value(1).toString() == "codigo_barras") {
            hasBarcodeColumn = true;
            break;
        }
    }

    if (!hasBarcodeColumn) {
        if (!query.exec("ALTER TABLE productos ADD COLUMN codigo_barras TEXT")) {
            lastErrorText = query.lastError().text();
            return false;
        }
    }

    lastErrorText.clear();
    return true;
}

bool DatabaseManager::saveAll(const Inventario& inventario)
{
    if (!isAvailable()) {
        lastErrorText = "La base SQLite no esta abierta.";
        return false;
    }

    // Transaction: si algo falla, hacemos rollback y no dejamos media base escrita.
    if (!database.transaction()) {
        lastErrorText = database.lastError().text();
        return false;
    }

    QSqlQuery query(database);
    if (!query.exec("DELETE FROM ventas")) {
        lastErrorText = query.lastError().text();
        database.rollback();
        return false;
    }

    if (!query.exec("DELETE FROM productos")) {
        lastErrorText = query.lastError().text();
        database.rollback();
        return false;
    }

    if (!query.exec("DELETE FROM reparaciones")) {
        lastErrorText = query.lastError().text();
        database.rollback();
        return false;
    }

    // prepare() + addBindValue() evita armar strings SQL manuales.
    query.prepare(
        "INSERT INTO productos (sku, codigo_barras, nombre, descripcion, modelo, marca, modelo_comp, observaciones, stock, precio) "
        "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");

    for (const auto& pair : inventario.getProductos()) {
        const Producto& producto = pair.second;
        query.addBindValue(producto.getSku());
        query.addBindValue(producto.getCodigoBarras());
        query.addBindValue(producto.getNombre());
        query.addBindValue(producto.getDescripcion());
        query.addBindValue(producto.getModelo());
        query.addBindValue(producto.getMarca());
        query.addBindValue(producto.getModeloComp());
        query.addBindValue(producto.getObserv());
        query.addBindValue(producto.getStock());
        query.addBindValue(producto.getPrecio());

        if (!query.exec()) {
            lastErrorText = query.lastError().text();
            database.rollback();
            return false;
        }
    }

    query.prepare(
        "INSERT INTO ventas (id, fecha_hora, cliente, sku, cantidad, precio_unitario, precio_ml, forma_pago, envio, observaciones, pagada_proveedor, fecha_pago_proveedor, monto_pago_proveedor) "
        "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");

    for (const Venta& venta : inventario.getVentas()) {
        query.addBindValue(venta.getId());
        query.addBindValue(venta.getFechaHora().toString(Qt::ISODate));
        query.addBindValue(venta.getCliente());
        query.addBindValue(venta.getSku());
        query.addBindValue(venta.getCantidad());
        query.addBindValue(venta.getPrecioUnitario());
        query.addBindValue(venta.getPrecioML());
        query.addBindValue(venta.getFormaPago());
        query.addBindValue(venta.getEnvio());
        query.addBindValue(venta.getObservaciones());
        query.addBindValue(venta.getPagadaProveedor() ? 1 : 0);
        query.addBindValue(venta.getFechaPagoProveedor().isValid() ? venta.getFechaPagoProveedor().toString(Qt::ISODate) : QString());
        query.addBindValue(venta.getMontoPagoProveedor());

        if (!query.exec()) {
            lastErrorText = query.lastError().text();
            database.rollback();
            return false;
        }
    }

    query.prepare(
        "INSERT INTO reparaciones (id, fecha_ingreso, cliente, tipo_reparacion, modelo_dispositivo, detalle_reparacion, mano_obra, tiempo_trabajo, observaciones, estado) "
        "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");

    for (const Reparacion& reparacion : inventario.getReparaciones()) {
        query.addBindValue(reparacion.getId());
        query.addBindValue(reparacion.getFechaIngreso().toString(Qt::ISODate));
        query.addBindValue(reparacion.getCliente());
        query.addBindValue(reparacion.getTipoReparacion());
        query.addBindValue(reparacion.getModeloDispositivo());
        query.addBindValue(reparacion.getDetalleReparacion());
        query.addBindValue(reparacion.getManoObra());
        query.addBindValue(reparacion.getTiempoTrabajo());
        query.addBindValue(reparacion.getObservaciones());
        query.addBindValue(reparacion.getEstado());

        if (!query.exec()) {
            lastErrorText = query.lastError().text();
            database.rollback();
            return false;
        }
    }

    if (!database.commit()) {
        lastErrorText = database.lastError().text();
        database.rollback();
        return false;
    }

    lastErrorText.clear();
    return true;
}

bool DatabaseManager::loadAll(std::map<QString, Producto>& productos,
                              std::vector<Venta>& ventas,
                              std::vector<Reparacion>& reparaciones)
{
    // Limpiamos los contenedores de salida antes de cargar.
    productos.clear();
    ventas.clear();
    reparaciones.clear();

    if (!isAvailable()) {
        lastErrorText = "La base SQLite no esta abierta.";
        return false;
    }

    QSqlQuery query(database);
    if (!query.exec(
            "SELECT sku, codigo_barras, nombre, descripcion, modelo, marca, modelo_comp, observaciones, stock, precio "
            "FROM productos ORDER BY nombre ASC")) {
        lastErrorText = query.lastError().text();
        return false;
    }

    while (query.next()) {
        // query.value(indice) devuelve cada columna de la fila actual.
        Producto producto(
            query.value(2).toString(),
            query.value(3).toString(),
            query.value(0).toString(),
            query.value(1).toString(),
            query.value(4).toString(),
            query.value(5).toString(),
            query.value(6).toString(),
            query.value(7).toString(),
            query.value(8).toInt(),
            query.value(9).toDouble());

        productos[producto.getSku()] = producto;
    }

    if (!query.exec(
            "SELECT id, fecha_hora, cliente, sku, cantidad, precio_unitario, precio_ml, forma_pago, envio, observaciones, pagada_proveedor, fecha_pago_proveedor, monto_pago_proveedor "
            "FROM ventas ORDER BY id ASC")) {
        lastErrorText = query.lastError().text();
        return false;
    }

    while (query.next()) {
        ventas.emplace_back(
            query.value(0).toInt(),
            QDateTime::fromString(query.value(1).toString(), Qt::ISODate),
            query.value(2).toString(),
            query.value(3).toString(),
            query.value(4).toInt(),
            query.value(5).toDouble(),
            query.value(6).toDouble(),
            query.value(7).toString(),
            query.value(8).toString(),
            query.value(9).toString(),
            query.value(10).toInt() != 0,
            QDateTime::fromString(query.value(11).toString(), Qt::ISODate),
            query.value(12).toDouble());
    }

    if (!query.exec(
            "SELECT id, fecha_ingreso, cliente, tipo_reparacion, modelo_dispositivo, detalle_reparacion, mano_obra, tiempo_trabajo, observaciones, estado "
            "FROM reparaciones ORDER BY id ASC")) {
        lastErrorText = query.lastError().text();
        return false;
    }

    while (query.next()) {
        reparaciones.emplace_back(
            query.value(0).toInt(),
            QDateTime::fromString(query.value(1).toString(), Qt::ISODate),
            query.value(2).toString(),
            query.value(3).toString(),
            query.value(4).toString(),
            query.value(5).toString(),
            query.value(6).toDouble(),
            query.value(7).toString(),
            query.value(8).toString(),
            query.value(9).toString());
    }

    lastErrorText.clear();
    return true;
}

bool DatabaseManager::executeSelect(const QString& sql, QStringList& headers, std::vector<QStringList>& rows)
{
    headers.clear();
    rows.clear();

    if (!isAvailable()) {
        lastErrorText = "La base SQLite no esta abierta.";
        return false;
    }

    QSqlQuery query(database);
    if (!query.exec(sql)) {
        lastErrorText = query.lastError().text();
        return false;
    }

    // record() nos permite leer nombres de columnas del resultado.
    const QSqlRecord record = query.record();
    for (int column = 0; column < record.count(); ++column) {
        headers << record.fieldName(column);
    }

    while (query.next()) {
        QStringList row;
        for (int column = 0; column < record.count(); ++column) {
            row << query.value(column).toString();
        }
        rows.push_back(row);
    }

    lastErrorText.clear();
    return true;
}

bool DatabaseManager::executeStatement(const QString& sql, int& affectedRows)
{
    affectedRows = 0;

    if (!isAvailable()) {
        lastErrorText = "La base SQLite no esta abierta.";
        return false;
    }

    QSqlQuery query(database);
    if (!query.exec(sql)) {
        lastErrorText = query.lastError().text();
        return false;
    }

    // Para UPDATE/DELETE/INSERT, numRowsAffected ayuda a informar que paso.
    affectedRows = query.numRowsAffected();
    lastErrorText.clear();
    return true;
}

bool DatabaseManager::resetDatabase()
{
    // Reinicio completo: deja la estructura pero borra el contenido.
    if (!isAvailable()) {
        lastErrorText = "La base SQLite no esta abierta.";
        return false;
    }

    if (!database.transaction()) {
        lastErrorText = database.lastError().text();
        return false;
    }

    QSqlQuery query(database);
    if (!query.exec("DELETE FROM ventas")) {
        lastErrorText = query.lastError().text();
        database.rollback();
        return false;
    }

    if (!query.exec("DELETE FROM productos")) {
        lastErrorText = query.lastError().text();
        database.rollback();
        return false;
    }

    if (!query.exec("DELETE FROM reparaciones")) {
        lastErrorText = query.lastError().text();
        database.rollback();
        return false;
    }

    if (!database.commit()) {
        lastErrorText = database.lastError().text();
        database.rollback();
        return false;
    }

    lastErrorText.clear();
    return true;
}
