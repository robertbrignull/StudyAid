#pragma once

#include "map"

#include <QDialog>
#include <QString>

class DeleteDialog : public QDialog
{
    Q_OBJECT

public:
    DeleteDialog(QWidget *parent, QString text);

signals:
    void accepted();
    void cancelled();
};