#include <array>

#ifdef __linux__
    #include <linux/limits.h>
    #include <unistd.h>
#elif _WIN32
    #include <../include/limits.h>
    #include <windows.h>
#endif

#ifdef __has_include
# if __has_include(<filesystem>)
    #include <filesystem>
    namespace fs = std::filesystem;
# elif __has_include(<experimental/filesystem>)
    #include <experimental/filesystem>
    namespace fs = std::experimental::filesystem;
# else
    #error "no filesystem support ='("
# endif
#endif

/**
 * @brief Cross platform way to get the path of the executable so we can derive the 
 * asset directory.
 * @see https://en.sfml-dev.org/forums/index.php?topic=12416.msg86622#msg86622
 */
auto my_executable_path() noexcept (false) -> std::string {
#ifdef __linux__
    char buff[PATH_MAX + 1]; // NOLINT(cppcoreguidelines-avoid-c-arrays, hicpp-avoid-c-arrays, modernize-avoid-c-arrays, cppcoreguidelines-pro-bounds-array-to-pointer-decay)
    ssize_t len = ::readlink("/proc/self/exe", buff, sizeof(buff) - 1); // NOLINT(hicpp-no-array-decay, cppcoreguidelines-pro-bounds-array-to-pointer-decay)
        if (len != -1) {
            buff[len] = '\0'; //NOLINT(cppcoreguidelines-pro-bounds-constant-array-index, hicpp-no-array-decay, cppcoreguidelines-pro-bounds-array-to-pointer-decay)
            return fs::path(buff).parent_path().string();
        } 
        throw std::runtime_error( "Failed to retrieve the executable path from /poroc/self/exe" );
#elif _WIN32
    char buff[MAX_PATH + 1];
    HMODULE module_handle = GetModuleHandle(nullptr);
    GetModuleFileName(module_handle, buff, sizeof(buff));
    return fs::path(buff).parent_path().string();
#else
#error "MISSING CODE :-( - See StackOverflow 1023306"
#endif
}


auto getAssetDir() noexcept(false) -> std::string{
    return my_executable_path() + "/sliding-tiles-assets/";
}