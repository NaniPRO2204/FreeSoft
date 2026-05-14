#include "inventario.h"

#include <algorithm>

// Arrancamos el contador de ventas en 1 para que los IDs sean amigables.
Inventario::Inventario()
    : siguienteIdVenta(1), siguienteIdReparacion(1)
{
}

bool Inventario::agregarProducto(const Producto& producto)
{
    // trim() quita espacios al principio y al final.
    const QString sku = producto.getSku().trimmed();
    const QString codigoBarras = producto.getCodigoBarras().trimmed();
    if (sku.isEmpty() || productos.find(sku) != productos.end()) {
        return false;
    }

    if (!codigoBarras.isEmpty() && existeCodigoBarrasEnOtroProducto(codigoBarras)) {
        return false;
    }

    productos[sku] = producto;
    return true;
}

bool Inventario::eliminarProducto(const QString& sku)
{
    // No dejamos borrar un producto si ya tiene ventas historicas asociadas.
    if (existeProductoConVentas(sku)) {
        return false;
    }

    return productos.erase(sku) > 0;
}

Producto* Inventario::buscarProductoPorSku(const QString& sku)
{
    // std::map::find devuelve un iterador. Si no encuentra, devuelve end().
    auto it = productos.find(sku.trimmed());
    if (it == productos.end()) {
        return nullptr;
    }

    return &(it->second);
}

Producto* Inventario::buscarProductoPorCodigoBarras(const QString& codigoBarras)
{
    const QString codigoNormalizado = codigoBarras.trimmed();
    if (codigoNormalizado.isEmpty()) {
        return nullptr;
    }

    for (auto& pair : productos) {
        if (pair.second.getCodigoBarras().trimmed() == codigoNormalizado) {
            return &(pair.second);
        }
    }

    return nullptr;
}

bool Inventario::actualizarProducto(const QString& skuActual, const Producto& nuevosDatos)
{
    // Buscamos el producto actual para reemplazarlo.
    auto it = productos.find(skuActual.trimmed());
    if (it == productos.end()) {
        return false;
    }

    const QString nuevoSku = nuevosDatos.getSku().trimmed();
    const QString nuevoCodigoBarras = nuevosDatos.getCodigoBarras().trimmed();
    if (nuevoSku.isEmpty()) {
        return false;
    }

    if (nuevoSku != skuActual && productos.find(nuevoSku) != productos.end()) {
        return false;
    }

    if (!nuevoCodigoBarras.isEmpty() && existeCodigoBarrasEnOtroProducto(nuevoCodigoBarras, skuActual)) {
        return false;
    }

    if (nuevoSku != skuActual && existeProductoConVentas(skuActual)) {
        return false;
    }

    // Si cambia el SKU, cambia la clave del mapa.
    if (nuevoSku != skuActual) {
        productos.erase(it);
    }

    productos[nuevoSku] = nuevosDatos;
    return true;
}

bool Inventario::existeProductoConVentas(const QString& sku) const
{
    // std::any_of devuelve true si algun elemento cumple la condicion.
    return std::any_of(ventas.begin(), ventas.end(), [&sku](const Venta& venta) {
        return venta.getSku() == sku;
    });
}

bool Inventario::existeCodigoBarrasEnOtroProducto(const QString& codigoBarras, const QString& skuIgnorado) const
{
    for (const auto& pair : productos) {
        if (pair.first == skuIgnorado) {
            continue;
        }

        if (pair.second.getCodigoBarras().trimmed() == codigoBarras.trimmed()) {
            return true;
        }
    }

    return false;
}

bool Inventario::registrarVenta(const QString& sku,
                                int cantidad,
                                const QString& cliente,
                                const QString& formaPago,
                                const QString& envio,
                                const QString& observaciones,
                                Venta* ventaCreada)
{
    // Validaciones basicas antes de modificar stock o registrar movimiento.
    Producto* producto = buscarProductoPorSku(sku);
    if (producto == nullptr || cantidad <= 0 || cliente.trimmed().isEmpty() ||
        formaPago.trimmed().isEmpty() || envio.trimmed().isEmpty() ||
        producto->getStock() < cantidad) {
        return false;
    }

    // Descontamos stock en memoria.
    producto->setStock(producto->getStock() - cantidad);

    // Creamos la venta con ID automatico y fecha actual.
    Venta venta(
        siguienteIdVenta++,
        QDateTime::currentDateTime(),
        cliente.trimmed(),
        producto->getSku(),
        cantidad,
        producto->getPrecio(),
        producto->calcularPrecioML(),
        formaPago.trimmed(),
        envio.trimmed(),
        observaciones.trimmed(),
        false,
        QDateTime(),
        0.0);

    ventas.push_back(venta);

    if (ventaCreada != nullptr) {
        *ventaCreada = venta;
    }

    return true;
}

Venta* Inventario::buscarVentaPorId(int id)
{
    auto it = std::find_if(ventas.begin(), ventas.end(), [id](const Venta& venta) {
        return venta.getId() == id;
    });

    if (it == ventas.end()) {
        return nullptr;
    }

    return &(*it);
}

bool Inventario::actualizarVenta(int id, const Venta& nuevaVenta)
{
    // Primero localizamos la venta real que ya existe en memoria.
    Venta* ventaActual = buscarVentaPorId(id);
    if (ventaActual == nullptr || nuevaVenta.getCantidad() <= 0 ||
        nuevaVenta.getCliente().trimmed().isEmpty() ||
        nuevaVenta.getFormaPago().trimmed().isEmpty() ||
        nuevaVenta.getEnvio().trimmed().isEmpty()) {
        return false;
    }

    Producto* productoOriginal = buscarProductoPorSku(ventaActual->getSku());
    Producto* productoNuevo = buscarProductoPorSku(nuevaVenta.getSku());

    if (productoNuevo == nullptr) {
        return false;
    }

    // Si la venta sigue apuntando al mismo SKU, recalculamos stock sobre el mismo producto.
    if (ventaActual->getSku() == nuevaVenta.getSku()) {
        const int stockDisponible = productoNuevo->getStock() + ventaActual->getCantidad();
        if (stockDisponible < nuevaVenta.getCantidad()) {
            return false;
        }

        productoNuevo->setStock(stockDisponible - nuevaVenta.getCantidad());
    } else {
        if (productoOriginal == nullptr || productoNuevo->getStock() < nuevaVenta.getCantidad()) {
            return false;
        }

        productoOriginal->setStock(productoOriginal->getStock() + ventaActual->getCantidad());
        productoNuevo->setStock(productoNuevo->getStock() - nuevaVenta.getCantidad());
    }

    Venta ventaActualizada = nuevaVenta;
    ventaActualizada.setId(id);
    ventaActualizada.setPagadaProveedor(ventaActual->getPagadaProveedor());
    ventaActualizada.setFechaPagoProveedor(ventaActual->getFechaPagoProveedor());
    ventaActualizada.setMontoPagoProveedor(ventaActual->getMontoPagoProveedor());
    *ventaActual = ventaActualizada;
    return true;
}

bool Inventario::eliminarVenta(int id)
{
    // Buscamos la venta y devolvemos el stock al producto antes de borrarla.
    auto it = std::find_if(ventas.begin(), ventas.end(), [id](const Venta& venta) {
        return venta.getId() == id;
    });

    if (it == ventas.end()) {
        return false;
    }

    Producto* producto = buscarProductoPorSku(it->getSku());
    if (producto != nullptr) {
        producto->setStock(producto->getStock() + it->getCantidad());
    }

    ventas.erase(it);
    return true;
}

bool Inventario::marcarVentaComoPagadaProveedor(int id, double montoPago, const QDateTime& fechaPago)
{
    Venta* venta = buscarVentaPorId(id);
    if (venta == nullptr || venta->getPagadaProveedor() || montoPago < 0.0) {
        return false;
    }

    venta->setPagadaProveedor(true);
    venta->setFechaPagoProveedor(fechaPago);
    venta->setMontoPagoProveedor(montoPago);
    return true;
}

double Inventario::calcularTotalPendienteProveedor() const
{
    double total = 0.0;
    for (const Venta& venta : ventas) {
        if (!venta.getPagadaProveedor()) {
            total += venta.getPrecioUnitario() * venta.getCantidad();
        }
    }
    return total;
}

bool Inventario::agregarReparacion(const Reparacion& reparacion)
{
    Reparacion copia = reparacion;
    copia.setId(siguienteIdReparacion++);
    if (!copia.getFechaIngreso().isValid()) {
        copia.setFechaIngreso(QDateTime::currentDateTime());
    }

    reparaciones.push_back(copia);
    return true;
}

Reparacion* Inventario::buscarReparacionPorId(int id)
{
    auto it = std::find_if(reparaciones.begin(), reparaciones.end(), [id](const Reparacion& reparacion) {
        return reparacion.getId() == id;
    });

    if (it == reparaciones.end()) {
        return nullptr;
    }

    return &(*it);
}

bool Inventario::actualizarReparacion(int id, const Reparacion& nuevaReparacion)
{
    Reparacion* reparacion = buscarReparacionPorId(id);
    if (reparacion == nullptr) {
        return false;
    }

    Reparacion copia = nuevaReparacion;
    copia.setId(id);
    *reparacion = copia;
    return true;
}

bool Inventario::eliminarReparacion(int id)
{
    auto it = std::find_if(reparaciones.begin(), reparaciones.end(), [id](const Reparacion& reparacion) {
        return reparacion.getId() == id;
    });

    if (it == reparaciones.end()) {
        return false;
    }

    reparaciones.erase(it);
    return true;
}

void Inventario::cargarDatos(const std::map<QString, Producto>& productosCargados,
                             const std::vector<Venta>& ventasCargadas,
                             const std::vector<Reparacion>& reparacionesCargadas)
{
    // Se usa al levantar datos desde SQLite.
    productos = productosCargados;
    ventas = ventasCargadas;
    reparaciones = reparacionesCargadas;
    siguienteIdVenta = 1;
    siguienteIdReparacion = 1;

    // Al cargar ventas viejas recalculamos el proximo ID disponible.
    for (const Venta& venta : ventas) {
        siguienteIdVenta = std::max(siguienteIdVenta, venta.getId() + 1);
    }

    for (const Reparacion& reparacion : reparaciones) {
        siguienteIdReparacion = std::max(siguienteIdReparacion, reparacion.getId() + 1);
    }
}

const std::map<QString, Producto>& Inventario::getProductos() const
{
    return productos;
}

const std::vector<Venta>& Inventario::getVentas() const
{
    return ventas;
}

const std::vector<Reparacion>& Inventario::getReparaciones() const
{
    return reparaciones;
}
