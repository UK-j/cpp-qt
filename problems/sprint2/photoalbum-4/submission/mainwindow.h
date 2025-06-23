#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QLabel>
#include <QDir>
#include <QPushButton>
#include <QResizeEvent>  // Добавлен заголовочный файл

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void SetFolder(const QString& dir);
    QString GetCurrentFile();

protected:
    void resizeEvent(QResizeEvent *event) override;  // Исправленное объявление

private slots:
    void on_btn_left_clicked();
    
    void on_btn_right_clicked();
    
private:
    Ui::MainWindow *ui;
    QPixmap active_pixmap;
    QLabel *lbl_img;
    QPushButton *btn_left;
    QPushButton *btn_right;
    QString current_folder;
    int cur_file_index = 0;

    void FitImage();
    void UpdateEnabled();
    void SetPixmap(const QString& path);
    [[nodiscard]] QPixmap ResizeImgToFit(const QPixmap &src, int window_width, int window_height);
};

#endif // MAINWINDOW_H
