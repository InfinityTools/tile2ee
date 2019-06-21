#ifndef _TILE2EE_HPP_
#define _TILE2EE_HPP_

namespace tc {

class Tile2EE
{
public:
  Tile2EE(int argc, char *argv[]) noexcept;
  ~Tile2EE() noexcept;

  // Initialize the converter object with the specified arguments
  bool init(int argc, char *argv[]) noexcept;

  // Initiate conversion process
  bool execute() noexcept;

  Options& getOptions() noexcept { return m_options; }

private:
  // Display information about the specified filename
  bool showInfo(const std::string &fileName) noexcept;

  // Returns whether arguments have been initialized successfully.
  bool isInitialized() const noexcept { return m_initialized; }

private:
  Options   m_options;
  bool      m_initialized;
};

}		// namespace tc

#endif		// _TILE2EE_HPP_
