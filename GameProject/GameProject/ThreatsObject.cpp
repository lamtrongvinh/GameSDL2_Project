#include "stdafx.h"
#include "ThreatsObject.h"

ThreatsObject::ThreatsObject()
{
	width_frame_ = 0;
	height_frame_ = 0;
	x_val_ = 0.0;
	y_val_ = 0.0;
	x_pos_ = 0.0;
	y_pos_ = 0.0;
	on_ground_ = false;
	come_back_time_ = 0;
	frame_ = 0;

	animation_a_ = 0;
	animatin_b_ = 0;
	input_type_.left_ = 0;
	type_move_ = STATIC_THREATS;

}
ThreatsObject::~ThreatsObject()
{

}

bool ThreatsObject::loadImg(std::string path, SDL_Renderer * screen)
{
	bool ret = BaseObject::loadImage(path, screen);
	if (ret == true)
	{
		width_frame_ = rect_.w / THREATS_FRAME_NUM;
		height_frame_ = rect_.h ;
	}

	return ret;
}

void ThreatsObject::set_clips()
{
	if (width_frame_ > 0 && height_frame_ > 0)
	{
		for (int i = 0; i < 8; i ++)
		{
			 frame_clip_[i].x = i * width_frame_;
			 frame_clip_[i].y = 0;
			 frame_clip_[i].w = width_frame_;
			 frame_clip_[i].h = height_frame_;
		}
	}
}

void ThreatsObject::Show(SDL_Renderer * des)
{
	if (come_back_time_  == 0)
	{
		rect_.x = x_pos_ - map_x_;
		rect_.y = y_pos_ - map_y_;
		frame_++;
		if (frame_ >= 8)
		{
			frame_ = 0;
		}

		SDL_Rect * current_clip = &frame_clip_[frame_]; 
		SDL_Rect  renderQuad = {rect_.x, rect_.y, width_frame_, height_frame_};
		SDL_RenderCopy(des, p_object, current_clip, &renderQuad);
	}
}

void ThreatsObject::DoPlayer(Map& gMap)
{
	if (come_back_time_ == 0)
	{
		x_val_ = 0;
		y_val_ += THREATS_GRAVITI_SPEED;
		if (y_val_ >= THREATS_MAX_FALL_SPEED)
		{
			y_val_ = THREATS_MAX_FALL_SPEED;
		}

		if (input_type_.left_ == 1)
		{
			x_val_ -= THREAT_SPEED;
		} else if (input_type_.right_ == 1)
		{
			x_val_ += THREAT_SPEED;
		}

		CheckToMap(gMap);
	} else if (come_back_time_ > 0)
	{
		come_back_time_--;
		if (come_back_time_ == 0)
		{
			InitThreat();
		}
	}
}

SDL_Rect ThreatsObject::GetRectFrame()
{
	SDL_Rect rect;
	rect.x = rect_.x;
	rect.y = rect_.y;
	rect.w = width_frame_;
	rect.h = height_frame_;

	return rect;
}

void ThreatsObject::RemoveBullet(const int& index)
{
	int size = bullet_list_.size();

	if (size > 0 && index < size)
	{
		BulletObject* p_bullet = bullet_list_.at(index);
		bullet_list_.erase(bullet_list_.begin() + index);

		if (p_bullet != NULL)
		{
			delete p_bullet;
			p_bullet =NULL;
		}
	}
}

void ThreatsObject::InitThreat()
{
	x_val_ = 0;
	y_val_ = 0;
	if (x_pos_ > 256)
	{
		x_pos_ -= 256;
		animation_a_ -= 256;
		animatin_b_ -= 256;
	} else {
		x_pos_ = 0;
	}
	y_pos_ = 0;
	come_back_time_ = 0;
	input_type_.left_ = 1;
}

void ThreatsObject::CheckToMap(Map& map_data)
{
	// gioi han kiem tra di chuyen theo OX
	int x1 = 0;
	int x2 = 0;
	// gioi han kiem tra di chuyen theo OY
	int y1 = 0;
	int y2 = 0;

	// check theo OX
	int height_min = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;

	// xac dinh vi tri o thu may
	x1 = (x_pos_  + x_val_) / TILE_SIZE;
	// so sanh kich thuoc
	x2 = (x_pos_ + x_val_ + width_frame_  - 1) / TILE_SIZE;

	y1 = (y_pos_) / TILE_SIZE;
	y2 = (y_pos_ + height_frame_ -1 ) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		if (x_val_ > 0) // di chuyen sang ben phai
		{
			int val_1 = map_data.tile[y1][x2];
			int val_2 = map_data.tile[y2][x2];

			
			if ((val_1 != BLANK_TILE && val_1 != STATE_COIN ) || (val_2 != BLANK_TILE && val_2 != STATE_COIN))
			{
				x_pos_ = x2 * TILE_SIZE;
				x_pos_ -= width_frame_ +1;
				x_val_ = 0;
			}
			
		} else if (x_val_ < 0 )
		{
			int val_1 = map_data.tile[y1][x1];
			int val_2 = map_data.tile[y2][x1];

			if ((val_1 != BLANK_TILE && val_1 != STATE_COIN )|| (val_2  != BLANK_TILE  && val_2 != STATE_COIN))
			{
					x_pos_ =  (x1 + 1 ) * TILE_SIZE;
					x_val_ = 0;
			}
		}
	}

	// check OY
	int width_min = width_frame_ > TILE_SIZE ? width_frame_ : TILE_SIZE;
	x1 = (x_pos_ ) / TILE_SIZE;
	x2 = (x_pos_ + width_frame_ ) / TILE_SIZE;

	y1 = (y_pos_ + y_val_) / TILE_SIZE;
	y2 = (y_pos_ + y_val_ + height_frame_ -1 ) / TILE_SIZE;


	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >=0 && y2 < MAX_MAP_Y )
	{

		if (y_val_ > 0 )
		{
			int val1 = map_data.tile[y2][x1];
			int val2 = map_data.tile[y2][x2];
	
			if ((val1 != BLANK_TILE && val1 != STATE_COIN  )|| (val2 != BLANK_TILE && val2 != STATE_COIN))
			{
				y_pos_ = y2 * TILE_SIZE;
				y_pos_ -= ( height_frame_  + 1 );
				y_val_ = 0;

				on_ground_ = true;
			}
			
		} else if (y_val_ < 0)
		{
			int val1 = map_data.tile[y1][x1];
			int val2 = map_data.tile[y1][x2];
			
			if ((val1 != BLANK_TILE && val1 != STATE_COIN)||( val2 != BLANK_TILE && val2 != STATE_COIN))
			{
				y_pos_ = (y1 + 1 ) * TILE_SIZE;
				y_val_ = 0;
			}
			
		}
	}

	x_pos_ += x_val_;
	y_pos_ += y_val_;

	if (x_pos_ < 0 )
	{
		x_pos_ = 0;
	} else if (x_pos_ + width_frame_ > map_data.max_x_)
	{
		x_pos_ = map_data.max_x_ - width_frame_ - 1;
	}


	if (y_pos_ > map_data.max_y_)
	{
		come_back_time_ = 60;
	}
}

void ThreatsObject::ImpMoveType(SDL_Renderer * screen)
{
	if ( type_move_ == STATIC_THREATS)
	{
		
	} 
	else
	{
		if (on_ground_ == true)
		{
			if ( x_pos_	> animatin_b_)
			{
				input_type_.left_ = 1;
				input_type_.right_ = 0;
				loadImg("img//threat_left.png", screen);
			}
			else if (x_pos_ < animation_a_)
			{
				input_type_.right_ = 1;
				input_type_.left_ = 0;
				loadImg("img//threat_right.png", screen);
			}
		} else {
			if (input_type_.left_ == 1)
			{
				loadImg("img//threat_left.png", screen);
			}
		}
	}
}


void ThreatsObject::InitBullet(BulletObject* p_bullet, SDL_Renderer * screen)
{
	if (p_bullet != NULL)
	{

		p_bullet->set_bullet_type(BulletObject::LASER_BULLET);
		bool ret = p_bullet->LoadImgBullet(screen);
		if (ret != NULL)
		{
			p_bullet->set_is_move(true);
			p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);

			int xp = x_pos_ - map_x_;
			int yp = y_pos_ - map_y_;

			p_bullet->SetRect(xp , yp + 15 );
			p_bullet->set_x_val(15);
			bullet_list_.push_back(p_bullet);
		}
	}
}

void ThreatsObject::MakeBullet(SDL_Renderer * screen, const int& x_limit_, const int& y_limit_)
{
	for (int i = 0 ; i < bullet_list_.size() ;i++)
	{
		BulletObject * p_bullet = bullet_list_.at(i);
		if (p_bullet != NULL)
		{
			if (p_bullet->get_is_move() )
			{
				int bullet_distance_ = rect_.x + width_frame_ - p_bullet->GetRect().x;
				if (bullet_distance_ < 350 && bullet_distance_ > 0)
				{
					p_bullet->HandleMove(x_limit_, y_limit_);
					p_bullet->Render(screen);
				} else
				{
					p_bullet->set_is_move(false);
				}
			}
			else 
			{
				p_bullet->set_is_move(true);
				p_bullet->SetRect(rect_.x + 5, rect_.y + 10);
			}
		}
	}
}