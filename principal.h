#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui { class Principal; }
QT_END_NAMESPACE

class Principal : public QMainWindow
{
    Q_OBJECT

public:
    Principal(QWidget *parent = nullptr);
    ~Principal();

protected:

    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override; //Libre
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private slots:
    void on_actionAncho_triggered();

    void on_actionSalir_triggered();

    void on_actionColor_triggered();

    void on_actionNuevo_triggered();

    void on_actionGuardar_triggered();

    void on_actionLineas_triggered();

    void on_actionLibre_triggered();

    void on_actionRect_nculos_triggered();

    void on_actionCircunferencias_triggered();

private:
    Ui::Principal *ui;
    int Opc;
    bool verificarOpc=true;
    QImage *mImagen;
    QPainter *mPainter;
    QPoint mInicial;
    QPoint mFinal;
    bool mPuedeDibujar;
    int mAncho;
    QColor mColor;
    int mNumLineas;
};
#endif // PRINCIPAL_H
