
#ifndef OVERVIEWPAGE_H
#define OVERVIEWPAGE_H

#include <QWidget>
#include <QWidget>
#include "listings.h"
#include "chatwindow.h"
#include "blockbrowser.h"

namespace Ui {
    class OverviewPage;
}
class ClientModel;
class WalletModel;
class TxViewDelegate;
class TransactionFilterProxy;

QT_BEGIN_NAMESPACE
class QModelIndex;
QT_END_NAMESPACE

/** Overview ("home") page widget */
class OverviewPage : public QWidget
{
    Q_OBJECT

public:
    explicit OverviewPage(QWidget *parent = 0);
    ~OverviewPage();

    void setClientModel(ClientModel *clientModel);
    void setWalletModel(WalletModel *walletModel);
    void showOutOfSyncWarning(bool fShow);
    void updatePlot(int count);

public slots:
    void setBalance(qint64 balance, qint64 unconfirmedBalance, qint64 immatureBalance);

signals:
    void transactionClicked(const QModelIndex &index);

private:
    Ui::OverviewPage *ui;
    CCexBox *ccexbox;
    ChatWindow *chatwindow;
    BlockBrowser *blockbrowser;
    ClientModel *clientModel;
    WalletModel *walletModel;
    qint64 currentBalance;
    qint64 currentUnconfirmedBalance;
    qint64 currentImmatureBalance;
    QVector<double> vX;
    QVector<double> vY;

    TxViewDelegate *txdelegate;
    TransactionFilterProxy *filter;

private slots:
    void updateDisplayUnit();
    void handleTransactionClicked(const QModelIndex &index);
    void updateAlerts(const QString &warnings);
    void on_commandLinkButton_clicked();
    void on_commandLinkButton_2_clicked();
    void on_commandLinkButton_3_clicked();
};

#endif // OVERVIEWPAGE_H
