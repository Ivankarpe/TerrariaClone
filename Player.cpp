#include "Player.h"

void Player::Move(Vector2 dir)
{
	cord.x += dir.x;
	cord.y += dir.y;
}
