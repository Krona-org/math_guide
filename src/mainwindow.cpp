#include <QVBoxLayout>
#include <QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QLineSeries>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stypehelper.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->groupBox->setTitle("");
    ui->groupBox_2->setTitle("");
    ui->groupBox->setAttribute(Qt::WA_TranslucentBackground);
    ui->groupBox_2->setAttribute(Qt::WA_TranslucentBackground);
    ui->groupBox->setStyleSheet(StyleHelper::getGlassStyle());
    ui->groupBox_2->setStyleSheet(StyleHelper::getGlassStyle());

    // Кнопка переключения
    ui->pushButton->setText("Следующий вид");
    ui->pushButton->setStyleSheet(
        "QPushButton { background-color: rgba(255,255,255,40); border-radius: 8px;"
        "color: white; padding: 6px; border: 1px solid rgba(255,255,255,80); }"
        "QPushButton:hover { background-color: rgba(255,255,255,70); }"
    );

    // Создаём chartView один раз
    m_chart = new QChart();
    m_chartView = new QChartView(m_chart);
    m_chartView->setRenderHint(QPainter::Antialiasing);
    m_chartView->setStyleSheet("background: transparent;");

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(m_chartView);
    ui->groupBox->setLayout(layout);

    // Показываем первый вид
    showPieChart();

    m_originalPixmap = QPixmap(":/res/image/kot_v_vode.png");
    updateBackground();
}

// --- Круговая диаграмма ---
void MainWindow::showPieChart()
{
    clearChart();
    m_chart->setTitle("Круговая диаграмма");

    QPieSeries *series = new QPieSeries();
    series->append("Алгебра", 40);
    series->append("Геометрия", 30);
    series->append("Физика", 20);
    series->append("Прочее", 10);

    series->slices().at(0)->setBrush(QColor("#e74c3c"));
    series->slices().at(1)->setBrush(QColor("#3498db"));
    series->slices().at(2)->setBrush(QColor("#2ecc71"));
    series->slices().at(3)->setBrush(QColor("#f39c12"));
    series->slices().at(0)->setExploded(true);

    for (QPieSlice *s : series->slices()) {
        s->setLabelVisible(true);
        s->setLabelColor(Qt::white);
    }

    m_chart->addSeries(series);
    applyChartStyle();
}

// --- Столбчатая диаграмма ---
void MainWindow::showBarChart()
{
    clearChart();
    m_chart->setTitle("Столбчатая диаграмма");

    QBarSet *set = new QBarSet("Баллы");
    set->append({40, 30, 20, 10});
    set->setColor(QColor("#3498db"));
    set->setLabelColor(Qt::white);

    QBarSeries *series = new QBarSeries();
    series->append(set);
    series->setLabelsVisible(true);

    m_chart->addSeries(series);

    QStringList categories = {"Алгебра", "Геометрия", "Физика", "Прочее"};
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    axisX->setLabelsColor(Qt::white);
    m_chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, 50);
    axisY->setLabelsColor(Qt::white);
    m_chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    applyChartStyle();
}

// --- Линейный график ---
void MainWindow::showLineChart()
{
    clearChart();
    m_chart->setTitle("Линейный график");

    QLineSeries *series = new QLineSeries();
    series->append(0, 40);
    series->append(1, 30);
    series->append(2, 20);
    series->append(3, 10);
    series->setColor(QColor("#e74c3c"));

    QPen pen(QColor("#e74c3c"));
    pen.setWidth(3);
    series->setPen(pen);

    m_chart->addSeries(series);

    QValueAxis *axisX = new QValueAxis();
    axisX->setRange(0, 3);
    axisX->setLabelsColor(Qt::white);
    m_chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, 50);
    axisY->setLabelsColor(Qt::white);
    m_chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    applyChartStyle();
}

// --- Общий стиль графика ---
void MainWindow::applyChartStyle()
{
    m_chart->setBackgroundBrush(QBrush(QColor(0, 0, 0, 0)));
    m_chart->setTitleBrush(QBrush(Qt::white));
    m_chart->setAnimationOptions(QChart::AllAnimations);
    m_chart->legend()->setLabelColor(Qt::white);
    m_chart->legend()->setVisible(true);
}

// --- Кнопка переключения ---
void MainWindow::on_pushButton_clicked()
{
    m_currentChartType = (m_currentChartType + 1) % 3;

    switch (m_currentChartType) {
        case 0: showPieChart();  break;
        case 1: showBarChart();  break;
        case 2: showLineChart(); break;
    }
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

// --- Вспомогательная функция очистки ---
void MainWindow::clearChart()
{
    m_chart->removeAllSeries();  // <-- вот что здесь должно быть!
    
    // Удаляем все оси
    for (QAbstractAxis *axis : m_chart->axes()) {
        m_chart->removeAxis(axis);
    }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    updateBackground();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    // пока пусто
}