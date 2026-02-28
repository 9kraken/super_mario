#include <QApplication>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QTimer>

#include "qt_ui_factory.hpp"
#include "first_level.hpp"
#include "game.hpp"
#include "user_input.hpp"

using namespace biv;

class GameView : public QGraphicsView {
public:
    GameView(Game* game, QtUIFactory* ui_factory, QWidget* parent = nullptr)
        : QGraphicsView(parent), game_(game), ui_factory_(ui_factory) {
        setRenderHint(QPainter::Antialiasing);
        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setFocusPolicy(Qt::StrongFocus);

        if (ui_factory_ && ui_factory_->get_game_map_qt()) {
            setScene(ui_factory_->get_game_map_qt()->scene());
            const QRectF rect = scene()->sceneRect();
            setFixedSize(1080, 720);
            fitInView(rect, Qt::KeepAspectRatio);
        }
    }

protected:
    void keyPressEvent(QKeyEvent* ev) override {
    if (ev->isAutoRepeat()) return;
    if (ev->key() == Qt::Key_A || ev->text().toLower() == "ф") leftPressed_ = true;  // Для русской "Ф" как A
    if (ev->key() == Qt::Key_D || ev->text().toLower() == "в") rightPressed_ = true;  // Для русской "В" как D
    if (ev->key() == Qt::Key_Space) jumpPressed_ = true;
    if (ev->key() == Qt::Key_Escape) exitPressed_ = true;
}

void keyReleaseEvent(QKeyEvent* ev) override {
    if (ev->isAutoRepeat()) return;
    if (ev->key() == Qt::Key_A || ev->text().toLower() == "ф") leftPressed_ = false;
    if (ev->key() == Qt::Key_D || ev->text().toLower() == "в") rightPressed_ = false;
    if (ev->key() == Qt::Key_Space) jumpPressed_ = false;
    if (ev->key() == Qt::Key_Escape) exitPressed_ = false;
}

public:
    void tick() {
        if (!game_ || !ui_factory_) return;

        using biv::os::UserInput;

        UserInput user_input = UserInput::NO_INPUT;
        if (leftPressed_) user_input = UserInput::MAP_RIGHT;  // A - влево (карта вправо)
        if (rightPressed_) user_input = UserInput::MAP_LEFT;  // D - вправо (карта влево)
        if (jumpPressed_) user_input = UserInput::MARIO_JUMP;
        if (exitPressed_) user_input = UserInput::EXIT;

        Mario* mario = ui_factory_->get_mario();
        switch (user_input) {
            case UserInput::MAP_LEFT:
                mario->move_map_left();
                if (!game_->check_static_collisions(mario)) {
                    game_->move_map_left();
                }
                mario->move_map_right();
                break;
            case UserInput::MAP_RIGHT:
                mario->move_map_right();
                if (!game_->check_static_collisions(mario)) {
                    game_->move_map_right();
                }
                mario->move_map_left();
                break;
            case UserInput::MARIO_JUMP:
                mario->jump();
                break;
            case UserInput::EXIT:
                game_->finish();
                break;
            default:
                break;
        }

        game_->move_objs_horizontally();
        game_->check_horizontally_static_collisions();

        game_->move_objs_vertically();
        game_->check_mario_collision();
        game_->check_vertically_static_collisions();

        GameMap* gm = ui_factory_->get_game_map();
        if (gm && (gm->is_below_map(mario->get_top()) || !mario->is_active())) {
            if (auto lvl = ui_factory_->get_current_level()) {
                lvl->restart();
                mario = ui_factory_->get_mario();  // Обновляем Марио после рестарта
                QTimer::singleShot(1000, this, [this]() { tick(); });  // Задержка
            }
        }

        if (game_->is_level_end()) {
            if (auto lvl = ui_factory_->get_current_level()) {
                if (!lvl->is_final()) {
                    GameLevel* next = lvl->get_next();
                    ui_factory_->set_current_level(next);
                    mario = ui_factory_->get_mario();
                    QTimer::singleShot(1000, this, [this]() { game_->start_level(); tick(); });
                } else {
                    game_->finish();
                }
            }
        }

        // Синхронизация модель -> представление
        ui_factory_->sync_model_to_view();

        if (ui_factory_->get_game_map_qt() && ui_factory_->get_game_map_qt()->scene()) {
            ui_factory_->get_game_map_qt()->scene()->update();
        }

        if (game_->is_finished()) {
            qApp->quit();
        }
    }

private:
    Game* game_ = nullptr;
    QtUIFactory* ui_factory_ = nullptr;

    bool leftPressed_ = false;
    bool rightPressed_ = false;
    bool jumpPressed_ = false;
    bool exitPressed_ = false;
};

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    Game game;
    QtUIFactory* ui_factory = new QtUIFactory(&game);

    GameLevel* level = new FirstLevel(ui_factory);
    ui_factory->set_current_level(level);

    GameView view(&game, ui_factory);
    view.show();

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, &view, &GameView::tick);
    timer.start(16);  // ~60 FPS

    int res = app.exec();

    delete ui_factory;
    delete level;

    return res;
}