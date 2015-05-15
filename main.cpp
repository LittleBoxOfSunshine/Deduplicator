#include <iostream>
#include <string>
#include <vector>
#include <boost/filesystem.hpp>

#include "consoleui.h"
#include "AVLTree.h"

struct File{
    boost::filesystem::path path;
    int size;

    File(boost::filesystem::path p, int s){
        this->path = p;
        this->size = s;
    }

    bool operator==(const File &rhs){
        if(this->size != rhs.size)
            return false;

        std::ifstream f1(this->path.string(), std::ios::binary);
        std::ifstream f2(rhs.path.string(), std::ios::binary);

        long t1;
        long t2;

        for(int i=0; i<size; i++){
            f1 >> t1;
            f2 >> t2;
            if(t1 != t2)
                return false;
        }
        return true;
    }

};

struct FileBucket{
    int size;
    std::vector<File> files;

    FileBucket(){
        size = 0;
    }

    FileBucket(int size){
        this->size = size;
    }

    void addFile(boost::filesystem::path path){
        this->files.push_back(File(path, this->size));
    }

    bool operator<(const FileBucket &rhs){
        return this->size < rhs.size;
    }

    bool operator==(const FileBucket &rhs){
        return this->size == rhs.size;
    }
};

///Filters out duplicate paths, if removeDuplicates is true it will remove those files, if false it will only keep them (gives a list of files to delete for example)
void filterDuplicates(std::vector<boost::filesystem::path> &paths, AVLNode<FileBucket>* file){
    if(file != nullptr){
        std::cout << "Bucket = " << file->getKey().size << " | size = " << file->getKey().files.size() << "\n" << std::endl;
        for(int i=0; i<file->getKey().files.size(); i++){
            for(int z =i+1; z<file->getKey().files.size(); z++){
                if(file->getKey().files[i] == file->getKey().files[z])
                    paths.push_back(file->getKey().files[z].path);
            }
        }

        filterDuplicates(paths, file->Left());
        filterDuplicates(paths, file->Right());
    }
}

//NOTE THIS IS MISSING NO RECURSION SUPPORT

///Builds file objects for all files contained within the given directory
void scanFiles(AVLTree<FileBucket> &files, std::string rootPath, bool recursive){
    boost::filesystem::path directory(rootPath);

    FileBucket temp(0);
    FileBucket* ptr;

    if (!boost::filesystem::exists(directory) || !boost::filesystem::is_directory(directory))
    {
        std::cout << "ERROR: the path \"" << directory << "\" is not a directory..." << std::endl;
    }

    if(recursive){
            boost::filesystem::recursive_directory_iterator itr(directory);
        while (itr != boost::filesystem::recursive_directory_iterator())
        {
             std::cout << "Itterating: " << itr->path().string() << std::endl;
            if(!boost::filesystem::is_directory(itr->path())){

            temp = FileBucket(boost::filesystem::file_size(itr->path()));
            files.insert(files.getTree(), temp, ptr);
            ptr->addFile(itr->path());
            }

            ++itr;
        }
    }
    else{
        boost::filesystem::directory_iterator end_iter;


          for( boost::filesystem::directory_iterator itr(directory) ; itr != end_iter ; ++itr)
          {
                    std::cout << "Itterating: " << itr->path().string() << std::endl;
                    if(!boost::filesystem::is_directory(itr->path())){

                    temp = FileBucket(boost::filesystem::file_size(itr->path()));
                    files.insert(files.getTree(), temp, ptr);
                    ptr->addFile(itr->path());
                    }
          }
        }
}

int main(int argc, char** argv) {
    std::cout << "Deduplicator V0.1:" << std::endl << std::endl;

    int mode = BMCA::UI::getIntInput({ "Select A Mode", "Move", "Delete" });

    std::string dest;

    std::string rootPath = BMCA::UI::getStringInput("Enter the path of the directory to scan:");

    bool recursive = BMCA::UI::getBoolInput("Search directories recursively? (look inside folders)");

    if(mode==1)
        dest = BMCA::UI::getStringInput("What directory would you like to move unique files to?");

    AVLTree<FileBucket> files;

    //scan all requested paths and generate prelimnary file information
    scanFiles(files, rootPath, recursive);

    std::vector<boost::filesystem::path> paths;

    filterDuplicates(paths, files.getTree());;

    //move duplicates
    if(mode==1){
        //this needs to handle the direc
        int tempLoc;
           for(boost::filesystem::path element : paths){
               tempLoc = element.string().rfind('/');
               boost::filesystem::rename(element, boost::filesystem::path(dest + element.string().substr(tempLoc+1)));

           }
    }
    //delete duplicates
    else{

        for(boost::filesystem::path element : paths){
            std::cout << "Deleting: " << element.string() << std::endl;
            boost::filesystem::remove(element);
        }
    }

    return 0;
}
