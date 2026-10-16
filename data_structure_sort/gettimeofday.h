// Now you can use gettimeofday() on both Windows and Unix
#ifdef _WIN32
#include <chrono>
struct timeval {
    time_t      tv_sec;   // seconds since epoch (Jan 1, 1970 UTC)
    long tv_usec;  // microseconds (0 to 999,999)
};
int gettimeofday(struct timeval* tv, void* tz = nullptr) {
    // Get the current time point
    auto now = std::chrono::system_clock::now();

    // Convert to microseconds since epoch
    auto duration = now.time_since_epoch();
    auto us = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();

    // To split into seconds and microseconds
    if (tv) {
        tv->tv_sec = us / 1000000;
        tv->tv_usec = us % 1000000;
    }
    return 0;
}
#else
#include <sys/time.h>
#endif