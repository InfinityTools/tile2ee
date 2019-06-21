#ifndef _TILETHREADPOOLPOSIX_HPP_
#define _TILETHREADPOOLPOSIX_HPP_

#ifndef USE_WINTHREADS
#include <vector>
#include <thread>
#include <mutex>
#include "TileThreadPoolBase.hpp"

namespace tc {

/** Provides threading capabilities specialized for encoding or decoding tile data, using posix calls. */
class TileThreadPoolPosix : public TileThreadPool
{
public:
  TileThreadPoolPosix(unsigned threadNum, unsigned tileNum) noexcept;
  ~TileThreadPoolPosix() noexcept;

  /** See TileThreadPool::addTileData() */
  void addTileData(TileDataPtr tileData) noexcept;

  /** See TileThreadPool::getResult() */
  TileDataPtr getResult() noexcept;
  /** See TileThreadPool::peekResult() */
  const TileDataPtr peekResult() noexcept;
  /** See TileThreadPool::waitForResult() */
  void waitForResult() noexcept;

  /** See TileThreadPool::finished() */
  bool finished() noexcept;

protected:
  void threadActivated() noexcept;
  void threadDeactivated() noexcept;
  int getActiveThreads() noexcept { return m_activeThreads; }

private:
  // Executed by each thread.
  void threadMain() noexcept;

private:
  int                       m_activeThreads;
  std::thread::id           m_mainThread;
  std::mutex                m_activeMutex;
  std::mutex                m_tilesMutex;
  std::mutex                m_resultsMutex;
  std::vector<std::thread>  m_threads;
};

}   // namespace tc

#endif    // USE_WINTHREADS

#endif		// _TILETHREADPOOLPOSIX_HPP_
