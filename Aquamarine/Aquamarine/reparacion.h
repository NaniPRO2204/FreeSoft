#pragma once

#include <QDateTime>
#include <QString>

// Reparacion representa un trabajo tecnico independiente de las ventas.
// Se usa para llevar control de mano de obra, equipo, cliente y detalle del trabajo.
class Reparacion
{
private:
    int id;
    QDateTime fechaIngreso;
    QString cliente;
    QString tipoReparacion;
    QString modeloDispositivo;
    QString detalleReparacion;
    double manoObra;
    QString tiempoTrabajo;
    QString observaciones;
    QString estado;

public:
    Reparacion();
    Reparacion(int id,
               const QDateTime& fechaIngreso,
               const QString& cliente,
               const QString& tipoReparacion,
               const QString& modeloDispositivo,
               const QString& detalleReparacion,
               double manoObra,
               const QString& tiempoTrabajo,
               const QString& observaciones,
               const QString& estado);

    int getId() const;
    QDateTime getFechaIngreso() const;
    QString getCliente() const;
    QString getTipoReparacion() const;
    QString getModeloDispositivo() const;
    QString getDetalleReparacion() const;
    double getManoObra() const;
    QString getTiempoTrabajo() const;
    QString getObservaciones() const;
    QString getEstado() const;

    void setId(int value);
    void setFechaIngreso(const QDateTime& value);
    void setCliente(const QString& value);
    void setTipoReparacion(const QString& value);
    void setModeloDispositivo(const QString& value);
    void setDetalleReparacion(const QString& value);
    void setManoObra(double value);
    void setTiempoTrabajo(const QString& value);
    void setObservaciones(const QString& value);
    void setEstado(const QString& value);
};
