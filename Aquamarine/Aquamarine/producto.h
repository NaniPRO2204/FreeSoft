#pragma once
#include <QString>

// Producto representa una fila "logica" del inventario.
// No sabe nada de botones, tablas ni SQLite: solo guarda datos del articulo.
class Producto {
private:
	// Atributos basicos del producto.
	QString nombre;
	QString descripcion;
	QString sku;
	QString codigoBarras;
	QString modelo;
	QString marca;
	QString modeloComp;
	QString observ;
	int stock;
	double precio;
public:
	Producto();

	// Constructor completo para crear un producto de una sola vez.
	Producto(QString nombre, QString descripcion, QString sku, QString codigoBarras, QString modelo, QString marca,
		QString modeloComp, QString observ, int stock, double precio);

	// Getters: devuelven el valor actual de cada atributo.
	QString getNombre() const;
	QString getDescripcion() const;
	QString getSku() const;
	QString getCodigoBarras() const;
	QString getModelo() const;
	QString getMarca() const;
	QString getModeloComp() const;
	QString getObserv() const;
	int getStock() const;
	double getPrecio() const;

	// calcularPrecioML() estima un precio de publicacion para Mercado Libre
	// a partir del precio base que ingresa el usuario.
	double calcularPrecioML() const;

	// Setters: actualizan cada campo del producto.
	void setNombre(const QString& value);
	void setDescripcion(const QString& value);
	void setSku(const QString& value);
	void setCodigoBarras(const QString& value);
	void setModelo(const QString& value);
	void setMarca(const QString& value);
	void setModeloComp(const QString& value);
	void setObserv(const QString& value);
	void setStock(int value);
	void setPrecio(double value);
};

