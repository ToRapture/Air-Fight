#ifndef COMMON_H
#define COMMON_H

#define SCREEN_W 1366
#define SCREEN_H 768
#define DELAY 16
#define GAMEOVER_DELAY_TIME 1500

#define ENEMY_CREATE_TIME 250
#define ENEMY_FIRE_TIME 250
#define ENEMY_NUM_MAX 9

#define APP_NAME "Air Fight"
#define FILE_PATH "../Res/"
#define PLAYER_FILE "Player.png"
#define ENEMY_FILE "Enemy.png"
#define BULLET_FILE "Bullet.png"
#define GAMEOVER_FILE "Gameover.png"
#define BYE_FILE "Bye.png"

#define PLAYER_FIRE_TIME 85


#define SCORE_PER_KILL 5
#define PLAYER_MOVE_SPEED 15
#define ENEMY_MOVE_SPEED 5
#define BULLET_MOVE_SPEED 14
#define ENEMY_MOVE_LEN (SCREEN_W  * 2 / 3)

enum Exit_Type {
	DIE, EXIT, EXIT_TYPE_TOTAL
};

enum Move_Dir {
	LEFT, RIGHT
};

enum BulletBelong {
	ENEMY, PLAYER
};

enum SoundType {
    FIRE,BOOM,LAUGH
};


#endif //COMMON_H