#include "ProyectoAquamarine.h"

#include <QDateTime>
#include <QDir>
#include <QDialogButtonBox>
#include <QDoubleValidator>
#include <QGuiApplication>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QIntValidator>
#include <QKeySequence>
#include <QLabel>
#include <QLinearGradient>
#include <QMessageBox>
#include <QPainter>
#include <QPushButton>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QScreen>
#include <QShortcut>
#include <QSizePolicy>
#include <QStandardPaths>
#include <QStatusBar>
#include <QFormLayout>
#include <QStringListModel>
#include <QTableWidgetItem>
#include <QVBoxLayout>

namespace
{
QString money(double value)
{
    return QString("$ %1").arg(QString::number(value, 'f', 2));
}
}

ProyectoAquamarine::ProyectoAquamarine(QWidget* parent)
    : QMainWindow(parent),
      inven(new Inventario()),
      prodAux(new Producto()),
      databaseManager(new DatabaseManager()),
      logModel(new QStringListModel(this)),
      ventaSeleccionadaId(-1),
      reparacionSeleccionadaId(-1),
      editandoProducto(false),
      editandoReparacion(false),
      adminPage(nullptr),
      adminSqlEditor(nullptr),
      adminResultsTable(nullptr),
      adminInfoLabel(nullptr),
      adminHintLabel(nullptr),
      adminExecuteButton(nullptr),
      adminResetButton(nullptr),
      adminShortcut(nullptr),
      btnRegistrarPagoProveedor(nullptr),
      btnReparaciones(nullptr),
      lblResumenVentas(nullptr),
      repairsPage(nullptr),
      repairFormPage(nullptr),
      tblReparaciones(nullptr),
      linRepairCliente(nullptr),
      linRepairTipo(nullptr),
      linRepairModelo(nullptr),
      linRepairEquipo(nullptr),
      linRepairManoObra(nullptr),
      linRepairTiempo(nullptr),
      linRepairEstado(nullptr),
      txtRepairObservaciones(nullptr),
      dateRepairIngreso(nullptr),
      linCodigoBarras(nullptr),
      txtCodigoBarrasDetalle(nullptr)
{
    ui.setupUi(this);

    configureUi();
    loadData();
    refreshViews();
}

ProyectoAquamarine::~ProyectoAquamarine()
{
    delete databaseManager;
    delete prodAux;
    delete inven;
}

void ProyectoAquamarine::configureUi()
{
    // Dejamos que la ventana y los layouts puedan crecer con libertad.
    configureProductBarcodeFields();
    configureResponsiveLayout();

    ui.stkPestanias->setCurrentWidget(ui.pagPrincipal);
    ui.listLog->setModel(logModel);
    ui.statusBar->showMessage("Listo para trabajar.");

    // Los botones "Volver" no usan auto-connect porque todos comparten la misma accion.
    connect(ui.btnVolver, &QPushButton::clicked, this, &ProyectoAquamarine::volverFuncion);
    connect(ui.btnVolver_2, &QPushButton::clicked, this, &ProyectoAquamarine::volverFuncion);
    connect(ui.btnVolver_3, &QPushButton::clicked, this, &ProyectoAquamarine::volverFuncion);
    connect(ui.btnVolver_4, &QPushButton::clicked, this, &ProyectoAquamarine::volverFuncion);
    connect(ui.btnVolver_5, &QPushButton::clicked, this, &ProyectoAquamarine::volverFuncion);

    configureTables();
    configureValidators();
    configureAdminPage();
    configureSalesEnhancements();
    configureRepairsPages();
    applyStyles();
    renderBrandLogo();

    ui.dateRegActual->setDisplayFormat("dd/MM/yyyy HH:mm");
    ui.dateRegNuevo->setDisplayFormat("dd/MM/yyyy HH:mm");
    ui.dateRegActual->setReadOnly(true);
    ui.dateRegActual->setButtonSymbols(QAbstractSpinBox::NoButtons);
    ui.dateRegNuevo->setDateTime(QDateTime::currentDateTime());

    ui.linBuscar->setPlaceholderText("Busca por SKU o codigo de barras");
    ui.linBuscarID->setPlaceholderText("Ingresa el ID de venta");
    ui.linVenderCant->setPlaceholderText("Cantidad");
    ui.linVenderCliente->setPlaceholderText("Cliente");
    ui.linVenderPago->setPlaceholderText("Transferencia, efectivo, etc.");
    ui.linVendeEnvio->setPlaceholderText("Retira, mensajeria, correo...");
    ui.linPrecio->setPlaceholderText("0.00");
    ui.linStock->setPlaceholderText("0");

    connect(ui.linBuscar, &QLineEdit::returnPressed, ui.btnBuscar, &QPushButton::click);
    connect(ui.linBuscarID, &QLineEdit::returnPressed, ui.btnBuscarID, &QPushButton::click);
    connect(ui.linRegPrecioNuevo, &QLineEdit::textChanged, this, [this](const QString& text) {
        const double precio = text.toDouble();
        if (precio > 0.0) {
            ui.linRegPrecioMLNuevo->setText(QString::number(precio * 1.16, 'f', 2));
        }
    });

    clearProductForm();
    clearSaleForm();
    clearSaleEditForm();
}

void ProyectoAquamarine::configureResponsiveLayout()
{
    // Quitamos las restricciones "Fixed" del .ui para que la app responda al tamano real de la ventana.
    resize(1180, 780);
    setMinimumSize(960, 680);

    if (QScreen* screen = QGuiApplication::primaryScreen()) {
        const QRect available = screen->availableGeometry();
        resize(qMin(available.width() - 80, 1400), qMin(available.height() - 80, 900));
    }

    ui.centralWidget->setMinimumSize(0, 0);
    ui.centralWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui.stkPestanias->setMinimumSize(0, 0);
    ui.stkPestanias->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui.listLog->setMinimumWidth(360);
    ui.listLog->setMaximumWidth(460);
    ui.listLog->setWordWrap(true);
    ui.listLog->setTextElideMode(Qt::ElideRight);
    ui.listLog->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    ui.gridLayout->setColumnStretch(0, 1);
    ui.gridLayout->setColumnStretch(1, 1);
    ui.gridLayout->setColumnStretch(2, 1);
    ui.gridLayout->setColumnStretch(3, 0);
    ui.gridLayout->setRowStretch(0, 0);
    ui.gridLayout->setRowStretch(1, 0);
    ui.gridLayout->setRowStretch(2, 0);

    const QList<QPushButton*> mainButtons = {
        ui.btnAgregar, ui.btnEditarVen, ui.btnConsInv, ui.btnConsProd, ui.btnConsVen
    };

    for (QPushButton* button : mainButtons) {
        button->setMinimumSize(190, 88);
        button->setMaximumHeight(120);
        button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    }

    const QList<QLineEdit*> lineEdits = findChildren<QLineEdit*>();
    for (QLineEdit* edit : lineEdits) {
        edit->setMinimumWidth(220);
        edit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    }

    const QList<QTextEdit*> textEdits = findChildren<QTextEdit*>();
    for (QTextEdit* edit : textEdits) {
        edit->setMinimumHeight(90);
        edit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    }
}

void ProyectoAquamarine::configureProductBarcodeFields()
{
    // Agregamos el campo en tiempo de ejecucion para no depender de una edicion manual del .ui.
    if (QFormLayout* addLayout = findChild<QFormLayout*>("formLayout")) {
        auto* barcodeLabel = new QLabel("Codigo de barras");
        linCodigoBarras = new QLineEdit();
        linCodigoBarras->setPlaceholderText("Solo numeros, opcional");
        addLayout->insertRow(2, barcodeLabel, linCodigoBarras);
    }

    if (QFormLayout* detailsLayout = findChild<QFormLayout*>("formLayout_2")) {
        auto* barcodeLabel = new QLabel("Codigo de barras");
        txtCodigoBarrasDetalle = new QTextEdit();
        txtCodigoBarrasDetalle->setReadOnly(true);
        txtCodigoBarrasDetalle->setMinimumHeight(36);
        txtCodigoBarrasDetalle->setMaximumHeight(52);
        detailsLayout->insertRow(2, barcodeLabel, txtCodigoBarrasDetalle);
    }
}

void ProyectoAquamarine::configureTables()
{
    // Las tablas son el resumen principal del inventario y de las ventas.
    ui.tblInventario->setColumnCount(8);
    ui.tblInventario->setHorizontalHeaderLabels(
        {"SKU", "Codigo de barras", "Nombre", "Marca", "Modelo", "Compatibilidad", "Stock", "Precio"});
    ui.tblInventario->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui.tblInventario->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui.tblInventario->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui.tblInventario->setAlternatingRowColors(true);

    ui.tblVentas->setColumnCount(12);
    ui.tblVentas->setHorizontalHeaderLabels(
        {"ID", "Fecha", "Cliente", "SKU", "Cantidad", "Precio", "Precio ML", "Pago", "Envio", "Estado", "Pago proveedor", "Fecha pago"});
    ui.tblVentas->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui.tblVentas->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui.tblVentas->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui.tblVentas->setAlternatingRowColors(true);
}

void ProyectoAquamarine::configureValidators()
{
    // Los validadores frenan errores comunes antes de tocar la logica de negocio.
    auto* integerValidator = new QIntValidator(0, 1000000, this);
    auto* positiveIntegerValidator = new QIntValidator(1, 1000000, this);
    auto* moneyValidator = new QDoubleValidator(0.0, 100000000.0, 2, this);
    auto* barcodeValidator = new QRegularExpressionValidator(QRegularExpression("\\d{0,32}"), this);
    moneyValidator->setNotation(QDoubleValidator::StandardNotation);

    ui.linStock->setValidator(integerValidator);
    ui.linVenderCant->setValidator(positiveIntegerValidator);
    ui.linPrecio->setValidator(moneyValidator);
    ui.linRegCantNuevo->setValidator(positiveIntegerValidator);
    ui.linRegPrecioNuevo->setValidator(moneyValidator);
    ui.linRegPrecioMLNuevo->setValidator(moneyValidator);
    if (linCodigoBarras != nullptr) {
        linCodigoBarras->setValidator(barcodeValidator);
    }

    if (linRepairManoObra != nullptr) {
        linRepairManoObra->setValidator(moneyValidator);
    }
}

void ProyectoAquamarine::configureSalesEnhancements()
{
    lblResumenVentas = new QLabel();
    lblResumenVentas->setWordWrap(true);
    ui.verticalLayout_4->insertWidget(2, lblResumenVentas);

    btnRegistrarPagoProveedor = new QPushButton("Registrar pago proveedor");
    ui.verticalLayout_4->addWidget(btnRegistrarPagoProveedor);
    connect(btnRegistrarPagoProveedor, &QPushButton::clicked, this, &ProyectoAquamarine::markSelectedSaleAsPaid);
}

void ProyectoAquamarine::configureRepairsPages()
{
    btnReparaciones = new QPushButton("Reparaciones");
    btnReparaciones->setMinimumSize(190, 88);
    btnReparaciones->setMaximumHeight(120);
    btnReparaciones->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    ui.gridLayout->addWidget(btnReparaciones, 3, 0, 1, 3);
    connect(btnReparaciones, &QPushButton::clicked, this, &ProyectoAquamarine::openRepairsPage);

    repairsPage = new QWidget();
    auto* repairsLayout = new QVBoxLayout(repairsPage);
    repairsLayout->setContentsMargins(16, 16, 16, 16);
    repairsLayout->setSpacing(10);

    auto* repairsTitle = new QLabel("Reparaciones");
    repairsTitle->setStyleSheet("font-size: 18pt; font-weight: 700;");
    repairsLayout->addWidget(repairsTitle);

    auto* repairsButtons = new QHBoxLayout();
    auto* btnNuevaReparacion = new QPushButton("Nueva reparacion");
    auto* btnEditarReparacion = new QPushButton("Editar reparacion");
    auto* btnBorrarReparacion = new QPushButton("Borrar reparacion");
    auto* btnVolverReparaciones = new QPushButton("Volver");
    repairsButtons->addWidget(btnNuevaReparacion);
    repairsButtons->addWidget(btnEditarReparacion);
    repairsButtons->addWidget(btnBorrarReparacion);
    repairsButtons->addStretch();
    repairsButtons->addWidget(btnVolverReparaciones);
    repairsLayout->addLayout(repairsButtons);

    tblReparaciones = new QTableWidget();
    tblReparaciones->setColumnCount(8);
    tblReparaciones->setHorizontalHeaderLabels(
        {"ID", "Fecha", "Cliente", "Tipo", "Equipo", "Mano de obra", "Tiempo", "Estado"});
    tblReparaciones->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tblReparaciones->setSelectionBehavior(QAbstractItemView::SelectRows);
    tblReparaciones->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tblReparaciones->setAlternatingRowColors(true);
    repairsLayout->addWidget(tblReparaciones);

    ui.stkPestanias->addWidget(repairsPage);

    repairFormPage = new QWidget();
    auto* formPageLayout = new QVBoxLayout(repairFormPage);
    formPageLayout->setContentsMargins(18, 18, 18, 18);
    formPageLayout->setSpacing(12);

    auto* repairTitle = new QLabel("Formulario de reparacion");
    repairTitle->setStyleSheet("font-size: 18pt; font-weight: 700;");
    formPageLayout->addWidget(repairTitle);

    auto* formLayout = new QFormLayout();
    dateRepairIngreso = new QDateTimeEdit();
    dateRepairIngreso->setDisplayFormat("dd/MM/yyyy HH:mm");
    dateRepairIngreso->setDateTime(QDateTime::currentDateTime());
    linRepairCliente = new QLineEdit();
    linRepairTipo = new QLineEdit();
    linRepairModelo = new QLineEdit();
    linRepairEquipo = new QLineEdit();
    linRepairManoObra = new QLineEdit();
    linRepairTiempo = new QLineEdit();
    linRepairEstado = new QLineEdit();
    txtRepairObservaciones = new QTextEdit();
    txtRepairObservaciones->setMinimumHeight(140);

    formLayout->addRow("Fecha ingreso", dateRepairIngreso);
    formLayout->addRow("Cliente", linRepairCliente);
    formLayout->addRow("Tipo de reparacion", linRepairTipo);
    formLayout->addRow("Modelo de dispositivo", linRepairModelo);
    formLayout->addRow("Que se reparo", linRepairEquipo);
    formLayout->addRow("Mano de obra", linRepairManoObra);
    formLayout->addRow("Tiempo que llevo", linRepairTiempo);
    formLayout->addRow("Estado", linRepairEstado);
    formLayout->addRow("Observaciones", txtRepairObservaciones);
    formPageLayout->addLayout(formLayout);

    auto* formButtons = new QHBoxLayout();
    auto* btnGuardarReparacion = new QPushButton("Guardar reparacion");
    auto* btnCancelarReparacion = new QPushButton("Cancelar");
    formButtons->addWidget(btnGuardarReparacion);
    formButtons->addWidget(btnCancelarReparacion);
    formButtons->addStretch();
    formPageLayout->addLayout(formButtons);

    ui.stkPestanias->addWidget(repairFormPage);

    connect(btnNuevaReparacion, &QPushButton::clicked, this, &ProyectoAquamarine::openNewRepairForm);
    connect(btnEditarReparacion, &QPushButton::clicked, this, &ProyectoAquamarine::openEditRepairForm);
    connect(btnBorrarReparacion, &QPushButton::clicked, this, &ProyectoAquamarine::deleteSelectedRepair);
    connect(btnVolverReparaciones, &QPushButton::clicked, this, &ProyectoAquamarine::volverFuncion);
    connect(btnGuardarReparacion, &QPushButton::clicked, this, &ProyectoAquamarine::saveRepairForm);
    connect(btnCancelarReparacion, &QPushButton::clicked, this, &ProyectoAquamarine::cancelRepairForm);
}

void ProyectoAquamarine::configureAdminPage()
{
    // Panel oculto: se abre con Ctrl+Alt+S y pide contrasena antes de entrar.
    adminPage = new QWidget();
    adminPage->setObjectName("pagAdminSql");

    auto* layout = new QVBoxLayout(adminPage);
    layout->setContentsMargins(18, 18, 18, 18);
    layout->setSpacing(12);

    auto* title = new QLabel("Admin SQLite");
    title->setStyleSheet("font-size: 18pt; font-weight: 700; color: #0f566c;");
    layout->addWidget(title);

    adminInfoLabel = new QLabel();
    adminInfoLabel->setWordWrap(true);
    layout->addWidget(adminInfoLabel);

    adminHintLabel = new QLabel();
    adminHintLabel->setWordWrap(true);
    layout->addWidget(adminHintLabel);

    adminSqlEditor = new QTextEdit();
    adminSqlEditor->setPlaceholderText(
        "Escribe aqui SQL.\n"
        "Ejemplos:\n"
        "SELECT * FROM productos;\n"
        "SELECT * FROM ventas WHERE cliente LIKE '%Juan%';\n"
        "DELETE FROM ventas WHERE id = 1;");
    adminSqlEditor->setMinimumHeight(180);
    layout->addWidget(adminSqlEditor);

    auto* buttonRow = new QHBoxLayout();
    adminExecuteButton = new QPushButton("Ejecutar SQL");
    adminResetButton = new QPushButton("Vaciar base");
    auto* backButton = new QPushButton("Volver");
    buttonRow->addWidget(adminExecuteButton);
    buttonRow->addWidget(adminResetButton);
    buttonRow->addStretch();
    buttonRow->addWidget(backButton);
    layout->addLayout(buttonRow);

    adminResultsTable = new QTableWidget();
    adminResultsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    adminResultsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    adminResultsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    adminResultsTable->setAlternatingRowColors(true);
    layout->addWidget(adminResultsTable);

    ui.stkPestanias->addWidget(adminPage);

    connect(adminExecuteButton, &QPushButton::clicked, this, &ProyectoAquamarine::runAdminQuery);
    connect(adminResetButton, &QPushButton::clicked, this, &ProyectoAquamarine::resetAdminDatabase);
    connect(backButton, &QPushButton::clicked, this, &ProyectoAquamarine::volverFuncion);

    adminShortcut = new QShortcut(QKeySequence("Ctrl+Alt+S"), this);
    connect(adminShortcut, &QShortcut::activated, this, &ProyectoAquamarine::openAdminPanel);

    refreshAdminHelpText();
}

void ProyectoAquamarine::applyStyles()
{
    setWindowTitle("Aquamarine");
    setStyleSheet(
        "QMainWindow {"
        "  background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #060b0f, stop:0.5 #0d1720, stop:1 #111d24);"
        "}"
        "QWidget {"
        "  color: #f1f5f9;"
        "  font-family: 'Segoe UI';"
        "  font-size: 10pt;"
        "}"
        "QStackedWidget {"
        "  border: 1px solid #1f2733;"
        "  border-radius: 18px;"
        "  background: rgba(12, 16, 22, 0.95);"
        "}"
        "QLabel#lblLogoCRM {"
        "  padding: 12px;"
        "  qproperty-alignment: AlignCenter;"
        "}"
        "QPushButton {"
        "  background-color: #171c24;"
        "  color: #f8fafc;"
        "  border: 1px solid #222b37;"
        "  border-radius: 12px;"
        "  padding: 10px 16px;"
        "  font-weight: 600;"
        "}"
        "QPushButton:hover {"
        "  border-color: #72f0df;"
        "  background-color: #1b2430;"
        "}"
        "QPushButton:pressed {"
        "  background-color: #11161f;"
        "}"
        "QLineEdit, QTextEdit, QDateTimeEdit, QListView, QTableWidget {"
        "  background: #0f141b;"
        "  color: #eef2f7;"
        "  border: 1px solid #273040;"
        "  border-radius: 10px;"
        "  padding: 6px 8px;"
        "  selection-background-color: #4cdcca;"
        "  selection-color: #081018;"
        "}"
        "QTableWidget {"
        "  gridline-color: #1c2533;"
        "  alternate-background-color: #131a24;"
        "}"
        "QHeaderView::section {"
        "  background: #0b1017;"
        "  color: #e6edf5;"
        "  padding: 8px;"
        "  border: none;"
        "  border-bottom: 1px solid #283346;"
        "  font-weight: 700;"
        "}"
        "QDialogButtonBox QPushButton {"
        "  min-width: 110px;"
        "}"
        "QListView {"
        "  background: #0b1016;"
        "  font-size: 10.5pt;"
        "}"
        "QLabel {"
        "  color: #e9eef6;"
        "}"
        "QMessageBox {"
        "  background: #0c1016;"
        "}"
        "QMessageBox QLabel {"
        "  color: #f8fafc;"
        "  min-width: 260px;"
        "}"
        "QMessageBox QPushButton {"
        "  background-color: #171c24;"
        "  color: #f8fafc;"
        "  border: 1px solid #2a3442;"
        "  padding: 8px 14px;"
        "}"
        "QMenuBar {"
        "  background: #090c11;"
        "  color: #e5edf5;"
        "}"
        "QStatusBar {"
        "  background: #090c11;"
        "  color: #a9b6c7;"
        "}"
        "QWidget#pagAdminSql {"
        "  background: rgba(10, 13, 18, 0.98);"
        "}"
    );
}

void ProyectoAquamarine::loadData()
{
    QString baseFolder = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    if (baseFolder.isEmpty()) {
        baseFolder = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    }

    const QString dataFolder = baseFolder + "/Aquamarine";
    QDir().mkpath(dataFolder);
    const QString dbPath = dataFolder + "/aquamarine.sqlite";

    if (!databaseManager->initialize(dbPath)) {
        addLog("SQLite no pudo inicializarse: " + databaseManager->lastError());
        ui.statusBar->showMessage("Trabajando en memoria. SQLite no disponible.");
        return;
    }

    std::map<QString, Producto> productos;
    std::vector<Venta> ventas;
    std::vector<Reparacion> reparaciones;
    if (databaseManager->loadAll(productos, ventas, reparaciones)) {
        inven->cargarDatos(productos, ventas, reparaciones);
        addLog("Datos cargados desde SQLite: " + databaseManager->path());
        ui.statusBar->showMessage("Base SQLite lista.");
        refreshAdminHelpText();
    } else {
        addLog("No se pudieron cargar datos previos: " + databaseManager->lastError());
    }
}

bool ProyectoAquamarine::persistData()
{
    if (!databaseManager->isAvailable()) {
        return false;
    }

    const bool ok = databaseManager->saveAll(*inven);
    if (!ok) {
        addLog("Error al guardar SQLite: " + databaseManager->lastError());
        ui.statusBar->showMessage("No se pudo guardar en SQLite.");
    }

    return ok;
}

void ProyectoAquamarine::addLog(const QString& message)
{
    QStringList items = logModel->stringList();
    items.prepend(QDateTime::currentDateTime().toString("dd/MM HH:mm") + " - " + message);
    while (items.size() > 50) {
        items.removeLast();
    }

    logModel->setStringList(items);
}

void ProyectoAquamarine::refreshViews()
{
    // Cuando cambia el estado del sistema, refrescamos las dos tablas visibles.
    refreshInventoryTable();
    refreshSalesTable();
    refreshRepairsTable();
}

void ProyectoAquamarine::refreshInventoryTable()
{
    ui.tblInventario->setRowCount(0);
    int row = 0;

    for (const auto& pair : inven->getProductos()) {
        const Producto& producto = pair.second;
        ui.tblInventario->insertRow(row);
        ui.tblInventario->setItem(row, 0, new QTableWidgetItem(producto.getSku()));
        ui.tblInventario->setItem(row, 1, new QTableWidgetItem(producto.getCodigoBarras().isEmpty() ? "-" : producto.getCodigoBarras()));
        ui.tblInventario->setItem(row, 2, new QTableWidgetItem(producto.getNombre()));
        ui.tblInventario->setItem(row, 3, new QTableWidgetItem(producto.getMarca()));
        ui.tblInventario->setItem(row, 4, new QTableWidgetItem(producto.getModelo()));
        ui.tblInventario->setItem(row, 5, new QTableWidgetItem(producto.getModeloComp()));
        ui.tblInventario->setItem(row, 6, new QTableWidgetItem(QString::number(producto.getStock())));
        ui.tblInventario->setItem(row, 7, new QTableWidgetItem(money(producto.getPrecio())));
        ++row;
    }
}

void ProyectoAquamarine::refreshSalesTable()
{
    ui.tblVentas->setRowCount(0);
    int row = 0;

    std::vector<Venta> ventas = inven->getVentas();
    std::stable_sort(ventas.begin(), ventas.end(), [](const Venta& a, const Venta& b) {
        if (a.getPagadaProveedor() != b.getPagadaProveedor()) {
            return !a.getPagadaProveedor();
        }
        return a.getId() > b.getId();
    });

    for (const Venta& venta : ventas) {
        ui.tblVentas->insertRow(row);
        ui.tblVentas->setItem(row, 0, new QTableWidgetItem(QString::number(venta.getId())));
        ui.tblVentas->setItem(row, 1, new QTableWidgetItem(venta.getFechaHora().toString("dd/MM/yyyy HH:mm")));
        ui.tblVentas->setItem(row, 2, new QTableWidgetItem(venta.getCliente()));
        ui.tblVentas->setItem(row, 3, new QTableWidgetItem(venta.getSku()));
        ui.tblVentas->setItem(row, 4, new QTableWidgetItem(QString::number(venta.getCantidad())));
        ui.tblVentas->setItem(row, 5, new QTableWidgetItem(money(venta.getPrecioUnitario())));
        ui.tblVentas->setItem(row, 6, new QTableWidgetItem(money(venta.getPrecioML())));
        ui.tblVentas->setItem(row, 7, new QTableWidgetItem(venta.getFormaPago()));
        ui.tblVentas->setItem(row, 8, new QTableWidgetItem(venta.getEnvio()));
        ui.tblVentas->setItem(row, 9, new QTableWidgetItem(venta.getPagadaProveedor() ? "Pagada" : "Pendiente"));
        ui.tblVentas->setItem(row, 10, new QTableWidgetItem(venta.getPagadaProveedor() ? money(venta.getMontoPagoProveedor()) : "-"));
        ui.tblVentas->setItem(row, 11, new QTableWidgetItem(venta.getPagadaProveedor() && venta.getFechaPagoProveedor().isValid()
                                                                 ? venta.getFechaPagoProveedor().toString("dd/MM/yyyy")
                                                                 : "-"));

        if (venta.getPagadaProveedor()) {
            for (int column = 0; column < ui.tblVentas->columnCount(); ++column) {
                if (QTableWidgetItem* item = ui.tblVentas->item(row, column)) {
                    item->setBackground(QColor("#102619"));
                    item->setForeground(QColor("#d9fbe7"));
                }
            }
        }

        ++row;
    }

    if (lblResumenVentas != nullptr) {
        lblResumenVentas->setText(
            "Pendiente de pagar al proveedor: " + money(inven->calcularTotalPendienteProveedor()) +
            "\nLas ventas pendientes aparecen arriba y las pagadas quedan resaltadas en verde.");
    }
}

void ProyectoAquamarine::refreshRepairsTable()
{
    if (tblReparaciones == nullptr) {
        return;
    }

    tblReparaciones->setRowCount(0);
    int row = 0;
    for (const Reparacion& reparacion : inven->getReparaciones()) {
        tblReparaciones->insertRow(row);
        tblReparaciones->setItem(row, 0, new QTableWidgetItem(QString::number(reparacion.getId())));
        tblReparaciones->setItem(row, 1, new QTableWidgetItem(reparacion.getFechaIngreso().toString("dd/MM/yyyy HH:mm")));
        tblReparaciones->setItem(row, 2, new QTableWidgetItem(reparacion.getCliente()));
        tblReparaciones->setItem(row, 3, new QTableWidgetItem(reparacion.getTipoReparacion()));
        tblReparaciones->setItem(row, 4, new QTableWidgetItem(reparacion.getModeloDispositivo()));
        tblReparaciones->setItem(row, 5, new QTableWidgetItem(money(reparacion.getManoObra())));
        tblReparaciones->setItem(row, 6, new QTableWidgetItem(reparacion.getTiempoTrabajo()));
        tblReparaciones->setItem(row, 7, new QTableWidgetItem(reparacion.getEstado()));
        ++row;
    }
}

void ProyectoAquamarine::showProductDetails(const Producto& producto)
{
    ui.txtNombre->setPlainText(producto.getNombre());
    ui.txtSKU->setPlainText(producto.getSku());
    if (txtCodigoBarrasDetalle != nullptr) {
        txtCodigoBarrasDetalle->setPlainText(producto.getCodigoBarras().isEmpty() ? "Sin codigo cargado" : producto.getCodigoBarras());
    }
    ui.txtMod->setPlainText(producto.getModelo());
    ui.txtDesc_2->setPlainText(producto.getDescripcion());
    ui.txtModComp->setPlainText(producto.getModeloComp());
    ui.txtPrecio->setPlainText(money(producto.getPrecio()));
    ui.txtStock->setPlainText(QString::number(producto.getStock()));
    ui.txtObs_2->setPlainText(producto.getObserv());
}

void ProyectoAquamarine::clearProductForm()
{
    // Este formulario se usa tanto para crear como para editar productos.
    ui.linNombre->clear();
    ui.linSKU->clear();
    if (linCodigoBarras != nullptr) {
        linCodigoBarras->clear();
    }
    ui.linModelo->clear();
    ui.linMarca->clear();
    ui.linModComp->clear();
    ui.linPrecio->clear();
    ui.linStock->clear();
    ui.txtDesc->clear();
    ui.txtObs->clear();
}

void ProyectoAquamarine::clearSaleForm()
{
    // Limpiamos el formulario para que una venta nueva no arrastre datos viejos.
    ui.linVenderCant->clear();
    ui.linVenderCliente->clear();
    ui.linVenderPago->clear();
    ui.linVendeEnvio->clear();
    ui.txtVenderObs->clear();
}

void ProyectoAquamarine::clearSaleEditForm()
{
    ventaSeleccionadaId = -1;
    ui.dateRegActual->setDateTime(QDateTime::currentDateTime());
    ui.dateRegNuevo->setDateTime(QDateTime::currentDateTime());
    ui.linRegClieActual->clear();
    ui.linRegClieNuevo->clear();
    ui.linRegSKUActual->clear();
    ui.linRegSKUNuevo->clear();
    ui.linRegCantActual->clear();
    ui.linRegCantNuevo->clear();
    ui.linRegPrecioActual->clear();
    ui.linRegPrecioNuevo->clear();
    ui.linRegPrecioMLActual->clear();
    ui.linRegPrecioMLNuevo->clear();
    ui.linRegPagoActual->clear();
    ui.linRegPagoNuevo->clear();
    ui.linRegEnvioActual->clear();
    ui.linRegEnvioNuevo->clear();
    ui.txtRegObsActual->clear();
    ui.txtRegObsNuevo->clear();
}

void ProyectoAquamarine::clearRepairForm()
{
    reparacionSeleccionadaId = -1;
    editandoReparacion = false;
    dateRepairIngreso->setDateTime(QDateTime::currentDateTime());
    linRepairCliente->clear();
    linRepairTipo->clear();
    linRepairModelo->clear();
    linRepairEquipo->clear();
    linRepairManoObra->clear();
    linRepairTiempo->clear();
    linRepairEstado->clear();
    txtRepairObservaciones->clear();
}

void ProyectoAquamarine::populateSaleEditForm(const Venta& venta)
{
    ventaSeleccionadaId = venta.getId();
    ui.dateRegActual->setDateTime(venta.getFechaHora());
    ui.dateRegNuevo->setDateTime(venta.getFechaHora());
    ui.linRegClieActual->setText(venta.getCliente());
    ui.linRegClieNuevo->setText(venta.getCliente());
    ui.linRegSKUActual->setText(venta.getSku());
    ui.linRegSKUNuevo->setText(venta.getSku());
    ui.linRegCantActual->setText(QString::number(venta.getCantidad()));
    ui.linRegCantNuevo->setText(QString::number(venta.getCantidad()));
    ui.linRegPrecioActual->setText(QString::number(venta.getPrecioUnitario(), 'f', 2));
    ui.linRegPrecioNuevo->setText(QString::number(venta.getPrecioUnitario(), 'f', 2));
    ui.linRegPrecioMLActual->setText(QString::number(venta.getPrecioML(), 'f', 2));
    ui.linRegPrecioMLNuevo->setText(QString::number(venta.getPrecioML(), 'f', 2));
    ui.linRegPagoActual->setText(venta.getFormaPago());
    ui.linRegPagoNuevo->setText(venta.getFormaPago());
    ui.linRegEnvioActual->setText(venta.getEnvio());
    ui.linRegEnvioNuevo->setText(venta.getEnvio());
    ui.txtRegObsActual->setPlainText(venta.getObservaciones());
    ui.txtRegObsNuevo->setPlainText(venta.getObservaciones());
}

void ProyectoAquamarine::populateRepairForm(const Reparacion& reparacion)
{
    reparacionSeleccionadaId = reparacion.getId();
    editandoReparacion = true;
    dateRepairIngreso->setDateTime(reparacion.getFechaIngreso());
    linRepairCliente->setText(reparacion.getCliente());
    linRepairTipo->setText(reparacion.getTipoReparacion());
    linRepairModelo->setText(reparacion.getModeloDispositivo());
    linRepairEquipo->setText(reparacion.getDetalleReparacion());
    linRepairManoObra->setText(QString::number(reparacion.getManoObra(), 'f', 2));
    linRepairTiempo->setText(reparacion.getTiempoTrabajo());
    linRepairEstado->setText(reparacion.getEstado());
    txtRepairObservaciones->setPlainText(reparacion.getObservaciones());
}

bool ProyectoAquamarine::buildProductFromForm(Producto& producto, QString& errorMessage) const
{
    // Leemos los widgets y los convertimos a un objeto de dominio.
    const QString nombre = ui.linNombre->text().trimmed();
    const QString sku = ui.linSKU->text().trimmed();
    const QString codigoBarras = linCodigoBarras != nullptr ? linCodigoBarras->text().trimmed() : QString();
    const QString modelo = ui.linModelo->text().trimmed();
    const QString marca = ui.linMarca->text().trimmed();
    const QString descripcion = ui.txtDesc->toPlainText().trimmed();
    const QString modeloComp = ui.linModComp->text().trimmed();
    const QString observaciones = ui.txtObs->toPlainText().trimmed();
    const int stock = ui.linStock->text().toInt();
    const double precio = ui.linPrecio->text().toDouble();

    if (nombre.isEmpty() || sku.isEmpty()) {
        errorMessage = "Nombre y SKU son obligatorios.";
        return false;
    }

    if (!codigoBarras.isEmpty() && !QRegularExpression("^\\d+$").match(codigoBarras).hasMatch()) {
        errorMessage = "El codigo de barras solo puede tener numeros.";
        return false;
    }

    if (precio <= 0.0) {
        errorMessage = "El precio debe ser mayor a cero.";
        return false;
    }

    producto = Producto(
        nombre,
        descripcion,
        sku,
        codigoBarras,
        modelo,
        marca,
        modeloComp,
        observaciones,
        stock,
        precio);

    return true;
}

bool ProyectoAquamarine::buildSaleFromEditForm(Venta& venta, QString& errorMessage) const
{
    // Esta funcion traduce la UI de edicion a una Venta lista para validar/guardar.
    const QString cliente = ui.linRegClieNuevo->text().trimmed();
    const QString sku = ui.linRegSKUNuevo->text().trimmed();
    const int cantidad = ui.linRegCantNuevo->text().toInt();
    const double precio = ui.linRegPrecioNuevo->text().toDouble();
    const double precioML = ui.linRegPrecioMLNuevo->text().toDouble();
    const QString pago = ui.linRegPagoNuevo->text().trimmed();
    const QString envio = ui.linRegEnvioNuevo->text().trimmed();
    const QString observaciones = ui.txtRegObsNuevo->toPlainText().trimmed();

    if (cliente.isEmpty() || sku.isEmpty() || pago.isEmpty() || envio.isEmpty()) {
        errorMessage = "Completa cliente, SKU, pago y envio.";
        return false;
    }

    if (cantidad <= 0) {
        errorMessage = "La cantidad debe ser mayor a cero.";
        return false;
    }

    if (precio <= 0.0 || precioML <= 0.0) {
        errorMessage = "Precio y precio ML deben ser mayores a cero.";
        return false;
    }

    venta.setFechaHora(ui.dateRegNuevo->dateTime());
    venta.setCliente(cliente);
    venta.setSku(sku);
    venta.setCantidad(cantidad);
    venta.setPrecioUnitario(precio);
    venta.setPrecioML(precioML);
    venta.setFormaPago(pago);
    venta.setEnvio(envio);
    venta.setObservaciones(observaciones);
    return true;
}

bool ProyectoAquamarine::buildRepairFromForm(Reparacion& reparacion, QString& errorMessage) const
{
    const double manoObra = linRepairManoObra->text().trimmed().isEmpty() ? 0.0 : linRepairManoObra->text().toDouble();

    reparacion.setFechaIngreso(dateRepairIngreso->dateTime());
    reparacion.setCliente(normalizedOptionalText(linRepairCliente->text()));
    reparacion.setTipoReparacion(normalizedOptionalText(linRepairTipo->text()));
    reparacion.setModeloDispositivo(normalizedOptionalText(linRepairModelo->text()));
    reparacion.setDetalleReparacion(normalizedOptionalText(linRepairEquipo->text()));
    reparacion.setManoObra(manoObra);
    reparacion.setTiempoTrabajo(normalizedOptionalText(linRepairTiempo->text()));
    reparacion.setObservaciones(normalizedOptionalText(txtRepairObservaciones->toPlainText()));
    reparacion.setEstado(normalizedOptionalText(linRepairEstado->text()));

    if (!reparacion.getFechaIngreso().isValid()) {
        errorMessage = "La fecha de ingreso no es valida.";
        return false;
    }

    return true;
}

void ProyectoAquamarine::setCurrentProduct(const QString& sku)
{
    productoSeleccionadoSku = sku;
}

bool ProyectoAquamarine::requestAdminAccess()
{
    // Cambia esta contrasena cuando quieras desde un unico lugar.
    const QString adminPassword = "crmov2026";

    bool accepted = false;
    const QString password = QInputDialog::getText(
        this,
        "Acceso admin",
        "Contrasena del panel SQLite:",
        QLineEdit::Password,
        QString(),
        &accepted);

    if (!accepted) {
        return false;
    }

    if (password != adminPassword) {
        QMessageBox::warning(this, "Acceso admin", "Contrasena incorrecta.");
        return false;
    }

    return true;
}

void ProyectoAquamarine::refreshAdminHelpText()
{
    if (adminInfoLabel != nullptr) {
        adminInfoLabel->setText(
            "Base actual: " + databaseManager->path() +
            "\nAtajo oculto: Ctrl+Alt+S");
    }

    if (adminHintLabel != nullptr) {
        adminHintLabel->setText(
            "Consultas utiles:\n"
            "SELECT sku, codigo_barras, nombre FROM productos;\n"
            "SELECT * FROM ventas;\n"
            "SELECT * FROM reparaciones;\n"
            "SELECT * FROM productos WHERE codigo_barras = '7790000000000';\n"
            "DELETE FROM ventas WHERE id = 1;\n"
            "La contrasena del panel se define en la funcion requestAdminAccess().");
    }
}

void ProyectoAquamarine::renderBrandLogo()
{
    // Banner principal de Aquamarine.
    const QSize targetSize(qMax(ui.lblLogoCRM->width(), 520),
        qMax(ui.lblLogoCRM->height(), 180));

    QPixmap pixmap(targetSize);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::TextAntialiasing, true);

    // Fondo
    QLinearGradient background(0, 0, targetSize.width(), targetSize.height());
    background.setColorAt(0.0, QColor("#081018"));
    background.setColorAt(1.0, QColor("#10222d"));

    painter.setPen(Qt::NoPen);
    painter.setBrush(background);
    painter.drawRoundedRect(pixmap.rect().adjusted(4, 4, -4, -4), 24, 24);

    // Título
    QFont titleFont("Segoe UI", 30, QFont::Bold);
    painter.setFont(titleFont);
    painter.setPen(QColor("#f2fbff"));

    painter.drawText(
        QRect(40, 45, targetSize.width() - 80, 50),
        Qt::AlignCenter,
        "Aquamarine");

    // Subtítulo
    QFont subtitleFont("Segoe UI", 11, QFont::Medium);
    painter.setFont(subtitleFont);
    painter.setPen(QColor("#b7d7df"));

    painter.drawText(
        QRect(40, 92, targetSize.width() - 80, 24),
        Qt::AlignCenter,
        "Inventory, sales and repair management");

    // Línea decorativa
    painter.setPen(QPen(QColor("#69ead8"), 3));
    painter.drawLine(
        (targetSize.width() / 2) - 110,
        128,
        (targetSize.width() / 2) + 110,
        128);

    // Firma
    QFont signatureFont("Segoe UI", 9, QFont::Medium);
    painter.setFont(signatureFont);
    painter.setPen(QColor("#8ea8b0"));

    painter.drawText(
        QRect(40, 140, targetSize.width() - 80, 20),
        Qt::AlignCenter,
        "by Nani220 & Codex");

    ui.lblLogoCRM->setText(QString());
    ui.lblLogoCRM->setMinimumHeight(180);
    ui.lblLogoCRM->setPixmap(pixmap);
    ui.lblLogoCRM->setScaledContents(false);
}

void ProyectoAquamarine::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);
    renderBrandLogo();
}

void ProyectoAquamarine::on_btnAgregar_clicked()
{
    // Entramos en modo alta de producto.
    editandoProducto = false;
    productoEnEdicionSku.clear();
    clearProductForm();
    ui.stkPestanias->setCurrentWidget(ui.pagAgregar);
    ui.statusBar->showMessage("Nuevo producto.");
}

void ProyectoAquamarine::on_btnBuscar_clicked()
{
    // La busqueda carga el producto en la pagina de detalle y lo deja seleccionado.
    if (ui.linBuscar->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Busqueda", "Ingresa un SKU o codigo de barras para buscar.");
        return;
    }

    const QString criterio = ui.linBuscar->text().trimmed();
    Producto* productoEncontrado = inven->buscarProductoPorSku(criterio);
    if (productoEncontrado == nullptr) {
        productoEncontrado = inven->buscarProductoPorCodigoBarras(criterio);
    }

    if (productoEncontrado == nullptr) {
        QMessageBox::information(this, "Producto", "No se encontro un producto con ese SKU o codigo de barras.");
        ui.linBuscar->clear();
        return;
    }

    setCurrentProduct(productoEncontrado->getSku());
    showProductDetails(*productoEncontrado);
    ui.linBuscar->clear();
    ui.stkPestanias->setCurrentWidget(ui.pagInfoProdu);
    addLog("Consulta de producto: " + productoEncontrado->getSku());
}

void ProyectoAquamarine::on_btnConsProd_clicked()
{
    ui.stkPestanias->setCurrentWidget(ui.pagBuscar);
}

void ProyectoAquamarine::on_btnConsVen_clicked()
{
    refreshSalesTable();
    ui.stkPestanias->setCurrentWidget(ui.pagVentas);
}

void ProyectoAquamarine::on_btnConsInv_clicked()
{
    refreshInventoryTable();
    ui.stkPestanias->setCurrentWidget(ui.pagInventario);
}

void ProyectoAquamarine::on_btnBorrarVenta_clicked()
{
    if (ventaSeleccionadaId < 0) {
        QMessageBox::warning(this, "Ventas", "Primero busca una venta por ID.");
        return;
    }

    if (!inven->eliminarVenta(ventaSeleccionadaId)) {
        QMessageBox::warning(this, "Ventas", "No se pudo borrar la venta.");
        return;
    }

    persistData();
    refreshViews();
    addLog("Venta eliminada: ID " + QString::number(ventaSeleccionadaId));
    clearSaleEditForm();
    volverFuncion();
}

void ProyectoAquamarine::on_btnBuscarID_clicked()
{
    const int id = ui.linBuscarID->text().trimmed().toInt();
    Venta* venta = inven->buscarVentaPorId(id);
    if (venta == nullptr) {
        QMessageBox::information(this, "Ventas", "No existe una venta con ese ID.");
        return;
    }

    populateSaleEditForm(*venta);
    ui.stkPestanias->setCurrentWidget(ui.pagEditarVenta);
    addLog("Edicion de venta abierta: ID " + QString::number(id));
}

void ProyectoAquamarine::on_btnDialAgregar_rejected()
{
    clearProductForm();
    volverFuncion();
}

void ProyectoAquamarine::on_btnDialAgregar_accepted()
{
    // El mismo formulario sirve para crear y para editar. La bandera define el comportamiento.
    QString errorMessage;
    Producto producto;
    if (!buildProductFromForm(producto, errorMessage)) {
        QMessageBox::warning(this, "Producto", errorMessage);
        return;
    }

    bool ok = false;
    if (editandoProducto) {
        ok = inven->actualizarProducto(productoEnEdicionSku, producto);
    } else {
        ok = inven->agregarProducto(producto);
    }

    if (!ok) {
        QMessageBox::warning(
            this,
            "Producto",
            editandoProducto
                ? "No se pudo actualizar. Revisa si cambiaste el SKU por uno repetido o si el producto ya tiene ventas."
                : "No se pudo agregar. Revisa si el SKU o el codigo de barras ya existen.");
        return;
    }

    persistData();
    refreshViews();
    setCurrentProduct(producto.getSku());
    showProductDetails(producto);
    addLog((editandoProducto ? "Producto actualizado: " : "Producto agregado: ") + producto.getSku());
    clearProductForm();
    editandoProducto = false;
    productoEnEdicionSku.clear();
    ui.stkPestanias->setCurrentWidget(ui.pagInfoProdu);
}

void ProyectoAquamarine::on_btnDialEditVenta_rejected()
{
    clearSaleEditForm();
    volverFuncion();
}

void ProyectoAquamarine::on_btnDialEditVenta_accepted()
{
    // Guardamos los cambios de una venta ya existente y recalculamos stock si hace falta.
    if (ventaSeleccionadaId < 0) {
        QMessageBox::warning(this, "Ventas", "Primero busca una venta.");
        return;
    }

    QString errorMessage;
    Venta venta;
    if (!buildSaleFromEditForm(venta, errorMessage)) {
        QMessageBox::warning(this, "Ventas", errorMessage);
        return;
    }

    if (!inven->actualizarVenta(ventaSeleccionadaId, venta)) {
        QMessageBox::warning(this, "Ventas", "No se pudo actualizar la venta. Revisa SKU y stock disponible.");
        return;
    }

    persistData();
    refreshViews();
    addLog("Venta actualizada: ID " + QString::number(ventaSeleccionadaId));
    volverFuncion();
}

void ProyectoAquamarine::on_btnDialVender_rejected()
{
    clearSaleForm();
    ui.stkPestanias->setCurrentWidget(ui.pagInfoProdu);
}

void ProyectoAquamarine::on_btnDialVender_accepted()
{
    // Registrar una venta descuenta stock y genera un ID automatico.
    if (productoSeleccionadoSku.isEmpty()) {
        QMessageBox::warning(this, "Ventas", "Primero selecciona un producto.");
        return;
    }

    const int cantidad = ui.linVenderCant->text().toInt();
    const QString cliente = ui.linVenderCliente->text().trimmed();
    const QString pago = ui.linVenderPago->text().trimmed();
    const QString envio = ui.linVendeEnvio->text().trimmed();
    const QString observaciones = ui.txtVenderObs->toPlainText().trimmed();

    Venta ventaCreada;
    if (!inven->registrarVenta(productoSeleccionadoSku, cantidad, cliente, pago, envio, observaciones, &ventaCreada)) {
        QMessageBox::warning(this, "Ventas", "No se pudo registrar la venta. Revisa stock y campos obligatorios.");
        return;
    }

    persistData();
    refreshViews();

    Producto* producto = inven->buscarProductoPorSku(productoSeleccionadoSku);
    if (producto != nullptr) {
        showProductDetails(*producto);
    }

    clearSaleForm();
    addLog("Venta registrada: ID " + QString::number(ventaCreada.getId()));
    ui.stkPestanias->setCurrentWidget(ui.pagVentas);
}

void ProyectoAquamarine::volverFuncion()
{
    ui.stkPestanias->setCurrentWidget(ui.pagPrincipal);
    ui.statusBar->showMessage("Menu principal.");
}

void ProyectoAquamarine::on_btnSalir_clicked()
{
    persistData();
    close();
}

void ProyectoAquamarine::on_btnEditarVenta_clicked()
{
    clearSaleEditForm();
    ui.linBuscarID->clear();
    ui.stkPestanias->setCurrentWidget(ui.pagBuscarVenta);
}

void ProyectoAquamarine::on_btnEditarVen_clicked()
{
    on_btnEditarVenta_clicked();
}

void ProyectoAquamarine::on_btnVender_clicked()
{
    if (productoSeleccionadoSku.isEmpty()) {
        QMessageBox::warning(this, "Ventas", "Primero busca un producto.");
        return;
    }

    clearSaleForm();
    ui.stkPestanias->setCurrentWidget(ui.pagVender);
}

void ProyectoAquamarine::on_btnEditar_clicked()
{
    Producto* producto = inven->buscarProductoPorSku(productoSeleccionadoSku);
    if (producto == nullptr) {
        QMessageBox::warning(this, "Producto", "Primero busca un producto.");
        return;
    }

    editandoProducto = true;
    productoEnEdicionSku = producto->getSku();
    ui.linNombre->setText(producto->getNombre());
    ui.linSKU->setText(producto->getSku());
    if (linCodigoBarras != nullptr) {
        linCodigoBarras->setText(producto->getCodigoBarras());
    }
    ui.linModelo->setText(producto->getModelo());
    ui.linMarca->setText(producto->getMarca());
    ui.linModComp->setText(producto->getModeloComp());
    ui.linPrecio->setText(QString::number(producto->getPrecio(), 'f', 2));
    ui.linStock->setText(QString::number(producto->getStock()));
    ui.txtDesc->setPlainText(producto->getDescripcion());
    ui.txtObs->setPlainText(producto->getObserv());
    ui.stkPestanias->setCurrentWidget(ui.pagAgregar);
}

void ProyectoAquamarine::on_btnBorrar_clicked()
{
    if (productoSeleccionadoSku.isEmpty()) {
        QMessageBox::warning(this, "Producto", "Primero busca un producto.");
        return;
    }

    if (!inven->eliminarProducto(productoSeleccionadoSku)) {
        QMessageBox::warning(
            this,
            "Producto",
            "No se puede borrar el producto. Puede no existir o ya tener ventas asociadas.");
        return;
    }

    persistData();
    refreshViews();
    addLog("Producto eliminado: " + productoSeleccionadoSku);
    productoSeleccionadoSku.clear();
    volverFuncion();
}

void ProyectoAquamarine::openAdminPanel()
{
    // Punto de entrada del panel oculto.
    if (!requestAdminAccess()) {
        return;
    }

    refreshAdminHelpText();
    ui.stkPestanias->setCurrentWidget(adminPage);
    ui.statusBar->showMessage("Panel admin SQLite.");
}

void ProyectoAquamarine::markSelectedSaleAsPaid()
{
    const int row = ui.tblVentas->currentRow();
    if (row < 0 || ui.tblVentas->item(row, 0) == nullptr) {
        QMessageBox::information(this, "Pago proveedor", "Selecciona una venta en la tabla.");
        return;
    }

    const int id = ui.tblVentas->item(row, 0)->text().toInt();
    Venta* venta = inven->buscarVentaPorId(id);
    if (venta == nullptr) {
        QMessageBox::warning(this, "Pago proveedor", "No se encontro la venta seleccionada.");
        return;
    }

    if (venta->getPagadaProveedor()) {
        QMessageBox::information(this, "Pago proveedor", "Esa venta ya esta marcada como pagada.");
        return;
    }

    bool accepted = false;
    const double montoPago = QInputDialog::getDouble(
        this,
        "Pago al proveedor",
        "Monto pagado al proveedor:",
        venta->getPrecioUnitario() * venta->getCantidad(),
        0.0,
        999999999.0,
        2,
        &accepted);

    if (!accepted) {
        return;
    }

    if (!inven->marcarVentaComoPagadaProveedor(id, montoPago, QDateTime::currentDateTime())) {
        QMessageBox::warning(this, "Pago proveedor", "No se pudo registrar el pago.");
        return;
    }

    persistData();
    refreshViews();
    addLog("Venta pagada al proveedor: ID " + QString::number(id));
    QMessageBox::information(this, "Pago proveedor", "Pago registrado correctamente.");
}

void ProyectoAquamarine::openRepairsPage()
{
    refreshRepairsTable();
    ui.stkPestanias->setCurrentWidget(repairsPage);
}

void ProyectoAquamarine::openNewRepairForm()
{
    clearRepairForm();
    ui.stkPestanias->setCurrentWidget(repairFormPage);
}

void ProyectoAquamarine::openEditRepairForm()
{
    const int row = tblReparaciones->currentRow();
    if (row < 0 || tblReparaciones->item(row, 0) == nullptr) {
        QMessageBox::information(this, "Reparaciones", "Selecciona una reparacion en la tabla.");
        return;
    }

    const int id = tblReparaciones->item(row, 0)->text().toInt();
    Reparacion* reparacion = inven->buscarReparacionPorId(id);
    if (reparacion == nullptr) {
        QMessageBox::warning(this, "Reparaciones", "No se encontro la reparacion.");
        return;
    }

    populateRepairForm(*reparacion);
    ui.stkPestanias->setCurrentWidget(repairFormPage);
}

void ProyectoAquamarine::saveRepairForm()
{
    QString errorMessage;
    Reparacion reparacion;
    if (!buildRepairFromForm(reparacion, errorMessage)) {
        QMessageBox::warning(this, "Reparaciones", errorMessage);
        return;
    }

    bool ok = false;
    if (editandoReparacion) {
        ok = inven->actualizarReparacion(reparacionSeleccionadaId, reparacion);
    } else {
        ok = inven->agregarReparacion(reparacion);
    }

    if (!ok) {
        QMessageBox::warning(this, "Reparaciones", "No se pudo guardar la reparacion.");
        return;
    }

    persistData();
    refreshViews();
    addLog(editandoReparacion ? "Reparacion actualizada." : "Reparacion registrada.");
    clearRepairForm();
    ui.stkPestanias->setCurrentWidget(repairsPage);
}

void ProyectoAquamarine::cancelRepairForm()
{
    clearRepairForm();
    ui.stkPestanias->setCurrentWidget(repairsPage);
}

void ProyectoAquamarine::deleteSelectedRepair()
{
    const int row = tblReparaciones->currentRow();
    if (row < 0 || tblReparaciones->item(row, 0) == nullptr) {
        QMessageBox::information(this, "Reparaciones", "Selecciona una reparacion.");
        return;
    }

    const int id = tblReparaciones->item(row, 0)->text().toInt();
    if (!inven->eliminarReparacion(id)) {
        QMessageBox::warning(this, "Reparaciones", "No se pudo borrar la reparacion.");
        return;
    }

    persistData();
    refreshViews();
    addLog("Reparacion eliminada: ID " + QString::number(id));
}

void ProyectoAquamarine::runAdminQuery()
{
    // Ejecuta SQL manual desde el panel admin.
    if (!databaseManager->isAvailable()) {
        QMessageBox::warning(this, "Admin SQLite", "SQLite no esta disponible.");
        return;
    }

    const QString sql = adminSqlEditor->toPlainText().trimmed();
    if (sql.isEmpty()) {
        QMessageBox::information(this, "Admin SQLite", "Escribe una consulta SQL.");
        return;
    }

    adminResultsTable->clear();
    adminResultsTable->setRowCount(0);
    adminResultsTable->setColumnCount(0);

    if (sql.startsWith("select", Qt::CaseInsensitive) || sql.startsWith("pragma", Qt::CaseInsensitive)) {
        QStringList headers;
        std::vector<QStringList> rows;
        if (!databaseManager->executeSelect(sql, headers, rows)) {
            QMessageBox::warning(this, "Admin SQLite", databaseManager->lastError());
            return;
        }

        adminResultsTable->setColumnCount(headers.size());
        adminResultsTable->setHorizontalHeaderLabels(headers);
        adminResultsTable->setRowCount(static_cast<int>(rows.size()));

        for (int row = 0; row < static_cast<int>(rows.size()); ++row) {
            for (int column = 0; column < rows[row].size(); ++column) {
                adminResultsTable->setItem(row, column, new QTableWidgetItem(rows[row][column]));
            }
        }

        addLog("Admin SQL ejecutado: consulta SELECT/PRAGMA");
        ui.statusBar->showMessage("Consulta SQL ejecutada.");
        return;
    }

    // Para INSERT/UPDATE/DELETE usamos el camino general.
    int affectedRows = 0;
    if (!databaseManager->executeStatement(sql, affectedRows)) {
        QMessageBox::warning(this, "Admin SQLite", databaseManager->lastError());
        return;
    }

    loadData();
    refreshViews();
    QMessageBox::information(
        this,
        "Admin SQLite",
        "Consulta ejecutada correctamente.\nFilas afectadas: " + QString::number(affectedRows));
    addLog("Admin SQL ejecutado: sentencia general");
}

void ProyectoAquamarine::resetAdminDatabase()
{
    // Accion fuerte: borra todos los datos pero deja las tablas listas.
    if (!databaseManager->isAvailable()) {
        QMessageBox::warning(this, "Admin SQLite", "SQLite no esta disponible.");
        return;
    }

    const QMessageBox::StandardButton answer = QMessageBox::warning(
        this,
        "Vaciar base",
        "Esto borrara TODOS los productos y ventas guardados.\n\nDeseas continuar?",
        QMessageBox::Yes | QMessageBox::No,
        QMessageBox::No);

    if (answer != QMessageBox::Yes) {
        return;
    }

    if (!databaseManager->resetDatabase()) {
        QMessageBox::warning(this, "Admin SQLite", databaseManager->lastError());
        return;
    }

    inven->cargarDatos({}, {}, {});
    refreshViews();
    clearProductForm();
    clearSaleForm();
    clearSaleEditForm();
    clearRepairForm();
    productoSeleccionadoSku.clear();
    productoEnEdicionSku.clear();
    adminResultsTable->clear();
    adminResultsTable->setRowCount(0);
    adminResultsTable->setColumnCount(0);
    addLog("Base SQLite vaciada desde admin.");
    QMessageBox::information(this, "Admin SQLite", "La base se vacio correctamente.");
}

QString ProyectoAquamarine::normalizedOptionalText(const QString& value) const
{
    const QString trimmed = value.trimmed();
    return trimmed.isEmpty() ? "NULL" : trimmed;
}
