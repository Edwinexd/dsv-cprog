#include <InvadersComponent.h>

InvadersComponent::InvadersComponent(std::shared_ptr<Session> session, int x, int y, int num_rows, int num_cols, int invader_width, int invader_height, int invader_spacing, std::shared_ptr<TextComponent> score_text) : Component(
              session, x, y, [&]()
              { return num_cols * (invader_width + invader_spacing) - invader_spacing; }(),
              [&]()
              { return num_rows * (invader_height + invader_spacing) - invader_spacing; }(),
              false),
          num_rows(num_rows), num_cols(num_cols),
          invader_width(invader_width), invader_height(invader_height), invader_spacing(invader_spacing), score_text(score_text)
    {
        create_invaders();
    }


void InvadersComponent::update_direction() {
  for (unsigned col = 0; col < num_cols; ++col) {
    if (!invaders[col].empty()) {
      for (unsigned row = 0; row < num_rows; ++row) {
        if (invaders[col][row] != nullptr) {
          // Guaranteed to not be nullptr by tick
          auto invader = invaders[col][row];
          invader->set_direction(unit_vec[is_left ? 1 : 0]);
        }
      }
    }
  }
}

bool InvadersComponent::check_wall_collision() {
  if (is_left) {
    for (unsigned col = 0; col < num_cols; ++col) {
      for (unsigned row = 0; row < num_rows; ++row) {
        auto current_invader = invaders[col][row];
        if (current_invader != nullptr) {
          if (!current_invader->is_dead()) {

            if (current_invader->get_x() <= invader_spacing * 2) {
              is_left = false;
              update_direction();
              return true;
            }
          }
        }
      }
    }
  } else {
    for (int col = (int)num_cols - 1; col >= 0; --col) {

      for (unsigned row = 0; row < num_rows; row++) {
        auto current_invader = invaders[col][row];
        if (current_invader != nullptr) {
          if (!current_invader->is_dead()) {
            if (current_invader->get_x() + invader_width >=
                get_session()->get_window_data().get_width() -
                    invader_spacing * 2) {
              is_left = true;
              update_direction();
              return true;
            }
          }
        }
      }
    }
  }
  return false;
}

void InvadersComponent::tick() {
  tick_count++;
  if (alive_invaders == 0 && !game_over) {
    score_text->set_text("You win!");
    return;
  }

  check_wall_collision();

  if (tick_count % 100 == 0 || (game_over && tick_count % 10 == 0)) {
    shoot_random_invader();
  }
  if (game_over) {
    score_text->set_text("Game over!");
  } else {
    score_text->set_text("Score: " +
                         std::to_string(total_invaders - alive_invaders));
  }
}

void InvadersComponent::shoot_bottom_invaders() {
  for (unsigned col = 0; col < num_cols; col++) {
    if (!invaders[col].empty()) {
      for (unsigned row = num_rows - 1; row >= 0; row--) {
        if (invaders[col][row] != nullptr) {
          // Guaranteed to not be nullptr by tick
          auto invader = invaders[col][row];
          invader->shoot();
          break;
        }
      }
    }
  }
}

void InvadersComponent::shoot_random_invader() {
  std::vector<unsigned> columns;
  for (unsigned col = 0; col < num_cols; col++) {
    if (!invaders[col].empty()) {
      columns.push_back(col);
    }
  }
  if (columns.empty()) {
    return;
  }
  // Shuffle columns
  std::default_random_engine rng(std::random_device{}());
  std::shuffle(columns.begin(), columns.end(), rng);
  for (auto col : columns) {
    if (shoot_bottom_of_column(col)) {
      return;
    }
  }
}

bool InvadersComponent::shoot_bottom_of_column(int col) {

  for (int row = num_rows - 1; row >= 0; row--) {
    if (invaders[col][row].get() != nullptr) {
      auto invader = invaders[col][row];
      if (invader->is_dead()) {
        continue;
      }
      if (!safe_to_shoot(col, row)) {
        return false;
      }
      if (safe_to_shoot(col, row)) {
        // DEBUG: std::cout << "Shooting from " << col << "," << row <<
        // std::endl;
        invader->shoot();
        return true;
      }
    }
  }
  return false;
}

void InvadersComponent::create_invaders() {
  invaders.resize(num_cols,
                  std::vector<std::shared_ptr<Spaceinvader>>(num_rows));

  for (unsigned row = 0; row < num_rows; row++) {
    for (unsigned col = 0; col < num_cols; col++) {
      int x = col * (invader_width + invader_spacing);
      int y = row * (invader_height + invader_spacing);
      auto invader = Spaceinvader::create_instance(
          get_session(), x + get_x(), y + get_y(), invader_width,
          invader_height, 1, "images/alive.png", "images/dead.png");
      get_session()->add_component(invader);
      invaders[col][row] = invader;
      total_invaders++;
      alive_invaders++;
    }
  }
  update_direction();
}

bool InvadersComponent::safe_to_shoot(unsigned col, unsigned row) {
  // We need to check if there effectively is a row in front of us
  // if there is, we can't shoot
  if (row == num_rows - 1) {
    return true;
  }
  auto invader = invaders[col][row];
  if (invader.get() == nullptr) {
    return true;
  }
  if (invader->is_dead()) {
    return true;
  }

  int laser_dy = 1;
  int laser_x = invader->get_x() + (invader->get_width() / 2);
  int laser_y = invader->get_y() + invader->get_height();

  // check all components in front of us to see if they are in the way or are
  // going to be in the way before the laser is clear of the invaders rect we
  // assume that all entities below us are moving +-2 pixels per tick in
  // x-direction
  int ticks_to_clear = (get_rect().y + get_rect().h - laser_y) / laser_dy;
  int ticks_to_clear_x = ticks_to_clear * 2;
  // int ticks_to_clear_y = ticks_to_clear * laser_dy;
  int left_x_bound = laser_x - ticks_to_clear_x;
  int right_x_bound = laser_x + ticks_to_clear_x;
  int top_y_bound = laser_y;
  int bottom_y_bound = get_rect().y + get_rect().h;
  /*
  //DEBUG: Draw multipart component with the dimensions above
  std::shared_ptr<MultipartComponent> multipart =
  MultipartComponent::create_instance(session, left_x_bound, top_y_bound,
  right_x_bound - left_x_bound, bottom_y_bound - top_y_bound, false, {0, 0});
  auto multipartRectangle = MultipartRectangleTexture::create_instance(session,
  right_x_bound - left_x_bound, bottom_y_bound - top_y_bound, Color(255, 0, 0,
  128)); multipart->add_texture(multipartRectangle);
  session->add_component(multipart);
  */
  // check if there is a component in the way of all components below us
  for (unsigned r = row + 1; r < num_rows; r++) {
    for (unsigned c = 0; c < num_cols; c++) {
      auto other_invader = invaders[c][r];
      if (other_invader.get() == nullptr) {
        continue;
      }
      if (other_invader->is_dead()) {
        continue;
      }
      if (other_invader->get_x() + other_invader->get_width() < left_x_bound) {
        continue;
      }
      if (other_invader->get_x() > right_x_bound) {
        continue;
      }
      if (other_invader->get_y() + other_invader->get_height() < top_y_bound) {
        continue;
      }
      if (other_invader->get_y() > bottom_y_bound) {
        continue;
      }
      // DEBUG: std::cout << "Can't shoot, invader " << col << "," << row << "
      // is in the way!" << std::endl;
      return false;
    }
  }
  return true;
}

void InvadersComponent::on_remove(std::shared_ptr<Component> other) {
  if (auto invader = std::dynamic_pointer_cast<Spaceinvader>(other)) {
    for (unsigned col = 0; col < num_cols; col++) {
      for (unsigned row = 0; row < num_rows; row++) {
        if (invaders[col][row] == invader) {
          invaders[col][row] = nullptr;
          alive_invaders--;
          if (game_over) {
            return;
          }
          get_session()->play_sound("sounds/score.wav", 0);
          return;
        }
      }
    }
  } else if (auto player = std::dynamic_pointer_cast<Player>(other)) {
    game_over = true;
    // TODO: Spawn death beam or some other end effect
  }
}
