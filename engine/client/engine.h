#include"common.h"
#include<map>
#include<tuple>
#include<vector>

#define _DEBUG_ON



//left upper-most corner treated as origin of plane - (0,0)
typedef class LOCATION* PLOCATION;

//ordered pairs of location - origin and destination
typedef tuple<ULONGLONG,ULONGLONG,ULONGLONG,ULONGLONG,ULONGLONG,ULONGLONG> ORDERED_POINTS_PAIR;

//path matrix
typedef vector< PLOCATION > PATH;
typedef vector< PATH > PATHS;

typedef map< ORDERED_POINTS_PAIR , PATHS > MAP_OF_PATHS;


class LOCATION{
private:
    ULONGLONG z:56;
    ULONGLONG floor:8;
    ULONGLONG y;
    ULONGLONG x;

public:
//parameter-less contstructor returns origin
    LOCATION(){
        z = 0;
        floor = 0;
        y = 0;
        z = 0;       
    }

    LOCATION(ULONGLONG length, ULONGLONG breadth, ULONGLONG altitude, ULONGLONG floor){
    //need to test for size of floor to avoid overflow
        z = altitude;
        floor = floor;
        y = length;
        x = breadth;
    }

    ULONGLONG getz(){ return this->z;}
    ULONGLONG getFloor(){ return this->floor;}
    ULONGLONG gety(){ return this->y;}
    ULONGLONG getx(){ return this->x;}



    //std::map::less
    const bool operator<(const LOCATION &loc){
    /*
        upper-left trinagles are smaller
        below-of || right-of will always be larger 
    */
        return  ( ( this->z < loc.z ) ||
                    ( this->y < loc.y ) || 
                        ( this->x < loc.x ) );
    }       
    

    const bool operator==(const LOCATION &loc) const{
            return ( ( this->z == loc.z ) &&
                        (this->y == loc.y) && 
                        (this->x == loc.x) );
        }   


#ifdef _DEBUG_ON
    friend ostream &operator<<(ostream &outstream, const LOCATION &location){
        outstream << "Altitude: " << location.z << endl 
        << "length: " << location.y << endl
        << "breadth: " << location.x <<endl;
    }

    friend ostream &operator<<(ostream &outstream, const PLOCATION pLocation){
        outstream << "Altitude: " << pLocation->z << endl 
        << "length: " << pLocation->y << endl
        << "breadth: " << pLocation->x <<endl;
    }
    
#endif


    ORDERED_POINTS_PAIR
    makeOrderedPair(LOCATION location1, LOCATION location2){
        return ( make_tuple(location1.getz(), location1.gety(), location1.getx(),
                            location2.getz(), location2.gety(), location2.getx()) );
    };

    //this will restrict all the paths to the rectangle where origin and destination are diagonally opposite
    //currently only positive move - i.e no moving backwards
    //no z 

    PLOCATION
    generateNextLocation(PLOCATION pDestination, bool moveInColum){
        ULONGLONG diff;

        diff = ( moveInColum ?  llabs(this->getx() - pDestination->getx()) :
                    llabs(this->gety() - pDestination->gety()) );

        return new LOCATION(moveInColum?this->gety(): CEIL_TO_TENS( (this->gety() + (rand() % diff) ) ),
                            moveInColum?CEIL_TO_TENS( (this->getx() + (rand() % diff)) ) : this->getx(),
                            0,0);                
    }

    PATH
    createPath(PLOCATION pDestination){
        PATH path;
        PLOCATION pTempLocation = this;
        bool bColumn = false;
        do{
            path.push_back(pTempLocation);
            pTempLocation = pTempLocation->generateNextLocation(pDestination,bColumn);
            bColumn = (bColumn == false);
        }while(!isInLineOfSight(pTempLocation,pDestination));
        path.push_back(pTempLocation);    
        path.push_back(pDestination);
    
        return path;
    }

    static bool
    isInLineOfSight(PLOCATION location1,PLOCATION location2){
        return (//either same column
                location1->gety() == location2->gety() ||
                //or same row
                location1->getx() == location2->getx() );
    }

};
