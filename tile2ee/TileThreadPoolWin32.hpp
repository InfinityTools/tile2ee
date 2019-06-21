#ifndef _TILETHREADPOOLWIN32_HPP_
#define _TILETHREADPOOLWIN32_HPP_

#ifdef USE_WINTHREADS
#include <windows.h>
#include "TileThreadPoolBase.hpp"

namespace tc {

class TileThreadPoolWin32 : public TileThreadPool
{
public:
  TileThreadPoolWin32(unsigned threadNum, unsigned tileNum) noexcept;
  ~TileThreadPoolWin32() noexcept;

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
  // Executed by each thread. lpParam points to the current TileThreadPoolWin32 class instance.
  static DWORD WINAPI threadMain(LPVOID lpParam);

private:
  int                       m_activeThreads;
  HANDLE                    m_mainThread;
  HANDLE                    m_activeMutex;
  HANDLE                    m_tilesMutex;
  HANDLE                    m_resultsMutex;
//  std::vector<HANDLE>       m_threads;
  unsigned                  m_threadsNum;
  std::shared_ptr<HANDLE>   m_threads;
};

}   // namespace tc

#endif    // USE_WINTHREADS

#endif		// _TILETHREADPOOLWIN32_HPP_
