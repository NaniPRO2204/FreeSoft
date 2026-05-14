#pragma once

#include "producto.h"
#include "reparacion.h"
#include "venta.h"

#include <map>
#include <QString>
#include <vector>

// Inventario es la capa de negocio principal:
// - guarda productos
// - guarda ventas
// - controla el stock
// - aplica reglas antes de que la UI o SQLite graben algo
class Inventario
{
private:
    // Mapa de productos usando SKU como clave unica.
    std::map<QString, Producto> productos;

    // Historial de ventas realizadas.
    std::vector<Venta> ventas;

    // Historial de reparaciones o trabajos de servicio tecnico.
    std::vector<Reparacion> reparaciones;

    // Se usa para generar IDs de venta automaticos.
    int siguienteIdVenta;
    int siguienteIdReparacion;

    bool existeCodigoBarrasEnOtroProducto(const QString& codigoBarras, const QString& skuIgnorado = QString()) const;

public:
    Inventario();

    // CRUD de productos.
    bool agregarProducto(const Producto& producto);
    bool eliminarProducto(const QString& sku);
    Producto* buscarProductoPorSku(const QString& sku);
    Producto* buscarProductoPorCodigoBarras(const QString& codigoBarras);
    bool actualizarProducto(const QString& skuActual, const Producto& nuevosDatos);
    bool existeProductoConVentas(const QString& sku) const;

    // Operaciones de ventas.
    bool registrarVenta(const QString& sku,
                        int cantidad,
                        const QString& cliente,
                        const QString& formaPago,
                        const QString& envio,
                        const QString& observaciones,
                        Venta* ventaCreada = nullptr);
    Venta* buscarVentaPorId(int id);
    bool actualizarVenta(int id, const Venta& nuevaVenta);
    bool eliminarVenta(int id);
    bool marcarVentaComoPagadaProveedor(int id, double montoPago, const QDateTime& fechaPago);
    double calcularTotalPendienteProveedor() const;

    // Operaciones de reparaciones.
    bool agregarReparacion(const Reparacion& reparacion);
    Reparacion* buscarReparacionPorId(int id);
    bool actualizarReparacion(int id, const Reparacion& nuevaReparacion);
    bool eliminarReparacion(int id);

    // Reemplaza el estado actual por datos cargados desde SQLite.
    void cargarDatos(const std::map<QString, Producto>& productosCargados,
                     const std::vector<Venta>& ventasCargadas,
                     const std::vector<Reparacion>& reparacionesCargadas);

    // Getters de solo lectura para poblar tablas o guardar en base.
    const std::map<QString, Producto>& getProductos() const;
    const std::vector<Venta>& getVentas() const;
    const std::vector<Reparacion>& getReparaciones() const;
};
