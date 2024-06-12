#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLinearGradient>
#include <QPainter>
#include <QPixmap>
#include <QPainterPath>
#include <QMouseEvent>
#include <QDateTime>
#include <QTimer>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QLabel *temperatureLabel;
    QLabel *placeLabel;
    QLabel *weatherLabel;
    QLabel *timeLabel;
    QTimer *timer;
    QTimer *animationTimer;
    int state;
    QLinearGradient currentGradient;
    QLinearGradient mountainGradient1;
    QLinearGradient mountainGradient2;
    QList<QPoint> sunPositions;
    QPoint currentSunPosition;

private:
    void drawCircles(QPainter &painter);
    bool isClickOnSun(const QPoint &point);
    QPoint sunPosition() const;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void setBackgroundGradient(const QLinearGradient& gradient, QWidget* widget = nullptr);
    void setBackgroundAndLabelColors(const QString &bgColor, const QString &gradientColor, const QString &tempLabelColor, const QString &placeLabelColor, const QString &weatherLabelColor);
    void handleSunAnimationFinished();

private slots:
    void updateTime();
    void changeWeather();

};

#endif
