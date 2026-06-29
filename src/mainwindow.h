#pragma once
#include <qmainwindow.h>
#include <qtconfigmacros.h>
#include <qtmetamacros.h>



QT_BEGIN_NAMESPACE
namespace Ui{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parrent = nullptr);
    void updateBackground();
    ~MainWindow();
protected:
    void resizeEvent(QResizeEvent *event) override;
private:
    Ui::MainWindow *ui;
    QPixmap m_originalPixmap;
private slots:
    void on_pushButton();
    void q_groupBox();
};