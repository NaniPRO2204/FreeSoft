#pragma once

#include <QDateTime>
#include <QString>

// Venta agrupa la informacion historica de una operacion realizada.
// A diferencia de Producto, una venta representa un movimiento ya hecho.
class Venta
{
private:
    // "id" nos sirve para encontrar, editar o borrar una venta concreta.
    int id;
    QDateTime fechaHora;
    QString cliente;
    QString sku;
    int cantidad;
    double precioUnitario;
    double precioML;
    QString formaPago;
    QString envio;
    QString observaciones;
    bool pagadaProveedor;
    QDateTime fechaPagoProveedor;
    double montoPagoProveedor;

public:
    Venta();

    // Constructor completo para registrar una venta ya armada.
    Venta(int id,
          const QDateTime& fechaHora,
          const QString& cliente,
          const QString& sku,
          int cantidad,
          double precioUnitario,
          double precioML,
          const QString& formaPago,
          const QString& envio,
          const QString& observaciones,
          bool pagadaProveedor = false,
          const QDateTime& fechaPagoProveedor = QDateTime(),
          double montoPagoProveedor = 0.0);

    // Getters: exponen los datos de solo lectura.
    int getId() const;
    QDateTime getFechaHora() const;
    QString getCliente() const;
    QString getSku() const;
    int getCantidad() const;
    double getPrecioUnitario() const;
    double getPrecioML() const;
    QString getFormaPago() const;
    QString getEnvio() const;
    QString getObservaciones() const;
    bool getPagadaProveedor() const;
    QDateTime getFechaPagoProveedor() const;
    double getMontoPagoProveedor() const;

    // Setters: permiten modificar la venta al editarla.
    void setId(int value);
    void setFechaHora(const QDateTime& value);
    void setCliente(const QString& value);
    void setSku(const QString& value);
    void setCantidad(int value);
    void setPrecioUnitario(double value);
    void setPrecioML(double value);
    void setFormaPago(const QString& value);
    void setEnvio(const QString& value);
    void setObservaciones(const QString& value);
    void setPagadaProveedor(bool value);
    void setFechaPagoProveedor(const QDateTime& value);
    void setMontoPagoProveedor(double value);
};
