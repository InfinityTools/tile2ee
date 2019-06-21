#ifndef _TILETHREADPOOL_HPP_
#define _TILETHREADPOOL_HPP_

#ifdef USE_WINTHREADS
  #include "TileThreadPoolWin32.hpp"
#else
  #include "TileThreadPoolPosix.hpp"
#endif


#endif		// _TILETHREADPOOL_HPP_
