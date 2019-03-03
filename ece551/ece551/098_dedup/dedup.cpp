#include <bits/stdc++.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <cstdlib>
#include <fstream>
#include <functional>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>

void add_remove(std::map<size_t, std::string> & mymap, const std::string & filepath) {
  std::ifstream f;
  f.open(filepath);
  if (f.is_open()) {
    std::stringstream s;
    s << f.rdbuf();
    std::string str = s.str();
    //mymap[str] = filepath;
    /*for (std::unordered_map<std::string, std::string>::iterator it = mymap.begin();
         it != mymap.end();
         ++it) {
      if (it->first == str) {
        std::cout << "#Removing " << it->second << "(duplicate of " << filepath << ")."
                  << "\n\nrm " << it->second << std::endl;
        mymap.erase(str);
        break;
      }
      }*/
    std::hash<std::string> myhash;
    size_t key = myhash(str);
    //size_t h = key % 1000;
    std::map<size_t, std::string>::iterator it = mymap.find(key);
    if (it == mymap.end()) {
      mymap[key] = filepath;
    }
    else {
      std::cout << "#Removing " << filepath << " (duplicate of " << it->second << ")."
                << "\n\nrm " << filepath << std::endl;
    }
    f.close();
  }
  else {
    std::cout << "can't open the file!:" << filepath << "\n";
    exit(EXIT_FAILURE);
  }
}

void getfile(std::map<size_t, std::string> & mymap, const char * path) {
  DIR * dirptr = NULL;
  struct dirent * entry;
  if ((dirptr = opendir(path)) == NULL) {
    /* could not open directory */
    perror("");
    exit(EXIT_FAILURE);
  }
  else {
    /* print all the files and directories within directory */
    while ((entry = readdir(dirptr)) != NULL) {
      if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
      }
      else if (entry->d_type & DT_DIR) {
        std::stringstream childpath;
        childpath << path << "/" << entry->d_name;
        getfile(mymap, (childpath.str()).c_str());
      }
      else {
        std::stringstream filepath;
        filepath << path << "/" << entry->d_name;
        struct stat info;
        if (lstat((filepath.str()).c_str(), &info) == -1) {
          perror("error loading name");
        }
        else {
          if (S_ISLNK(info.st_mode)) {
          }
          else {
            add_remove(mymap, filepath.str());
          }
        }
      }
    }
    closedir(dirptr);
  }
}

int main(int argc, char ** argv) {
  if (argc < 1) {
    std::cout << "Expect more input argument!\n";
    return EXIT_FAILURE;
  }
  else {
    std::map<size_t, std::string> mymap;
    std::cout << "#!/bin/bash\n";
    for (int i = 1; i < argc; i++) {
      getfile(mymap, argv[i]);
    }
    return EXIT_SUCCESS;
  }
}
