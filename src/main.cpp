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
#include <Color.h>
#include <Enemy.h>
#include <Laser.h>
#include <Spaceinvader.h>
#include <InvadersComponent.h>
#include <Player.h>
#include <Fonts.h>
#include <BlockadeComponent.h>

int main(int argc, char** argv) {
	std::shared_ptr<Session> g_session = Session::create_instance();

	g_session->play_sound("sounds/legends.wav", -1);

	auto bg_image = ImageComponent::create_instance(g_session, 0, 0, 850, 850, "images/dalle_generated_bg.jpg", false);
	g_session->add_component(bg_image);

	// Create invaders component
	int invader_size = 45;
	int invader_spacing = 10;
	int num_of_columns = 650 / (invader_size + invader_spacing);

	auto score_text = TextComponent::create_instance(g_session, g_session->get_window_data().get_width() / 2 - 50, 100, 300, 50, "Loading...", {255, 255, 255, 255}, Font::REGULAR);
	g_session->add_component(score_text);
	auto invaders = InvadersComponent::create_instance(g_session, 100, 150, 4, num_of_columns, invader_size, invader_size, invader_spacing, score_text);
	g_session->add_component(invaders);

	// Create some blockade components
	auto blockade = BlockadeComponent::create_instance(g_session, 100, 600, 100, 100, 10, "images/castle_full_health.png", "images/castle_low_health.png");
	g_session->add_component(std::move(blockade));
	auto blockade2 = BlockadeComponent::create_instance(g_session, 300, 600, 100, 100, 10, "images/castle_full_health.png", "images/castle_low_health.png");
	g_session->add_component(std::move(blockade2));
	auto blockade3 = BlockadeComponent::create_instance(g_session, 500, 600, 100, 100, 10, "images/castle_full_health.png", "images/castle_low_health.png");
	g_session->add_component(std::move(blockade3));
	auto blockade4 = BlockadeComponent::create_instance(g_session, 700, 600, 100, 100, 10, "images/castle_full_health.png", "images/castle_low_health.png");
	g_session->add_component(std::move(blockade4));

	// Create player
	auto player = Player::create_instance(g_session, 700, 750, 75, 75, true, 3, "images/player_alive.png", "images/player_dead.png");
	g_session->add_component(player);
	
	g_session->run();
	
	return 0;
}
