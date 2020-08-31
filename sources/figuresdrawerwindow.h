#ifndef FIGURESDRAWERWINDOW_H
#define FIGURESDRAWERWINDOW_H

#include <QMainWindow>
#include <QTranslator>
#include <QPainter>
#include <QPoint>
#include <QRandomGenerator>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class FiguresDrawerWindow; }
QT_END_NAMESPACE

class FiguresDrawerWindow : public QMainWindow
{
    Q_OBJECT

public:
    FiguresDrawerWindow(QWidget *parent = nullptr);
    ~FiguresDrawerWindow();

    void paintEvent(QPaintEvent *);

private:
    Ui::FiguresDrawerWindow *ui;
    QTranslator Translator;
    QString translation_path;

    int height;
    int width;

    QColor color;
    int prev_figure;

    enum Figure{
        None,
        Rectangle,
        Square,
        Triangle,
        Circle,
        Star,
        Random
    };

private slots:
    void change_language();
    void draw_figure(const int &figure, bool is_repaint_enabled);
    QPainterPath draw_triangle();
    QPainterPath draw_star();
    void on_pB_rectangle_clicked();
    void on_pB_square_clicked();
    void on_pB_triangle_clicked();
    void on_pB_circle_clicked();
    void on_pB_star_clicked();
    void on_pB_random_clicked();
    void on_pB_clear_clicked();
};

#endif // FIGURESDRAWERWINDOW_H
