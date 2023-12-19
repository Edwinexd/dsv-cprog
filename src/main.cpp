#include "Constants.h" //gResPath-contains path to your resources.
#include <SDL2/SDL.h>
#include "Session.h"
#include "Component.h"
#include <SDL2/SDL_image.h>
#include "System.h"
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

/*
*   'gResPath' is a global constant defined in "Constants.h", 
*   representing the relative path to your resource folders as a string,
*   i.e. ' const std::string gResPath = "../../resources/" '
*   Use it through its namespace, 'constants::gResPath'.
*/

Session ses;


class Bullet : public Component {
public:
	static std::shared_ptr<Bullet> createInstance(int x) {
        return std::make_shared<Bullet>(x);
	}
	Bullet(int x) : Component(x, 500, 40,40, true){
        // todo abstract away behind IMGComponent, which takes care of calculating width and height as well
		texture = IMG_LoadTexture(sys.ren, (constants::gResPath + "images/dot40x40.bmp").c_str() );
	}
	~Bullet() {
        // todo abstract away behind IMGComponent, which takes care of calculating width and height as well
		SDL_DestroyTexture(texture);
	}
	void render() const {
		// Code adjustment to handle the address to temporary object. 
		const SDL_Rect &rect = getRect();
		//SDL_RenderCopy(sys.ren, texture, NULL, &getRect());
		SDL_RenderCopy(sys.ren, texture, NULL, &rect);
	}
		void tick() {
			counter++;
			/*if (rect.y <= 0) {
				ses.remove(shared_from_this());
			} else */
			if (counter % 2 == 0) {
				rect.y--;
			}
		}
	private:
		SDL_Texture* texture;
	int counter = 0;
};

class Spaceinvader : public Enemy
{
public:
    static std::shared_ptr<Spaceinvader> createInstance(int x, int y, int w, int h, bool has_collission, int hp, std::string alive_image_path, std::string dead_image_path) {
        return std::shared_ptr<Spaceinvader>(new Spaceinvader(x, y, w, h, has_collission, hp, alive_image_path, dead_image_path));
    }
    void shoot() {
		std::shared_ptr<Laser> b = Laser::createInstance(getRect().x + (getRect().w/2), getRect().y + getRect().h, 5, 40, true, {0, 1}, 10);
		ses.add(b);
	}
	void mouseDown(int x, int y) {
		shoot();
	}
protected:
	Spaceinvader(int x, int y, int w, int h, bool has_collission, int hp, std::string alive_path, std::string dead_path) : Enemy(x, y, w, h, has_collission, hp, alive_path, dead_path) {}
};


class Pistol : public Component {
public:
	Pistol() :Component(0, 0, 0, 0, false) {}
	void render() const {}
	void tick() {}
	void mouseDown(int x, int y) {
		std::shared_ptr<Bullet> b = Bullet::createInstance(x);
		ses.add(b);
	}
};

int main(int argc, char** argv) {
	std::shared_ptr<Pistol> pistol = std::make_shared<Pistol>();
	ses.add(pistol);
	// ses.play_sound("sounds/bgMusic.wav", -1);
	auto text = TextComponent::createInstance(250, 250, 200, 200, "Hello World!");
	ses.add(text);
	auto image = ImageComponent::createInstance(0, 0, 100, 100, "images/png_sample.png", false);
	ses.add(image);
	auto multipart = MultipartComponent::createInstance(250, 250, 250, 250, false);
	auto multipartImageTexture1 = MultipartImageTexture::createInstance("images/alive.png");
	auto multipartImageTexture2 = MultipartImageTexture::createInstance("images/dead.png");
	auto multipartRectangle = MultipartRectangleTexture::createInstance(250, 250, Color(255, 0, 0, 255));
	multipart->addTexture(multipartImageTexture1);
	multipart->addTexture(multipartImageTexture2);
	multipart->addTexture(multipartRectangle);
	multipart->setTexture(2);

	auto enemy = Enemy::createInstance(100, 100, 45, 45, true, 100, "images/alive.png", "images/dead.png");
	ses.add(enemy);
	enemy->kill();

	auto spaceinvader = Spaceinvader::createInstance(200, 200, 45, 45, true, 100, "images/alive.png", "images/dead.png");
	const int numRows = 5;
	const int numCols = 10;
	const int invaderWidth = 40;
	const int invaderHeight = 40;
	const int invaderSpacing = 10;

	for (int row = 0; row < numRows; row++) {
		for (int col = 0; col < numCols; col++) {
			int x = col * (invaderWidth + invaderSpacing);
			int y = row * (invaderHeight + invaderSpacing);
			std::shared_ptr<Spaceinvader> invader = Spaceinvader::createInstance(x, y, invaderWidth, invaderHeight, true, 100, "images/alive.png", "images/dead.png");
			ses.add(invader);
		}
}
	ses.add(spaceinvader);
	
	ses.add(multipart);

	ses.run();
	
	// SDL_RenderPresent(sys.ren);
	// sys.play_sound("sounds/bgMusic.wav", -1);
	// SDL_Delay(10000);

	return 0;
}
