#ifndef KUNAI_PATH_HEADER
#  define KUNAI_PATH_HEADER

#  if defined(_WIN32)
#    define PATH_SEPARATOR "\\"
#    include <direct.h>
#    define __getCwd _getcwd
#  else
#    define PATH_SEPARATOR "/"
#    include <unistd.h>
#    define __getCwd getcwd
#  endif

#  include <vector>
#  include <string>
#  include <cstring>
#  include <iostream>
#  include <algorithm>

namespace path {
  std::string getCwd() {
    char buff[FILENAME_MAX];
    __getCwd(buff, FILENAME_MAX);
    std::string cwd(buff);
    return cwd;
  }

  std::string beautify(std::string path) {
    if (PATH_SEPARATOR == "\\") {
      std::replace(path.begin(), path.end(), '/', '\\');
    }
    
    std::vector<std::string> pathParts;
    int last = 0;
    int next = 0;
    while ((next = path.find(PATH_SEPARATOR, last)) != std::string::npos) {
      pathParts.push_back(path.substr(last, next - last));
      last = next + 1;
    }

    try { pathParts.push_back(path.substr(last, path.length())); } catch(std::exception e) {}

    std::string newPath = "";

    if (PATH_SEPARATOR == "/") {
      newPath = "/";
    }

    int subLen = 0;
    int lastMatchLen = 0;
    for(int i = 0; i < pathParts.size(); i++) {
      if (pathParts[i] != "..") {
        if (newPath[newPath.length() - 1] != PATH_SEPARATOR[0] && i != 0) newPath += "\\";
        if (i == pathParts.size() - 1) {
          newPath += pathParts[i];
        } else {
          newPath += pathParts[i] + PATH_SEPARATOR;
        }
      } else {
        newPath = newPath.substr(0, subLen - lastMatchLen);
        subLen = newPath.length() - 1;
        continue;
      }
      lastMatchLen = pathParts[i].length();
      subLen = newPath.length() - 1;
    }

    return newPath;
  }

  std::string join(std::string path1, std::string path2) {
    return beautify(path1 + PATH_SEPARATOR + path2);
  }

  std::string join(std::string path1, std::string path2, std::string path3) {
    return beautify(join(path1, join(path2, path3)));
  }

  std::string join(std::string path1, std::string path2, std::string path3, std::string path4) {
    return beautify(join(path1, join(path2, join(path3, path4))));
  }

  std::string join(std::string path1, std::string path2, std::string path3, std::string path4, std::string path5) {
    return beautify(join(path1, join(path2, join(path3, join(path4, path5)))));
  }
}

#endif // #ifndef KUNAI_PATH_HEADER