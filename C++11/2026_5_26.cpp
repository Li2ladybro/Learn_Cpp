#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;


int n = 1000;

mutex mux1, mux2;
condition_variable cv1,cv2 ;

int main()
{

    thread t1([&]() {
        for (int i = 0;i < n;i += 2)
        {
            cout << this_thread::get_id() << ":" << i << endl;
            cv2.notify_one();
            unique_lock<mutex> lock(mux1);
            cv1.wait(lock);
        }});

        thread t2([&]() {
            for (int i = 1;i < n;i += 2)
            {
                unique_lock<mutex> lock(mux2);

                cv2.wait(lock);
                cout << this_thread::get_id() << ":" << i << endl;
                cv1.notify_one();
            }});

    t1.join();
    t2.join();

    return 0;
}