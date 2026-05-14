/********************************************************************************
** Form generated from reading UI file 'ProyectoAquamarine.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROYECTOAQUAMARINE_H
#define UI_PROYECTOAQUAMARINE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProyectoAquamarineClass
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    QStackedWidget *stkPestanias;
    QWidget *pagPrincipal;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QLabel *lblLogoCRM;
    QListView *listLog;
    QPushButton *btnConsInv;
    QPushButton *btnConsProd;
    QPushButton *btnSalir;
    QPushButton *btnConsVen;
    QPushButton *btnAgregar;
    QPushButton *btnEditarVen;
    QWidget *pagVentas;
    QVBoxLayout *verticalLayout_4;
    QPushButton *btnVolver;
    QTableWidget *tblVentas;
    QPushButton *btnEditarVenta;
    QWidget *pagBuscarVenta;
    QVBoxLayout *verticalLayout_7;
    QPushButton *btnVolver_2;
    QFormLayout *formLayout_4;
    QLineEdit *linBuscarID;
    QPushButton *btnBuscarID;
    QWidget *pagEditarVenta;
    QVBoxLayout *verticalLayout_5;
    QPushButton *btnBorrarVenta;
    QGridLayout *gridLayout_2;
    QLabel *label_25;
    QLabel *label_26;
    QLabel *label_21;
    QLabel *label_27;
    QLabel *label_23;
    QLineEdit *linRegClieNuevo;
    QLabel *label_22;
    QLabel *label_18;
    QLineEdit *linRegClieActual;
    QLabel *label_20;
    QLabel *label_28;
    QDateTimeEdit *dateRegActual;
    QDateTimeEdit *dateRegNuevo;
    QLabel *label_24;
    QLabel *label_19;
    QLabel *label_17;
    QLineEdit *linRegSKUActual;
    QLineEdit *linRegSKUNuevo;
    QLineEdit *linRegCantActual;
    QLineEdit *linRegCantNuevo;
    QLineEdit *linRegPrecioActual;
    QLineEdit *linRegPrecioNuevo;
    QLineEdit *linRegPrecioMLActual;
    QLineEdit *linRegPrecioMLNuevo;
    QLineEdit *linRegPagoActual;
    QLineEdit *linRegPagoNuevo;
    QLineEdit *linRegEnvioActual;
    QLineEdit *linRegEnvioNuevo;
    QTextEdit *txtRegObsActual;
    QTextEdit *txtRegObsNuevo;
    QDialogButtonBox *btnDialEditVenta;
    QWidget *pagBuscar;
    QVBoxLayout *verticalLayout_3;
    QPushButton *btnVolver_3;
    QFormLayout *formLayout_3;
    QPushButton *btnBuscar;
    QLineEdit *linBuscar;
    QWidget *pagInventario;
    QVBoxLayout *verticalLayout_8;
    QPushButton *btnVolver_4;
    QTableWidget *tblInventario;
    QWidget *pagAgregar;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *linNombre;
    QLabel *label_2;
    QLineEdit *linModelo;
    QLabel *label_3;
    QTextEdit *txtDesc;
    QLabel *label_4;
    QLineEdit *linModComp;
    QLabel *label_5;
    QLineEdit *linPrecio;
    QLabel *label_6;
    QLineEdit *linStock;
    QLabel *label_7;
    QTextEdit *txtObs;
    QLabel *label_8;
    QLineEdit *linSKU;
    QDialogButtonBox *btnDialAgregar;
    QLabel *label_34;
    QLineEdit *linMarca;
    QWidget *pagInfoProdu;
    QVBoxLayout *verticalLayout_2;
    QPushButton *btnVolver_5;
    QFormLayout *formLayout_2;
    QLabel *label_9;
    QTextEdit *txtNombre;
    QLabel *label_10;
    QTextEdit *txtSKU;
    QLabel *label_11;
    QTextEdit *txtMod;
    QLabel *label_12;
    QTextEdit *txtDesc_2;
    QLabel *label_13;
    QTextEdit *txtModComp;
    QLabel *label_14;
    QTextEdit *txtPrecio;
    QLabel *label_15;
    QTextEdit *txtStock;
    QLabel *label_16;
    QTextEdit *txtObs_2;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *btnVender;
    QPushButton *btnEditar;
    QPushButton *btnBorrar;
    QWidget *pagVender;
    QVBoxLayout *verticalLayout_6;
    QFormLayout *formLayout_5;
    QLabel *label_29;
    QLabel *label_30;
    QLabel *label_31;
    QLabel *label_32;
    QLabel *label_33;
    QLineEdit *linVenderCant;
    QLineEdit *linVenderCliente;
    QLineEdit *linVenderPago;
    QLineEdit *linVendeEnvio;
    QTextEdit *txtVenderObs;
    QDialogButtonBox *btnDialVender;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ProyectoAquamarineClass)
    {
        if (ProyectoAquamarineClass->objectName().isEmpty())
            ProyectoAquamarineClass->setObjectName("ProyectoAquamarineClass");
        ProyectoAquamarineClass->resize(856, 643);
        centralWidget = new QWidget(ProyectoAquamarineClass);
        centralWidget->setObjectName("centralWidget");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        centralWidget->setMinimumSize(QSize(800, 600));
        centralWidget->setSizeIncrement(QSize(1, 1));
        centralWidget->setCursor(QCursor(Qt::CursorShape::ArrowCursor));
        centralWidget->setMouseTracking(false);
        centralWidget->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        centralWidget->setAutoFillBackground(true);
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        stkPestanias = new QStackedWidget(centralWidget);
        stkPestanias->setObjectName("stkPestanias");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(stkPestanias->sizePolicy().hasHeightForWidth());
        stkPestanias->setSizePolicy(sizePolicy1);
        stkPestanias->setMinimumSize(QSize(800, 600));
        stkPestanias->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        stkPestanias->setFrameShape(QFrame::Shape::WinPanel);
        pagPrincipal = new QWidget();
        pagPrincipal->setObjectName("pagPrincipal");
        horizontalLayout = new QHBoxLayout(pagPrincipal);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
        lblLogoCRM = new QLabel(pagPrincipal);
        lblLogoCRM->setObjectName("lblLogoCRM");

        gridLayout->addWidget(lblLogoCRM, 1, 0, 1, 3);

        listLog = new QListView(pagPrincipal);
        listLog->setObjectName("listLog");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(listLog->sizePolicy().hasHeightForWidth());
        listLog->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(listLog, 0, 3, 3, 1);

        btnConsInv = new QPushButton(pagPrincipal);
        btnConsInv->setObjectName("btnConsInv");
        sizePolicy.setHeightForWidth(btnConsInv->sizePolicy().hasHeightForWidth());
        btnConsInv->setSizePolicy(sizePolicy);
        btnConsInv->setMinimumSize(QSize(200, 100));

        gridLayout->addWidget(btnConsInv, 2, 0, 1, 1);

        btnConsProd = new QPushButton(pagPrincipal);
        btnConsProd->setObjectName("btnConsProd");
        sizePolicy.setHeightForWidth(btnConsProd->sizePolicy().hasHeightForWidth());
        btnConsProd->setSizePolicy(sizePolicy);
        btnConsProd->setMinimumSize(QSize(200, 100));

        gridLayout->addWidget(btnConsProd, 2, 1, 1, 1);

        btnSalir = new QPushButton(pagPrincipal);
        btnSalir->setObjectName("btnSalir");

        gridLayout->addWidget(btnSalir, 3, 3, 1, 1);

        btnConsVen = new QPushButton(pagPrincipal);
        btnConsVen->setObjectName("btnConsVen");
        sizePolicy.setHeightForWidth(btnConsVen->sizePolicy().hasHeightForWidth());
        btnConsVen->setSizePolicy(sizePolicy);
        btnConsVen->setMinimumSize(QSize(200, 100));

        gridLayout->addWidget(btnConsVen, 2, 2, 1, 1);

        btnAgregar = new QPushButton(pagPrincipal);
        btnAgregar->setObjectName("btnAgregar");
        sizePolicy.setHeightForWidth(btnAgregar->sizePolicy().hasHeightForWidth());
        btnAgregar->setSizePolicy(sizePolicy);
        btnAgregar->setMinimumSize(QSize(200, 100));

        gridLayout->addWidget(btnAgregar, 0, 0, 1, 2);

        btnEditarVen = new QPushButton(pagPrincipal);
        btnEditarVen->setObjectName("btnEditarVen");
        sizePolicy.setHeightForWidth(btnEditarVen->sizePolicy().hasHeightForWidth());
        btnEditarVen->setSizePolicy(sizePolicy);
        btnEditarVen->setMinimumSize(QSize(200, 100));

        gridLayout->addWidget(btnEditarVen, 0, 2, 1, 1);


        horizontalLayout->addLayout(gridLayout);

        stkPestanias->addWidget(pagPrincipal);
        pagVentas = new QWidget();
        pagVentas->setObjectName("pagVentas");
        verticalLayout_4 = new QVBoxLayout(pagVentas);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName("verticalLayout_4");
        btnVolver = new QPushButton(pagVentas);
        btnVolver->setObjectName("btnVolver");
        sizePolicy.setHeightForWidth(btnVolver->sizePolicy().hasHeightForWidth());
        btnVolver->setSizePolicy(sizePolicy);

        verticalLayout_4->addWidget(btnVolver);

        tblVentas = new QTableWidget(pagVentas);
        tblVentas->setObjectName("tblVentas");

        verticalLayout_4->addWidget(tblVentas);

        btnEditarVenta = new QPushButton(pagVentas);
        btnEditarVenta->setObjectName("btnEditarVenta");

        verticalLayout_4->addWidget(btnEditarVenta);

        stkPestanias->addWidget(pagVentas);
        pagBuscarVenta = new QWidget();
        pagBuscarVenta->setObjectName("pagBuscarVenta");
        verticalLayout_7 = new QVBoxLayout(pagBuscarVenta);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName("verticalLayout_7");
        btnVolver_2 = new QPushButton(pagBuscarVenta);
        btnVolver_2->setObjectName("btnVolver_2");
        sizePolicy.setHeightForWidth(btnVolver_2->sizePolicy().hasHeightForWidth());
        btnVolver_2->setSizePolicy(sizePolicy);

        verticalLayout_7->addWidget(btnVolver_2);

        formLayout_4 = new QFormLayout();
        formLayout_4->setSpacing(6);
        formLayout_4->setObjectName("formLayout_4");
        formLayout_4->setLabelAlignment(Qt::AlignmentFlag::AlignCenter);
        formLayout_4->setFormAlignment(Qt::AlignmentFlag::AlignCenter);
        linBuscarID = new QLineEdit(pagBuscarVenta);
        linBuscarID->setObjectName("linBuscarID");

        formLayout_4->setWidget(0, QFormLayout::ItemRole::LabelRole, linBuscarID);

        btnBuscarID = new QPushButton(pagBuscarVenta);
        btnBuscarID->setObjectName("btnBuscarID");
        sizePolicy.setHeightForWidth(btnBuscarID->sizePolicy().hasHeightForWidth());
        btnBuscarID->setSizePolicy(sizePolicy);

        formLayout_4->setWidget(0, QFormLayout::ItemRole::FieldRole, btnBuscarID);


        verticalLayout_7->addLayout(formLayout_4);

        stkPestanias->addWidget(pagBuscarVenta);
        pagEditarVenta = new QWidget();
        pagEditarVenta->setObjectName("pagEditarVenta");
        verticalLayout_5 = new QVBoxLayout(pagEditarVenta);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName("verticalLayout_5");
        btnBorrarVenta = new QPushButton(pagEditarVenta);
        btnBorrarVenta->setObjectName("btnBorrarVenta");

        verticalLayout_5->addWidget(btnBorrarVenta);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName("gridLayout_2");
        label_25 = new QLabel(pagEditarVenta);
        label_25->setObjectName("label_25");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label_25->sizePolicy().hasHeightForWidth());
        label_25->setSizePolicy(sizePolicy3);

        gridLayout_2->addWidget(label_25, 8, 0, 1, 1);

        label_26 = new QLabel(pagEditarVenta);
        label_26->setObjectName("label_26");
        sizePolicy3.setHeightForWidth(label_26->sizePolicy().hasHeightForWidth());
        label_26->setSizePolicy(sizePolicy3);

        gridLayout_2->addWidget(label_26, 9, 0, 1, 1);

        label_21 = new QLabel(pagEditarVenta);
        label_21->setObjectName("label_21");
        sizePolicy3.setHeightForWidth(label_21->sizePolicy().hasHeightForWidth());
        label_21->setSizePolicy(sizePolicy3);

        gridLayout_2->addWidget(label_21, 3, 0, 1, 1);

        label_27 = new QLabel(pagEditarVenta);
        label_27->setObjectName("label_27");
        sizePolicy3.setHeightForWidth(label_27->sizePolicy().hasHeightForWidth());
        label_27->setSizePolicy(sizePolicy3);

        gridLayout_2->addWidget(label_27, 5, 0, 1, 1);

        label_23 = new QLabel(pagEditarVenta);
        label_23->setObjectName("label_23");
        sizePolicy3.setHeightForWidth(label_23->sizePolicy().hasHeightForWidth());
        label_23->setSizePolicy(sizePolicy3);

        gridLayout_2->addWidget(label_23, 6, 0, 1, 1);

        linRegClieNuevo = new QLineEdit(pagEditarVenta);
        linRegClieNuevo->setObjectName("linRegClieNuevo");

        gridLayout_2->addWidget(linRegClieNuevo, 3, 2, 1, 1);

        label_22 = new QLabel(pagEditarVenta);
        label_22->setObjectName("label_22");
        sizePolicy3.setHeightForWidth(label_22->sizePolicy().hasHeightForWidth());
        label_22->setSizePolicy(sizePolicy3);

        gridLayout_2->addWidget(label_22, 4, 0, 1, 1);

        label_18 = new QLabel(pagEditarVenta);
        label_18->setObjectName("label_18");

        gridLayout_2->addWidget(label_18, 0, 1, 1, 1);

        linRegClieActual = new QLineEdit(pagEditarVenta);
        linRegClieActual->setObjectName("linRegClieActual");

        gridLayout_2->addWidget(linRegClieActual, 3, 1, 1, 1);

        label_20 = new QLabel(pagEditarVenta);
        label_20->setObjectName("label_20");
        sizePolicy3.setHeightForWidth(label_20->sizePolicy().hasHeightForWidth());
        label_20->setSizePolicy(sizePolicy3);

        gridLayout_2->addWidget(label_20, 1, 0, 1, 1);

        label_28 = new QLabel(pagEditarVenta);
        label_28->setObjectName("label_28");
        sizePolicy3.setHeightForWidth(label_28->sizePolicy().hasHeightForWidth());
        label_28->setSizePolicy(sizePolicy3);

        gridLayout_2->addWidget(label_28, 10, 0, 1, 1);

        dateRegActual = new QDateTimeEdit(pagEditarVenta);
        dateRegActual->setObjectName("dateRegActual");
        sizePolicy.setHeightForWidth(dateRegActual->sizePolicy().hasHeightForWidth());
        dateRegActual->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(dateRegActual, 1, 1, 1, 1);

        dateRegNuevo = new QDateTimeEdit(pagEditarVenta);
        dateRegNuevo->setObjectName("dateRegNuevo");
        sizePolicy.setHeightForWidth(dateRegNuevo->sizePolicy().hasHeightForWidth());
        dateRegNuevo->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(dateRegNuevo, 1, 2, 1, 1);

        label_24 = new QLabel(pagEditarVenta);
        label_24->setObjectName("label_24");
        sizePolicy3.setHeightForWidth(label_24->sizePolicy().hasHeightForWidth());
        label_24->setSizePolicy(sizePolicy3);

        gridLayout_2->addWidget(label_24, 7, 0, 1, 1);

        label_19 = new QLabel(pagEditarVenta);
        label_19->setObjectName("label_19");

        gridLayout_2->addWidget(label_19, 0, 2, 1, 1);

        label_17 = new QLabel(pagEditarVenta);
        label_17->setObjectName("label_17");

        gridLayout_2->addWidget(label_17, 0, 0, 1, 1);

        linRegSKUActual = new QLineEdit(pagEditarVenta);
        linRegSKUActual->setObjectName("linRegSKUActual");

        gridLayout_2->addWidget(linRegSKUActual, 4, 1, 1, 1);

        linRegSKUNuevo = new QLineEdit(pagEditarVenta);
        linRegSKUNuevo->setObjectName("linRegSKUNuevo");

        gridLayout_2->addWidget(linRegSKUNuevo, 4, 2, 1, 1);

        linRegCantActual = new QLineEdit(pagEditarVenta);
        linRegCantActual->setObjectName("linRegCantActual");

        gridLayout_2->addWidget(linRegCantActual, 5, 1, 1, 1);

        linRegCantNuevo = new QLineEdit(pagEditarVenta);
        linRegCantNuevo->setObjectName("linRegCantNuevo");

        gridLayout_2->addWidget(linRegCantNuevo, 5, 2, 1, 1);

        linRegPrecioActual = new QLineEdit(pagEditarVenta);
        linRegPrecioActual->setObjectName("linRegPrecioActual");

        gridLayout_2->addWidget(linRegPrecioActual, 6, 1, 1, 1);

        linRegPrecioNuevo = new QLineEdit(pagEditarVenta);
        linRegPrecioNuevo->setObjectName("linRegPrecioNuevo");

        gridLayout_2->addWidget(linRegPrecioNuevo, 6, 2, 1, 1);

        linRegPrecioMLActual = new QLineEdit(pagEditarVenta);
        linRegPrecioMLActual->setObjectName("linRegPrecioMLActual");

        gridLayout_2->addWidget(linRegPrecioMLActual, 7, 1, 1, 1);

        linRegPrecioMLNuevo = new QLineEdit(pagEditarVenta);
        linRegPrecioMLNuevo->setObjectName("linRegPrecioMLNuevo");

        gridLayout_2->addWidget(linRegPrecioMLNuevo, 7, 2, 1, 1);

        linRegPagoActual = new QLineEdit(pagEditarVenta);
        linRegPagoActual->setObjectName("linRegPagoActual");

        gridLayout_2->addWidget(linRegPagoActual, 8, 1, 1, 1);

        linRegPagoNuevo = new QLineEdit(pagEditarVenta);
        linRegPagoNuevo->setObjectName("linRegPagoNuevo");

        gridLayout_2->addWidget(linRegPagoNuevo, 8, 2, 1, 1);

        linRegEnvioActual = new QLineEdit(pagEditarVenta);
        linRegEnvioActual->setObjectName("linRegEnvioActual");

        gridLayout_2->addWidget(linRegEnvioActual, 9, 1, 1, 1);

        linRegEnvioNuevo = new QLineEdit(pagEditarVenta);
        linRegEnvioNuevo->setObjectName("linRegEnvioNuevo");

        gridLayout_2->addWidget(linRegEnvioNuevo, 9, 2, 1, 1);

        txtRegObsActual = new QTextEdit(pagEditarVenta);
        txtRegObsActual->setObjectName("txtRegObsActual");

        gridLayout_2->addWidget(txtRegObsActual, 10, 1, 1, 1);

        txtRegObsNuevo = new QTextEdit(pagEditarVenta);
        txtRegObsNuevo->setObjectName("txtRegObsNuevo");

        gridLayout_2->addWidget(txtRegObsNuevo, 10, 2, 1, 1);


        verticalLayout_5->addLayout(gridLayout_2);

        btnDialEditVenta = new QDialogButtonBox(pagEditarVenta);
        btnDialEditVenta->setObjectName("btnDialEditVenta");
        sizePolicy1.setHeightForWidth(btnDialEditVenta->sizePolicy().hasHeightForWidth());
        btnDialEditVenta->setSizePolicy(sizePolicy1);
        btnDialEditVenta->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);

        verticalLayout_5->addWidget(btnDialEditVenta);

        stkPestanias->addWidget(pagEditarVenta);
        pagBuscar = new QWidget();
        pagBuscar->setObjectName("pagBuscar");
        verticalLayout_3 = new QVBoxLayout(pagBuscar);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName("verticalLayout_3");
        btnVolver_3 = new QPushButton(pagBuscar);
        btnVolver_3->setObjectName("btnVolver_3");
        sizePolicy.setHeightForWidth(btnVolver_3->sizePolicy().hasHeightForWidth());
        btnVolver_3->setSizePolicy(sizePolicy);

        verticalLayout_3->addWidget(btnVolver_3);

        formLayout_3 = new QFormLayout();
        formLayout_3->setSpacing(6);
        formLayout_3->setObjectName("formLayout_3");
        formLayout_3->setLabelAlignment(Qt::AlignmentFlag::AlignCenter);
        formLayout_3->setFormAlignment(Qt::AlignmentFlag::AlignCenter);
        btnBuscar = new QPushButton(pagBuscar);
        btnBuscar->setObjectName("btnBuscar");
        sizePolicy.setHeightForWidth(btnBuscar->sizePolicy().hasHeightForWidth());
        btnBuscar->setSizePolicy(sizePolicy);

        formLayout_3->setWidget(0, QFormLayout::ItemRole::FieldRole, btnBuscar);

        linBuscar = new QLineEdit(pagBuscar);
        linBuscar->setObjectName("linBuscar");
        sizePolicy.setHeightForWidth(linBuscar->sizePolicy().hasHeightForWidth());
        linBuscar->setSizePolicy(sizePolicy);

        formLayout_3->setWidget(0, QFormLayout::ItemRole::LabelRole, linBuscar);


        verticalLayout_3->addLayout(formLayout_3);

        stkPestanias->addWidget(pagBuscar);
        pagInventario = new QWidget();
        pagInventario->setObjectName("pagInventario");
        verticalLayout_8 = new QVBoxLayout(pagInventario);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName("verticalLayout_8");
        btnVolver_4 = new QPushButton(pagInventario);
        btnVolver_4->setObjectName("btnVolver_4");
        sizePolicy.setHeightForWidth(btnVolver_4->sizePolicy().hasHeightForWidth());
        btnVolver_4->setSizePolicy(sizePolicy);

        verticalLayout_8->addWidget(btnVolver_4);

        tblInventario = new QTableWidget(pagInventario);
        tblInventario->setObjectName("tblInventario");

        verticalLayout_8->addWidget(tblInventario);

        stkPestanias->addWidget(pagInventario);
        pagAgregar = new QWidget();
        pagAgregar->setObjectName("pagAgregar");
        verticalLayout = new QVBoxLayout(pagAgregar);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName("formLayout");
        formLayout->setLabelAlignment(Qt::AlignmentFlag::AlignCenter);
        formLayout->setFormAlignment(Qt::AlignmentFlag::AlignCenter);
        label = new QLabel(pagAgregar);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, label);

        linNombre = new QLineEdit(pagAgregar);
        linNombre->setObjectName("linNombre");
        sizePolicy.setHeightForWidth(linNombre->sizePolicy().hasHeightForWidth());
        linNombre->setSizePolicy(sizePolicy);

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, linNombre);

        label_2 = new QLabel(pagAgregar);
        label_2->setObjectName("label_2");

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, label_2);

        linModelo = new QLineEdit(pagAgregar);
        linModelo->setObjectName("linModelo");
        sizePolicy.setHeightForWidth(linModelo->sizePolicy().hasHeightForWidth());
        linModelo->setSizePolicy(sizePolicy);

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, linModelo);

        label_3 = new QLabel(pagAgregar);
        label_3->setObjectName("label_3");

        formLayout->setWidget(4, QFormLayout::ItemRole::LabelRole, label_3);

        txtDesc = new QTextEdit(pagAgregar);
        txtDesc->setObjectName("txtDesc");
        sizePolicy.setHeightForWidth(txtDesc->sizePolicy().hasHeightForWidth());
        txtDesc->setSizePolicy(sizePolicy);

        formLayout->setWidget(4, QFormLayout::ItemRole::FieldRole, txtDesc);

        label_4 = new QLabel(pagAgregar);
        label_4->setObjectName("label_4");

        formLayout->setWidget(5, QFormLayout::ItemRole::LabelRole, label_4);

        linModComp = new QLineEdit(pagAgregar);
        linModComp->setObjectName("linModComp");
        sizePolicy.setHeightForWidth(linModComp->sizePolicy().hasHeightForWidth());
        linModComp->setSizePolicy(sizePolicy);

        formLayout->setWidget(5, QFormLayout::ItemRole::FieldRole, linModComp);

        label_5 = new QLabel(pagAgregar);
        label_5->setObjectName("label_5");

        formLayout->setWidget(6, QFormLayout::ItemRole::LabelRole, label_5);

        linPrecio = new QLineEdit(pagAgregar);
        linPrecio->setObjectName("linPrecio");
        sizePolicy.setHeightForWidth(linPrecio->sizePolicy().hasHeightForWidth());
        linPrecio->setSizePolicy(sizePolicy);

        formLayout->setWidget(6, QFormLayout::ItemRole::FieldRole, linPrecio);

        label_6 = new QLabel(pagAgregar);
        label_6->setObjectName("label_6");

        formLayout->setWidget(7, QFormLayout::ItemRole::LabelRole, label_6);

        linStock = new QLineEdit(pagAgregar);
        linStock->setObjectName("linStock");
        sizePolicy.setHeightForWidth(linStock->sizePolicy().hasHeightForWidth());
        linStock->setSizePolicy(sizePolicy);

        formLayout->setWidget(7, QFormLayout::ItemRole::FieldRole, linStock);

        label_7 = new QLabel(pagAgregar);
        label_7->setObjectName("label_7");

        formLayout->setWidget(8, QFormLayout::ItemRole::LabelRole, label_7);

        txtObs = new QTextEdit(pagAgregar);
        txtObs->setObjectName("txtObs");
        sizePolicy.setHeightForWidth(txtObs->sizePolicy().hasHeightForWidth());
        txtObs->setSizePolicy(sizePolicy);

        formLayout->setWidget(8, QFormLayout::ItemRole::FieldRole, txtObs);

        label_8 = new QLabel(pagAgregar);
        label_8->setObjectName("label_8");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, label_8);

        linSKU = new QLineEdit(pagAgregar);
        linSKU->setObjectName("linSKU");
        sizePolicy.setHeightForWidth(linSKU->sizePolicy().hasHeightForWidth());
        linSKU->setSizePolicy(sizePolicy);

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, linSKU);

        btnDialAgregar = new QDialogButtonBox(pagAgregar);
        btnDialAgregar->setObjectName("btnDialAgregar");
        sizePolicy.setHeightForWidth(btnDialAgregar->sizePolicy().hasHeightForWidth());
        btnDialAgregar->setSizePolicy(sizePolicy);
        btnDialAgregar->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);

        formLayout->setWidget(9, QFormLayout::ItemRole::FieldRole, btnDialAgregar);

        label_34 = new QLabel(pagAgregar);
        label_34->setObjectName("label_34");

        formLayout->setWidget(3, QFormLayout::ItemRole::LabelRole, label_34);

        linMarca = new QLineEdit(pagAgregar);
        linMarca->setObjectName("linMarca");
        sizePolicy.setHeightForWidth(linMarca->sizePolicy().hasHeightForWidth());
        linMarca->setSizePolicy(sizePolicy);

        formLayout->setWidget(3, QFormLayout::ItemRole::FieldRole, linMarca);


        verticalLayout->addLayout(formLayout);

        stkPestanias->addWidget(pagAgregar);
        pagInfoProdu = new QWidget();
        pagInfoProdu->setObjectName("pagInfoProdu");
        verticalLayout_2 = new QVBoxLayout(pagInfoProdu);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName("verticalLayout_2");
        btnVolver_5 = new QPushButton(pagInfoProdu);
        btnVolver_5->setObjectName("btnVolver_5");
        sizePolicy.setHeightForWidth(btnVolver_5->sizePolicy().hasHeightForWidth());
        btnVolver_5->setSizePolicy(sizePolicy);

        verticalLayout_2->addWidget(btnVolver_5);

        formLayout_2 = new QFormLayout();
        formLayout_2->setSpacing(6);
        formLayout_2->setObjectName("formLayout_2");
        label_9 = new QLabel(pagInfoProdu);
        label_9->setObjectName("label_9");
        sizePolicy2.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy2);

        formLayout_2->setWidget(0, QFormLayout::ItemRole::LabelRole, label_9);

        txtNombre = new QTextEdit(pagInfoProdu);
        txtNombre->setObjectName("txtNombre");
        txtNombre->setEnabled(true);
        txtNombre->setReadOnly(true);

        formLayout_2->setWidget(0, QFormLayout::ItemRole::FieldRole, txtNombre);

        label_10 = new QLabel(pagInfoProdu);
        label_10->setObjectName("label_10");
        sizePolicy2.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy2);

        formLayout_2->setWidget(1, QFormLayout::ItemRole::LabelRole, label_10);

        txtSKU = new QTextEdit(pagInfoProdu);
        txtSKU->setObjectName("txtSKU");
        txtSKU->setReadOnly(true);

        formLayout_2->setWidget(1, QFormLayout::ItemRole::FieldRole, txtSKU);

        label_11 = new QLabel(pagInfoProdu);
        label_11->setObjectName("label_11");
        sizePolicy2.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy2);

        formLayout_2->setWidget(2, QFormLayout::ItemRole::LabelRole, label_11);

        txtMod = new QTextEdit(pagInfoProdu);
        txtMod->setObjectName("txtMod");
        txtMod->setReadOnly(true);

        formLayout_2->setWidget(2, QFormLayout::ItemRole::FieldRole, txtMod);

        label_12 = new QLabel(pagInfoProdu);
        label_12->setObjectName("label_12");
        sizePolicy2.setHeightForWidth(label_12->sizePolicy().hasHeightForWidth());
        label_12->setSizePolicy(sizePolicy2);

        formLayout_2->setWidget(3, QFormLayout::ItemRole::LabelRole, label_12);

        txtDesc_2 = new QTextEdit(pagInfoProdu);
        txtDesc_2->setObjectName("txtDesc_2");
        txtDesc_2->setReadOnly(true);

        formLayout_2->setWidget(3, QFormLayout::ItemRole::FieldRole, txtDesc_2);

        label_13 = new QLabel(pagInfoProdu);
        label_13->setObjectName("label_13");
        sizePolicy2.setHeightForWidth(label_13->sizePolicy().hasHeightForWidth());
        label_13->setSizePolicy(sizePolicy2);

        formLayout_2->setWidget(4, QFormLayout::ItemRole::LabelRole, label_13);

        txtModComp = new QTextEdit(pagInfoProdu);
        txtModComp->setObjectName("txtModComp");
        txtModComp->setReadOnly(true);

        formLayout_2->setWidget(4, QFormLayout::ItemRole::FieldRole, txtModComp);

        label_14 = new QLabel(pagInfoProdu);
        label_14->setObjectName("label_14");
        sizePolicy2.setHeightForWidth(label_14->sizePolicy().hasHeightForWidth());
        label_14->setSizePolicy(sizePolicy2);

        formLayout_2->setWidget(5, QFormLayout::ItemRole::LabelRole, label_14);

        txtPrecio = new QTextEdit(pagInfoProdu);
        txtPrecio->setObjectName("txtPrecio");
        txtPrecio->setReadOnly(true);

        formLayout_2->setWidget(5, QFormLayout::ItemRole::FieldRole, txtPrecio);

        label_15 = new QLabel(pagInfoProdu);
        label_15->setObjectName("label_15");
        sizePolicy2.setHeightForWidth(label_15->sizePolicy().hasHeightForWidth());
        label_15->setSizePolicy(sizePolicy2);

        formLayout_2->setWidget(6, QFormLayout::ItemRole::LabelRole, label_15);

        txtStock = new QTextEdit(pagInfoProdu);
        txtStock->setObjectName("txtStock");
        txtStock->setReadOnly(true);

        formLayout_2->setWidget(6, QFormLayout::ItemRole::FieldRole, txtStock);

        label_16 = new QLabel(pagInfoProdu);
        label_16->setObjectName("label_16");
        sizePolicy2.setHeightForWidth(label_16->sizePolicy().hasHeightForWidth());
        label_16->setSizePolicy(sizePolicy2);

        formLayout_2->setWidget(7, QFormLayout::ItemRole::LabelRole, label_16);

        txtObs_2 = new QTextEdit(pagInfoProdu);
        txtObs_2->setObjectName("txtObs_2");
        txtObs_2->setReadOnly(true);

        formLayout_2->setWidget(7, QFormLayout::ItemRole::FieldRole, txtObs_2);


        verticalLayout_2->addLayout(formLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        btnVender = new QPushButton(pagInfoProdu);
        btnVender->setObjectName("btnVender");

        horizontalLayout_3->addWidget(btnVender);

        btnEditar = new QPushButton(pagInfoProdu);
        btnEditar->setObjectName("btnEditar");

        horizontalLayout_3->addWidget(btnEditar);

        btnBorrar = new QPushButton(pagInfoProdu);
        btnBorrar->setObjectName("btnBorrar");

        horizontalLayout_3->addWidget(btnBorrar);


        verticalLayout_2->addLayout(horizontalLayout_3);

        stkPestanias->addWidget(pagInfoProdu);
        pagVender = new QWidget();
        pagVender->setObjectName("pagVender");
        verticalLayout_6 = new QVBoxLayout(pagVender);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName("verticalLayout_6");
        formLayout_5 = new QFormLayout();
        formLayout_5->setSpacing(6);
        formLayout_5->setObjectName("formLayout_5");
        label_29 = new QLabel(pagVender);
        label_29->setObjectName("label_29");

        formLayout_5->setWidget(0, QFormLayout::ItemRole::LabelRole, label_29);

        label_30 = new QLabel(pagVender);
        label_30->setObjectName("label_30");

        formLayout_5->setWidget(1, QFormLayout::ItemRole::LabelRole, label_30);

        label_31 = new QLabel(pagVender);
        label_31->setObjectName("label_31");

        formLayout_5->setWidget(2, QFormLayout::ItemRole::LabelRole, label_31);

        label_32 = new QLabel(pagVender);
        label_32->setObjectName("label_32");

        formLayout_5->setWidget(3, QFormLayout::ItemRole::LabelRole, label_32);

        label_33 = new QLabel(pagVender);
        label_33->setObjectName("label_33");

        formLayout_5->setWidget(4, QFormLayout::ItemRole::LabelRole, label_33);

        linVenderCant = new QLineEdit(pagVender);
        linVenderCant->setObjectName("linVenderCant");

        formLayout_5->setWidget(0, QFormLayout::ItemRole::FieldRole, linVenderCant);

        linVenderCliente = new QLineEdit(pagVender);
        linVenderCliente->setObjectName("linVenderCliente");

        formLayout_5->setWidget(1, QFormLayout::ItemRole::FieldRole, linVenderCliente);

        linVenderPago = new QLineEdit(pagVender);
        linVenderPago->setObjectName("linVenderPago");

        formLayout_5->setWidget(2, QFormLayout::ItemRole::FieldRole, linVenderPago);

        linVendeEnvio = new QLineEdit(pagVender);
        linVendeEnvio->setObjectName("linVendeEnvio");

        formLayout_5->setWidget(3, QFormLayout::ItemRole::FieldRole, linVendeEnvio);

        txtVenderObs = new QTextEdit(pagVender);
        txtVenderObs->setObjectName("txtVenderObs");

        formLayout_5->setWidget(4, QFormLayout::ItemRole::FieldRole, txtVenderObs);


        verticalLayout_6->addLayout(formLayout_5);

        btnDialVender = new QDialogButtonBox(pagVender);
        btnDialVender->setObjectName("btnDialVender");
        btnDialVender->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);

        verticalLayout_6->addWidget(btnDialVender);

        stkPestanias->addWidget(pagVender);

        horizontalLayout_2->addWidget(stkPestanias);

        ProyectoAquamarineClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ProyectoAquamarineClass);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 856, 21));
        ProyectoAquamarineClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(ProyectoAquamarineClass);
        statusBar->setObjectName("statusBar");
        ProyectoAquamarineClass->setStatusBar(statusBar);

        retranslateUi(ProyectoAquamarineClass);

        stkPestanias->setCurrentIndex(6);


        QMetaObject::connectSlotsByName(ProyectoAquamarineClass);
    } // setupUi

    void retranslateUi(QMainWindow *ProyectoAquamarineClass)
    {
        ProyectoAquamarineClass->setWindowTitle(QCoreApplication::translate("ProyectoAquamarineClass", "Aquamarine", nullptr));
        lblLogoCRM->setText(QCoreApplication::translate("ProyectoAquamarineClass", "Aquamarine", nullptr));
        btnConsInv->setText(QCoreApplication::translate("ProyectoAquamarineClass", "Consultar inventario", nullptr));
        btnConsProd->setText(QCoreApplication::translate("ProyectoAquamarineClass", "Consultar producto", nullptr));
        btnSalir->setText(QCoreApplication::translate("ProyectoAquamarineClass", "Guardar y salir", nullptr));
        btnConsVen->setText(QCoreApplication::translate("ProyectoAquamarineClass", "Consultar ventas", nullptr));
        btnAgregar->setText(QCoreApplication::translate("ProyectoAquamarineClass", "Agregar producto", nullptr));
        btnEditarVen->setText(QCoreApplication::translate("ProyectoAquamarineClass", "Editar venta", nullptr));
        btnVolver->setText(QCoreApplication::translate("ProyectoAquamarineClass", "Volver", nullptr));
        btnEditarVenta->setText(QCoreApplication::translate("ProyectoAquamarineClass", "Editar venta", nullptr));
        btnVolver_2->setText(QCoreApplication::translate("ProyectoAquamarineClass", "Volver", nullptr));
        btnBuscarID->setText(QCoreApplication::translate("ProyectoAquamarineClass", "Buscar ID", nullptr));
        btnBorrarVenta->setText(QCoreApplication::translate("ProyectoAquamarineClass", "Borrar venta", nullptr));
        label_25->setText(QCoreApplication::translate("ProyectoAquamarineClass", "Forma de pago", nullptr));
        label_26->setText(QCoreApplication::translate("ProyectoAquamarineClass", "Envio", nullptr));
        label_21->setText(QCoreApplication::translate("ProyectoAquamarineClass", "Cliente", nullptr));
        label_27->setText(QCoreApplication::translate("ProyectoAquamarineClass", "Cantidad", nullptr));
        label_23->setText(QCoreApplication::translate("ProyectoAquamarineClass", "Precio", nullptr));
        label_22->setText(QCoreApplication::translate("ProyectoAquamarineClass", "Producto (SKU)", nullptr));
        label_18->setText(QCoreApplication::translate("ProyectoAquamarineClass", "Actual", nullptr));
        label_20->setText(QCoreApplication::translate("ProyectoAquamarineClass", "Fecha y hora", nullptr));
        label_28->setText(QCoreApplication::translate("ProyectoAquamarineClass", "Observaciones", nullptr));
        label_24->setText(QCoreApplication::translate("ProyectoAquamarineClass", "Precio ML", nullptr));
        label_19->setText(QCoreApplication::translate("ProyectoAquamarineClass", "Nueva", nullptr));
        label_17->setText(QCoreApplication::translate("ProyectoAquamarineClass", "Opcion", nullptr));
        btnVolver_3->setText(QCoreApplication::translate("ProyectoAquamarineClass", "Volver", nullptr));
        btnBuscar->setText(QCoreApplication::translate("ProyectoAquamarineClass", "Buscar", nullptr));
        btnVolver_4->setText(QCoreApplication::translate("ProyectoAquamarineClass", "Volver", nullptr));
        label->setText(QCoreApplication::translate("ProyectoAquamarineClass", "Nombre", nullptr));
        label_2->setText(QCoreApplication::translate("ProyectoAquamarineClass", "Modelo", nullptr));
        label_3->setText(QCoreApplication::translate("ProyectoAquamarineClass", "Descripcion", nullptr));
        txtDesc->setHtml(QCoreApplication::translate("ProyectoAquamarineClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">NA</p></body></html>", nullptr));
        label_4->setText(QCoreApplication::translate("ProyectoAquamarineClass", "Modelos compatibles", nullptr));
        linModComp->setText(QCoreApplication::translate("ProyectoAquamarineClass", "NA", nullptr));
        label_5->setText(QCoreApplication::translate("ProyectoAquamarineClass", "Precio", nullptr));
        label_6->setText(QCoreApplication::translate("ProyectoAquamarineClass", "Stock", nullptr));
        label_7->setText(QCoreApplication::translate("ProyectoAquamarineClass", "Observaciones", nullptr));
        txtObs->setHtml(QCoreApplication::translate("ProyectoAquamarineClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">NA</p></body></html>", nullptr));
        label_8->setText(QCoreApplication::translate("ProyectoAquamarineClass", "SKU", nullptr));
        label_34->setText(QCoreApplication::translate("ProyectoAquamarineClass", "Marca", nullptr));
        btnVolver_5->setText(QCoreApplication::translate("ProyectoAquamarineClass", "Volver", nullptr));
        label_9->setText(QCoreApplication::translate("ProyectoAquamarineClass", "Nombre", nullptr));
        label_10->setText(QCoreApplication::translate("ProyectoAquamarineClass", "SKU", nullptr));
        label_11->setText(QCoreApplication::translate("ProyectoAquamarineClass", "Modelo", nullptr));
        label_12->setText(QCoreApplication::translate("ProyectoAquamarineClass", "Descripcion", nullptr));
        label_13->setText(QCoreApplication::translate("ProyectoAquamarineClass", "Modelos compatibles", nullptr));
        label_14->setText(QCoreApplication::translate("ProyectoAquamarineClass", "Precio", nullptr));
        label_15->setText(QCoreApplication::translate("ProyectoAquamarineClass", "Stock", nullptr));
        label_16->setText(QCoreApplication::translate("ProyectoAquamarineClass", "Observaciones", nullptr));
        btnVender->setText(QCoreApplication::translate("ProyectoAquamarineClass", "Vender producto", nullptr));
        btnEditar->setText(QCoreApplication::translate("ProyectoAquamarineClass", "Editar producto", nullptr));
        btnBorrar->setText(QCoreApplication::translate("ProyectoAquamarineClass", "Borrar producto", nullptr));
        label_29->setText(QCoreApplication::translate("ProyectoAquamarineClass", "Cantidad", nullptr));
        label_30->setText(QCoreApplication::translate("ProyectoAquamarineClass", "Nombre cliente", nullptr));
        label_31->setText(QCoreApplication::translate("ProyectoAquamarineClass", "Forma de pago", nullptr));
        label_32->setText(QCoreApplication::translate("ProyectoAquamarineClass", "Envio", nullptr));
        label_33->setText(QCoreApplication::translate("ProyectoAquamarineClass", "Observaciones", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProyectoAquamarineClass: public Ui_ProyectoAquamarineClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROYECTOAQUAMARINE_H
