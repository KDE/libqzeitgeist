#include "mainwindow.h"
#include <QtWebKit/QWebView>
#include <QtCore/QDebug>
#include <QtGui/QMenuBar>
#include <QtGui/QListView>
#include <QtGui/QDockWidget>

#include <QZeitgeist/Log>
#include <QZeitgeist/Manifestation>
#include <QZeitgeist/Interpretation>
#include <QZeitgeist/LogModel>

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

    QZeitgeist::LogModel *history = new QZeitgeist::LogModel(this);
    QZeitgeist::DataModel::Event eventTemplate;
    QZeitgeist::DataModel::Subject subjectTemplate;
    subjectTemplate.setInterpretation(QZeitgeist::Interpretation::Subject::NFOWebsite);
    eventTemplate.setSubjects(QZeitgeist::DataModel::SubjectList() << subjectTemplate);

    history->setResultType(QZeitgeist::Log::MostRecentSubjects);
    history->setEventTemplates(QZeitgeist::DataModel::EventList() << eventTemplate);

    QDockWidget *historyDock = new QDockWidget(tr("History"), this);
    addDockWidget(Qt::LeftDockWidgetArea, historyDock);
    QAbstractItemView *historyView = new QListView(historyDock);
    historyView->setModel(history);
    connect(historyView, SIGNAL(activated(QModelIndex)), this, SLOT(loadHistory(QModelIndex)));
    historyDock->setWidget(historyView);
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

void MainWindow::loadHistory(const QModelIndex &idx)
{
    m_webView->load(idx.data(QZeitgeist::LogModel::URLRole).toUrl());
}

#include "mainwindow.moc"
