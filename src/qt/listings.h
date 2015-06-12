#ifndef CCEXBOX_H
#define CCEXBOX_H

#include <QDialog>

namespace Ui {
class CCexBox;
}

class CCexBox : public QDialog
{
    Q_OBJECT
    
public:
    explicit CCexBox(QWidget *parent = 0);
    ~CCexBox();
    
private:
    Ui::CCexBox *ui;
};

#endif // CCEXBOX_H
