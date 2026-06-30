#include <QVBoxLayout>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <qnamespace.h>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui/stypehelper.hpp"

#include "drivercard.h"
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->groupBox->setTitle("");
    ui->groupBox->setAttribute(Qt::WA_TranslucentBackground);
    ui->groupBox->setStyleSheet(StyleHelper::getGlassStyle());

    ui->pushButton->setText("Следующий вид");
    ui->pushButton->setStyleSheet(StyleHelper::getStyleButtonGlass());

    m_chart = new QChart();
    m_chartView = new QChartView(m_chart);
    m_chartView->setRenderHint(QPainter::Antialiasing);
    m_chartView->setStyleSheet("background: transparent;");

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(m_chartView);
    ui->groupBox->setLayout(layout);

    showPieChart();

    ui->widget_test->setStyleSheet(StyleHelper::getGlassStyle());
    m_originalPixmap = QPixmap(":/res/image/kot_v_vode.png");

    QList<std::tuple<int,QString,QString,int>> drivers = {
        {1,  "Verstappen",  "Red Bull",    400},
        {2,  "Hamilton",    "Mercedes",    350},
        {3,  "Leclerc",     "Ferrari",     300},
        {4,  "Norris",      "McLaren",     280},
        {5,  "Sainz",       "Ferrari",     260},
        {6,  "Russell",     "Mercedes",    240},
        {7,  "Perez",       "Red Bull",    220},
        {8,  "Alonso",      "Aston Martin",200},
        {9,  "Piastri",     "McLaren",     180},
        {10, "Stroll",      "Aston Martin",150},
        {11, "Gasly",       "Alpine",      120},
        {12, "Ocon",        "Alpine",      100},
        {13, "Albon",       "Williams",     80},
        {14, "Bottas",      "Sauber",       60},
        {15, "Zhou",        "Sauber",       50},
        {16, "Hulkenberg",  "Haas",         40},
        {17, "Magnussen",   "Haas",         30},
        {18, "Tsunoda",     "RB",           20},
        {19, "Ricciardo",   "RB",           10},
        {20, "Sargeant",    "Williams",      5},
    };

    auto *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    scrollArea->setStyleSheet(
        "QScrollArea { background: transparent; border: none; }"
        "QScrollBar:vertical { width: 4px; background: transparent; }"
        "QScrollBar::handle:vertical { background: rgba(255,255,255,60); border-radius: 2px; }"
    );

    auto *container = new QWidget();
    container->setStyleSheet("QWidget { background: transparent; border: none; }");

    auto *vLayout = new QVBoxLayout(container);
    vLayout->setSpacing(4);
    vLayout->setContentsMargins(6, 6, 6, 6);

    for (auto &[pos, name, team, pts] : drivers) {
        vLayout->addWidget(new DriverCard(pos, name, team, pts, this));
    }

    vLayout->addStretch();
    scrollArea->setWidget(container);

    auto *wLayout = new QVBoxLayout();
    wLayout->setContentsMargins(0, 0, 0, 0);
    wLayout->addWidget(scrollArea);
    ui->widget_test->setLayout(wLayout);

    updateBackground();
}

void MainWindow::showPieChart()
{
    clearChart();
    m_chart->setTitle(" ");

    QPieSeries *series = new QPieSeries();
    series->append(" ", 25);
    series->append(" ", 25);
    series->append(" ", 25);
    series->append(" ", 25);

    auto makeGradient = [](QColor c1, QColor c2) {
        QLinearGradient g(0, 0, 1, 1);
        g.setCoordinateMode(QGradient::ObjectBoundingMode);
        g.setColorAt(0.0, c1);
        g.setColorAt(1.0, c2);
        return QBrush(g);
    };

    series->slices().at(0)->setBrush(makeGradient("#000000", "#000000"));
    series->slices().at(1)->setBrush(makeGradient("#512451", "#492749"));
    series->slices().at(2)->setBrush(makeGradient("#214735", "#006633"));
    series->slices().at(3)->setBrush(makeGradient("#453f1d", "#4e2a1d"));

    series->setHoleSize(0.6);


    for (QPieSlice *s : series->slices()) {
        s->setLabelVisible(false);
        s->setLabelColor(Qt::black);
        s->setBorderColor(Qt::transparent);  // убирает обводку
        s->setBorderWidth(0);
        s->setExplodeDistanceFactor(0.1);
        
        connect(s, &QPieSlice::clicked, series, [series, s]() {
            for (QPieSlice *other : series->slices())
                other->setExploded(false);
            s->setExploded(true);
        });
    }

    m_chart->addSeries(series);
    applyChartStyle();
}

void MainWindow::applyChartStyle()
{
    m_chart->setBackgroundBrush(QBrush(QColor(0, 0, 0, 0)));
    m_chart->setTitleBrush(QBrush(Qt::white));
    m_chart->setAnimationOptions(QChart::SeriesAnimations);
    m_chart->legend()->setLabelColor(Qt::white);
    m_chart->legend()->setVisible(false);
}

void MainWindow::clearChart()
{
    m_chart->removeAllSeries();
    for (QAbstractAxis *axis : m_chart->axes())
        m_chart->removeAxis(axis);
}

void MainWindow::updateBackground()
{
    QPixmap pm = m_originalPixmap.scaled(this->size(),
        Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QPainter painter(&pm);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.fillRect(pm.rect(), QColor(0, 0, 0, 150));
    painter.end();

    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(pm));
    this->setPalette(palette);
    this->setAutoFillBackground(true);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    m_chart->setAnimationOptions(QChart::NoAnimation);
    QMainWindow::resizeEvent(event);
    updateBackground();
    m_chart->setAnimationOptions(QChart::SeriesAnimations);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    // пока пусто
}

void MainWindow::on_pushButton_2_clicked()
{
    // пока пусто
}