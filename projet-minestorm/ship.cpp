#include "ship.h"
#include <memory>
Ship::Ship() : QObject(nullptr){
    pixmap.load(path);
    shipLine.setLine(400, 400, 400, 387);
    radiant = angle * M_PI / 180.0;
    createCollisionBox();
}
void Ship::acceleration(){
    if (currentSpeed  < 20)
        currentSpeed += 1;
    lastEcart_dx = shipLine.dx();
    lastEcart_dy = shipLine.dy();
}
void Ship::hited(){
    if(!immune && life >= 1){
        life--;
        respawn();
    }
}
void Ship::respawn(){
    if(_timerRespawn == nullptr){
        immune = true;
        qDebug() << "Création QTimer de réapparition";
        this->_timerRespawn = QSharedPointer<QTimer>(new QTimer());
        this->_timerRespawn->setSingleShot(false);
        connect(_timerRespawn.data(), SIGNAL(timeout()), this, SLOT(immunity()));
        _timerRespawn->start(1000);
    }
    shipLine.setLine(400, 400, 400, 387);
    updatePositionBox();
    pixmap.load(path);
    currentSpeed = 0;
    rotation = 0;
}
void Ship::rotateLeft(){
    auto left_x = shipLine.x1();
    auto left_y = shipLine.y1();
    auto newBX = cos(-radiant)*(shipLine.x2()-left_x) - sin(-radiant)*(shipLine.y2()-left_y) + left_x;
    auto newBY = sin(-radiant)*(shipLine.x2()-left_x) + cos(-radiant)*(shipLine.y2()-left_y) + left_y;
    int x = newBX + 1;
    double decimalx = x - newBX;
    if (decimalx < 0.5)
        newBX = x;
    int y = newBY + 1;
    double decimaly = y - newBY;
    if (decimaly < 0.5)
        newBY = y;
    shipLine = QLine(QPoint(left_x,left_y),QPoint(newBX,newBY));
    updatePositionBox();
    QPixmap pixmapRotated;
    pixmapRotated.load(path);
    QTransform t;
    rotation -= angle;
    t.rotate(rotation);
    pixmap = pixmapRotated.transformed(t, Qt::SmoothTransformation);
}
void Ship::rotateRight(){
    auto left_x = shipLine.x1();
    auto left_y = shipLine.y1();
    auto newBX = cos(radiant)*(shipLine.x2()-left_x) - sin(radiant)*(shipLine.y2()-left_y) + left_x;
    auto newBY = sin(radiant)*(shipLine.x2()-left_x) + cos(radiant)*(shipLine.y2()-left_y) + left_y;
    int x = newBX + 1;
    double decimalx = x - newBX;
    if (decimalx < 0.5)
        newBX = x;
    int y = newBY + 1;
    double decimaly = y - newBY;
    if (decimaly < 0.5)
        newBY = y;
    shipLine = QLine(QPoint(left_x,left_y),QPoint(newBX,newBY));
    updatePositionBox();
    QPixmap pixmapRotated;
    pixmapRotated.load(path);
    QTransform t;
    rotation += angle;
    t.rotate(rotation);
    pixmap = pixmapRotated.transformed(t);
}
void Ship::fire(){
    if(_timer == nullptr){
        this->_timer = QSharedPointer<QTimer>(new QTimer());
        this->_timer->setSingleShot(true);
        connect(_timer.data(), SIGNAL(timeout()), this, SLOT(shotSignal()));
        _timer->start(1000);
    }

    if (nbShot < 4) {
        Bullet shipBullet(shipLine.x1(), shipLine.y1(), shipLine.dx(), shipLine.dy(), shipLine.x2(),shipLine.y2());
        shipFire.push_back(shipBullet);
        nbShot++;
    }
}
void Ship::shotSignal(){
    qDebug() << "On remet les shot à 0 ";
    nbShot = 0;
    _timer.clear();
}
void Ship::immunity(){
    compteurTimer++;
    qDebug() << "Invincible : " << immune;
    if (compteurTimer >= 3 || life <= 1) {
        immune = false;
        _timerRespawn.clear();
        compteurTimer = 0;
        qDebug() << "invincible : "<< immune;
    }
}
bool Ship::getImmune() const
{
    return immune;
}

void Ship::setImmune(bool value)
{
    immune = value;
}

bool Ship::checkCollision(QPolygon poly){
    auto polygonCollision =  _box.getPolygon().intersected(poly);
    return polygonCollision.isEmpty();
}
void Ship::draw(QPainter &painter){
    if (immune) {
        painter.setPen(Qt::GlobalColor::red);
        painter.drawEllipse(shipLine.p1(),20,20);
    }
    painter.drawPixmap(shipLine.x1()-(pixmap.width()/2),shipLine.y1()-(pixmap.height()/2),pixmap);
    painter.drawLine(shipLine);
}
void Ship::drawBullet(QPainter &painter, QSize size, vector<QSharedPointer<Mine>> &_mines, vector<Explosion> &_explosions){
    scoreFrame = 0;
    int l = 0;
    int pos;
    for (vector<Bullet>::iterator it=shipFire.begin(); it!=shipFire.end();){
        bool bulletErased = false;
        pos = 0;
        painter.setPen(Qt::GlobalColor::red);
        shipFire[l].getBulletLine().translate(shipFire[l].getX_abscisse(), shipFire[l].getY_ordonne());
        shipFire[l].setBulletLine(shipFire[l].getBulletLine().translated(shipFire[l].getBulletLine().dx() + shipFire[l].getBulletLine().dx()/2, shipFire[l].getBulletLine().dy() +  shipFire[l].getBulletLine().dy()/2));
        painter.drawLine(shipFire[l].getBulletLine());
        for (auto itMine = _mines.begin(); itMine != _mines.end(); ++itMine) {
            auto point2 = shipFire[l].getBulletLine().p2();
            if (_mines[pos]->checkCollision(point2)){
                Explosion explosionMine(_mines[pos]->point());
                _explosions.push_back(explosionMine);
                if (_mines[pos]->checkCollision(point2)){
                    mines_to_be_deleted.push_back(*itMine);
                    shipFire.erase(it);
                    bulletErased = true;
                    scoreFrame += 100;
                    qDebug() << "Collision bullet mine";
                }
            }
            pos++;
        }
        while(!mines_to_be_deleted.empty() ) {
            std::remove(begin(_mines),end(_mines),mines_to_be_deleted.front());
            _mines.pop_back();
            mines_to_be_deleted.pop_front();
        }
        if (!bulletErased){
            if (shipFire[l].getBulletLine().x1() > size.width() || shipFire[l].getBulletLine().x1() < 0)
                shipFire.erase(it);
            else if (shipFire[l].getBulletLine().y1() > size.height() || shipFire[l].getBulletLine().y1() < 0)
                shipFire.erase(it);
            else
                ++it;
        }
        l++;
    }
}
void Ship::move(QSize size){
    shipLine = shipLine.translated(lastEcart_dx,lastEcart_dy);

    if (shipLine.x1() > size.width()) {

        shipLine = QLine(QPoint(shipLine.x1() - size.width(), shipLine.y1()),QPoint(shipLine.x2() - size.width(), shipLine.y2()));
    }
    else if (shipLine.x1() < 0) {
        shipLine = QLine(QPoint(shipLine.x1() + size.width(), shipLine.y1()),QPoint(shipLine.x2() + size.width(), shipLine.y2()));
    }

    else if (shipLine.y1() > size.height()) {
        shipLine = QLine(QPoint(shipLine.x1(), shipLine.y1() - size.height()),QPoint(shipLine.x2(), shipLine.y2() - size.height()));
    }
    else if (shipLine.y1() < 0) {
        shipLine = QLine(QPoint(shipLine.x1(), shipLine.y1() + size.height()),QPoint(shipLine.x2(), shipLine.y2() + size.height()));
    }
    updatePositionBox();
    if (currentSpeed > 0)
        currentSpeed -= 0.1;
}
void Ship::createCollisionBox(){
    QRect rect(QPoint(shipLine.x1() - (size/2),shipLine.y1() - (size/2)),QPoint(shipLine.x1() + (size/2) - 2,shipLine.y1() + (size/2)));
    _box = Box(rect);
}
void Ship::updatePositionBox(){
    QRect rect(QPoint(shipLine.x1() - (size/2),shipLine.y1() - (size/2)),QPoint(shipLine.x1() + (size/2) - 5,shipLine.y1() + (size/2)));
    QPolygon polygon(rect);
    _box.setPolygon(polygon);
}
int Ship::getLastEcart_dx() const{
    return lastEcart_dx;
}

void Ship::setLastEcart_dx(int value){
    lastEcart_dx = value;
}

double Ship::getCurrentSpeed() const{
    return currentSpeed;
}

void Ship::setCurrentSpeed(double value){
    currentSpeed = value;
}
QLine Ship::getShipLine() const{
    return shipLine;
}
void Ship::setShipLine(const QLine &value){
    shipLine = value;
}
int Ship::getLife() const{
    return life;
}
void Ship::setLife(int value){
    life = value;
}
double Ship::getScoreFrame() const{
    return scoreFrame;
}

void Ship::setScoreFrame(double value){
    scoreFrame = value;
}
Box Ship::box() const{
    return _box;
}
void Ship::setBox(const Box &box){
    _box = box;
}
vector<Bullet> Ship::getShipFire() const{
    return shipFire;
}
void Ship::setShipFire(const vector<Bullet> &value){
    shipFire = value;
}
int Ship::getLastEcart_dy() const{
    return lastEcart_dy;
}
void Ship::setLastEcart_dy(int value){
    lastEcart_dy = value;
}
float Ship::getAngle() const{
    return angle;
}
void Ship::setAngle(float value){
    angle = value;
}
float Ship::getRadiant() const{
    return radiant;
}
void Ship::setRadiant(float value){
    radiant = value;
}
