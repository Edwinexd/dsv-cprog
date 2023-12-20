#include "Constants.h" //gResPath-contains path to your resources.
#include <SDL2/SDL.h>
#include "Session.h"
#include "Component.h"
#include <SDL2/SDL_image.h>
#include <string>
#include <memory>
#include <iostream>
#include "TextComponent.h"
#include <ImageComponent.h>
#include <MultipartImageTexture.h>
#include <MultipartTexture.h>
#include <MultipartComponent.h>
#include <MultipartRectangleTexture.h>
#include <Color.h>
#include <Enemy.h>
#include <Laser.h>
#include <Spaceinvader.h>

/*
*   'gResPath' is a global constant defined in "Constants.h", 
*   representing the relative path to your resource folders as a string,
*   i.e. ' const std::string gResPath = "../../resources/" '
*   Use it through its namespace, 'constants::gResPath'.
*/

/*
class Spaceinvader : public Enemy
{
public:
    static std::shared_ptr<Spaceinvader> createInstance(std::shared_ptr<Session> session, int x, int y, int w, int h, bool has_collision, int hp, std::string alive_image_path, std::string dead_image_path) {
        return std::shared_ptr<Spaceinvader>(new Spaceinvader(g_session, x, y, w, h, has_collision, hp, alive_image_path, dead_image_path));
    }
    void shoot() {
		std::shared_ptr<Laser> b = Laser::createInstance(g_session, get_rect().x + (get_rect().w/2), get_rect().y + get_rect().h, 5, 40, true, {0, 1}, 10);
		g_session->add_component(b);
	}
	void mouseDown(int x, int y) {
		shoot();
	}
protected:
	Spaceinvader(std::shared_ptr<Session> session, int x, int y, int w, int h, bool has_collision, int hp, std::string alive_path, std::string dead_path) : Enemy(session, x, y, w, h, has_collision, hp, alive_path, dead_path) {}
};*/


// class Pistol : public Component {
// public:
// 	Pistol() :Component(0, 0, 0, 0, false) {}
// 	void render() const {}
// 	void tick() {}
// 	void mouseDown(int x, int y) {
// 		std::shared_ptr<Bullet> b = Bullet::createInstance(x);
// 		g_session->add_component(b);
// 	}
// };

int main(int argc, char** argv) {
	std::shared_ptr<Session> g_session = std::make_shared<Session>();
	// g_session->play_sound("sounds/bgMusic.wav", -1);
    std::cout << "Ticking: 1" << std::endl;
	auto text = TextComponent::createInstance(g_session, 250, 250, 200, 200, "Hello World!");
	g_session->add_component(std::move(text));
    std::cout << "Ticking: 2" << std::endl;
	auto image = ImageComponent::createInstance(g_session, 0, 0, 100, 100, "images/png_sample.png", false);
	g_session->add_component(std::move(image));
    std::cout << "Ticking: 3" << std::endl;
	std::unique_ptr<MultipartComponent> multipart = MultipartComponent::createInstance(g_session, 250, 250, 250, 250, false);
    std::cout << "Ticking: 4" << std::endl;
	auto multipartImageTexture1 = MultipartImageTexture::createInstance(g_session, "images/alive.png");
	auto multipartImageTexture2 = MultipartImageTexture::createInstance(g_session, "images/dead.png");
	auto multipartRectangle = MultipartRectangleTexture::createInstance(g_session, 250, 250, Color(255, 0, 0, 255));
	multipart->addTexture(multipartImageTexture1);
	multipart->addTexture(multipartImageTexture2);
	multipart->addTexture(multipartRectangle);
	multipart->setTexture(2);
    std::cout << "Ticking: 5" << std::endl;

	auto enemy = Enemy::createInstance(g_session, 100, 100, 45, 45, true, 100, "images/alive.png", "images/dead.png");
	enemy->damage(100);
	g_session->add_component(std::move(enemy));
	// kill enemy
	std::cout << (enemy.get() == nullptr) << std::endl;
    std::cout << "Ticking: 6" << std::endl;
	
	auto spaceinvader = Spaceinvader::createInstance(g_session, 200, 200, 45, 45, 100, "images/alive.png", "images/dead.png");
    std::cout << "Ticking: 7" << std::endl;
	const int numRows = 5;
	const int numCols = 10;
	const int invaderWidth = 40;
	const int invaderHeight = 40;
	const int invaderSpacing = 10;

	for (int row = 0; row < numRows; row++) {
		for (int col = 0; col < numCols; col++) {
			int x = col * (invaderWidth + invaderSpacing);
			int y = row * (invaderHeight + invaderSpacing);
			auto invader = Spaceinvader::createInstance(g_session, x, y, invaderWidth, invaderHeight, 100, "images/alive.png", "images/dead.png");
			g_session->add_component(std::move(invader));
		}
}
	g_session->add_component(std::move(spaceinvader));
	
	g_session->add_component(std::move(multipart));

	g_session->run();
	
	// SDL_RenderPresent(sys.ren);
	// sys.play_sound("sounds/bgMusic.wav", -1);
	// SDL_Delay(10000);

	return 0;
}
