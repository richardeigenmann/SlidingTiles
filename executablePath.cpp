#include <stdexcept> // ADDED: For std::runtime_error
#include <string>
#include <sys/types.h> // ADDED: For ssize_t (POSIX)
#include <vector>

#ifdef __linux__
    #include <linux/limits.h>
    #include <unistd.h>
#elif _WIN32
    #include <../include/limits.h>
    #include <windows.h>
#endif

#ifdef __has_include
#if __has_include(<filesystem>)
    #include <filesystem>
    namespace fs = std::filesystem;
#elif __has_include(<experimental/filesystem>)
    #include <experimental/filesystem>
    namespace fs = std::experimental::filesystem;
#else
    #error "no filesystem support ='("
#endif
#endif

namespace {
/**
 * @brief Cross platform way to get the path of the executable so we can derive
 * the asset directory.
 * @see https://en.sfml-dev.org/forums/index.php?topic=12416.msg86622#msg86622
 */
auto my_executable_path() noexcept(false) -> std::string {
#ifdef __linux__
  // Initialize a vector to the required maximum size + 1 for null terminator
  std::vector<char> buff(PATH_MAX + 1);

  // Pass the underlying raw buffer to readlink using .data()
  // No array-decay warnings here.
  const ssize_t len =
      ::readlink("/proc/self/exe", buff.data(), buff.size() - 1);

  if (len != -1) {
    // Now you are assigning to a known index of the vector's buffer
    buff[len] = '\0';

    // Construct the string directly from the vector's buffer
    return fs::path(std::string(buff.data())).parent_path().string();
  }
  throw std::runtime_error(
      "Failed to retrieve the executable path from /poroc/self/exe");
#elif _WIN32
  char buff[MAX_PATH + 1];
  HMODULE module_handle = GetModuleHandle(nullptr);
  GetModuleFileName(module_handle, buff, sizeof(buff));
  return fs::path(buff).parent_path().string();
#else
#error "MISSING CODE :-( - See StackOverflow 1023306"
#endif
}
} // namespace

auto getAssetDir() noexcept(false) -> std::string {
    return my_executable_path() + "/sliding-tiles-assets/";
}
