#pragma once
#include <QMainWindow>
#include <QPixmap>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    Ui::MainWindow *ui;
    QPixmap m_originalPixmap;

    // Для диаграммы
    QChartView *m_chartView;
    QChart *m_chart;
    int m_currentChartType = 0;  // 0=круговая, 1=столбчатая, 2=линейная

    void updateBackground();
    void showPieChart();
    void showBarChart();
    void showLineChart();
    void applyChartStyle();
    void clearChart();

private slots:
    void on_pushButton_clicked();   // переключение диаграммы
    void on_pushButton_2_clicked(); // пока пусто
};