#include "stdc++.h"
#include <vector>
#include "FNS.cpp"

using namespace std;
using namespace SORT_m;

int main()
{
    setlocale(LC_ALL, "Russian");
    vector<int>a;
    int start = 0;

    GEN_SORT g;
    int size = 0;
    cout << "Get size ";
    cin >> size;
    cout << "Size = "<<size<<endl;
    g.gen_number_p(a, size);

    cout << "Library sort ? ";
    cin >> start;
    if (start > 0)
    {
        g.library_sort_v(a);
        cout <<"library sort time "<<g.final_time << " seconds " << endl;
        random_shuffle(a.begin(), a.end());
        start = 0;
    }

    cout << "Stable sort ? ";
    cin >> start;
    if (start > 0)
    {
        g.stable_sort_v(a);
        cout << "Stable sort time "<<g.final_time << " seconds " << endl;
        random_shuffle(a.begin(), a.end());
        start = 0;
    }

    cout << "Radix sort ? ";
    cin >> start;
    if (start > 0)
    {
        g.lsd_sort_v(a);
        cout << "Radix sort time "<< g.final_time << " seconds " << endl;
        random_shuffle(a.begin(), a.end());
        start = 0;
    }
    
    cout << "Heap sort ? ";
    cin >> start;
    if (start > 0)
    {
        g.heap_sort_v(a);
        cout << "Heap sort time " << g.final_time << " seconds " << endl;
        random_shuffle(a.begin(), a.end());
        start = 0;
    }

    cout << "Introsort sort ? ";
    cin >> start;
    if (start > 0)
    {
        g.introsort_sort_v(a);
        cout << "Introsort sort time " << g.final_time << " seconds " << endl;
        random_shuffle(a.begin(), a.end());
        start = 0;
    }

    cout << "Sort sort ? ";
    cin >> start;
    if (start > 0)
    {
        g.sort_sort_v(a);
        cout << "Sort sort time " << g.final_time << " seconds " << endl;
        random_shuffle(a.begin(), a.end());
        start = 0;
    }

    return 0;
}
