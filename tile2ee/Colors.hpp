#ifndef _COLORS_HPP_
#define _COLORS_HPP_
#include <unordered_map>
#include "Options.hpp"

namespace tc {

/** Provides functions for colorspace reduction and expansion. */
class Colors
{
public:
  Colors(const Options &options) noexcept;
  ~Colors() noexcept;

  /**
   * Converts a 8-bit paletted data block into a 32-bit ARGB data block.
   * \param src Data block containing 8-bit color indices.
   * \param palette A color table of 256 entries using ARGB component order.
   * \param dst Data block to store the resulting 32-bit ARGB pixel into. (Note: ARGB = {b, g, r, a, ...})
   * \param size Number of pixels in the source block and available space in the target block.
   * \return The number of converted pixels or 0 on error.
   */
  int palToARGB(uint8_t *src, uint8_t *palette, uint8_t *dst, uint32_t size) noexcept;

  /**
   * Converts a 32-bit ARGB data block into a 8-bit paletted data block.
   * \param src Data block containing 32-bit ARGB pixels. (Note: ARGB = {b, g, r, a, ...})
   * \param dst Data block to store the resulting 8-bit indices into.
   * \param palette A ARGB color table to store 256 entries into. (Note: ARGB = {b, g, r, a, ...})
   * \param width Image width in pixels.
   * \param height Image height in pixels.
   * \return The number of converted pixels or 0 on error.
   */
  int ARGBToPal(uint8_t *src, uint8_t *dst, uint8_t *palette, uint32_t width, uint32_t height) noexcept;

  /** Read-only access to Options structure. */
  const Options& getOptions() const noexcept { return m_options; }

private:
  const Options&    m_options;
};

}   // namespace tc

#endif  // _COLORS_HPP_
