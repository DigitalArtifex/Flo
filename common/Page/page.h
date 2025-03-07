#ifndef PAGE_H
#define PAGE_H

#include <QFrame>
#include <qwizard.h>

class Page : public QFrame
{
    Q_OBJECT
public:
    Page(QWidget *parent);
    ~Page();

public slots:
    void close();

signals:
    void closed(Page*);
    void dialogRequested(QDialog *);
    void wizardRequested(QWizard *);
};

#endif // PAGE_H
