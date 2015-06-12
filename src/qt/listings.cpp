#include "listings.h"
#include "ui_listings.h"
#include <QWebView>
#include <QUrl>
CCexBox::CCexBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CCexBox)
{
    ui->setupUi(this);
    
    QWebSettings *settings = QWebSettings::globalSettings();
	settings->setAttribute (QWebSettings::PluginsEnabled, true);
    ui->webView->load(QUrl("http://flaxscript.info"));
    QWebView* webViewChild = new QWebView;
    webViewChild->settings()->setAttribute(QWebSettings::PluginsEnabled, true);
}

CCexBox::~CCexBox()
{
    delete ui;
}
