#include <cstdlib> 
#include <iostream>
#include <map>
#include <string>
using namespace std;

void erosion() {
    system("./erosion");
}

void dilation() {
   system("./dilation");
}

void lighting() {
    system("./lighting");
}

void edgedetection() {
   system("./edgedetection");
}

void resizing() {
   system("./resizing");
}

void blending() {
   system("./blending");
}

void stitching() {
   system("./stitching --d3 --try_use_gpu yes --mode scans img1.jpg img2.jpg");
} 

void shapedetection() {
   system("./shapes");
}
void all() {
   system("./all ");
}

void help() {
   system("./help ");
}

std::map<std::string,void (*)(void)> tmap = {
    {"erosion",&erosion},
    {"dilation",&dilation},
    {"edgedetection",&edgedetection},
    {"resizing",&resizing},  
    {"blending",&blending},  
     {"lighting",&lighting},
      {"stitching",&stitching}, 
      {"shapedetection",&shapedetection}, 
     {"all",&all},  
     {"help",&help}                         
};

int main(int argc, char* argv[]) {
    if (argc > 1) {
        for (int i =1; i != argc; ++i) {
            if (tmap.find(argv[i]) != tmap.end()) {
                tmap[argv[i]]();
            }
            else {
                std::cout << "There is no " << argv[i] << " function available.\n Available functions are  \n erosion \n dilation \n edgedetection \n resizing \n blending \n shapedetection (advanced (expremental)) \n lighting \n stitching \n all \n help \n run it like .backslash run function name" << std::endl;
             }
         }
    }
    else {
        std::cout << "No functions were choosen.\n Available functions are  \n erosion \n dilation \n edgedetection \n resizing\n blending \n shapedetection (advanced (expremental)) \n lighting \n stitching \n all \n help \n run it like .backslash run function name" << std::endl;
    }
    return 0;
}
