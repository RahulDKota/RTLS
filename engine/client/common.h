#include <stdlib.h>
#include<iostream>
using namespace std;


#define FLOOR_TO_TENS(n) \
 ( ( n / 10 ) * 10 )

#define CEIL_TO_TENS(n) \
( FLOOR_TO_TENS( (n+10) ) )

#define CMS_IN_M 100

typedef unsigned long ULONG;
typedef unsigned long* PULONG;
typedef unsigned long long ULONGLONG;
typedef unsigned long long* PULONGLONG;


#define CONTAINING_RECORD(p,t,m) \
 (t*)( (char*)p - (char*)&(t*)0)->m )  



