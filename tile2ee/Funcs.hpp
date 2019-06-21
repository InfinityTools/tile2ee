#ifndef _FUNCS_HPP_
#define _FUNCS_HPP_
#include <cstdint>

namespace tc {

// Performs unconditional byte swaps
static inline uint16_t swap16u(const uint16_t *ptr, int idx = 0) { return (uint16_t)(((uint8_t*)(&ptr[idx]))[0] << 8 | ((uint8_t*)(&ptr[idx]))[1]); }
static inline int16_t swap16s(const int16_t *ptr, int idx = 0)   { return (int16_t)(((uint8_t*)(&ptr[idx]))[0] << 8 | ((uint8_t*)(&ptr[idx]))[1]); }

static inline uint32_t swap32u(const uint32_t *ptr, int idx = 0) { return (uint32_t)swap16u((uint16_t*)(&ptr[idx]), 0) << 16 | (uint32_t)swap16u((uint16_t*)(&ptr[idx]), 1); }
static inline int32_t swap32s(const int32_t *ptr, int idx = 0)   { return (int32_t)swap16s((int16_t*)(&ptr[idx]), 0) << 16 | (uint32_t)swap16u((uint16_t*)(&ptr[idx]), 1); }

static inline uint64_t swap64u(const uint64_t *ptr, int idx = 0) { return (uint64_t)swap32u((uint32_t*)(&ptr[idx]), 0) << 32 | (uint64_t)swap32u((uint32_t*)(&ptr[idx]), 1); }
static inline int64_t swap64s(const int64_t *ptr, int idx = 0)   { return (int64_t)swap32s((int32_t*)(&ptr[idx]), 0) << 32 | (uint64_t)swap32u((uint32_t*)(&ptr[idx]), 1); }

// Peforms no operation
static inline uint16_t noop16u(const uint16_t *ptr, int idx = 0) { return ptr[idx]; }
static inline int16_t noop16s(const int16_t *ptr, int idx = 0) { return ptr[idx]; }

static inline uint32_t noop32u(const uint32_t *ptr, int idx = 0) { return ptr[idx]; }
static inline int32_t noop32s(const int32_t *ptr, int idx = 0) { return ptr[idx]; }

static inline uint64_t noop64u(const uint64_t *ptr, int idx = 0) { return ptr[idx]; }
static inline int64_t noop64s(const int64_t *ptr, int idx = 0) { return ptr[idx]; }


// The following functions may be used for endian-swapping,
#if (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
#define get16u_le swap16u
#define get16s_le swap16s

#define get32u_le swap32u
#define get32s_le swap32s

#define get64u_le swap64u
#define get64s_le swap64s

#define get16u_be noop16u
#define get16s_be noop16s

#define get32u_be noop32u
#define get32s_be noop32s

#define get64u_be noop64u
#define get64s_be noop64s
#else
#define get16u_le noop16u
#define get16s_le noop16s

#define get32u_le noop32u
#define get32s_le noop32s

#define get64u_le noop64u
#define get64s_le noop64s

#define get16u_be swap16u
#define get16s_be swap16s

#define get32u_be swap32u
#define get32s_be swap32s

#define get64u_be swap64u
#define get64s_be swap64s

#endif

}   // namespace tc

#endif  // _FUNCS_HPP_
