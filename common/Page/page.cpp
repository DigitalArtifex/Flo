#include "page.h"

Page::Page(QWidget *parent) : QFrame(parent)
{
    setProperty("class", QStringList {"Page"} + property("class").toStringList());
}

Page::~Page() {}

void Page::close()
{
    emit closed(this);
}
