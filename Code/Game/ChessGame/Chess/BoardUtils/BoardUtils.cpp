#include "BoardUtils.h"

int BoardUtils::CellNameToIndex(const std::string& cellName)
{
	if (cellName.length() != 2) throw std::exception("Cell Name size has to be 2 letters length");

	if (cellName[0] >= 'a' && cellName[0] <= 'h' && cellName[1] >= '1' && cellName[1] <= '8')
	{
		return ((cellName[1] - '0' - 1) * 8) + (cellName[0] - 'a'); // row * 8 + column
	}
	else throw std::exception("Bad cell name");
}

std::string BoardUtils::IndexToCellName(int index)
{
	if (index < 0 || index > 63) throw std::exception("Index has to be btw 0-64");

	std::string cellName = "00";

	cellName[0] = (char)(index % 8 + 'a');
	cellName[1] = (char)(index / 8 + '1');

	return cellName;
}
