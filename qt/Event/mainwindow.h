#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QButtonGroup>
#include <QStackedWidget>
#include <QVBoxLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    QButtonGroup *btnGroup;
    QStackedWidget *rightWidget;

    QVBoxLayout *SetButtonLayout();
    void SetRightWidget();
private slots:
    void onButtonClicked();
};
#endif // MAINWINDOW_H
