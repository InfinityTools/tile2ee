#ifndef USE_WINTHREADS
#include "TileThreadPoolPosix.hpp"

namespace tc {

unsigned getThreadPoolAutoThreads()
{
  return std::max(1u, std::min(TileThreadPool::MAX_THREADS, std::thread::hardware_concurrency()));
}


ThreadPoolPtr createThreadPool(int threadNum, int tileNum)
{
  return ThreadPoolPtr(new TileThreadPoolPosix(threadNum, tileNum));
}


TileThreadPoolPosix::TileThreadPoolPosix(unsigned threadNum, unsigned tileNum) noexcept
: TileThreadPool(tileNum)
, m_activeThreads(0)
, m_mainThread(std::this_thread::get_id())
, m_activeMutex()
, m_tilesMutex()
, m_resultsMutex()
, m_threads()
{
  threadNum = std::max(1u, std::min(MAX_THREADS, threadNum));
  for (unsigned i = 0; i < threadNum; i++) {
    m_threads.emplace_back(std::thread(&TileThreadPoolPosix::threadMain, this));
  }
}


TileThreadPoolPosix::~TileThreadPoolPosix() noexcept
{
  setTerminate(true);
  for (auto iter = m_threads.begin(); iter != m_threads.end(); ++iter) {
    iter->join();
  }
}


void TileThreadPoolPosix::addTileData(TileDataPtr tileData) noexcept
{
  while (!canAddTileData()) {
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
  }

  std::lock_guard<std::mutex> lock(m_tilesMutex);
  getTileQueue().emplace(tileData);
}


TileDataPtr TileThreadPoolPosix::getResult() noexcept
{
  std::lock_guard<std::mutex> lock(m_resultsMutex);
  if (!getResultQueue().empty()) {
    TileDataPtr retVal = getResultQueue().top();
    getResultQueue().pop();
    return retVal;
  } else {
    return TileDataPtr(nullptr);
  }
}


const TileDataPtr TileThreadPoolPosix::peekResult() noexcept
{
  std::lock_guard<std::mutex> lock(m_resultsMutex);
  if (!getResultQueue().empty()) {
    return getResultQueue().top();
  } else {
    return TileDataPtr(nullptr);
  }
}


void TileThreadPoolPosix::waitForResult() noexcept
{
  while (!hasResult() && !finished()) {
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
  }
}


bool TileThreadPoolPosix::finished() noexcept
{
  std::unique_lock<std::mutex> lock1(m_tilesMutex, std::defer_lock);
  std::unique_lock<std::mutex> lock2(m_activeMutex, std::defer_lock);
  std::unique_lock<std::mutex> lock3(m_resultsMutex, std::defer_lock);
  std::lock(lock1, lock2, lock3);
  bool retVal = (getTileQueue().empty() && getActiveThreads() == 0 && getResultQueue().empty());
  lock1.unlock(); lock2.unlock(); lock3.unlock();
  return retVal;
}


void TileThreadPoolPosix::threadMain() noexcept
{
  std::unique_lock<std::mutex> lockTiles(m_tilesMutex, std::defer_lock);
  std::unique_lock<std::mutex> lockResults(m_resultsMutex, std::defer_lock);
  while (!terminate()) {
    lockTiles.lock();
    if (!getTileQueue().empty()) {
      threadActivated();

      TileDataPtr tileData = getTileQueue().front();
      getTileQueue().pop();
      lockTiles.unlock();

      (*tileData)();

      // storing results
      lockResults.lock();
      getResultQueue().push(tileData);
      lockResults.unlock();

      threadDeactivated();
    } else {
      lockTiles.unlock();
      std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
  }
}


void TileThreadPoolPosix::threadActivated() noexcept
{
  std::lock_guard<std::mutex> lock(m_activeMutex);
  m_activeThreads++;
}


void TileThreadPoolPosix::threadDeactivated() noexcept
{
  std::lock_guard<std::mutex> lock(m_activeMutex);
  m_activeThreads--;
}

}   // namespace tc

#endif    // USE_WINTHREADS
