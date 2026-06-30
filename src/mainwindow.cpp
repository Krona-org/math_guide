#include <QVBoxLayout>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QLineSeries>
#include <QRandomGenerator>
#include <algorithm>
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

    ui->pushButton_2->setText("Перемешать пилотов");
    ui->pushButton_2->setStyleSheet(StyleHelper::getStyleButtonGlass());

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
        auto *card = new DriverCard(pos, name, team, pts, this);
        m_driverCards.append(card);
        vLayout->addWidget(card);
    }

    vLayout->addStretch();
    scrollArea->setWidget(container);

    m_driverContainer = container;
    m_driverLayout = vLayout;

    auto *wLayout = new QVBoxLayout();
    wLayout->setContentsMargins(0, 0, 0, 0);
    wLayout->addWidget(scrollArea);
    ui->widget_test->setLayout(wLayout);

    updateBackground();
}

// ---------------- Диаграммы ----------------

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
        s->setBorderColor(Qt::transparent);
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

void MainWindow::showBarChart()
{
    clearChart();
    m_chart->setTitle(" ");

    QBarSet *set = new QBarSet(" ");
    *set << 5 << 8 << 3 << 6;

    QBarSeries *series = new QBarSeries();
    series->append(set);

    m_chart->addSeries(series);

    QStringList categories = {"A", "B", "C", "D"};
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    axisX->setLabelsColor(Qt::white);
    m_chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setLabelsColor(Qt::white);
    m_chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    applyChartStyle();
}

void MainWindow::showLineChart()
{
    clearChart();
    m_chart->setTitle(" ");

    QLineSeries *series = new QLineSeries();
    series->append(0, 2);
    series->append(1, 5);
    series->append(2, 3);
    series->append(3, 7);

    QPen pen(QColor("#9b6dd6"));
    pen.setWidth(3);
    series->setPen(pen);

    m_chart->addSeries(series);
    m_chart->createDefaultAxes();

    for (QAbstractAxis *axis : m_chart->axes())
        axis->setLabelsColor(Qt::white);

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

// ---------------- Фон ----------------

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

// ---------------- Таблица пилотов: анимация перестановки ----------------

void MainWindow::animateReorder(const QList<DriverCard*> &newOrder)
{
    // 1. Запоминаем текущие позиции карточек
    QMap<DriverCard*, QRect> oldGeometry;
    for (DriverCard *card : m_driverCards)
        oldGeometry[card] = card->geometry();

    // 2. Переставляем виджеты в layout в новом порядке
    for (DriverCard *card : m_driverCards)
        m_driverLayout->removeWidget(card);

    for (DriverCard *card : newOrder)
        m_driverLayout->addWidget(card);

    m_driverCards = newOrder;
    m_driverLayout->activate();

    // 3. Анимируем от старой геометрии к новой
    auto *group = new QParallelAnimationGroup(this);

    for (DriverCard *card : m_driverCards) {
        const QRect endGeom = card->geometry();
        const QRect startGeom = oldGeometry.value(card, endGeom);

        if (startGeom == endGeom)
            continue;

        card->setGeometry(startGeom);

        auto *anim = new QPropertyAnimation(card, "geometry", this);
        anim->setDuration(450);
        anim->setStartValue(startGeom);
        anim->setEndValue(endGeom);
        anim->setEasingCurve(QEasingCurve::InOutCubic);

        group->addAnimation(anim);
    }

    group->start(QAbstractAnimation::DeleteWhenStopped);
}

void MainWindow::sortDriversByPoints()
{
    QList<DriverCard*> sorted = m_driverCards;
    std::sort(sorted.begin(), sorted.end(), [](DriverCard *a, DriverCard *b) {
        return a->points() > b->points(); // нужен геттер points() в DriverCard
    });
    animateReorder(sorted);
}

void MainWindow::shuffleDrivers()
{
    QList<DriverCard*> shuffled = m_driverCards;
    std::shuffle(shuffled.begin(), shuffled.end(), *QRandomGenerator::global());
    animateReorder(shuffled);
}

// ---------------- Слоты кнопок ----------------

void MainWindow::on_pushButton_clicked()
{
    m_currentChartType = (m_currentChartType + 1) % 3;
    switch (m_currentChartType) {
    case 0: showPieChart(); break;
    case 1: showBarChart(); break;
    case 2: showLineChart(); break;
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    shuffleDrivers();
}