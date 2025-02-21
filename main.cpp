#include <QApplication>
#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWebEngineView>
#include <QWebEnginePage>
#include <QWebEngineSettings>
#include <QDebug>
#include <QPixmap>
#include <QIcon>

class Browser : public QMainWindow {
    Q_OBJECT

public:
    Browser(QWidget *parent = nullptr) : QMainWindow(parent) {
        // setWindowTitle("Browser Vitor");
        setGeometry(100, 100, 800, 600);

        QWidget *topWidget = new QWidget(this);
        QHBoxLayout *topLayout = new QHBoxLayout(topWidget);
        QWidget *centralWidget = new QWidget(this);
        QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
        QWidget *bottomWidget = new QWidget(this);
        QHBoxLayout *bottomLayout = new QHBoxLayout(bottomWidget);


        searchBar = new QLineEdit(this);
        searchBar->setPlaceholderText("Digite o texto para pesquisar...");


        QPushButton *backButton = new QPushButton(this);
        QIcon backIcon(":/icons/icons/back.svg");
        if (backIcon.isNull()) {
            qDebug() << "Falha ao carregar o ícone backIcon.svg";
        } else {
            qDebug() << "Ícone backIcon.svg carregado com sucesso!";
        }
        backButton->setIcon(backIcon);
        backButton->setIconSize(QSize(24, 24));  // Ajusta o tamanho do ícone
        backButton->setStyleSheet("QPushButton {"
                                  "   color: transparent;"
                                  "   background-color: transparent;"
                                  "   border: none;"
                                  "   border-radius: 3px;"
                                  "}"
                                  "QPushButton::hover {"
                                  "   border: 1px solid black;"
                                  "}");

        // Criação do botão de avançar
        QPushButton *forwardButton = new QPushButton(this);
        QIcon forwardIcon(":/icons/icons/forward.svg");
        if (forwardIcon.isNull()) {
            qDebug() << "Falha ao carregar o ícone forward.svg";
        } else {
            qDebug() << "Ícone forward.svg carregado com sucesso!";
        }
        forwardIcon = forwardIcon.pixmap(24, 24);
        forwardButton->setIcon(forwardIcon);
        forwardButton->setIconSize(QSize(24, 24));  // Ajusta o tamanho do ícone
        forwardButton->setStyleSheet("QPushButton {"
                                     "   color: transparent;"
                                     "   background-color: transparent;"
                                     "   border: none;"
                                     "   border-radius: 3px;"
                                     "}"
                                     "QPushButton::hover {"
                                     "   border: 1px solid black;"
                                     "}");

        topLayout->addWidget(searchBar);
        topLayout->addWidget(backButton);
        topLayout->addWidget(forwardButton);

        webView = new QWebEngineView(this);
        webView->setUrl(QUrl("https://www.google.com"));
        bottomLayout->addWidget(webView);

        mainLayout->addWidget(topWidget);
        mainLayout->addWidget(bottomWidget);

        mainLayout->setStretchFactor(topWidget, 0);
        mainLayout->setStretchFactor(bottomWidget, 1);

        setCentralWidget(centralWidget);

        QWebEngineSettings *settings = webView->settings();
        settings->setAttribute(QWebEngineSettings::JavascriptEnabled, true);

        connect(webView, &QWebEngineView::urlChanged, this, &Browser::updateSearchBar);
        connect(searchBar, &QLineEdit::returnPressed, this, &Browser::loadPage);
        connect(backButton, &QPushButton::clicked, webView, &QWebEngineView::back);
        connect(forwardButton, &QPushButton::clicked, webView, &QWebEngineView::forward);


        settings->setAttribute(QWebEngineSettings::AutoLoadImages, true);
    }

private slots:
    void loadPage() {
        QString url = searchBar->text();
        if (!url.isEmpty()) {
            if (!url.startsWith("www.")) {
                url = "www." + url;
            }
            if (!url.startsWith("https://")) {
                url = "https://" + url;
            }
            webView->setUrl(QUrl(url));
        }
    }

    void updateSearchBar(const QUrl &url) {
        qDebug() << url.toString();
        searchBar->setText(url.toString());
    }

private:
    QWebEngineView *webView;
    QLineEdit *searchBar;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Browser browser;
    browser.show();

    return app.exec();
}

#include "main.moc"
