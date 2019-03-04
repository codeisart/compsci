#include <iostream>

struct C2d 
{
	int x = 0;
	int y = 0;
	C2d(int inx=0, int iny = 0) : x(inx), y(iny) {}
	C2d operator+(const C2d& P) { return C2d{x+P.x, y+P.y}; } 
	C2d& operator+=(const C2d& P) { x+=P.x; y+=P.y; return *this; } 
	bool operator==(const C2d& P) { return x==P.x && y == P.y; }
};

char gMtrx[4][4] = {
	'1','2','3','4',
	'c','d','e','5',
	'b','g','f','6',
	'a','9','8','7'
};
bool gVisted[4][4] = { 
	false,false,false,false, 
	false,false,false,false, 
	false,false,false,false, 
	false,false,false,false
};

static const auto kLeft  = C2d(-1,0 );
static const auto kDown  = C2d( 0,1 );
static const auto kRight = C2d( 1,0 );
static const auto kUp    = C2d( 0,-1);

bool canMove(const C2d& pos)
{
	if( pos.x <0 || pos.x >=4) 
		return false;
	if( pos.y <0 || pos.y >=4) 
		return false;

	if( gVisted[pos.y][pos.x] )
	{
		//std::cout << "visited this before " << gMtrx[pos.y][pos.x] << std::endl;
		return false;
	}
	return true;
}

void changeDir(C2d& dir)
{
	// Clockwise. (right, down, left, up)
	//if(      dir == kRight )  dir = kDown;
	//else if( dir == kDown )  dir = kLeft;
	//else if( dir == kLeft )  dir = kUp;
	//else if( dir == kUp ) 	 dir = kRight;
	
	// Anti-Clockwise. (down,right,up,left)
	if(      dir == kDown )  dir = kRight;
	else if( dir == kRight ) dir = kUp;
	else if( dir == kUp )    dir = kLeft;
	else if( dir == kLeft )  dir = kDown;
}

void move(C2d& pos, const C2d& dir)
{
	gVisted[pos.y][pos.x] = true;
	pos+=dir;
}	      

bool canMoveAny(C2d& pos)
{
	if( canMove(pos+kLeft) ) return true;
	if( canMove(pos+kRight) ) return true;
	if( canMove(pos+kUp) ) return true;
	if( canMove(pos+kDown) ) return true;
	
	return false;
}

int main()
{
	C2d dir = kDown; 
	C2d pos = C2d(0,0);

	for(;;)
	{
		// is currnt pos valid?
		//if(!canMove(pos))
		//	break;

		// print contents.
		//std::cout << "\tx=" << pos.x
		//	<< "\ty=" << pos.y
		//	<< "\tval=" << gMtrx[pos.y][pos.x] 
		//	<< std::endl;
		std::cout << gMtrx[pos.y][pos.x];

		// find next location loop.
	      	int i = 0;
		for(; i < 4; ++i)	
		{
			// can move in current direction?
			if( canMove(pos+dir) )
			{
				move(pos,dir);
				break;
			}
			else 
				changeDir(dir);
		}
		if(i==4)
			break;
	}
	std::cout << std::endl;
}
