#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <omp.h>
#define NO_OF_CHARS 256
#define ASIZE 500
#define XSIZE 500

using namespace std;

class SR
{public:

    vector<int> index;

    double timer_start = 0;
    double timer_end = 0;
    double final_time = 0;

    inline void create_res(int indx)
    {
        ofstream file("out.txt");
        char vh[64] = { 0 };

        sprintf(vh, "%d" ,indx);

        for (int i = 0; i < strlen(vh) + 1; i++)
        {
            file.put(vh[i]);
        }

    }

    inline void timer_m(int i)
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

    int find_word(const std::string filename, const std::string word)
    {
        ifstream file(filename); 
        string s, find;
        char c;

        while (!file.eof()) {
            file.get(c);
            s.push_back(c);
        }

        file.close(); 

        find = word;

        int pos = s.find(find);
    }

    int file_size(const std::string filename)
    {
        std::ifstream file(filename);
        
        file.seekg(0, ios::end);
        int size = (int)file.tellg();

        file.close();

        return size;
    }

    void data_copi(ifstream& file, int data_size, char* buffer)
    {
       
        file.read(buffer, data_size);
    }

    void preBmBc(char* x, int m, int bmBc[]) {
        int i;

        for (i = 0; i < ASIZE; ++i)
            bmBc[i] = m;
        for (i = 0; i < m - 1; ++i)
            bmBc[x[i]] = m - i - 1;
    }

    void RAITA(char* x, int m, char* y, int n) 
    {
        int j, bmBc[ASIZE];
        char c, firstCh, * secondCh, middleCh, lastCh;

        preBmBc(x, m, bmBc);
        firstCh = x[0];
        secondCh = x + 1;
        middleCh = x[m / 2];
        lastCh = x[m - 1];

        j = 0;
        while (j <= n - m) {
            c = y[j + m - 1];
            if (lastCh == c && middleCh == y[j + m / 2] &&
                firstCh == y[j] &&
                memcmp(secondCh, y + j + 1, m - 2) == 0)
                OUTPUT(j);
            j += bmBc[c];
        }
    }
    void preRc(char* x, int m, int h[],
        int rcBc[ASIZE][XSIZE], int rcGs[]) {
        int a, i, j, k, q, r, s,
            hmin[XSIZE], kmin[XSIZE], link[XSIZE],
            locc[ASIZE], rmin[XSIZE];

        for (a = 0; a < ASIZE; ++a)
            locc[a] = -1;
        link[0] = -1;
        for (i = 0; i < m - 1; ++i) {
            link[i + 1] = locc[x[i]];
            locc[x[i]] = i;
        }

        for (a = 0; a < ASIZE; ++a)
            for (s = 1; s <= m; ++s) {
                i = locc[a];
                j = link[m - s];
                while (i - j != s && j >= 0)
                    if (i - j > s)
                        i = link[i + 1];
                    else
                        j = link[j + 1];
                while (i - j > s)
                    i = link[i + 1];
                rcBc[a][s] = m - i - 1;
            }

        k = 1;
        i = m - 1;
        while (k <= m) {
            while (i - k >= 0 && x[i - k] == x[i])
                --i;
            hmin[k] = i;
            q = k + 1;
            while (hmin[q - k] - (q - k) > i) {
                hmin[q] = hmin[q - k];
                ++q;
            }
            i += (q - k);
            k = q;
            if (i == m)
                i = m - 1;
        }

        memset(kmin, 0, m * sizeof(int));
        for (k = m; k > 0; --k)
            kmin[hmin[k]] = k;

        for (i = m - 1; i >= 0; --i) {
            if (hmin[i + 1] == i)
                r = i + 1;
            rmin[i] = r;
        }

        i = 1;
        for (k = 1; k <= m; ++k)
            if (hmin[k] != m - 1 && kmin[hmin[k]] == k) {
                h[i] = hmin[k];
                rcGs[i++] = k;
            }
        i = m - 1;
        for (j = m - 2; j >= 0; --j)
            if (kmin[j] == 0) {
                h[i] = j;
                rcGs[i--] = rmin[j];
            }
        rcGs[m] = rmin[0];
    }


    void Reverse_Colussi(char* x, int m, char* y, int n) 
    {
        int i, j, s, rcBc[ASIZE][XSIZE], rcGs[XSIZE], h[XSIZE];

        preRc(x, m, h, rcBc, rcGs);

        j = 0;
        s = m;
        while (j <= n - m) {
            while (j <= n - m && x[m - 1] != y[j + m - 1]) {
                s = rcBc[y[j + m - 1]][s];
                j += s;
            }
            for (i = 1; i < m && x[h[i]] == y[j + h[i]]; ++i);
            if (i >= m)
                OUTPUT(j);
            s = rcGs[i];
            j += s;
        }
    }
    void OUTPUT(int j)
    {
        index.push_back(j);
    }
    int getNextState(char* pat, int M, int state, int x)
    {
 
        if (state < M&& x == pat[state])
            return state + 1;

        int ns, i;

        for (ns = state; ns > 0; ns--)
        {
            if (pat[ns - 1] == x)
            {
                for (i = 0; i < ns - 1; i++)
                    if (pat[i] != pat[state - ns + 1 + i])
                        break;
                if (i == ns - 1)
                    return ns;
            }
        }

        return 0;
    }

    void computeTF(char* pat, int M, int **TF)
    {
        int state, x;
        for (state = 0; state <= M; ++state)
            for (x = 0; x < NO_OF_CHARS; ++x)
                TF[state][x] = getNextState(pat, M, state, x);
    }

    void Deterministic_Finite_Automaton(char* pat, char* txt)
    {
        int M = strlen(pat);
        int N = strlen(txt);

        int** TF = new int* [M + 1];
        for (size_t i = 0; i < M + 1; i++)
        {
            TF[i] = new int[NO_OF_CHARS];
        }

        computeTF(pat, M, TF);
 
        int i, state = 0;
        for (i = 0; i < N; i++)
        {
            state = TF[state][txt[i]];
            if (state == M)
                cout<<endl<<"Pattern found at index "<<i - M + 1<<endl;
        }
        delete[]TF;
    }

};


int main()
{
    string filename_in = "1.txt";
    string filename_sl = "slovo.txt";

    ifstream file_in(filename_in);
    ifstream file_sl(filename_sl);

    SR a;
    int in_file_size = a.file_size(filename_in);
    int ls_file_size = a.file_size(filename_sl);

    char* buffer = new char[in_file_size + 1];
    buffer[in_file_size] = 0;

    char* buffer2 = new char[ls_file_size + 1];
    buffer2[ls_file_size] = 0;

    a.data_copi(file_in,in_file_size,buffer);
    a.data_copi(file_sl, ls_file_size, buffer2);
    a.Deterministic_Finite_Automaton(buffer2, buffer);

    for (size_t i = 0; i < a.index.size(); i++)
    {
        cout<<a.index[i];
    }

    delete[]buffer;
    delete[]buffer2;
    return 0;
}
