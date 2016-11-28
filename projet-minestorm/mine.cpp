#include "mine.h"

Mine::Mine(QPoint point, double size, int timerLenght) : QObject(nullptr){
    this->setPoint(point);
    this->setSize(size);
    compteur = timerLenght/1000;
    directionLine.setPoints(_point, _point);
    createCollisionBox();
    angle = -7 + (rand() %(int)(7 - (-7) +1 ));
    pixmap.load(path);
    pixmap = pixmap.scaled(QSize(size,size),Qt::AspectRatioMode::KeepAspectRatio);

    //QTimer
    this->_timer = QSharedPointer<QTimer>(new QTimer());
    this->_timer->setSingleShot(false);
    connect(_timer.data(), SIGNAL(timeout()), this, SLOT(eclosion()));
    _timer->start(timerLenght);
}

void Mine::createCollisionBox(){
    QRect rect(QPoint(_point.x() - (_size),_point.y() - (_size)),QPoint(_point.x() + (_size),_point.y() + (_size)));
    _box = Box(rect);
}
QSharedPointer<QTimer> Mine::timer() const
{
    return _timer;
}

void Mine::setTimer(const QSharedPointer<QTimer> &timer)
{
    _timer = timer;
}

bool Mine::getIsEclosion() const
{
    return isEclosion;
}

void Mine::setIsEclosion(bool value)
{
    isEclosion = value;
}

double Mine::getCompteur() const
{
    return compteur;
}

void Mine::setCompteur(double value)
{
    compteur = value;
}


void Mine::draw(QPainter &painter){
    painter.drawPixmap(_point.x()-(pixmap.width()/2),_point.y()-(pixmap.height()/2),pixmap);
}

void Mine::move(QSize size){
    directionLine = directionLine.translated(directionLine.dx(),directionLine.dy());
    _point = directionLine.p1();

    // Check limit
    if (_point.x() > size.width()) {
        _point = QPoint(_point.x() - size.width(), _point.y());
        directionLine = QLine(QPoint(directionLine.x1() - size.width(), directionLine.y1()),QPoint(directionLine.x2() - size.width(), directionLine.y2()));
    }
    else if (_point.x() < 0) {
        _point = QPoint(_point.x() + size.width(), _point.y());
        directionLine = QLine(QPoint(directionLine.x1() + size.width(), directionLine.y1()),QPoint(directionLine.x2() + size.width(), directionLine.y2()));
    }
    else if (_point.y() > size.height()) {
        _point = QPoint(_point.x(), _point.y() - size.height());
        directionLine = QLine(QPoint(directionLine.x1(), directionLine.y1() - size.height()),QPoint(directionLine.x2(), directionLine.y2()  - size.height()));
    }
    else if (_point.y() < 0) {
        _point = QPoint(_point.x(), _point.y() + size.height());
        directionLine = QLine(QPoint(directionLine.x1(), directionLine.y1() + size.height()),QPoint(directionLine.x2(), directionLine.y2()  + size.height()));
    }

    updatePositionBox();
}

void Mine::updatePositionBox(){
    QRect rect(QPoint(_point.x() - (_size),_point.y() - (_size)),QPoint(_point.x() + (_size),_point.y() + (_size)));
    QPolygon polygon(rect);
    _box.setPolygon(polygon);
}

bool Mine::checkCollision(QPoint bulletPoint){
    return _box.getPolygon().containsPoint(bulletPoint, Qt::OddEvenFill);
}

void Mine::eclosion(){
    compteur--;
    if (compteur == 0) {
        _newPoint.setX(this->point().x() + 3 * cos(angle));
        _newPoint.setY(this->point().y() + 3 * sin(angle));
        directionLine.setPoints(point(),_newPoint);
        _timer.clear();
        isEclosion = true;
    }
}
QPixmap Mine::getPixmap() const{
    return pixmap;
}

void Mine::setPixmap(const QPixmap &value){
    pixmap = value;
}


QLine Mine::getDirectionLine() const{
    return directionLine;
}
void Mine::setDirectionLine(const QLine &value){
    directionLine = value;
}

QPoint Mine::point() const{
    return _point;
}
void Mine::setPoint(const QPoint &point){
    _point = point;
}

Box Mine::box() const{
    return _box;
}
void Mine::setBox(const Box &box){
    _box = box;
}

double Mine::size() const{
    return _size;
}
void Mine::setSize(double size){
    _size = size;
}

QPoint Mine::newPoint() const
{
    return _newPoint;
}

void Mine::setNewPoint(const QPoint &newPoint)
{
    _newPoint = newPoint;
}
