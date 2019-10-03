#include <iostream>
#include <pthread.h>
#include "read_polylines.hpp"
#include "ramer_douglas.hpp"

#define NUM_THREADS 5

using namespace std;
vector< vector<Point> > AllPolylines = read_polylines("polylines.txt");
vector< vector<Point> > SimplePolylines;
pthread_mutex_t mutex;
double epsilon;

void *safeRamerDouglas(void *threadid) {
   long tid;
   tid = (long)threadid;
   cout << "Hello World! Thread ID, " << tid << endl;

   while(AllPolylines.size()>0)
   {
       pthread_mutex_lock(&mutex);
       vector<Point> pline = AllPolylines.back();
       AllPolylines.pop_back();
       pthread_mutex_unlock(&mutex);
       vector<Point> sPLine;
       RamerDouglasPeucker(pline, epsilon,sPLine);
       pthread_mutex_lock(&mutex);
       SimplePolylines.push_back(sPLine);
       pthread_mutex_unlock(&mutex);
   }
   pthread_exit(NULL);
}

int main(int argc, char** argv) {

    pthread_t threads[NUM_THREADS];
    int rc;
    int i;
    epsilon = atof(argv[1]);
    pthread_mutex_init(&mutex, NULL);    
    for( i = 0; i < NUM_THREADS; i++ ) {
        cout << "main() : creating thread, " << i << endl;
        rc = pthread_create(&threads[i], NULL, safeRamerDouglas, (void *)i);
          
        if (rc) {
            cout << "Error:unable to create thread," << rc << endl;
            return -1;
        }
    }
    for( i = 0; i < NUM_THREADS; i++ ) {
        cout << "main() : joining thread, " << i << endl;
        rc = pthread_join(threads[i], NULL);
          
        if (rc) {
            cout << "Error:unable to join thread," << rc << endl;
            return -1;
        }
    }

    pthread_exit(NULL);

    print_polylines(SimplePolylines);

}
