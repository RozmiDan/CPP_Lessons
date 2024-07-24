#include <iostream>
#include <vector>

using namespace std;

struct PeekingIterator;
struct MergeIterator;
struct Iterator;

struct Iterator
{
    Iterator(const vector<int>& thread) : thread_m(thread), size_m(thread.size()), ptr_m(0)
    {}

    Iterator() = delete;

    void cout_thread() {
        for (int i = 0; i < size_m; ++i)
            cout << thread_m[i] << " ";
    }

    bool hasNext() {
        return ptr_m >= thread_m.size() ? false : true;
    }

    int next() {
        if(!hasNext()){
            throw std::runtime_error("thread size was limited");
        }
        return thread_m[ptr_m++];
    }

    size_t ptr_m = 0;
    size_t size_m = 0;
    vector<int> thread_m;
};

struct PeekingIterator : public Iterator
{
    PeekingIterator(const vector<int>& thread) : Iterator(thread) {}

    PeekingIterator(Iterator& it) : Iterator(it){
        ptr_m = 0;
    }

    int peek(){
        return thread_m[ptr_m];
    }

    void monitor_thread() {
        for (auto& it : thread_m)
            cout << it << " ";
    }
};

struct MergeIterator
{
    MergeIterator(PeekingIterator* it_fst, PeekingIterator* it_scnd) : result({}) {
        result = MergeTwoIterators(it_fst, it_scnd);
    }

    MergeIterator(vector<PeekingIterator*>& arr_it) : result({}) {
        size_t strt = 0;
        size_t end = arr_it.size() - 1;
        result = MergeKIterators(arr_it, strt, end);
    }

    PeekingIterator MergeTwoIterators(PeekingIterator* fst_ptr, PeekingIterator* scnd_ptr) {

        vector<int> merge_res;

        while (fst_ptr->hasNext() || scnd_ptr->hasNext()) {

            if(fst_ptr->hasNext() && scnd_ptr->hasNext()) {
                if(fst_ptr->peek() > scnd_ptr->peek()) {
                    merge_res.push_back(scnd_ptr->next());
                }
                else {
                    merge_res.push_back(fst_ptr->next());
                }
            }
            else if (fst_ptr->hasNext()) {
                merge_res.push_back(fst_ptr->next());
            }
            else if (scnd_ptr->hasNext()) {
                merge_res.push_back(scnd_ptr->next());
            }
        }
        return PeekingIterator(merge_res);
    }

    PeekingIterator MergeKIterators(vector<PeekingIterator*>& arr, int rght_bound, int lft_bound) {


        if(rght_bound == lft_bound)
            return *arr[rght_bound];

        size_t mid = (rght_bound + lft_bound) / 2;

        PeekingIterator left_res = MergeKIterators(arr, rght_bound, mid);
        PeekingIterator rght_res = MergeKIterators(arr, mid+1, lft_bound);
        return MergeTwoIterators(&left_res, &rght_res);
    }
    PeekingIterator result;
};


int main()
{
    Iterator it({6,2,1,3,6,4,6,34,7,12,7,5});
    PeekingIterator pit({1,3,6,6,14,17,26,34,73});
    PeekingIterator pit2({1,3,6,44,345});
//    MergeIterator mit(&pit, &pit2);
//    mit.result.monitor_thread();

    PeekingIterator pit3({15,19,22,53});
    PeekingIterator pit4({4,8,85});
    PeekingIterator pit5({54,65,65,75,87,95,125});
    PeekingIterator pit6({2,2,2,2});
    vector<PeekingIterator*> vec{&pit,&pit2,&pit3,&pit4,&pit5,&pit6};
    MergeIterator mit2(vec);
    mit2.result.monitor_thread();



//    for (int i = 0; i < 3; ++i) {
//        cout << pit.peek();
//    }

//    while(1) {
//        cout << pit.next() << " ";
//    }

    //it.cout_thread();

    return 0;
}
