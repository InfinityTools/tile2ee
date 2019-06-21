#ifndef _COMPRESSION_HPP_
#define _COMPRESSION_HPP_

#include <cstdint>
#include <zlib.h>

namespace tc {

/** Provides zlib compression and decompression routines. */
class Compression
{
public:
  Compression() noexcept;
  ~Compression() noexcept;

  /**
   * Applies zlib compression to a source data block and stores the result in a target data block.
   * \param src The source data block with raw data.
   * \param srcSize The number of bytes to compress.
   * \param dst  The data block to store the compressed data into.
   * \param dstSize The number of bytes available to store data into.
   * \return The size of the compressed data stored in the target data block or 0 on error.
   */
  uint32_t deflate(uint8_t *src, uint32_t srcSize, uint8_t *dst, uint32_t dstSize) noexcept;

  /**
   * Applies zlib decompression to a source data block and stores the result in a target data block.
   * \param src The source data containing the compressed data including size prefix.
   * \param srcSize The number of bytes to decompress.
   * \param dst The target block to store the decompressed data into.
   * \param dstSize The number of bytes available to store data into.
   * \return The size of the decompressed data stored in the target data block or 0 on error.
   */
  uint32_t inflate(uint8_t *src, uint32_t srcSize, uint8_t *dst, uint32_t dstSize) noexcept;

private:
  bool      m_defResult;    // stores the current state of the compressor
  bool      m_infResult;    // stores the current state of the decompressor
  z_stream  m_defStream;    // working structure for deflate
  z_stream  m_infStream;    // working structure for inflate
};

}   // namespace tc

#endif  // _COMPRESSION_HPP_
