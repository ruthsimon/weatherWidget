#include "widget.h"//

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    // Window Size and Title
    setWindowTitle("Weather Widget");
    resize(350, 600);

    // Temperature Label
    temperatureLabel = new QLabel("+24°", this);
    temperatureLabel->setFont(QFont("Arial", 70, QFont::Bold));
    temperatureLabel->setObjectName("temperatureLabel");
    temperatureLabel->setStyleSheet("color: #4F787D"); // Initial color for temperature label

    // Place Label
    placeLabel = new QLabel("MADRID", this);
    placeLabel->setFont(QFont("Helvetica", 11, QFont::Medium));
    placeLabel->setObjectName("placeLabel");
    placeLabel->setStyleSheet("color: #45355a"); // Initial color for place label

    // Weather Label
    weatherLabel = new QLabel("Clear", this);
    weatherLabel->setFont(QFont("Arial", 10, QFont::Medium));
    weatherLabel->setObjectName("weatherLabel");

    // Current time Label
    timeLabel = new QLabel(this);
    timeLabel->setFont(QFont("Arial", 11, QFont::Medium));
    timeLabel->setAlignment(Qt::AlignRight | Qt::AlignBottom);

    // Time update timer
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Widget::updateTime);
    timer->start(1000); // 1000 milliseconds = 1 second

    // Animation timer to change weather
    animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, this, &Widget::changeWeather);
    animationTimer->start(4000); // Change weather every 8 seconds

    // Call updateTime initially to set the current time immediately
    updateTime();

    // Layout for Labels
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 50, 0, 0);
    mainLayout->setSpacing(7);

    // Horizontal Layout for Temperature Label
    QHBoxLayout *tempLayout = new QHBoxLayout;
    tempLayout->addWidget(temperatureLabel);
    tempLayout->setAlignment(Qt::AlignHCenter); // Aligns temperature label to the center horizontally

    // Horizontal Layout for Place Label
    QHBoxLayout *placeLayout = new QHBoxLayout;
    placeLayout->addWidget(placeLabel);
    placeLayout->setAlignment(Qt::AlignHCenter);

    // Horizontal Layout for Weather Label
    QHBoxLayout *weatherLayout = new QHBoxLayout;
    weatherLayout->addWidget(weatherLabel);
    weatherLayout->setAlignment(Qt::AlignHCenter);

    // Horizontal Layout for current time
    QHBoxLayout *timeLayout = new QHBoxLayout;
    timeLayout->addWidget(timeLabel);
    timeLayout->setContentsMargins(0, 0, 10, 20); // Added bottom margin to lift the timeLabel
    timeLayout->setAlignment(Qt::AlignRight | Qt::AlignBottom); // Align time label to the bottom right

    // Layout for Labels (temperature, place, weather)
    QVBoxLayout *labelsLayout = new QVBoxLayout;
    labelsLayout->setAlignment(Qt::AlignTop);
    labelsLayout->addLayout(tempLayout);
    labelsLayout->addLayout(placeLayout);
    labelsLayout->addLayout(weatherLayout);

    // Add Horizontal Layouts to the Main Layout
    mainLayout->addLayout(labelsLayout);
    mainLayout->addLayout(timeLayout);

    //mousetracking
    setMouseTracking(true);

    // Initialize default gradient
    currentGradient = QLinearGradient(0, 0, 0, height());
    currentGradient.setColorAt(0, QColor(15, 33, 41)); // Dark Blue
    currentGradient.setColorAt(1, QColor(71, 51, 74)); // Purple

    // Initialize mountain gradients
    mountainGradient1 = QLinearGradient(0, height() - 150, 0, height());
    mountainGradient1.setColorAt(0.3, QColor(47, 43, 60)); // Dark Purple
    mountainGradient1.setColorAt(1, QColor(9, 27, 33)); // Dark Blue

    mountainGradient2 = QLinearGradient(0, height() - 140, width() + 180, height());
    mountainGradient2.setColorAt(0, QColor(47, 43, 60)); // Dark Purple
    mountainGradient2.setColorAt(1, QColor(9, 27, 33)); // Dark Blue

    //sunPositions
    sunPositions = { QPoint(370, 90), QPoint(230, 430), QPoint(174, 247) }; // Example positions
    state = 0;
    currentSunPosition = sunPositions[state];

    // Initialize state
    setLayout(mainLayout);
}


void Widget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);

    // Enable antialiasing for smoother lines
    painter.setRenderHint(QPainter::Antialiasing);

    // Draw the background gradient using currentGradient
    painter.fillRect(rect(), currentGradient);

    // Draw the mountain shapes
    painter.setPen(Qt::NoPen);

    // First mountain
    painter.setBrush(mountainGradient1);
    QPainterPath path1;
    path1.moveTo(-70, height()-30);
    path1.quadTo(width() / 7 , height() - 180, width()/2+100, height());
    path1.lineTo(0, height()+1000);
    painter.drawPath(path1);

    // Second mountain
    painter.setBrush(mountainGradient2);
    QPainterPath path2;
    path2.moveTo(-130, height());
    path2.quadTo(width() / 2+350, height() - 190, width() + 20, height());
    path2.lineTo(width() + 150, height());
    painter.drawPath(path2);

    // Draw circles
    if (placeLabel->text() == "ANKARA")
    {
        sunPositions[state].setY(174);
        sunPositions[state].setX(247);        // Adjust the y-coordinate as needed
    }
    if (placeLabel->text() == "MADRID")
    {
        sunPositions[state].setY(370);
        sunPositions[state].setX(90);        // Adjust the y-coordinate as needed
    }
    drawCircles(painter);
}


// Function to draw circles
void Widget::drawCircles(QPainter &painter)
{
    // Circle colors and styles
    QColor crescentColor(188, 174, 118); // Crescent color
    QColor clearColor(254, 255, 223); // Clear color for non-sunny conditions
    QColor sunnyColor(255, 219, 80); // Sunny yellow color


    // current center position for the sun/moon
    QPoint center = sunPositions[state];

    // Adjusted sizes for smaller circles
    int radius1 = 60;
    int radius2 = 50;
    int radius3 = 40;
    int mainRadius = 30;

    QColor circleColor1;

    // Set circleColor1 based on placeLabel text
    if (placeLabel->text() == "MADRID") {
        circleColor1 = QColor(188, 174, 118, 25); // Color for Madrid
    } else if (placeLabel->text() == "ANKARA") {
        circleColor1 = QColor(255, 223, 128, 25); // Brighter color for Ankara
    } else {
        circleColor1 = QColor(240, 240, 240, 25); // Another color for other places
    }

    if (placeLabel->text() == "MADRID") {
        // Create a QPainterPath for the moon crescent
        QPainterPath moonCrescentPath;

        // Outer arc for the moon
        QPainterPath outerArc;
        outerArc.arcMoveTo(center.x() - mainRadius, center.y() - mainRadius, 2 * mainRadius, 2 * mainRadius, 0);
        outerArc.arcTo(center.x() - mainRadius, center.y() - mainRadius, 2 * mainRadius, 2 * mainRadius, 0, 360);

        // Inner arc for the moon
        QPainterPath innerArc;
        innerArc.arcMoveTo(center.x() - mainRadius + 10, center.y() - mainRadius - 9, 2 * mainRadius, 2 * mainRadius, 0);
        innerArc.arcTo(center.x() - mainRadius + 10, center.y() - mainRadius - 9, 2 * mainRadius, 2 * mainRadius, 0, 300);

        // Combine the outer and inner arcs to create the crescent shape
        moonCrescentPath = outerArc.subtracted(innerArc);

        // Draw the crescent moon shape
        painter.setBrush(crescentColor);
        painter.drawPath(moonCrescentPath);
    }
    else if (placeLabel->text() == "ANKARA") {
        // Draw the main circle for sunny weather
        painter.setBrush(sunnyColor);
        painter.drawEllipse(center.x() - mainRadius, center.y() - mainRadius, 2 * mainRadius, 2 * mainRadius);
    }
    else {
        // Draw the main circle for other weather states
        painter.setBrush(clearColor);
        painter.drawEllipse(center.x() - mainRadius, center.y() - mainRadius, 2 * mainRadius, 2 * mainRadius);
    }

    // Draw surrounding circles with location-specific color
    painter.setBrush(circleColor1);
    painter.drawEllipse(center.x() - radius1, center.y() - radius1, 2 * radius1, 2 * radius1);
    painter.drawEllipse(center.x() - radius2, center.y() - radius2, 2 * radius2, 2 * radius2);
    painter.drawEllipse(center.x() - radius3, center.y() - radius3, 2 * radius3, 2 * radius3);
}


// Check if sun is clicked
bool Widget::isClickOnSun(const QPoint &point)
{
    QPoint center = sunPositions[state];
    int mainRadius = 30;

    // Check distance clicked from circle
    int dx = point.x() - center.x();
    int dy = point.y() - center.y();
    return (dx * dx + dy * dy) <= (mainRadius * mainRadius);
}


void Widget::mousePressEvent(QMouseEvent *event)
{
    // Call changeWeather when the widget(sun) is clicked
    if (isClickOnSun(event->pos()))
    {
        changeWeather();
    }
}


void Widget::changeWeather() {
    QStringList cities = {"MOSCOW", "ANKARA", "MADRID"};
    QStringList temperatures = {"-13", "+32", "+24"};
    QStringList conditions = {"Frosty", "Hot", "Clear"};
    QStringList tempLabelColors = {"#a8ddff", "#fff5b8", "#4F787D"};
    QStringList placeLabelColors = {"#4497bf", "#f7a526", "#45355a"};
    QStringList weatherLabelColors = {"white", "white", "white"};
    QStringList bgColors = {"#b8f5ff", "#fff097", "#47334A"}; // Background colors for each city
    QStringList gradientColors = {"#29386f", "#ffbd3f", "#0F2129"}; // Gradient colors for each city
    QStringList mountainColor1Start = {"#f3ffff", "#e0d7a4", "#2f2b3c"}; // Mountain start colors
    QStringList mountainColor1End = {"#9af2ff", "#e7c77a", "#091B21"}; // Mountain end colors
    QStringList mountainColor2Start = {"#f3ffff", "#e0d7a4", "#2f2b3c"}; // Second mountain start colors
    QStringList mountainColor2End = {"#9af2ff", "#e7c77a", "#091B21"}; // Second mountain end colors
    QStringList timeLabelColors = {"#000000", "#000000", "white"}; // Crrent time colors

    // Update weather information
    placeLabel->setText(cities[state]);
    temperatureLabel->setText(temperatures[state] + "°");
    weatherLabel->setText(conditions[state]);

    // Set the current background gradient
    currentGradient = QLinearGradient(0, 0, 0, height());
    currentGradient.setColorAt(0, QColor(gradientColors[state]));
    currentGradient.setColorAt(1, QColor(bgColors[state]));

    // Set the current mountain gradients
    mountainGradient1 = QLinearGradient(0, height() - 150, 0, height());
    mountainGradient1.setColorAt(0.3, QColor(mountainColor1Start[state]));
    mountainGradient1.setColorAt(1, QColor(mountainColor1End[state]));

    mountainGradient2 = QLinearGradient(0, height() - 150, width() + 100, height());
    mountainGradient2.setColorAt(0, QColor(mountainColor2Start[state]));
    mountainGradient2.setColorAt(1, QColor(mountainColor2End[state]));

    // Set label colors based on the current state
    temperatureLabel->setStyleSheet("color: " + tempLabelColors[state]);
    placeLabel->setStyleSheet("color: " + placeLabelColors[state]);
    weatherLabel->setStyleSheet("color: " + weatherLabelColors[state]);
    timeLabel->setStyleSheet("color: " + timeLabelColors[state]); // Set timeLabel color


    state = (state + 1) % 3;
    if (state < 0 || state >= 3) {
        state = 0;
    }

    update();
}


// Update time
void Widget::updateTime()
{
    QString currentTime = QDateTime::currentDateTime().toString("dddd, hh:mm:ss");
    timeLabel->setText(currentTime);
}


// Return position o
QPoint Widget::sunPosition() const
{
    return currentSunPosition;
}




Widget::~Widget()
{
}

