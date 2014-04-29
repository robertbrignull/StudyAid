#include <iostream>
#include <algorithm>

#include <QHBoxLayout>
#include <QMouseEvent>
#include <QPainter>
#include <QLabel>
#include <QVariantAnimation>

#include "model.h"
#include "latex/latex.h"
#include "widgets/imageButton.h"
#include "widgets/resizableImage.h"
#include "widgets/resizableStackedWidget.h"
#include "views/factListView.h"
#include "views/factList.h"
#include "database/methods.h"

#include "views/expandingFactWidget.h"

ExpandingFactWidget::ExpandingFactWidget(Fact fact, Model *model, ResizableStackedWidget *pageStack, FactListView *factListView, QWidget *parent)
    : QWidget(parent)
{
    this->model = model;
    this->pageStack = pageStack;
    this->fact = fact;
    this->factListView = factListView;

    headColor = QColor(QString::fromStdString(std::string("#") + Database::findFactType(fact.type).colour));
    bodyColor = Qt::white;
    radius = 4;
    border = 16;

    expanded = false;
    currentHeight = 0.0;



    headWidget = new QWidget();
    QHBoxLayout *headLayout = new QHBoxLayout(headWidget);
    headLayout->setContentsMargins(16, 8, 16, 8);

    nameLabel = new QLabel(QString::fromStdString(fact.name));
    nameLabel->setWordWrap(true);
    nameLabel->setScaledContents(true);

    QFont font = nameLabel->font();
    font.setPointSize(18);
    nameLabel->setFont(font);

    QPalette pal = nameLabel->palette();
    pal.setColor(QPalette::WindowText, Qt::white);
    pal.setColor(QPalette::Text, Qt::white);
    nameLabel->setPalette(pal);

    viewButton = new ImageButton(QPixmap(":/images/arrow_right_white.png"), QSize(24, 24));

    moveButton = new ImageButton(QPixmap(":/images/move_white.png"), QSize(24, 24));
    moveAboveButton = new ImageButton(QPixmap(":/images/arrow_up_white.png"), QSize(24, 24));
    moveBelowButton = new ImageButton(QPixmap(":/images/arrow_down_white.png"), QSize(24, 24));

    headLayout->addWidget(nameLabel);
    headLayout->addWidget(moveBelowButton);
    headLayout->addWidget(moveAboveButton);
    headLayout->addWidget(moveButton);
    headLayout->addWidget(viewButton);

    deactivateMoveMode();

    headWidget->setParent(this);
    headWidget->show();

    headWidgetHeight = headWidget->heightForWidth(size().width());
    headWidget->setGeometry(0, 0, size().width(), headWidgetHeight);

    imageFilename = getFactImageFilename(fact);
    imageNeedsLoading = true;
    imageNeedsScaling = true;



    setFixedHeight(headWidgetHeight);



    connect(viewButton, SIGNAL(clicked()), this, SLOT(viewButtonClicked()));

    connect(moveButton, SIGNAL(clicked()), this, SLOT(moveButtonClickedSlot()));
    connect(moveAboveButton, SIGNAL(clicked()), this, SLOT(moveAboveButtonClickedSlot()));
    connect(moveBelowButton, SIGNAL(clicked()), this, SLOT(moveBelowButtonClickedSlot()));

    connect(this, SIGNAL(moveButtonClicked(Fact)), factListView, SIGNAL(moveButtonClicked(Fact)));
    connect(this, SIGNAL(moveCompleted()), factListView, SIGNAL(moveCompleted()));

    connect(factListView, SIGNAL(moveButtonClicked(Fact)), this, SLOT(activateMoveMode(Fact)));
    connect(factListView, SIGNAL(moveCompleted()), this, SLOT(deactivateMoveMode()));

    connect(model, SIGNAL(factEdited(Fact)), this, SLOT(factEditedSlot(Fact)));
    connect(model, SIGNAL(factRendered(Fact, bool)), this, SLOT(factRenderedSlot(Fact, bool)));
}

void ExpandingFactWidget::setExpanded(bool expanded)
{
    if (expanded != this->expanded) {
        this->expanded = expanded;

        QVariantAnimation *animation = new QVariantAnimation(this);
        animation->setStartValue((expanded) ? 0.0 : 1.0);
        animation->setEndValue((expanded) ? 1.0 : 0.0);
        animation->setDuration(250);
        animation->setEasingCurve(QEasingCurve::InOutCubic);

        connect(animation, &QVariantAnimation::valueChanged, [=](QVariant value){
            currentHeight = value.toFloat();
            setFixedHeight(headWidgetHeight + (scaledImage.height() + border*2) * currentHeight);
            repaint();
        });

        animation->start();
    }
}

void ExpandingFactWidget::resizeEvent(QResizeEvent *event)
{
    headWidgetHeight = headWidget->heightForWidth(event->size().width());
    headWidget->setGeometry(0, 0, event->size().width(), headWidgetHeight);

    imageNeedsScaling = true;

    setFixedHeight(headWidgetHeight + (scaledImage.height() + border*2) * currentHeight);
}

void ExpandingFactWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && event->y() <= headWidgetHeight) {
        setExpanded(!expanded);
    }
}

void ExpandingFactWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    QSize headSize = headWidget->size();
    QSize totalSize = size();

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    painter.setPen(QPen(QBrush(headColor), 1));
    painter.setBrush(QBrush(bodyColor));
    painter.drawRoundedRect(1, headSize.height()-radius*2, totalSize.width()-2, totalSize.height()-headSize.height()+radius*2-2, radius, radius);

    painter.setPen(QPen(QBrush(headColor), 1));
    painter.setBrush(QBrush(headColor));
    painter.drawRoundedRect(1, 1, totalSize.width()-2, headSize.height()-2, radius, radius);



    if (imageNeedsLoading) {
        image = QPixmap(QString::fromStdString(imageFilename));
        imageNeedsLoading = false;
        imageNeedsScaling = true;
    }

    if (image.width() != 0 && expanded) {
        if (imageNeedsScaling) {
            scaledImage = image.scaledToWidth(std::min(width() - border*2, 1000), Qt::SmoothTransformation);
            imageNeedsScaling = false;
        }

        painter.drawPixmap((width() - scaledImage.width()) / 2, headWidgetHeight + border, scaledImage);
    }
}

void ExpandingFactWidget::viewButtonClicked()
{
    model->setFactSelected(fact);
    pageStack->setCurrentIndex(2);
}

void ExpandingFactWidget::moveButtonClickedSlot()
{
    if (inMoveMode) {
        emit moveCompleted();
    }
    else {
        emit moveButtonClicked(fact);
    }
}

void ExpandingFactWidget::moveAboveButtonClickedSlot()
{
    moveFact.parent = fact.parent;
    moveFact.ordering = fact.ordering;

    model->editFactOrdering(moveFact);

    emit moveCompleted();
}

void ExpandingFactWidget::moveBelowButtonClickedSlot()
{
    moveFact.parent = fact.parent;
    moveFact.ordering = fact.ordering + 1;

    model->editFactOrdering(moveFact);

    emit moveCompleted();
}

void ExpandingFactWidget::activateMoveMode(Fact fact)
{
    // Very important we don't enter move mode if it's one of our ancestors
    // being moved. Making a section its own parent causes problems!
    bool isAncestor = false;
    Fact currentFact = this->fact;

    while (currentFact.parent != -1) {
        FactList *factList = factListView->idFactListMap.at(currentFact.parent);
        if (factList->fact.id == fact.id) {
            isAncestor = true;
            break;
        }
        currentFact = factList->fact;
    }



    inMoveMode = true;

    if (fact.id == this->fact.id) {
        moveButton->show();
        viewButton->hide();
        moveAboveButton->hide();
        moveBelowButton->hide();
    }
    else {
        moveButton->hide();
        viewButton->hide();

        if (!isAncestor) {
            moveFact = fact;

            moveAboveButton->show();
            moveBelowButton->show();
        }
        else {
            moveAboveButton->hide();
            moveBelowButton->hide();
        }
    }
}

void ExpandingFactWidget::deactivateMoveMode()
{
    inMoveMode = false;

    viewButton->show();
    moveButton->show();
    moveAboveButton->hide();
    moveBelowButton->hide();
}

void ExpandingFactWidget::factEditedSlot(Fact fact)
{
    if (fact.id == this->fact.id) {
        this->fact = fact;

        nameLabel->setText(QString::fromStdString(fact.name));
        headColor = QColor(QString::fromStdString(std::string("#") + Database::findFactType(fact.type).colour));

        adjustSize();
    }
}

void ExpandingFactWidget::factRenderedSlot(Fact fact, bool success)
{
    if (fact.id == this->fact.id && success) {
        imageNeedsLoading = true;
        imageNeedsScaling = true;

        headColor = QColor(QString::fromStdString(std::string("#") + Database::findFactType(fact.type).colour));

        adjustSize();
    }
}