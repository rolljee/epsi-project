#include "minestorm.h"

Minestorm::Minestorm(const QSize &size,QObject *parent):Game(size,parent) {
    initMine();
    font.setPixelSize(15);
    _mines.reserve(31);
    Game::start();
}

void Minestorm::addMines(QPoint point, double size,int timerLenght) {
    _mines.push_back(QSharedPointer<Mine>(new Mine(point, size,timerLenght)));
}
void Minestorm::step() {
    if (myShip.getCurrentSpeed() > 0)
        myShip.move(size());
}
void Minestorm::draw(QPainter &painter, QRect &rect) {
    painter.fillRect(rect, QColor(0,0,0));
    QString shipVie = QString::number(myShip.getLife() -1);
    auto indexExplo = 0u;
    for (auto itExplo=_explosions.begin(); itExplo != _explosions.end();){
        _explosions[indexExplo].draw(painter);
        ++itExplo;
        indexExplo++;
    }
    if (!_mines[0]->getIsEclosion()) {
        QString compteurEclosion = QString::number(_mines[0]->getCompteur());
        painter.setPen(Qt::GlobalColor::red);
        font.setPixelSize(100);
        painter.setFont(font);
        painter.drawText(250,400, compteurEclosion);
    }
    auto index = 0;
    for (auto itMine=_mines.begin(); itMine != _mines.end(); ++itMine){
        _mines[index]->move(size());
        _mines[index]->draw(painter);
        if (!myShip.checkCollision(_mines[index]->box().getPolygon())){
            if(!myShip.getImmune()) {
                Explosion explosionMine(_mines[index]->point());
                Explosion explosionShip(QPoint(myShip.getShipLine().p2()));
                _explosions.push_back(explosionMine);
                _explosions.push_back(explosionShip);
                mines_to_be_deleted.push_back(*itMine);
                myShip.hited();
            }
            if(myShip.getLife() <= 1){
                //Font for isWinning
                font.setPixelSize(60);
                painter.setFont(font);
                QString score = QString::number(this->score());
                painter.drawText(250,400,this->endGame(false));
                painter.drawText(260,450,"Score : " + score);
                this->pause();
            }
        }
        index++;
    }
    while(!mines_to_be_deleted.empty()) {
        std::remove(begin(_mines),end(_mines),mines_to_be_deleted.front());
        _mines.pop_back();
        mines_to_be_deleted.pop_front();
    }

    if (_mines.empty() && myShip.getLife() > 1) {
        this->setScore(this->score() + (200*myShip.getLife()));
        QString score = QString::number(this->score());
        font.setPixelSize(60);
        painter.setFont(font);
        painter.setPen(Qt::GlobalColor::red);
        painter.drawText(250,400,this->endGame(true));
        painter.drawText(260,450,"Score : " + score);
        this->pause();
    }
    else if (!_mines.empty() && myShip.getLife() > 1) {
        QString score = QString::number(this->score());
        font.setPixelSize(15);
        painter.setFont(font);
        painter.setPen(Qt::GlobalColor::red);
        painter.drawText(750, 790, "Vie : " + shipVie);
        painter.drawText(720, 20, "Score : " + score);
    }


    //Dessin des balles
    myShip.drawBullet(painter, size(), _mines, _explosions);
    this->setScore(this->score() + myShip.getScoreFrame());

    //Dessin du vaisseaux
    if(myShip.getLife() > 1)
        myShip.draw(painter);
}


void Minestorm::goDown(){
    if (myShip.getCurrentSpeed() > 0)
        myShip.setCurrentSpeed(myShip.getCurrentSpeed() - 1);
}

void Minestorm::initMine(){

    int sizeMine = 10;
    auto firstMine = QPoint(rand() % size().width(), rand() % size().height());
    addMines(firstMine, sizeMine,3000);
    qDebug() << "First mine : " << firstMine;
    for (int var = 0; var < 29;) {
        if (_mines.size() > 20 && _mines.size() < 26){
            sizeMine = 20;
        }
        else if (_mines.size() > 25){
            sizeMine = 30;
        }
        bool isCollision = false;
        auto point = QPoint(rand() % size().width(), rand() % size().height());
        auto _box = Box(QRect(QPoint(point.x() - (sizeMine),point.y() - (sizeMine)),QPoint(point.x() + (sizeMine),point.y() + (sizeMine))));
        int timerLenght = rand()%(3000-1000+ 1000) + 3000;
        qDebug() << _box.getPolygon();
        auto polygonCollision = myShip.box().getPolygon().intersected(_box.getPolygon());
        isCollision = !polygonCollision.isEmpty();

        if (!isCollision)
        {
            for (int index = 0; index < _mines.size(); index++)
            {
                qDebug() << index;
                auto mineCollision = _mines[index]->box().getPolygon().intersected(_box.getPolygon());
                if (!mineCollision.isEmpty()) {
                    isCollision = true;
                    break;
                }
            }
        }
        if (!isCollision)
        {
            addMines(point, sizeMine,timerLenght);
            qDebug() << "addMine()";
            var++;
        }
    }
}

void Minestorm::initialize(){
    _mines.clear();
    _explosions.clear();
    myShip.setCurrentSpeed(0);
    myShip.hited();
    myShip.setLife(4);
    this->setScore(0);
    initMine();
    Game::start();
}
void Minestorm::mousePressed( int x, int y) {
    //myShip.fire();
}
void Minestorm::keyPressed( int key ) {
    switch (key) {
    case Qt::Key_Left:myShip.rotateLeft();
        break;
    case Qt::Key_Right:myShip.rotateRight();
        break;
    case Qt::Key_Up:myShip.acceleration();
        break;
    case Qt::Key_Down:goDown();
        break;
    case Qt::Key_Space:
        if ( _mines[0]->getIsEclosion()) {
            qDebug() << "A";
            myShip.fire();
        }
        break;
    default:
        break;
    }
}
void Minestorm::keyReleased( int  /*key*/) {
}
void Minestorm::mouseReleased( int /* x */, int /* y */) {
}
void Minestorm::mouseMoved(int /* x */, int /* y */) {
}
