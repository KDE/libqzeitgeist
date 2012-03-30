#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

class QWebView;
class QListView;
class QModelIndex;

namespace QZeitgeist {
    class Log;
    class LogModel;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0, Qt::WindowFlags flags = 0);
private slots:
    void logPage();
    void loadHistory(const QModelIndex &);
private:
    QWebView *m_webView;
    QZeitgeist::Log *m_log;
};

#endif // MAINWINDOW_H
