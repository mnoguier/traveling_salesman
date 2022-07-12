//1761414855B69983BD8035097EFBD312EB0527F0
//  main.cpp
//  p4
//
//  Created by Mathieu Noguier on 4/12/21.
//

#include <iostream>
#include <vector>
#include <deque>
#include "xcode_redirect.hpp"
#include <getopt.h>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <iterator>
#include <iomanip>
#include <limits>
#include <cmath>
using namespace std;

struct Graph {
    int x = 0;
    int y = 0;
    char category = '?';
    
};
struct Vert {
    bool visited = 0;
    double edgWeight = numeric_limits<double>::infinity();
    uint32_t parent = 0;
    size_t index = 0;
    
};
class MST {
public:
    void readData();
    void runMST();
    void printData();
    void runData();
    void printBData();
    bool promising(size_t permLength);
    void genPerms(size_t permLength);
    void optimal();
    void getMode(int argc, char * argv[]);
    double findDistanceMST(size_t x, size_t y);
    double findDistance(size_t x, size_t y);
    vector<Graph> coor;
    vector<Vert> cat;
    vector<size_t> best;
    vector<size_t> bestPath;
    uint32_t numVert = 0;
    double distance = 0;
    double totalWeight = 0;
    double totalBWeight = 0;
    double tester = 0;
    double bestCycle = 0;
    double currCycle = 0;
    //double permLength = 0;
    string mode;
    uint32_t modeType;
    bool notPossible = 0;
    
};

struct partC {
    void genPerms(vector<Graph>, size_t permLength);
    void runData ();
    void promising();
    vector<Graph> path;
    size_t permLength = 0;
};
double MST::findDistance(size_t p, size_t q) {
    double dist1 = double((coor[p].x - coor[q].x));
    double dist2 = double((coor[p].y - coor[q].y));
    double dist = (dist1 * dist1) + (dist2 * dist2);
    return sqrt(dist);
}
double MST::findDistanceMST(size_t x, size_t y) {
    bool noPath = 0;
    if(coor[x].category == 'm') {
        if(coor[y].category == 'n') {
            noPath = 1;
        }
    }
    if(coor[y].category == 'm') {
        if(coor[x].category == 'n') {
            noPath = 1;
        }
    }
    if (noPath) {
        return numeric_limits<double>::infinity();
    }
    else {
    double dist1 = double((coor[x].x - coor[y].x));
    double dist2 = double((coor[x].y - coor[y].y));
    double dist = (dist1 * dist1) + (dist2 * dist2);
    return dist;
    }
}
void MST::readData() {
    Graph info;
    
    cin >> numVert >> ws;
    cat.resize(numVert);
    coor.reserve(numVert);
    uint32_t bCheck = 0;
    uint32_t mCheck = 0;
    uint32_t nCheck = 0;
    while (cin >> info.x) {
        // handle ws?
        cin >> info.y;
        if ((int(info.x) == 0 && int(info.y < 0))|| (int(info.x < 0) && int(info.y) == 0)) {
            info.category = 'b';
            bCheck++;
        }// if
        else if (int(info.x) < 0 && int(info.y) < 0) {
            info.category = 'm';
            mCheck++;
        }
        else {
            info.category = 'n';
            nCheck++;
        }
        coor.push_back({info.x,info.y, info.category});
    }// while
    if(modeType == 1) {
        if (bCheck == 0 && mCheck > 0 && nCheck > 0) {
            cerr << "Cannot construct MST\n";
            exit(1);
        }//if
    }// if
}//readData
class SortDistance {
public:
    bool operator() (const Vert &lhs, const Vert &rhs) {
        if(lhs.edgWeight < rhs.edgWeight) {
            return true;
        }
        else {
            return false;
        }
    }
};
void MST:: runMST() {
    
   
    for (size_t i = 0; i < coor.size(); i++) {
        cat[i].index = i;
    }
    cat[0].edgWeight = 0;
    for (size_t i = 0; i < coor.size(); i++) {
        double bestDist = numeric_limits<double>::infinity();
        size_t bestIdx = 0;
        for (size_t j = 0; j < coor.size(); j++) {
            if(!cat[j].visited) {
                if (cat[j].edgWeight < bestDist) {
                    bestDist = cat[j].edgWeight;
                    bestIdx = j;
                }//if
                
            }// if
        }//inner loop 1
        cat[bestIdx].visited = 1;
        totalWeight += cat[bestIdx].edgWeight;
        for (size_t k = 0; k < coor.size(); k++) {
            bool noPath = false;
            if(!cat[k].visited) {
                if(coor[bestIdx].category == 'm') {
                    if(coor[k].category == 'n') {
                        noPath = 1;
                    }
                }
                if(coor[k].category == 'm') {
                    if(coor[bestIdx].category == 'n') {
                        noPath = 1;
                    }
                }
               
                if (!noPath) {
                    double dist1 = double((coor[k].x - coor[bestIdx].x));
                    double dist2 = double((coor[k].y - coor[bestIdx].y));
                    dist1 = pow(dist1, 2.0);
                    dist2 = pow(dist2, 2.0);
                    //move sqrt
                    distance = sqrt(dist1 + dist2);
                    if(distance < cat[k].edgWeight) {
                    cat[k].edgWeight = distance;
                    cat[k].parent = uint32_t(bestIdx);
                    }
                }
            }
        }//inner loop 2
    }//outer for
}//runMST()
void MST::runData() {
    
    double dist1 = 0;
    double dist2 = 0;
    double dist3 = 0;
    double delta = 0;
    //double dist = 0;
    
    
    best.push_back(0);
    best.push_back(1);
    best.push_back(2);
    best.push_back(0);
    /**
    for (size_t i = 0; i < 2; i++) {
        double temp = findDistance(i, i+1);
        dist += temp;
    }
    dist += findDistance(2, 0);
    */
    for (size_t k = 3; k < coor.size(); k++) {
        double bestDlt = numeric_limits<double>::infinity();
        uint32_t bestInx = 0;
        tester = 0;
        for (size_t i = 0; i < best.size() - 1; i++) {
            dist1 = findDistance(best[i], k);
            dist2 = findDistance(best[i + 1], k);
            dist3 = findDistance(best[i], best[i + 1]);
            delta = dist1 + dist2 - dist3;
            if (delta < bestDlt) {
                bestDlt = delta;
                bestInx = uint32_t(i + 1);
            }
            
            double temp = findDistance(best[i], best[i+1]);
            tester += temp;
            
        }
        auto it = best.begin();
        best.insert(it + bestInx, k);
        //totalBWeight += bestDlt;
        tester += bestDlt;
    }
    //totalBWeight += dist;
}
void MST::printBData() {
    best.pop_back();
    cout << tester << endl;
    for (size_t i = 0; i < best.size(); i++) {
        cout << best[i] << " ";
    }
    cout << endl;
}

void MST::printData() {
    cout << totalWeight <<"\n";
    for (size_t i = 1; i < cat.size(); i++) {
        if (cat[i].parent < cat[i].index) {
            cout << cat[i].parent << " " << cat[i].index << "\n";
        }//if
        else {
            cout << cat[i].index << " " << cat[i].parent << "\n";
        }//else
    }
}//printData()
bool MST::promising(size_t permLength) {
    // run mst on vector //permlength to path.size()
    // add up the mst + 0 to permlength + arms
    //more return false
    double MSTweight = 0;
    double bestArmFront = numeric_limits<double>::infinity();
    double bestArmBack = numeric_limits<double>::infinity();
    
    if (best.size() - permLength < 4) {
        return true;
    }
    
    cat.clear();
    cat.resize(best.size() - permLength);
    for (size_t i = permLength; i < best.size(); i++) {
       double armFront = findDistance(best[0], best[i]);
        if(armFront < bestArmFront) {
            bestArmFront = armFront;
        }
        double armBack = findDistance(best[permLength - 1], best[i]);
        if(armBack < bestArmBack) {
            bestArmBack = armBack;
        }
    }
    
    cat[0].edgWeight = 0;
    for (size_t i = permLength; i < best.size(); i++) {
        double bestDist = numeric_limits<double>::infinity();
        size_t bestIdx = 0;
        for (size_t j = permLength; j < best.size(); j++) {
            if(!cat[j - permLength].visited) {
                if (cat[j - permLength].edgWeight < bestDist) {
                    bestDist = cat[j - permLength].edgWeight;
                    bestIdx = j - permLength;
                }//if
            }// if
        }//inner loop 1
        cat[bestIdx].visited = 1;
        MSTweight += cat[bestIdx].edgWeight;
        for (size_t k = permLength; k < best.size(); k++) {
            if(!cat[k - permLength].visited) {
                double distance = findDistance(best[k], best[bestIdx + permLength]);
                    if(distance < cat[k - permLength].edgWeight) {
                    cat[k - permLength].edgWeight = distance;
                    cat[k - permLength].parent = uint32_t(bestIdx);
                    }
            }
        }//inner loop 2
    }//outer for
    double promisingCheck = 0;
    if (permLength == 1) {
         promisingCheck = MSTweight + bestArmBack + currCycle;
    }
    else {
         promisingCheck = MSTweight + bestArmBack + bestArmFront + currCycle;
    }
    
    if (promisingCheck > bestCycle) {
        return false;
    }
    else {
        return true;
    }
    
    //total weight
    
}
void MST::genPerms(size_t permLength) {
    //use best
    //path can fasttsp
    //0 to permlegth is done
    //permlength to path.size() is what needs to be done
    //look at endpoints perm - 1 and 0
    
        if (permLength == best.size()) {
            currCycle += findDistance(best.front(), best.back());
            if(currCycle < bestCycle) {
                bestCycle = currCycle; // vector
                bestPath = best; //sum of all
                // connect beginning and end
            }
                currCycle -= findDistance(best.front(),best.back());
            return;
        }// if
    
        if (!promising(permLength)) {
            return;
        }//if
    
        for (size_t i = permLength; i < best.size(); ++i) {
            double adjustCycle = findDistance(best[permLength - 1], best[i]);
            swap(best[permLength],best[i]);
            currCycle += adjustCycle;
            genPerms(permLength + 1);
            currCycle -= adjustCycle;
            swap(best[permLength],best[i]);
        }//for
}
void MST::optimal() {
    bestCycle = tester;
    best.pop_back();
    genPerms(1);
    cout << bestCycle << "\n";
    for (size_t i = 0; i < bestPath.size(); i++) {
        cout << bestPath[i] << " ";
    }
    cout << "\n";
}
void printHelp(char *argv[]) {
    cout << "Usage: " << argv[0] << " [-m [MST, FASTTP, OTTSP] |-h" << endl;
    cout << "This program searchs graphs and stuff," << endl;
    cout << "using MST or not MST," << endl;
    cout << "then prints edges." << endl;
} // printHelp()
void MST::getMode(int argc, char * argv[]) {
    bool modeSpecified = false;
    string mode;
    
    // make class variable ^^
    // These are used with getopt_long()
    opterr = false; // Let us handle all error output for command line options
    int choice;
    int option_index = 0;
    option long_options[] = {
        // Fill in two lines, for the "mode" ('m') and
        // the "help" ('h') options.
        // ./project0 -m nosize
        // ./project0 --help
        // array of structures
        { "mode", required_argument, nullptr, 'm' },
        { "help", no_argument,       nullptr, 'h' },
        { nullptr, 0,                nullptr, '\0'}
        // always last ^^^^^
    };
    
    // Fill in the double quotes, to match the mode and help options.
    while ((choice = getopt_long(argc, argv, "m:h", long_options, &option_index)) != -1) {
        switch (choice) {
            case 'h':
                printHelp(argv);
                exit(0);
                break;
                
            case 'm':
                
                mode = *optarg;
                //if(strcmp(mode, "MST"))
                if(mode == "M") {
                    modeType = 1;
                }
                if(mode == "F") {
                    modeType = 2;
                }
                if(mode == "O") {
                    modeType = 3;
                }
                modeSpecified = true;
                break;
                
            /**
            case 'o':
                outType = *optarg;
                if (outType != 'M' && outType != 'L') {
                    outType = 'M';
                    
                } // if
                modeSpecified = true;
                break;
               */
            default:
                cerr << "Unknown command line option" << endl;
                exit(1);
                
        } // switch
    } // while
    
    if (!modeSpecified) {
        cerr << "Error: no mode specified" << endl;
        exit(1);
    } // if
    
    
} // getMode()
int main(int argc, char * argv[]) {
    ios_base::sync_with_stdio(false);
    xcode_redirect(argc, argv);
    MST mst;
    
    cout << setprecision(2);
    cout << fixed;
    mst.getMode(argc, argv);
    mst.readData();
    if (mst.modeType == 1) {
        mst.runMST();
        mst.printData();
    }
    if (mst.modeType == 2) {
        mst.runData();
        mst.printBData();
    }
    if (mst.modeType == 3) {
        mst.runData();
        mst.optimal();
    }
    
    return 0;
}
