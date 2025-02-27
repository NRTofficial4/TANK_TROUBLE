/*CELL_PARAMETERS------------------------------------*/
#define CELL_NUMBER_HEIGH 7
#define CELL_NUMBER_WIDTH (CELL_NUMBER_HEIGH*1920/1000)
#define CELL_WALL_THICKNESS CELL_NUMBER_WIDTH
/*-----------------------------------------------------*/

#define MAZE_CELL_NUMBER (CELL_NUMBER_WIDTH*CELL_NUMBER_HEIGH)

/*CELL_CORNERS - INDEX------------------------------------*/
#define CELL_TOP_LEFT 0
#define CELL_TOP_RIGHT CELL_NUMBER_WIDTH-1
#define CELL_BOTTON_LEFT CELL_NUMBER_WIDTH*(CELL_NUMBER_HEIGH-1)
#define CELL_BOTTON_RIGHT MAZE_CELL_NUMBER-1
/*------------------------------------------------------*/

/*WINDOW PARAMETERS-------------------------------------*/
#define WINDOW_HEIGH 1000
#define WINDOW_WIDTH 1920
/*----------------------------------------------------*/

#define CELL_SIZE WINDOW_HEIGH/CELL_NUMBER_HEIGH

