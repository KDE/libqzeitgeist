#include "mainwindow.h"
#include <QtWebKit/QWebView>
#include <QtCore/QDebug>
#include <QtGui/QMenuBar>
#include <QtGui/QListView>
#include <QtGui/QDockWidget>

#include <QZeitgeist/Log>
#include <QZeitgeist/Manifestation>
#include <QZeitgeist/Interpretation>
#include <QZeitgeist/LogBrowser>

MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags)
    : QMainWindow(parent, flags)
{
    m_webView = new QWebView(this);
    m_webView->load(QUrl("http://zeitgeist-project.com"));
    connect(m_webView, SIGNAL(loadFinished(bool)), this, SLOT(logPage()));
    setCentralWidget(m_webView);

    QMenu *menu = menuBar()->addMenu(tr("&File"));
    QAction *quitAction = menu->addAction(tr("&Quit"));
    connect(quitAction, SIGNAL(triggered(bool)), this, SLOT(close()));

    m_log = new QZeitgeist::Log(this);

    QDockWidget *historyDock = new QDockWidget(tr("History"), this);
    addDockWidget(Qt::LeftDockWidgetArea, historyDock);
    QZeitgeist::LogBrowser *historyView = new QZeitgeist::LogBrowser(historyDock);
    connect(historyView, SIGNAL(activated(QZeitgeist::DataModel::Event)), this, SLOT(loadHistory(QZeitgeist::DataModel::Event)));
    historyDock->setWidget(historyView);

    QZeitgeist::DataModel::Event eventTemplate;
    QZeitgeist::DataModel::Subject subjectTemplate;
    subjectTemplate.setInterpretation(QZeitgeist::Interpretation::Subject::NFOWebsite);
    eventTemplate.setSubjects(QZeitgeist::DataModel::SubjectList() << subjectTemplate);
    historyView->addEventFilter(QZeitgeist::DataModel::EventList() << eventTemplate, tr("Websites"));
    historyView->setApplicationActor("application://zeitgeist-browser-demo.desktop", tr("Zeitgeist Browser Demo"));
}

void MainWindow::logPage()
{
    QZeitgeist::DataModel::EventList events;
    QZeitgeist::DataModel::Event event;
    event.setActor("applicaton://zeitgeist-browser-demo.desktop");
    event.setInterpretation(QZeitgeist::Interpretation::Event::ZGAccessEvent);
    event.setManifestation(QZeitgeist::Manifestation::Event::ZGUserActivity);

    QZeitgeist::DataModel::Subject subject;
    subject.setInterpretation(QZeitgeist::Interpretation::Subject::NFOWebsite);
    subject.setManifestation(QZeitgeist::Manifestation::Subject::NFORemoteDataObject);
    subject.setUri(m_webView->url().toString());
    subject.setText(m_webView->title());

    event.setSubjects(QZeitgeist::DataModel::SubjectList() << subject);
    m_log->insertEvents(QZeitgeist::DataModel::EventList() << event);
    qDebug() << "Logged" << subject.uri();
}

void MainWindow::loadHistory(const QZeitgeist::DataModel::Event &event)
{
    m_webView->load(event.subjects()[0].uri());
}

#include "mainwindow.moc"
