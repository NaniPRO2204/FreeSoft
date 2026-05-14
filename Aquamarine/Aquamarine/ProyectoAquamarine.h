#pragma once

#include <QtWidgets/QMainWindow>
#include <QResizeEvent>

#include "database_manager.h"
#include "inventario.h"
#include "ui_ProyectoAquamarine.h"

class QStringListModel;
class QLabel;
class QShortcut;
class QTableWidget;
class QTextEdit;
class QWidget;
class QPushButton;
class QLineEdit;
class QDateTimeEdit;
class QFormLayout;

class ProyectoAquamarine : public QMainWindow
{
    Q_OBJECT

public:
    ProyectoAquamarine(QWidget* parent = nullptr);
    ~ProyectoAquamarine();

protected:
    void resizeEvent(QResizeEvent* event) override;

private slots:
    void on_btnAgregar_clicked();
    void on_btnBuscar_clicked();
    void on_btnConsProd_clicked();
    void on_btnConsVen_clicked();
    void on_btnConsInv_clicked();
    void on_btnBorrarVenta_clicked();
    void on_btnBuscarID_clicked();
    void on_btnDialAgregar_rejected();
    void on_btnDialAgregar_accepted();
    void on_btnDialEditVenta_rejected();
    void on_btnDialEditVenta_accepted();
    void on_btnDialVender_rejected();
    void on_btnDialVender_accepted();
    void volverFuncion();
    void on_btnSalir_clicked();
    void on_btnEditarVenta_clicked();
    void on_btnEditarVen_clicked();
    void on_btnVender_clicked();
    void on_btnEditar_clicked();
    void on_btnBorrar_clicked();
    void openAdminPanel();
    void runAdminQuery();
    void resetAdminDatabase();
    void markSelectedSaleAsPaid();
    void openRepairsPage();
    void openNewRepairForm();
    void openEditRepairForm();
    void saveRepairForm();
    void cancelRepairForm();
    void deleteSelectedRepair();

private:
    Ui::ProyectoAquamarineClass ui;
    Inventario* inven;
    Producto* prodAux;
    DatabaseManager* databaseManager;
    QStringListModel* logModel;
    QString productoSeleccionadoSku;
    QString productoEnEdicionSku;
    int ventaSeleccionadaId;
    int reparacionSeleccionadaId;
    bool editandoProducto;
    bool editandoReparacion;
    QWidget* adminPage;
    QTextEdit* adminSqlEditor;
    QTableWidget* adminResultsTable;
    QLabel* adminInfoLabel;
    QLabel* adminHintLabel;
    QPushButton* adminExecuteButton;
    QPushButton* adminResetButton;
    QShortcut* adminShortcut;
    QPushButton* btnRegistrarPagoProveedor;
    QPushButton* btnReparaciones;
    QLabel* lblResumenVentas;
    QWidget* repairsPage;
    QWidget* repairFormPage;
    QTableWidget* tblReparaciones;
    QLineEdit* linRepairCliente;
    QLineEdit* linRepairTipo;
    QLineEdit* linRepairModelo;
    QLineEdit* linRepairEquipo;
    QLineEdit* linRepairManoObra;
    QLineEdit* linRepairTiempo;
    QLineEdit* linRepairEstado;
    QTextEdit* txtRepairObservaciones;
    QDateTimeEdit* dateRepairIngreso;
    QLineEdit* linCodigoBarras;
    QTextEdit* txtCodigoBarrasDetalle;

    void configureUi();
    void configureResponsiveLayout();
    void configureProductBarcodeFields();
    void configureTables();
    void configureValidators();
    void configureAdminPage();
    void configureSalesEnhancements();
    void configureRepairsPages();
    void applyStyles();
    void loadData();
    bool persistData();
    void addLog(const QString& message);
    void refreshViews();
    void refreshInventoryTable();
    void refreshSalesTable();
    void refreshRepairsTable();
    void showProductDetails(const Producto& producto);
    void clearProductForm();
    void clearSaleForm();
    void clearSaleEditForm();
    void clearRepairForm();
    void populateSaleEditForm(const Venta& venta);
    void populateRepairForm(const Reparacion& reparacion);
    bool buildProductFromForm(Producto& producto, QString& errorMessage) const;
    bool buildSaleFromEditForm(Venta& venta, QString& errorMessage) const;
    bool buildRepairFromForm(Reparacion& reparacion, QString& errorMessage) const;
    void setCurrentProduct(const QString& sku);
    void renderBrandLogo();
    bool requestAdminAccess();
    void refreshAdminHelpText();
    QString normalizedOptionalText(const QString& value) const;
};
