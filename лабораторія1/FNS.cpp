/*
5  Library sort (gapped insertion sort)
9  STL::stable-sort
14 LSD radix sort
24 Heap (pyramid) sort
25 Introsort
30 STL::sort
*/
#if !defined(FNS)
#define FNS

#include "stdc++.h"
#include <omp.h>
using namespace std;

namespace SORT_m 
{
    class data_record
    {
    public:
        string algoritm;//алгоритм 
        double time;//за скільки часу засортував
        int l_p;//довжина послідовності
        string rp;//розподіл
        data_record(string al, double t, int l, bool pr, bool nr)
        {
            this->algoritm = al;
            this->time = t;
            this->l_p = l;
            if (pr == 1)// розподіл рівномірний
            {
                this->rp = "rivnomirnuy";
            }
            else if (nr == 1)// розподіл нормальний
            {
                this->rp = "normalnuy";
            }
        }

    };
    class GEN_SORT
    {
    public:
        double timer_start = 0;
        double timer_end = 0;
        double final_time = 0;

        inline void timer_m(int i);

        template <typename t_sort> inline void gen_number_p(vector<t_sort>& vec, int n);

        template <typename t_sort> inline void gen_number_n(vector<t_sort>& vec, int n);

        template <typename t_sort> inline void library_sort_v(vector<t_sort>& vec);

        template <typename t_sort> inline void stable_sort_v(vector<t_sort>& vec);

        template <typename t_sort> inline void lsd_sort_v(vector<t_sort>& vec);

        template <typename t_sort> inline void heap_sort_v(vector<t_sort>& vec);

        template <typename t_sort> inline void introsort_sort_v(vector<t_sort>& vec);

        template <typename t_sort> inline void sort_sort_v(vector<t_sort>& vec);

        template <typename t_sort> inline void co(vector<t_sort>& vec)
        {
            for (size_t i = 0; i < vec.size(); i++)
            {
                cout << vec[i] << ' ';
            }

        }

        template <typename t_sort> inline int getMax(vector<t_sort>& vec);

        template <typename t_sort> inline void countSort(vector<t_sort>& vec, int exp);

        template <typename t_sort> inline void radixsort(vector<t_sort>& vec);

    };

    inline void GEN_SORT::timer_m(int i)
    {
        if (i == 0)
        {
            timer_start = 0;
            timer_start = omp_get_wtime();

        }
        else if (i == 1)
        {
            timer_end = 0;
            timer_end = omp_get_wtime();
            final_time = timer_end - timer_start;
        }
    }

    template <typename t_sort>
    inline void GEN_SORT::gen_number_p(vector<t_sort> & vec, int n)
    {
        srand(unsigned(time(0)));
        for (t_sort i = 0; i < n; i++)
        {
            vec.push_back(i);
        }
        random_shuffle(vec.begin(), vec.end());
    }
    template <typename t_sort>
    inline void GEN_SORT::gen_number_n(vector<t_sort>& vec, int n)
    {
        srand(unsigned(time(0)));
        for (t_sort i = 0; i < n; i++)
        {
            vec.push_back(i);
        }
        int ch = vec.end() / 4;
        random_shuffle(vec.begin(), ch);
        random_shuffle(ch * 3, ch * 4);
    }
    template <typename t_sort>
    inline void GEN_SORT::library_sort_v(vector<t_sort> & vec)
    {
        timer_m(0);

        int n = vec.size();
        int i, key, j;

        for (i = 1; i < n; i++)
        {
            key = vec[i];
            j = i - 1;

            while (j >= 0 && vec[j] > key)
            {
                vec[j + 1] = vec[j];
                j = j - 1;
            }
            vec[j + 1] = key;
        }

        timer_m(1);
    }

    template <typename t_sort>
    inline void GEN_SORT::stable_sort_v(vector<t_sort> & vec)
    {
        timer_m(0);
        stable_sort(vec.begin(), vec.end());
        timer_m(1);
    }
    template <typename t_sort>
    inline void GEN_SORT::lsd_sort_v(vector<t_sort> & vec)
    {
        timer_m(0);
        radixsort(vec);
        timer_m(1);
    }
    template <typename t_sort>
    inline void GEN_SORT::heap_sort_v(vector<t_sort> & vec)
    {
        timer_m(0);
        make_heap(vec.begin(), vec.end());
        sort_heap(vec.begin(), vec.end());
        timer_m(1);
    }
    template <typename t_sort>
    inline void GEN_SORT::introsort_sort_v(vector<t_sort> &vec)
    {
        timer_m(0);
        sort(vec.begin(), vec.end());
        timer_m(1);
    }

    template <typename t_sort>
    inline void GEN_SORT::sort_sort_v(vector<t_sort> & vec)
    {
        timer_m(0);
        sort(vec.begin(), vec.end());
        timer_m(1);
    }
    template <typename t_sort>
    inline void GEN_SORT::countSort(vector<t_sort> & vec, int exp)
    {
        int n = vec.size();
        vector<int>output(n, 0);
        int i, count[10] = { 0 };

        for (i = 0; i < n; i++)
        {
            count[(vec[i] / exp) % 10]++;
        }

        for (i = 1; i < 10; i++)
        {
            count[i] += count[i - 1];
        }

        for (i = n - 1; i >= 0; i--)
        {
            output[count[(vec[i] / exp) % 10] - 1] = vec[i];
            count[(vec[i] / exp) % 10]--;
        }

        for (i = 0; i < n; i++)
        {
            vec[i] = output[i];
        }
    }
    template <typename t_sort>
    inline void GEN_SORT::radixsort(vector<t_sort> & vec)
    {
        int m = getMax(vec);
        int n = vec.size();
        for (int exp = 1; m / exp > 0; exp *= 10)
        {
            countSort(vec, exp);
        }
    }
    template <typename t_sort>
    inline int GEN_SORT::getMax(vector<t_sort> & vec)
    {
        int mx = vec[0];
        for (int i = 1; i < vec.size(); i++)
        {
            if (vec[i] > mx)
            {
                mx = vec[i];
            }
        }
        return mx;
    }
}
#endif