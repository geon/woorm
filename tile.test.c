#include "tile.h"
#include "cc65-test.h"
#include "direction.h"

void tileTest()
{
	beginTest("Create tile up step 0.");
	{
		assertByteDecimal("Head", tileCreate(TileType_animated_head, Direction_up, Direction_up, Microstep_0), Tile_worm_up_0_0);
		assertByteDecimal("Head to middle", tileCreate(TileType_animated_headToMiddle, Direction_up, Direction_up, Microstep_0), Tile_worm_up_1_0);
		assertByteDecimal("End to middle", tileCreate(TileType_animated_endToMiddle, Direction_up, Direction_up, Microstep_0), Tile_worm_up_2_0);
		assertByteDecimal("End", tileCreate(TileType_animated_end, Direction_up, Direction_up, Microstep_0), Tile_empty);
	}
	endTest();
}
