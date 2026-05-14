#include "venta.h"

// Constructor por defecto.
Venta::Venta()
    : id(0), cantidad(0), precioUnitario(0.0), precioML(0.0), pagadaProveedor(false), montoPagoProveedor(0.0)
{
}

// Constructor principal.
Venta::Venta(int id,
             const QDateTime& fechaHora,
             const QString& cliente,
             const QString& sku,
             int cantidad,
             double precioUnitario,
             double precioML,
             const QString& formaPago,
             const QString& envio,
             const QString& observaciones,
             bool pagadaProveedor,
             const QDateTime& fechaPagoProveedor,
             double montoPagoProveedor)
    : id(id),
      fechaHora(fechaHora),
      cliente(cliente),
      sku(sku),
      cantidad(cantidad),
      precioUnitario(precioUnitario),
      precioML(precioML),
      formaPago(formaPago),
      envio(envio),
      observaciones(observaciones),
      pagadaProveedor(pagadaProveedor),
      fechaPagoProveedor(fechaPagoProveedor),
      montoPagoProveedor(montoPagoProveedor)
{
}

// Getters compactos: devuelven el valor guardado.
int Venta::getId() const { return id; }
QDateTime Venta::getFechaHora() const { return fechaHora; }
QString Venta::getCliente() const { return cliente; }
QString Venta::getSku() const { return sku; }
int Venta::getCantidad() const { return cantidad; }
double Venta::getPrecioUnitario() const { return precioUnitario; }
double Venta::getPrecioML() const { return precioML; }
QString Venta::getFormaPago() const { return formaPago; }
QString Venta::getEnvio() const { return envio; }
QString Venta::getObservaciones() const { return observaciones; }
bool Venta::getPagadaProveedor() const { return pagadaProveedor; }
QDateTime Venta::getFechaPagoProveedor() const { return fechaPagoProveedor; }
double Venta::getMontoPagoProveedor() const { return montoPagoProveedor; }

// Setters compactos: reemplazan el valor actual por otro nuevo.
void Venta::setId(int value) { id = value; }
void Venta::setFechaHora(const QDateTime& value) { fechaHora = value; }
void Venta::setCliente(const QString& value) { cliente = value; }
void Venta::setSku(const QString& value) { sku = value; }
void Venta::setCantidad(int value) { cantidad = value; }
void Venta::setPrecioUnitario(double value) { precioUnitario = value; }
void Venta::setPrecioML(double value) { precioML = value; }
void Venta::setFormaPago(const QString& value) { formaPago = value; }
void Venta::setEnvio(const QString& value) { envio = value; }
void Venta::setObservaciones(const QString& value) { observaciones = value; }
void Venta::setPagadaProveedor(bool value) { pagadaProveedor = value; }
void Venta::setFechaPagoProveedor(const QDateTime& value) { fechaPagoProveedor = value; }
void Venta::setMontoPagoProveedor(double value) { montoPagoProveedor = value; }
