#pragma once
#include <QMainWindow>
#include <QPixmap>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QMap>
#include <QList>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

class DriverCard;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    Ui::MainWindow *ui;
    QPixmap m_originalPixmap;

    // Диаграмма
    QChartView *m_chartView = nullptr;
    QChart *m_chart = nullptr;
    int m_currentChartType = 0; // 0=круговая, 1=столбчатая, 2=линейная

    void setupDrivers();
    void updateBackground();
    void showPieChart();
    void showBarChart();
    void showLineChart();
    void applyChartStyle();
    void clearChart();

    // Таблица пилотов
    QWidget *m_driverContainer = nullptr;
    QVBoxLayout *m_driverLayout = nullptr;
    QList<DriverCard*> m_driverCards;

    void animateReorder(const QList<DriverCard*> &newOrder);
    void renumberByListOrder(const QList<DriverCard*> &list); // 1..N по порядку в списке
    void sortDriversByPoints();
    void shuffleDrivers();

private slots:
    void on_pushButton_clicked();   // переключение диаграммы
    void on_pushButton_2_clicked(); // перестановка пилотов
};