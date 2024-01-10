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
#include <InvadersComponent.h>
#include <Player.h>
#include <Fonts.h>
#include <BlockadeComponent.h>

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
    static std::shared_ptr<Spaceinvader> create_instance(std::shared_ptr<Session> session, int x, int y, int w, int h, bool has_collision, int hp, std::string alive_image_path, std::string dead_image_path) {
        return std::shared_ptr<Spaceinvader>(new Spaceinvader(g_session, x, y, w, h, has_collision, hp, alive_image_path, dead_image_path));
    }
    void shoot() {
		std::shared_ptr<Laser> b = Laser::create_instance(g_session, get_rect().x + (get_rect().w/2), get_rect().y + get_rect().h, 5, 40, true, {0, 1}, 10);
		g_session->add_component(b);
	}
	void mouse_down(int x, int y) {
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
// 	void mouse_down(int x, int y) {
// 		std::shared_ptr<Bullet> b = Bullet::create_instance(x);
// 		g_session->add_component(b);
// 	}
// };

int main(int argc, char** argv) {
	std::shared_ptr<Session> g_session = std::make_shared<Session>();

	g_session->play_sound("sounds/legends.wav", -1);
	// g_session->play_sound("sounds/bgMusic.wav", -1);
	auto text = TextComponent::create_instance(g_session, 250, 250, 200, 200, "Hello World!", {255, 255, 255, 255}, Font::REGULAR);
	g_session->add_component(text);
	auto image = ImageComponent::create_instance(g_session, 0, 0, 100, 100, "images/png_sample.png", false);
	g_session->add_component(image);
	auto bg_image = ImageComponent::create_instance(g_session, 0, 0, 850, 850, "images/dalle_generated_bg.jpg", false);
	g_session->add_component(bg_image);
	std::shared_ptr<MultipartComponent> multipart = MultipartComponent::create_instance(g_session, 250, 250, 250, 250, true, {0,0});
	auto multipartImageTexture1 = MultipartImageTexture::create_instance(g_session, "images/alive.png");
	auto multipartImageTexture2 = MultipartImageTexture::create_instance(g_session, "images/dead.png");
	auto multipartRectangle = MultipartRectangleTexture::create_instance(g_session, 250, 250, Color(255, 0, 0, 255));
	multipart->add_texture(multipartImageTexture1);
	multipart->add_texture(multipartImageTexture2);
	multipart->add_texture(multipartRectangle);
	multipart->set_texture(2);

	auto enemy = Enemy::create_instance(g_session, 100, 100, 45, 45, true, {0,0}, 100, "images/alive.png", "images/dead.png");
	enemy->damage(100);
	g_session->add_component(enemy);
	// kill enemy
	std::cout << (enemy.get() == nullptr) << std::endl;
	
	auto spaceinvader = Spaceinvader::create_instance(g_session, 200, 200, 45, 45, 100, "images/alive.png", "images/dead.png", 29);
	spaceinvader->kill();

	// Create invaders component
	// calculate number of invaders we can fit on the x-axis
	// invaders move +-200 pixels on the x-axis so we have 850 - 200 = 650 pixels to work with
	int invader_size = 45;
	int invader_spacing = 10;
	int num_of_columns = 650 / (invader_size + invader_spacing);


	auto score_text = TextComponent::create_instance(g_session, g_session->get_window_data().w / 2 - 50, 100, 300, 50, "Loading...", {255, 255, 255, 255}, Font::REGULAR);
	g_session->add_component(score_text);
	auto invaders = InvadersComponent::create_instance(g_session, 100, 150, 4, num_of_columns, invader_size, invader_size, invader_spacing, score_text);
	g_session->add_component(invaders);

	// Create some blockade components
	auto blockade = BlockadeComponent::create_instance(g_session, 100, 600, 100, 100, 10, "images/castle_full_health.png", "images/castle_low_health.png");
	g_session->add_component(blockade);
	auto blockade2 = BlockadeComponent::create_instance(g_session, 300, 600, 100, 100, 10, "images/castle_full_health.png", "images/castle_low_health.png");
	g_session->add_component(blockade2);
	auto blockade3 = BlockadeComponent::create_instance(g_session, 500, 600, 100, 100, 10, "images/castle_full_health.png", "images/castle_low_health.png");
	g_session->add_component(blockade3);
	auto blockade4 = BlockadeComponent::create_instance(g_session, 700, 600, 100, 100, 10, "images/castle_full_health.png", "images/castle_low_health.png");
	g_session->add_component(blockade4);

	// Create player
	auto player = Player::create_instance(g_session, 700, 750, 75, 75, true, 3, "images/player_alive.png", "images/player_dead.png");
	g_session->add_component(player);

	g_session->add_component(invaders);

	g_session->add_component(spaceinvader);
	
	// g_session->add_component(multipart);

	g_session->run();
	
	// SDL_RenderPresent(sys.ren);
	// sys.play_sound("sounds/bgMusic.wav", -1);
	// SDL_Delay(10000);

	return 0;
}
