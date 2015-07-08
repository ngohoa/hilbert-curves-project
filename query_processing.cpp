/*extern "C" {
	#include "Bplus_tree.h"
}*/
#include <iostream>
#include <math.h> 
#include <string>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <map>
#include <time.h>
#include <map>
#include <stdio.h>
#include <cassert>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define SIZE 104770
#define TESTFILE 2000
#define RANGE 40
#define ORDER 1024
using namespace std;
using namespace __gnu_pbds;

/*clock_t clock_start, clock_end;
time_t time_start, time_end;
double dist_time_cpu, dist_time;
double total_time_cpu = 0.0;
double total_time = 0.0;*/

typedef
tree<
  int,
  null_mapped_type,
  less_equal<int>,
  rb_tree_tag,
  // This policy updates nodes' metadata for order statistics.
  tree_order_statistics_node_update>
set_t;

class Grid {
public:
    int x;
    int y;
};

struct Area {
    int **size;
    std::multimap<int,Grid> index_tree;
    set_t rank_tree;
    string test;
    int order;
};

void rot(int n, int &x, int &y, int rx, int ry) {
    if (ry == 0) {
        if (rx == 1) {
            x = n-1 - x;
            y = n-1 - y;
        }
 
        int t  = x;
        x = y;
        y = t;
    }
}

int xy2d (int n, int x, int y) {
    int rx, ry, s, d=0;
    for (s=n/2; s>0; s/=2) {
        rx = (x & s) > 0;
        ry = (y & s) > 0;
        d += s * s * ((3 * rx) ^ ry);
        rot(s, x, y, rx, ry);
    }
    return d;
}

/*void timerstart(){
    clock_t clock_start = clock();
    time_t time_start;
    time (&time_start);
}

void timerend(double &total_time_cpu){
    time (&time_end);
    clock_t clock_end = clock ();
    double dist_time_cpu = (double) (clock_end - clock_start) / 
    (double) CLOCKS_PER_SEC;
    double dist_time = difftime(time_end, time_start);
    total_time_cpu = total_time_cpu + dist_time_cpu;
    //total_time_cpu = dist_time_cpu;
    //printf("%f sec cpu,   %f sec real\n", 
       //total_time_cpu, total_time);
    total_time = total_time + dist_time;
}*/

string* extractIndexString(string s, int number) {
    string* container = new string[number];
    string temp = "";
    int space = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == ' ') {
            container[space++] = temp;
            temp = "";
        }
        else
            temp += s[i];
    }
    container[space] = temp;    
    return container;
}

int PrintIndicesForPoint(double points[][2], double x, double y, int length) {
    if (points == NULL)
        return -1;

    int low = 0, high = length - 1;
    // get the start index of x coor
    int startIndex = -1;
    while (low <= high) {
        int mid = (high - low) / 2 + low;
        if (points[mid][0] > x) {
            high = mid - 1;
        } else if (points[mid][0] == x) {
            startIndex = mid;
            high = mid - 1;
        } else
            low = mid + 1;
    }

    // get the end index of x coor
    int endIndex = -1;
    low = 0;
    high = length - 1;
    while (low <= high) {
        int mid = (high - low) / 2 + low;
        if (points[mid][0] > x) {
            high = mid - 1;
        } else if (points[mid][0] == x) {
            endIndex = mid;
            low = mid + 1;
        } else
            low = mid + 1;
    }

    if (startIndex != -1 && endIndex != -1){
        for(int i=0; i+startIndex<=endIndex;i++){
            if (points[i+startIndex][1] == y)
                return i+startIndex;
        }
    }
    else {
    	cout << "Not found";
    }
}

// batch query with B+ tree

// int * point_query(multimap<int,Grid> root, int interval, set_t points, double xcoor, double ycoor) {
//     double min_x = -124.48111, min_y = 32.53722;
//     double max_x = -114.13694, max_y = 42.16;
//     double unit_x = (max_x-min_x)/ORDER;
//     double unit_y = (max_y-min_y)/ORDER;

//     int *areas = (int *) malloc(TESTFILE * sizeof(int));
//     ifstream test(file.c_str());
//     string sLine = "";
//     int count = 0;

//     int x = floor((strtod(xcoor.c_str(), NULL)- min_x)/unit_x);
//     int y = floor((strtod(ycoor.c_str(), NULL)- min_y)/unit_y);
//     int xt1=x, yt1=y;
//     int xt2=ORDER-1-x, yt2=ORDER-1-y;
//     int xt3=ORDER-1-y; yt3=x;
//     int xt4=y; yt4=ORDER-1-x;
//     if (x < ORDER - 1 && y < ORDER - 1) {xt5=x+1; yt=y+1;}
//     if (curveid==6) {
//         if (x > 0 && y < ORDER - 1) {xt=x-1; yt=y+1;}
//     }
//     if (curveid==7) {
//         if (x < ORDER - 1 && y > 0) {xt=x+1; yt=y-1;}
//     }
//     if (curveid==8) {
//         if (x > 0 && y > 0) {xt=x-1; yt=y-1;}
//     }
//     /*cout << x << " " << y << endl;
//     cout << xt << " " << yt << endl;*/
//     int hind = xy2d(1024, xt, yt);
//     //cout << hind << endl;

//     /*printf ("%.12f %.12f ", strtod(lineIndex[0].c_str(), NULL), strtod(lineIndex[1].c_str(), NULL));
//     std::cout << x << " " << y << " " << hind << endl;*/

//     int rank = points.order_of_key(hind) + 1;
//     //std::cout << rank << endl;
      
//     int start = rank - (rank-1)%RANGE;
//     // HIndex of start position of bucket
//     int hindstart = *points.find_by_order(start);
//     // The first position match this index in case of duplication
//     int starthind = points.order_of_key(hindstart)+1;
//     //std::cout << start << " " << starthind << endl;
//     // The distance
//     int distance = start - starthind;
//     //std::cout << distance << endl;
      
//     itlow = root.lower_bound (hindstart);
//     for (int i = 0; i < distance; i++) {
//         itlow++;
//     }

//     /*std::cout << (*itlow).first << " => " << (*itlow).second.x << 
//         " " << (*itlow).second.y << '\n';*/
//     int minx =1030, miny = 1030;
//     int maxx = -1, maxy = -1;
//     std::multimap<int,Grid>::const_iterator itend = root.end();
//     for (int j = 0; j < RANGE && itlow!=itend; j++) {
//         /*std::cout << (*itlow).first << " => " << (*itlow).second.x << 
//         " " << (*itlow).second.y << '\n';*/
//         int first = (*itlow).second.x;
//         int second = (*itlow).second.y;
//         if (first <= minx)
//             minx = first;
//         if (first >= maxx)
//             maxx = first;
//         if (second <= miny)
//             miny = second;
//         if (second >= maxy)
//             maxy = second;
//         itlow++;
//     }
//     areas[count] = (maxy-miny+1)*(maxx-minx+1);
//     count++;

//     test.close();
//     return areas;
// }

//int * test_execution(string test, string file, int curveid) {
inline void *test_execution(void *ptr){
    register struct Area * Data = (struct Area*) ptr;
    int **areaSize = Data->size;
    std::multimap<int,Grid> root = Data->index_tree;
    set_t points = Data->rank_tree;
    string file = Data->test;
    int curveid = Data->order;
    int interval = RANGE;
    




///////////////////////////////////////////////////////
    double min_x = -124.48111, min_y = 32.53722;
    double max_x = -114.13694, max_y = 42.16;
    double unit_x = (max_x-min_x)/ORDER;
    double unit_y = (max_y-min_y)/ORDER;

    int *areas = (int *) malloc(TESTFILE * sizeof(int));
    ifstream test(file.c_str());
    string sLine = "";
    int count = 0;
    double total_time = 0.0;
    double elapsed = 0.0;
    while (getline(test, sLine)) {
        string *lineIndex;
        lineIndex = extractIndexString(sLine, 3);
        std::multimap<int,Grid>::const_iterator itlow;
          
        if (count < TESTFILE) {
            clock_t clock_start = clock();
            struct timespec time_start, time_finish;
            clock_gettime(CLOCK_MONOTONIC, &time_start);


            int x = floor((strtod(lineIndex[0].c_str(), NULL)- min_x)/unit_x);
            int y = floor((strtod(lineIndex[1].c_str(), NULL)- min_y)/unit_y);
            int xt=x, yt=y;
            if (curveid == 2) {xt=ORDER-1-x; yt=ORDER-1-y;}
            if (curveid == 3) {xt=ORDER-1-y; yt=x;}
            if (curveid == 4) {xt=y; yt=ORDER-1-x;}
            if (curveid == 5) {
                if (x < ORDER - 1 && y < ORDER - 1) {xt=x+1; yt=y+1;}
            }
            if (curveid==6) {
                if (x > 0 && y < ORDER - 1) {xt=x-1; yt=y+1;}
            }
            if (curveid==7){
                if (x < ORDER - 1 && y > 0) {xt=x+1; yt=y-1;}
            }
            if (curveid==8){
                if (x > 0 && y > 0) {xt=x-1; yt=y-1;}
            }
            /*cout << x << " " << y << endl;
            cout << xt << " " << yt << endl;*/
            int hind = xy2d(1024, xt, yt);
            //cout << hind << endl;

            /*printf ("%.12f %.12f ", strtod(lineIndex[0].c_str(), NULL), strtod(lineIndex[1].c_str(), NULL));
            std::cout << x << " " << y << " " << hind << endl;*/

            int rank = points.order_of_key(hind) + 1;
            //std::cout << rank << endl;
              
            int start = rank - (rank-1)%RANGE;
            // HIndex of start position of bucket
            int hindstart = *points.find_by_order(start);
            // The first position match this index in case of duplication
            int starthind = points.order_of_key(hindstart)+1;
            //std::cout << start << " " << starthind << endl;
            // The distance
            int distance = start - starthind;
            //std::cout << distance << endl;
              
            itlow = root.lower_bound (hindstart);
            for (int i = 0; i < distance; i++) {
                itlow++;
            }

            /*std::cout << (*itlow).first << " => " << (*itlow).second.x << 
                " " << (*itlow).second.y << '\n';*/
            int minx =1030, miny = 1030;
            int maxx = -1, maxy = -1;
            std::multimap<int,Grid>::const_iterator itend = root.end();
            for (int j = 0; j < RANGE && itlow!=itend; j++) {
                /*std::cout << (*itlow).first << " => " << (*itlow).second.x << 
                " " << (*itlow).second.y << '\n';*/
                int first = (*itlow).second.x;
                int second = (*itlow).second.y;
                if (first <= minx)
                    minx = first;
                if (first >= maxx)
                    maxx = first;
                if (second <= miny)
                    miny = second;
                if (second >= maxy)
                    maxy = second;
                itlow++;
            }
            areas[count] = (maxy-miny+1)*(maxx-minx+1);
            count++;


            clock_t clock_end = clock();
            clock_gettime(CLOCK_MONOTONIC, &time_finish);
            total_time += (double) (clock_end - clock_start) / 
                          (double) CLOCKS_PER_SEC;
            elapsed += (time_finish.tv_sec - time_start.tv_sec);
            elapsed += (time_finish.tv_nsec - time_start.tv_nsec) / 1000000000.0;
        }
    }
    printf("Thread time: %f sec cpu, %f sec wall\n", total_time, elapsed);
    //std::cout << sLine << endl;
    test.close();
    *areaSize = areas;
////////////////////////////////////////////







    //*areaSize = batch_query(index_tree, test, RANGE, rank_tree, curveid);
    pthread_exit(NULL);
    //return batch_query(root, test, RANGE, s, curveid, areaSize);
}

void make_trees(std::multimap<int,Grid> &root, set_t &s, string file) {
    string sLine = "";
    ifstream data(file.c_str());
    int count = 0;
    while (getline(data, sLine)) {
        if (count < SIZE) {
            string *lineIndex;
            lineIndex = extractIndexString(sLine, 5);
            int hind = (int)atof(lineIndex[4].c_str());
            s.insert(hind);

            Grid grid;
            grid.x = (int)atof(lineIndex[2].c_str());
            grid.y = (int)atof(lineIndex[3].c_str());
            root.insert(std::make_pair(hind,grid));
            count++;
        }
    }
    data.close();
}

int main(int argc, char ** argv) {
    int  *areas1, *areas2, *areas3, *areas4, *areas5, *areas6, *areas7, *areas8;
    ofstream outfile;
    outfile.open("test_result.txt");
    string testfile = "Test/test10.txt";

    //pthread_t * threads = new pthread_t [8];
    pthread_t  threads0;
    pthread_t  threads1;
    pthread_t  threads2;
    pthread_t  threads3;
    pthread_t  threads4;
    pthread_t  threads5;
    pthread_t  threads6;
    pthread_t  threads7;

    pthread_attr_t attr;
    struct Area threadData0, threadData1, threadData2, threadData3, threadData4, threadData5,
    threadData6, threadData7;

    //for (int i=0; i<8; i++) {
        threadData0.test = testfile;
        threadData0.order = 1;
        threadData1.test = testfile;
        threadData1.order = 2;
        threadData2.test = testfile;
        threadData2.order = 3;
        threadData3.test = testfile;
        threadData3.order = 4;
        threadData4.test = testfile;
        threadData4.order = 5;
        threadData5.test = testfile;
        threadData5.order = 6;
        threadData6.test = testfile;
        threadData6.order = 7;
        threadData7.test = testfile;
        threadData7.order = 8;
    //}

    std::multimap<int,Grid> t1, t2, t3, t4, t5, t6, t7, t8;
    set_t s1, s2, s3, s4, s5, s6, s7, s8;
    make_trees(t1, s1, "HIndexO/cali-HIndex-sorted.txt");
    make_trees(t2, s2, "HIndex180/cali-HIndex-sorted.txt");
    make_trees(t3, s3, "HIndexN90/cali-HIndex-sorted.txt");
    make_trees(t4, s4, "HIndexP90/cali-HIndex-sorted.txt");
    make_trees(t5, s5, "HIndexBL/cali-HIndex-sorted.txt");
    make_trees(t6, s6, "HIndexBR/cali-HIndex-sorted.txt");
    make_trees(t7, s7, "HIndexTL/cali-HIndex-sorted.txt");
    make_trees(t8, s8, "HIndexTR/cali-HIndex-sorted.txt");

    threadData0.index_tree = t1;
    threadData1.index_tree = t2;
    threadData2.index_tree = t3;
    threadData3.index_tree = t4;
    threadData4.index_tree = t5;
    threadData5.index_tree = t6;
    threadData6.index_tree = t7;
    threadData7.index_tree = t8;

    threadData0.rank_tree = s1;
    threadData1.rank_tree = s2;
    threadData2.rank_tree = s3;
    threadData3.rank_tree = s4;
    threadData4.rank_tree = s5;
    threadData5.rank_tree = s6;
    threadData6.rank_tree = s7;
    threadData7.rank_tree = s8;

    threadData0.size = &areas1;
    threadData1.size = &areas2;
    threadData2.size = &areas3;
    threadData3.size = &areas4;
    threadData4.size = &areas5;
    threadData5.size = &areas6;
    threadData6.size = &areas7;
    threadData7.size = &areas8;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);


    /*struct timespec time_start, time_finish;
            clock_gettime(CLOCK_MONOTONIC, &time_start);
    clock_t start = clock();*/

    for (; ;) {
        cout << "Commit the flag: ";
        int flag;
        cin >> flag;
        if (flag == 1) { 



            double total_time1 = 0;
            double elapsed1 = 0;
            clock_t clock_start1 = clock();
            struct timespec time_start1, time_finish1;
            clock_gettime(CLOCK_MONOTONIC, &time_start1);



            //for(int i = 0; i < 8; i++)
            pthread_create(&threads0, NULL, test_execution, (void*) &threadData0);
            pthread_create(&threads1, NULL, test_execution, (void*) &threadData1);
            pthread_create(&threads2, NULL, test_execution, (void*) &threadData2);
            pthread_create(&threads3, NULL, test_execution, (void*) &threadData3);
            pthread_create(&threads4, NULL, test_execution, (void*) &threadData4);
            pthread_create(&threads5, NULL, test_execution, (void*) &threadData5);
            pthread_create(&threads6, NULL, test_execution, (void*) &threadData6);
            pthread_create(&threads7, NULL, test_execution, (void*) &threadData7);

            pthread_attr_destroy(&attr);
            //for(int i = 0; i < 8; i++)
                pthread_join(threads0,NULL);
                pthread_join(threads1,NULL);
                pthread_join(threads2,NULL);
                pthread_join(threads3,NULL);
                pthread_join(threads4,NULL);
                pthread_join(threads5,NULL);
                pthread_join(threads6,NULL);
                pthread_join(threads7,NULL);



            clock_t clock_end1 = clock();
            clock_gettime(CLOCK_MONOTONIC, &time_finish1);
            total_time1 += (double) (clock_end1 - clock_start1) / 
                          (double) CLOCKS_PER_SEC;
            elapsed1 += (time_finish1.tv_sec - time_start1.tv_sec);
            elapsed1 += (time_finish1.tv_nsec - time_start1.tv_nsec) / 1000000000.0;
            printf("Total time: %f sec cpu, %f sec wall\n", total_time1, elapsed1);



            int sum = 0;
            int originR = 0;
            for (int i = 0; i < TESTFILE; i++) {
                int min_area = areas1[i];
                if (areas2[i] < min_area) min_area = areas2[i];
                if (areas3[i] < min_area) min_area = areas3[i];
                if (areas4[i] < min_area) min_area = areas4[i];
                if (areas5[i] < min_area) min_area = areas5[i];
                if (areas6[i] < min_area) min_area = areas6[i];
                if (areas7[i] < min_area) min_area = areas7[i];
                if (areas8[i] < min_area) min_area = areas8[i];
                sum = sum + min_area;
                originR = originR + areas1[i];
            }
            cout << sum << " " << originR << endl;
        }
        else break;
    }

    for (int i = 0; i < TESTFILE; i++) {
        outfile << areas1[i] << " " << areas2[i] << " " << areas3[i] << " " << areas4[i] << " ";
        outfile << areas5[i] << " " << areas6[i] << " " << areas7[i] << " " << areas8[i] << endl;     
    }
    
    outfile.close();
    return EXIT_SUCCESS;
}