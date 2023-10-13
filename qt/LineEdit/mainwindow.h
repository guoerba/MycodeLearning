#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    QPushButton *btnGroup1NormalMode;
    QPushButton *btnGroup1PasswordMode;
    QPushButton *btnGroup1NoDisplayBackMode;
    QPushButton *btnGroup1Password2Mode;
    QPushButton *btnGroup1Output;
    QLineEdit *lineGroup1;

    QPushButton *btnGroup2LeftAlign;
    QPushButton *btnGroup2MiddleAlign;
    QPushButton *btnGroup2RightAlign;
    QLineEdit *lineGroup2;

    QPushButton *btnGroup3WriteRead;
    QPushButton *btnGroup3ReadOnly;
    QPushButton *btnGroup3Disable;
    QPushButton *btnGroup3Enable;
    QPushButton *btnGroup3Output;
    QLineEdit *lineGroup3;

    QPushButton *btnGroup4NoControl;
    QPushButton *btnGroup4PhoneNumber;
    QPushButton *btnGroup4Password;
    QLineEdit *lineGroup4;

    QLineEdit *lineGroup5textChanged_1;
    QLineEdit *lineGroup5textChanged_2;
    QLineEdit *lineGroup5textChanged_3;
    QLineEdit *lineGroup5editingFinished_1;
    QLineEdit *lineGroup5editingFinished_2;
    QLineEdit *lineGroup5editingFinished_3;
public slots:
    void lineGroup5textChangedSlot(const QString &text);
    void lineGroup5EditingFinishedSlot();
};
#endif // MAINWINDOW_H
