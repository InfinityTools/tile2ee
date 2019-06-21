#include <algorithm>
#include "TileThreadPoolBase.hpp"

namespace tc {

const unsigned TileThreadPool::MAX_THREADS  = 256u;
const unsigned TileThreadPool::MAX_TILES    = std::numeric_limits<int>::max();


TileThreadPool::TileThreadPool(unsigned tileNum) noexcept
: m_terminate(false)
, m_maxTiles(MAX_TILES)
, m_tiles()
, m_results()
{
  setMaxTiles(tileNum);
}


void TileThreadPool::setMaxTiles(unsigned maxTiles) noexcept
{
  m_maxTiles = std::max(1u, std::min(MAX_TILES, maxTiles));
}

}   // namespace tc
