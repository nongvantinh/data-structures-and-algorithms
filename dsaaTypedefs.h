#ifndef DSAA_TYPEDEFS_H
#define DSAA_TYPEDEFS_H

// Adds nodiscard modifer to function.
#ifdef DSAA_NODISCARD
#define NODISCARD [[nodiscard]]
#define PNODISCARD(param) [[nodiscard(param)]]
#else
#define NODISCARD
#define PNODISCARD
#endif

// Makes function constexpr.
#ifdef DSAA_CONSTEXPR
#define CONSTEXPR constexpr
#else
#define CONSTEXPR
#endif

// Makes function inline.
#ifdef DSAA_FORCE_INLINE
#if defined(__GNUC__)
#define INLINE __attribute__((always_inline)) inline
#elif defined(_MSC_VER)
#define INLINE __forceinline
#else
#define INLINE inline
#endif //!(__GNUC__)
#elif DSAA_INLINE
#define INLINE inline
#else
#define INLINE
#endif //!DSAA_INLINE

// Allows checking for valid arguments in function.
#ifdef DSAA_PARAM_CHECK
#define PARAM_CHECK
#endif //!DSAA_PARAM_CHECK

#ifdef PARAM_CHECK
#define NOEXCEPT
#else
#define NOEXCEPT noexcept
#endif //!PARAM_CHECK

#endif //!DSAA_TYPEDEFS_H