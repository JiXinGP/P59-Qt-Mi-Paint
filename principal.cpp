#include "principal.h"
#include "ui_principal.h"

#include <QImage>
#include <QPainter>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QDebug>
#include <QInputDialog>
#include <QColorDialog>
#include <QFileDialog>
#include <QMessageBox>

#define DEFAULT_ANCHO 3

Principal::Principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Principal)
{
    ui->setupUi(this);
    mImagen = new QImage(this->size(),QImage::Format_ARGB32_Premultiplied);
    mImagen->fill(Qt::white);
    mPainter = new QPainter(mImagen);
    mPainter->setRenderHint(QPainter::Antialiasing);
    mPuedeDibujar = false;
    mColor = Qt::black;
    mAncho = DEFAULT_ANCHO;
    mNumLineas = 0;
    Opc=1;
}

Principal::~Principal()
{
    delete ui;
    delete mPainter;
    delete mImagen;
}

void Principal::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(0, 0, *mImagen);
    event->accept();
}

void Principal::mousePressEvent(QMouseEvent *event)
{
    if(Opc==1){
        mInicial=event->pos();
    }else if(Opc==2){
        if(verificarOpc){
            mInicial = event->pos();
        }else{
            mFinal=event->pos();
            QPen pincel;
            pincel.setWidth(mAncho);
            pincel.setColor(mColor);
            mPainter->setPen(pincel);
            mPainter->drawLine(mInicial, mFinal);
            update();
        }
    }else if(Opc==3){
        if(verificarOpc){
            mInicial = event->pos();
        }else{
            mFinal=event->pos();
            int ancho=mFinal.x() - mInicial.x();
            int alto=mFinal.y() - mInicial.y();
            QPen pincel;
            pincel.setWidth(mAncho);
            pincel.setColor(mColor);
            mPainter->setPen(pincel);
            mPainter->drawRect(mInicial.x(), mInicial.y(), ancho, alto);
            update();
        }
    }else if(Opc==4){
        if(verificarOpc){
            mInicial = event->pos();
        }else{
            mFinal=event->pos();
            int ancho=mFinal.x() - mInicial.x();
            int alto=mFinal.y() - mInicial.y();
            QPen pincel;
            pincel.setWidth(mAncho);
            pincel.setColor(mColor);
            mPainter->setPen(pincel);
            QRectF rectangulo(mInicial.x(), mInicial.y(), ancho, alto);
            mPainter->drawEllipse(rectangulo);
            update();
        }
    }
    verificarOpc=!verificarOpc;
}

void Principal::mouseMoveEvent(QMouseEvent *event)
{
    if (mPuedeDibujar ) {
        event->accept();
        return;
    }

    if(Opc==1){
        mFinal = event->pos();
        QPen pincel;
        pincel.setColor(mColor);
        pincel.setWidth(mAncho);
        mPainter->setPen(pincel);
        mPainter->drawLine(mInicial, mFinal);
        ui->statusbar->showMessage("Número de líneas: " + QString::number(++mNumLineas));
    }
    update();
    mInicial = mFinal;
}

void Principal::mouseReleaseEvent(QMouseEvent *event)
{
    mPuedeDibujar = false;
    // Aceptar el vento
    event->accept();
}


void Principal::on_actionAncho_triggered()
{
    mAncho = QInputDialog::getInt(this,
                                  "Ancho del pincel",
                                  "Ingrese el ancho del pincel de dibujo",
                                  mAncho,
                                  1, 100);
}

void Principal::on_actionSalir_triggered()
{
    this->close();
}

void Principal::on_actionColor_triggered()
{
    mColor = QColorDialog::getColor(mColor,
                                    this,
                                    "Color del pincel");
}

void Principal::on_actionNuevo_triggered()
{
    mImagen->fill(Qt::white);
    mNumLineas = 0;
    update();
}

void Principal::on_actionGuardar_triggered()
{
    QString nombreArchivo = QFileDialog::getSaveFileName(this,
                                                         "Guardar imagen",
                                                         QString(),
                                                         "Imágenes (*.png)");
    if ( !nombreArchivo.isEmpty() ){
        if (mImagen->save(nombreArchivo))
            QMessageBox::information(this,
                                     "Guardar imagen",
                                     "Archivo almacenado en: " + nombreArchivo);
        else
            QMessageBox::warning(this,
                                 "Guardar imagen",
                                 "No se pudo almacenar la imagen.");
    }
}

void Principal::on_actionLineas_triggered()
{
    Opc=2;
}


void Principal::on_actionLibre_triggered()
{
    Opc=1;
}


void Principal::on_actionRect_nculos_triggered()
{
    Opc=3;
}


void Principal::on_actionCircunferencias_triggered()
{
    Opc=4;
}
