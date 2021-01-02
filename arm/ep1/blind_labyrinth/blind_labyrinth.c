
#include "blind_labyrinth.h"
#include "stdint.h"

#define REAL_COORD(val)															(val + 0x1)
#define IS_OBSTACLE(game_ptr, pos)									(game_ptr->map[pos.row][pos.col] == OBSTACLE)
#define IS_EXIT(game_ptr, pos)											(game_ptr->map[pos.row][pos.col] == AWW_EXIT)

pos_t get_next_pos(robot_t robot);
void update_obstacles_val(game_t *game);

const slot_t default_map[NROWS][NCOLS] = {
	{ OBSTACLE, OBSTACLE, OBSTACLE, OBSTACLE, OBSTACLE, OBSTACLE, OBSTACLE, OBSTACLE, OBSTACLE, OBSTACLE, OBSTACLE, OBSTACLE, OBSTACLE, OBSTACLE, OBSTACLE, OBSTACLE, OBSTACLE },
	{ OBSTACLE, AWW_EXIT, NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, NORMAL, 	NORMAL, 		AWW_EXIT, OBSTACLE },
	{ OBSTACLE, NORMAL, 	NORMAL, 	OBSTACLE, OBSTACLE, OBSTACLE, OBSTACLE, NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, NORMAL, 	NORMAL, 		NORMAL, 	OBSTACLE },
	{ OBSTACLE, NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	OBSTACLE, NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, NORMAL, 	NORMAL, 		NORMAL, 	OBSTACLE },
	{ OBSTACLE, NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	OBSTACLE, NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, NORMAL, 	NORMAL, 		NORMAL, 	OBSTACLE },
	{ OBSTACLE, NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	OBSTACLE, NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, NORMAL, 	NORMAL, 		NORMAL, 	OBSTACLE },
	{ OBSTACLE, OBSTACLE, OBSTACLE, OBSTACLE, OBSTACLE, OBSTACLE, NORMAL, 	NORMAL, 	OBSTACLE, NORMAL, 	OBSTACLE, NORMAL, 	NORMAL, NORMAL, 	OBSTACLE, 	NORMAL, 	OBSTACLE },
	{ OBSTACLE, NORMAL,		NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, NORMAL, 	OBSTACLE, 	NORMAL, 	OBSTACLE },
	{ OBSTACLE, OBSTACLE, NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, NORMAL, 	OBSTACLE, 	NORMAL, 	OBSTACLE },
	{ OBSTACLE, OBSTACLE, NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, NORMAL, 	OBSTACLE, 	NORMAL, 	OBSTACLE },
	{ OBSTACLE, OBSTACLE, NORMAL, 	OBSTACLE, NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, NORMAL, 	NORMAL, 		NORMAL, 	OBSTACLE },
	{ OBSTACLE, OBSTACLE, NORMAL, 	OBSTACLE, NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, NORMAL, 	NORMAL, 		NORMAL, 	OBSTACLE },
	{ OBSTACLE, OBSTACLE, NORMAL, 	OBSTACLE, NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, NORMAL, 	NORMAL, 		NORMAL, 	OBSTACLE },
	{ OBSTACLE, AWW_EXIT, NORMAL, 	OBSTACLE, NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, 	NORMAL, NORMAL, 	NORMAL, 		AWW_EXIT, OBSTACLE },
	{ OBSTACLE, OBSTACLE, OBSTACLE, OBSTACLE, OBSTACLE, OBSTACLE, OBSTACLE, OBSTACLE, OBSTACLE, OBSTACLE, OBSTACLE, OBSTACLE, OBSTACLE, OBSTACLE, OBSTACLE, OBSTACLE, OBSTACLE }
};

robot_t new_robot() {
	robot_t robot;
	
	robot.curr_pos.col = REAL_COORD(0x7);
	robot.curr_pos.row = REAL_COORD(0x7);
	
	return robot;
}

game_t new_game(robot_t robot) {
	game_t game;
	
	game.robot = robot;
	game.robot.dir_obstacle.direction = EAST;
	update_obstacles_val(&game);
	
	game.map = default_map;
	
	return game;
}

void set_dir(game_t *game, uint8_t dir) {
	game->robot.dir_obstacle.direction = dir;
	update_obstacles_val(game);
}

bool go_on(game_t *game) {
	
	if (IS_OBSTACLE(game, get_next_pos(game->robot))) {
		return false;
	}
	
	game->robot.curr_pos = get_next_pos(game->robot);
	update_obstacles_val(game);
	
	return true;
}

bool is_exit_reached(game_t game) {
	return (default_map[game.robot.curr_pos.row][game.robot.curr_pos.col] == AWW_EXIT);
}

void update_obstacles_val(game_t *game) {
	uint8_t dist;
	pos_t next_pos;
	robot_t robot_cp;
	bool is_exit_found = false;
	
	next_pos = get_next_pos(game->robot);
	robot_cp = game->robot;
	robot_cp.curr_pos = next_pos;
	
	game->robot.dir_obstacle.is_dist0_obstacle = IS_OBSTACLE(game, next_pos);
	is_exit_found |= IS_EXIT(game, next_pos);
	
	game->robot.dir_obstacle.is_dist2_obstacle = 0;
	game->robot.dir_obstacle.is_dist5_obstacle = 0;
	
	for (dist = 1; dist <= 5 && !is_exit_found; dist++) {
		robot_cp.curr_pos = next_pos;
		next_pos = get_next_pos(robot_cp);
		
		if (dist <= 2) {
			game->robot.dir_obstacle.is_dist2_obstacle |= IS_OBSTACLE(game, next_pos);
		} else {
			game->robot.dir_obstacle.is_dist5_obstacle |= IS_OBSTACLE(game, next_pos);
		}

		is_exit_found |= IS_EXIT(game, next_pos);
	}
	
	game->robot.dir_obstacle.is_dist0_obstacle &= !is_exit_found;
	game->robot.dir_obstacle.is_dist2_obstacle &= !is_exit_found;
	game->robot.dir_obstacle.is_dist5_obstacle &= !is_exit_found;
}

pos_t get_next_pos(robot_t robot) {
	pos_t new_pos;
	
	new_pos = robot.curr_pos;
	if (robot.dir_obstacle.direction == NORTH) {
		new_pos.row--;
	} else if (robot.dir_obstacle.direction == SOUTH) {
		new_pos.row++;
	} else if (robot.dir_obstacle.direction == EAST) {
		new_pos.col++;
	} else if (robot.dir_obstacle.direction == WEST) {
		new_pos.col--;
	}
	
	return new_pos;
}
