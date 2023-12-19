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
	multipart->addTexture(multipartImageTexture1);
	multipart->addTexture(multipartImageTexture2);
	multipart->nextTexture();
	
	ses.add(multipart);

	ses.run();
	
	// SDL_RenderPresent(sys.ren);
	// sys.play_sound("sounds/bgMusic.wav", -1);
	// SDL_Delay(10000);

	return 0;
}
