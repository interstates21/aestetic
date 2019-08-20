typedef struct s_player
{
	t_v3f pos;
	t_v3f motion;
    float angle, anglesin, anglecos, yaw;
	// double move_speed;
	// double rot_speed;
	// bool move_forw;
	// bool move_back;
	// bool rot_left;
	// bool rot_right;
} t_player;


static struct sector
{
    float floorHeight;
    float ceilHeight;
    t_v2f wall;
    signed char *neighbors;         
    unsigned npoints;              
} *sectors = NULL;