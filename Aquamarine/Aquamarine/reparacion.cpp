#include "reparacion.h"

Reparacion::Reparacion()
    : id(0), manoObra(0.0)
{
}

Reparacion::Reparacion(int id,
                       const QDateTime& fechaIngreso,
                       const QString& cliente,
                       const QString& tipoReparacion,
                       const QString& modeloDispositivo,
                       const QString& detalleReparacion,
                       double manoObra,
                       const QString& tiempoTrabajo,
                       const QString& observaciones,
                       const QString& estado)
    : id(id),
      fechaIngreso(fechaIngreso),
      cliente(cliente),
      tipoReparacion(tipoReparacion),
      modeloDispositivo(modeloDispositivo),
      detalleReparacion(detalleReparacion),
      manoObra(manoObra),
      tiempoTrabajo(tiempoTrabajo),
      observaciones(observaciones),
      estado(estado)
{
}

int Reparacion::getId() const { return id; }
QDateTime Reparacion::getFechaIngreso() const { return fechaIngreso; }
QString Reparacion::getCliente() const { return cliente; }
QString Reparacion::getTipoReparacion() const { return tipoReparacion; }
QString Reparacion::getModeloDispositivo() const { return modeloDispositivo; }
QString Reparacion::getDetalleReparacion() const { return detalleReparacion; }
double Reparacion::getManoObra() const { return manoObra; }
QString Reparacion::getTiempoTrabajo() const { return tiempoTrabajo; }
QString Reparacion::getObservaciones() const { return observaciones; }
QString Reparacion::getEstado() const { return estado; }

void Reparacion::setId(int value) { id = value; }
void Reparacion::setFechaIngreso(const QDateTime& value) { fechaIngreso = value; }
void Reparacion::setCliente(const QString& value) { cliente = value; }
void Reparacion::setTipoReparacion(const QString& value) { tipoReparacion = value; }
void Reparacion::setModeloDispositivo(const QString& value) { modeloDispositivo = value; }
void Reparacion::setDetalleReparacion(const QString& value) { detalleReparacion = value; }
void Reparacion::setManoObra(double value) { manoObra = value; }
void Reparacion::setTiempoTrabajo(const QString& value) { tiempoTrabajo = value; }
void Reparacion::setObservaciones(const QString& value) { observaciones = value; }
void Reparacion::setEstado(const QString& value) { estado = value; }
