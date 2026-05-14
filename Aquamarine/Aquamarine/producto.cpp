#pragma once
#include "producto.h"
using namespace std;

// Constructor vacio: Qt y otras partes del proyecto a veces necesitan
// construir primero y completar despues.
Producto::Producto() {}

// Constructor principal.
// "this->" indica que estamos guardando el valor recibido dentro del objeto actual.
Producto::Producto(QString nombre, QString descripcion, QString sku, QString codigoBarras, QString modelo, QString marca,
	QString modeloComp, QString observ, int stock, double precio) {
	this->nombre = nombre;
	this->descripcion = descripcion;
	this->sku = sku;
	this->codigoBarras = codigoBarras;
	this->modelo = modelo;
	this->marca = marca;
	this->modeloComp = modeloComp;
	this->observ = observ;
	this->stock = stock;
	this->precio = precio;
}

// Los getters son funciones const: prometen no modificar el objeto.
QString Producto::getNombre() const { return nombre; }
QString Producto::getDescripcion() const { return descripcion; }
QString Producto::getSku() const { return sku; }
QString Producto::getCodigoBarras() const { return codigoBarras; }
QString Producto::getModelo() const { return modelo; }
QString Producto::getMarca() const { return marca; }
QString Producto::getModeloComp() const { return modeloComp; }
QString Producto::getObserv() const { return observ; }
int Producto::getStock() const { return stock; }
double Producto::getPrecio() const { return precio; }
double Producto::calcularPrecioML() const {
	// Esta es una aproximacion conservadora para Mercado Libre Argentina.
	// Base tomada de ayuda oficial para Entre Rios:
	// - cargo por vender de hasta 16,23%
	// - costo fijo adicional para publicaciones menores a $33.000
	//
	// La idea de esta formula no es ser "contable", sino darte un piso de precio
	// para no quedar corto. Si luego cambian comisiones o tu categoria real usa otro
	// porcentaje, puedes tocar SOLO estas constantes y volver a compilar.
	//
	// Lugar para ajustar a futuro:
	// - comisionPorcentaje: porcentaje de cargo por venta.
	// - costoFijo: costo fijo aproximado segun tramo de precio.
	//
	// Formula:
	// precioML = (precioBase + costoFijo) / (1 - comision)
	const double comisionPorcentaje = 0.1623; // Entre Rios: aproximacion alta.

	double costoFijo = 0.0;
	if (precio <= 15000.0) {
		costoFijo = 1115.0;
	}
	else if (precio <= 25000.0) {
		costoFijo = 2300.0;
	}
	else if (precio <= 33000.0) {
		costoFijo = 2810.0;
	}

	const double divisor = 1.0 - comisionPorcentaje;
	if (divisor <= 0.0) {
		return precio;
	}

	const double precioML = (precio + costoFijo) / divisor;
	return precioML;
}

// Los setters reciben un valor nuevo y reemplazan el anterior.
void Producto::setNombre(const QString& value) { nombre = value; }
void Producto::setDescripcion(const QString& value) { descripcion = value; }
void Producto::setSku(const QString& value) { sku = value; }
void Producto::setCodigoBarras(const QString& value) { codigoBarras = value; }
void Producto::setModelo(const QString& value) { modelo = value; }
void Producto::setMarca(const QString& value) { marca = value; }
void Producto::setModeloComp(const QString& value) { modeloComp = value; }
void Producto::setObserv(const QString& value) { observ = value; }
void Producto::setStock(int value) { stock = value; }
void Producto::setPrecio(double value) { precio = value; }
