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

	beginTest("Create tile up step 1.");
	{
		assertByteDecimal("Head", tileCreate(TileType_animated_head, Direction_up, Direction_up, Microstep_1), Tile_worm_up_0_1);
		assertByteDecimal("Head to middle", tileCreate(TileType_animated_headToMiddle, Direction_up, Direction_up, Microstep_1), Tile_worm_up_1_1);
		assertByteDecimal("End to middle", tileCreate(TileType_animated_endToMiddle, Direction_up, Direction_up, Microstep_1), Tile_worm_up_2_1);
		assertByteDecimal("End", tileCreate(TileType_animated_end, Direction_up, Direction_up, Microstep_1), Tile_worm_up_3_1);
	}
	endTest();

	beginTest("Create tile up step 2.");
	{
		assertByteDecimal("Head", tileCreate(TileType_animated_head, Direction_up, Direction_up, Microstep_2), Tile_worm_up_0_2);
		assertByteDecimal("Head to middle", tileCreate(TileType_animated_headToMiddle, Direction_up, Direction_up, Microstep_2), Tile_worm_up_1_2);
		assertByteDecimal("End to middle", tileCreate(TileType_animated_endToMiddle, Direction_up, Direction_up, Microstep_2), Tile_worm_up_2_2);
		assertByteDecimal("End", tileCreate(TileType_animated_end, Direction_up, Direction_up, Microstep_2), Tile_worm_up_3_2);
	}
	endTest();

	beginTest("Create tile up step 3.");
	{
		assertByteDecimal("Head", tileCreate(TileType_animated_head, Direction_up, Direction_up, Microstep_3), Tile_worm_up_0_3);
		assertByteDecimal("Head to middle", tileCreate(TileType_animated_headToMiddle, Direction_up, Direction_up, Microstep_3), Tile_worm_up_1_3);
		assertByteDecimal("End to middle", tileCreate(TileType_animated_endToMiddle, Direction_up, Direction_up, Microstep_3), Tile_worm_up_2_3);
		assertByteDecimal("End", tileCreate(TileType_animated_end, Direction_up, Direction_up, Microstep_3), Tile_worm_up_3_3);
	}
	endTest();

	beginTest("Create tile right step 0.");
	{
		assertByteDecimal("Head", tileCreate(TileType_animated_head, Direction_right, Direction_right, Microstep_0), Tile_worm_right_0_0);
		assertByteDecimal("Head to middle", tileCreate(TileType_animated_headToMiddle, Direction_right, Direction_right, Microstep_0), Tile_worm_right_1_0);
		assertByteDecimal("End to middle", tileCreate(TileType_animated_endToMiddle, Direction_right, Direction_right, Microstep_0), Tile_worm_right_2_0);
		assertByteDecimal("End", tileCreate(TileType_animated_end, Direction_right, Direction_right, Microstep_0), Tile_empty);
	}
	endTest();

	beginTest("Create tile right step 1.");
	{
		assertByteDecimal("Head", tileCreate(TileType_animated_head, Direction_right, Direction_right, Microstep_1), Tile_worm_right_0_1);
		assertByteDecimal("Head to middle", tileCreate(TileType_animated_headToMiddle, Direction_right, Direction_right, Microstep_1), Tile_worm_right_1_1);
		assertByteDecimal("End to middle", tileCreate(TileType_animated_endToMiddle, Direction_right, Direction_right, Microstep_1), Tile_worm_right_2_1);
		assertByteDecimal("End", tileCreate(TileType_animated_end, Direction_right, Direction_right, Microstep_1), Tile_worm_right_3_1);
	}
	endTest();

	beginTest("Create tile right step 2.");
	{
		assertByteDecimal("Head", tileCreate(TileType_animated_head, Direction_right, Direction_right, Microstep_2), Tile_worm_right_0_2);
		assertByteDecimal("Head to middle", tileCreate(TileType_animated_headToMiddle, Direction_right, Direction_right, Microstep_2), Tile_worm_right_1_2);
		assertByteDecimal("End to middle", tileCreate(TileType_animated_endToMiddle, Direction_right, Direction_right, Microstep_2), Tile_worm_right_2_2);
		assertByteDecimal("End", tileCreate(TileType_animated_end, Direction_right, Direction_right, Microstep_2), Tile_worm_right_3_2);
	}
	endTest();

	beginTest("Create tile right step 3.");
	{
		assertByteDecimal("Head", tileCreate(TileType_animated_head, Direction_right, Direction_right, Microstep_3), Tile_worm_right_0_3);
		assertByteDecimal("Head to middle", tileCreate(TileType_animated_headToMiddle, Direction_right, Direction_right, Microstep_3), Tile_worm_right_1_3);
		assertByteDecimal("End to middle", tileCreate(TileType_animated_endToMiddle, Direction_right, Direction_right, Microstep_3), Tile_worm_right_2_3);
		assertByteDecimal("End", tileCreate(TileType_animated_end, Direction_right, Direction_right, Microstep_3), Tile_worm_right_3_3);
	}
	endTest();
}
