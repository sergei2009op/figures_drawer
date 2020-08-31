#include "figuresdrawerwindow.h"
#include "ui_figuresdrawerwindow.h"

FiguresDrawerWindow::FiguresDrawerWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::FiguresDrawerWindow)
{
    ui->setupUi(this);

    translation_path = ":/figures_drawer_en";
    Translator.load(translation_path);
    qApp->installTranslator(&Translator);

    connect(ui->actionTranslate, SIGNAL(triggered()), this, SLOT(change_language()));

    prev_figure = None;
}

FiguresDrawerWindow::~FiguresDrawerWindow()
{
    delete ui;
}

void FiguresDrawerWindow::change_language()
{
    if (translation_path == ":/figures_drawer_ru_RU")
        translation_path = ":/figures_drawer_en";
    else
        translation_path = ":/figures_drawer_ru_RU";

    Translator.load(translation_path);
    ui->retranslateUi(this);
}

void FiguresDrawerWindow::paintEvent(QPaintEvent *)
{
    height = ui->l_canvas->size().height();
    width = ui->l_canvas->size().width();

    draw_figure(prev_figure, false);
}

void FiguresDrawerWindow::draw_figure(const int &figure, bool is_repaint_enabled)
{
    QPixmap pix(width, height);
    QPainter painter(&pix);
    painter.fillRect(0, 0, width, height, Qt::white);

    if (is_repaint_enabled)
        color = QColor::fromRgb(QRandomGenerator::global()->generate());

    switch(figure)
    {
    case None:
        break;
    case Rectangle:
        painter.fillRect(width/4, height/4, width/2, height/2, color);
        break;
    case Square:
        painter.fillRect(width/2 - height/4, height/4, height/2, height/2, color);
        break;
    case Triangle:
        painter.fillPath(draw_triangle(), color);
        break;
    case Circle:
        painter.setBrush(color);
        painter.drawEllipse(QPoint(width/2, height/2), height/2, height/2);
        break;
    case Star:
        painter.fillPath(draw_star(), color);
        break;
    case Random:
        break;
    default:
        break;
    }

    prev_figure = figure;
    ui->l_canvas->setPixmap(pix);
}

QPainterPath FiguresDrawerWindow::draw_triangle()
{
    qreal a_x = width/4;
    qreal a_y = height * 3/4;

    qreal b_x = width * 3/4;
    qreal b_y = height * 3/4;

    qreal c_x = width/2;
    qreal c_y = height/4;

    QPainterPath path;
    path.moveTo (a_x, a_y);
    path.lineTo (b_x, b_y);
    path.lineTo (c_x, c_y);
    path.lineTo (a_x, a_y);

    return path;
}

QPainterPath FiguresDrawerWindow::draw_star()
{
    qreal N_S_x = width/2;
    qreal N_y = 0;

    qreal WN_SW_x = width/2 - height/8;
    qreal WN_NE_y = height * 3/8;

    qreal W_x = width/2 - height/2;
    qreal W_E_y = height/2;

    qreal SW_ES_y = height * 5/8;

    qreal S_y = height;

    qreal ES_NE_x = width/2 + height/8;

    qreal E_x = width/2 + height/2;

    QPainterPath path;
    path.moveTo (N_S_x, N_y);
    path.lineTo (WN_SW_x, WN_NE_y);
    path.lineTo (W_x, W_E_y);
    path.lineTo (WN_SW_x, SW_ES_y);
    path.lineTo (N_S_x, S_y);
    path.lineTo (ES_NE_x, SW_ES_y);
    path.lineTo (E_x, W_E_y);
    path.lineTo (ES_NE_x, WN_NE_y);

    return path;
}

void FiguresDrawerWindow::on_pB_rectangle_clicked()
{
    draw_figure(Rectangle, true);
}

void FiguresDrawerWindow::on_pB_square_clicked()
{
    draw_figure(Square, true);
}

void FiguresDrawerWindow::on_pB_triangle_clicked()
{
    draw_figure(Triangle, true);
}

void FiguresDrawerWindow::on_pB_circle_clicked()
{
    draw_figure(Circle, true);
}

void FiguresDrawerWindow::on_pB_star_clicked()
{
    draw_figure(Star, true);
}

void FiguresDrawerWindow::on_pB_random_clicked()
{
    int rand_figure = QRandomGenerator::global()->bounded(1,6);
    draw_figure(rand_figure, true);
}

void FiguresDrawerWindow::on_pB_clear_clicked()
{
    draw_figure(None, false);
}
