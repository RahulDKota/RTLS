#include "engine.h"
#include <random>


typedef struct _CUBOID{
    
    ULONGLONG height;
    ULONGLONG length;
    ULONGLONG breadth;

}CUBOID,*PCUBOID;

CUBOID g_Cuboid = {100*CMS_IN_M,100*CMS_IN_M,100*CMS_IN_M};
PATH g_TestPath;
mt19937* g_GeneratorRange;

void
prepareRandomInt(){
    srand( time(nullptr) ) ;
    uint32_t r[ mt19937::state_size ] ;
    for( uint32_t& n : r ) n = rand() ;
    seed_seq sseq( begin(r), end(r) ) ;
    g_GeneratorRange = new mt19937(sseq) ;
}

int randomInt( mt19937* &rng, int low, int high )
{ return uniform_int_distribution<int>( low, high )(*rng) ; }


PCUBOID
pickRandomPoint(){
PCUBOID pCuboid = (PCUBOID)malloc(sizeof(CUBOID));
    if(pCuboid){
        pCuboid->height = FLOOR_TO_TENS( randomInt(g_GeneratorRange,0,RAND_MAX) % g_Cuboid.height);
        pCuboid->length = FLOOR_TO_TENS( randomInt(g_GeneratorRange,0,RAND_MAX) % g_Cuboid.length);
        pCuboid->breadth = FLOOR_TO_TENS( randomInt(g_GeneratorRange,0,RAND_MAX) % g_Cuboid.breadth);
    }
return pCuboid; 
}


int main(int argc, char** argv){
prepareRandomInt();
PCUBOID pCuboid = pickRandomPoint();
PCUBOID pCuboid2 = pickRandomPoint();

//zero height for now - treating it as a rectangle
LOCATION *pLocation1 = new LOCATION(pCuboid->length,pCuboid->breadth,pCuboid->height,0);
LOCATION *pLocation2 = new LOCATION(pCuboid2->length,pCuboid2->breadth,pCuboid2->height,0);


    g_TestPath = pLocation1->createPath(pLocation2);

     while(!g_TestPath.empty()){
        cout << g_TestPath.back() << endl;
        g_TestPath.pop_back();
    }

return 0;
}