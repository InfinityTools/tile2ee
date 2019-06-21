#ifndef _TYPES_HPP_
#define _TYPES_HPP_

#include <cstdint>
#include <memory>

namespace tc {

typedef std::shared_ptr<uint8_t> BytePtr;
typedef std::shared_ptr<uint32_t> IntPtr;

/**
 * Supported input file types:
 * UNKNOWN: Returned in case of error
 * TISV1:   Palette-based TIS resource type
 * TISV2:   PVRZ-based TIS resource type
 * MOSV1:   Palette-based MOS resource type
 * MOSV2:   PVRZ-based MOS resource type
 */
enum class FileType { UNKNOWN, TISV1, TISV2, MOSV1, MOSV2 };

/** Pixel encoding type used for MOS/TIS V2 data. */
enum class Encoding { UNKNOWN, BC1, BC2, BC3 };

/** Available ARGB color formats. (Example: ARGB = 0xaarrggbb) */
enum class ColorFormat { ARGB, ABGR, BGRA, RGBA };

static const unsigned PALETTE_SIZE                = 1024;     // palette size in bytes
static const unsigned TILE_DIMENSION              = 64;       // max. tile dimension
static const unsigned MAX_TILE_SIZE_8             = TILE_DIMENSION*TILE_DIMENSION;    // max. size (in bytes) of a 8-bit pixels tile
static const unsigned MAX_TILE_SIZE_32            = TILE_DIMENSION*TILE_DIMENSION*4;  // max. size (in bytes) of a 32-bit pixels tile
static const unsigned MAX_TILE_SIZE_ENCODED       = MAX_TILE_SIZE_8;    // DXT1: 8 bytes per 4x4 pixels, DXT3/5: 16 bytes per 4x4 pixels

}   // namespace tc

#endif		// _TYPES_HPP_
