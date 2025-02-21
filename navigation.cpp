//
// Created by vitorhprsilva on 2/21/25.
//
#include <QApplication>
#include <QWebEngineView>
#include <QWebEngineProfile>
#include <QWebEngineSettings>
#include "navigation.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWebEngineView *view = new QWebEngineView();

    QWebEngineProfile *profile = QWebEngineProfile::defaultProfile();
    profile->settings()->setAttribute(QWebEngineSettings::JavascriptEnabled, true);
    profile->settings()->setAttribute(QWebEngineSettings::LocalContentCanAccessRemoteUrls, true);
    profile->settings()->setAttribute(QWebEngineSettings::LocalContentCanAccessFileUrls, true);
    profile->settings()->setAttribute(QWebEngineSettings::AllowRunningInsecureContent, true);


    view->setUrl(QUrl("https://www.google.com"));
    view->resize(1024, 768);
    view->show();

    view->page()->runJavaScript(R"(
        document.body.style.backgroundColor = 'black';
        document.body.style.color = 'white';
    )");

    return app.exec();
}
