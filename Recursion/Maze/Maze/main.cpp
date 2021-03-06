//
//  main.cpp
//  Maze
//
//  Created by Adam Saher on 22/02/2019.
//  Copyright © 2019 Adam Saher. All rights reserved.
//

#include <iostream>

#include "Maze.hpp"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
#define VERBOSE 0


int findPath (Maze& theMaze, const Coord& start, const Coord& end, Coord path[]);
void printPath(const char* fname, Coord path[],int n);
bool operator==(const Maze& left, const Maze& right);
bool testPath(const Maze* original,const Maze* marked, Coord start, Coord end, const Coord path[], int n);

int main(void){
    int testStart[7][2]={{1,1},{75,69},{75,69},{99,85},{1,1},{1,1}};
    int testEnd[7][2]={{1,99},{99,85},{75,69},{75,69},{191,199},{75,69}};
    const char* mazeFiles[10]={"maze1.txt", "maze1.txt","maze1.txt", "maze1.txt","maze2.txt", "maze3.txt"};
    const char* json[10]={"test1result.txt","test2result.txt","test3result.txt","test4result.txt","test5result.txt","test6result.txt"};
    const int numTests=6;
    int pathLength;
    Coord start;
    Coord end;
    Coord path[10000];
    Maze* m;
    Maze* original;
    ofstream out;
    int numPassed=0;
    for(int i=0;i<numTests && i == numPassed;i++){
        
        m=new Maze(mazeFiles[i]);
        start.set(testStart[i][0],testStart[i][1]);
        end.set(testEnd[i][0],testEnd[i][1]);
        pathLength=findPath (*m, start, end, path);
        original=new Maze(mazeFiles[i]);
        cout << "checking path for Test #" << i+1 << endl;
        
        if(testPath(original, m, start, end, path, pathLength)){
            cout << "Test # " << i+1 << " passed" << endl;
            numPassed++;
        }
        else{
            cout << "Test # " << i+1 << " failed" << endl;
        }
        if(pathLength > 0){
            printPath(json[i],path,pathLength);
        }
        delete original;
        delete m;
#if VERBOSE == 1
        cout << "your maze" << endl;
        m->print();
#endif
        
    }
    cout << numPassed << "/" << numTests << " passed" << endl;
    if(numPassed <  numTests){
        cout << "It looks like you still have some work to do" << endl;
    }
    else{
        cout << "This question is now completed" << endl;
    }
}

void printPath(const char* fname, Coord path[],int n){
    ofstream fs(fname);
    fs << "[";
    for(int i=0;i<n-1;i++){
        fs << path[i].x << ", " << path[i].y <<", " ;
    }
    fs << path[n-1].x << ", " << path[n-1].y <<"]" << endl;
    fs.close();
}

bool isBeside(const Coord& a, const Coord& b){
    bool rc=true;
    if(a.x == b.x){
        if(abs(a.y-b.y) != 1){
            rc=false;
        }
    }
    else if(a.y==b.y){
        if(abs(a.x-b.x) != 1){
            rc=false;
        }
    }
    else{
        rc=false;
    }
    return rc;
}
bool search(const Coord& c, const Coord path[], int n){
    bool found=false;
    for(int i=0;!found && i<n;i++){
        if(c==path[i]){
            found=true;
        }
    }
    return found;
}
bool testPath(const Maze* original,const Maze* marked, Coord start, Coord end, const Coord path[], int n){
    std::cout << "n: " << n << std::endl;
    for (auto i = 0u; i < n; ++i)
        std::cout << path[i] << endl;
    bool isGood=true;
    if(n > 0){
        if(path[0]!= start){
            std::cout << "Failed at first" << std::endl;
            isGood=false;
        }
        if(path[n-1]!= end){
            std::cout << "Failed at second" << std::endl;
            isGood=false;
        }
        for(int i=1;isGood && i<n;i++){
            //ensures each point on path is beside the next
            if(!isBeside(path[i],path[i-1])){
                std::cout << "failed at third" << std::endl;
                isGood=false;
            }
            //ensures that the point of path was originally empty
            //ie you can't run through walls
            if(!original->isEmpty(path[i])){
                std::cout << "Failed at fourth" << std::endl;
                isGood=false;
            }
            //ensure that the path is marked on the path
            if(!marked->isMarked(path[i])){
                std::cout << "Failed at fifth" << std::endl;
                isGood=false;
            }
        }
    }
    Coord curr;
    for(int i=0;isGood && i<original->height();i++){
        for(int j=0;isGood && j<original->width();j++){
            curr.set(j,i);
            //this sequence ensures that only points on the path are marked
            if(marked->isMarked(curr)){
                if(!search(curr,path,n)){
                    std::cout << "Failed at sixth" << std::endl;
                    isGood = false;
                }
            }
            else{
                if(search(curr,path,n)){
                    isGood = false;
                }
            }
        }
    }
    return isGood;
}
