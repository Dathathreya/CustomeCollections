#define N ((int)1e5+4)
typedef long long int lli;
typedef struct pii{
    int f,s;
}pii;

pii dq[N];
int tail = -1 , head = -1;

bool empty(){
    return ((tail==-1)&&(head==-1));
}

bool full(){
    return (((tail+1)%N)==(head%N));
}

int front(int e){
    if(empty()){return -1;}
    return ((e==0)?(dq[head].f):(dq[head].s));
}

int back(int e){
    if(empty()){return -1;}
    return ((e==0)?(dq[tail].f):(dq[tail].s));
}

void pop_front(){
    if(!empty()){
        if(head==tail){
            head = -1;tail = -1;
        }
        else{
            head = (head+1)%N;
        }
    }
}

void pop_back(){
    if(!empty()){
        if(head==tail){
            head = -1;tail = -1;
        }
        else{
           tail = (N-1+tail)%N;
        }
    }
}

void push_front(int fir,int sec){
    if(full()){
        return;
    }
    if(empty()){
        tail = 0;
        head = 0;
    }
    else{
        head = (head-1+N)%N;
    }
    dq[head].f = fir;
    dq[head].s = sec;
}

void push_back(int fir,int sec){
    if(full()){
        return;
    }
    if(empty()){
        tail = 0;
        head = 0;
    }
    else{
        tail = (tail+1)%N;
    }
    dq[tail].f = fir;
    dq[tail].s = sec;
}

// Function to get the total size of the deque
int total_size(){
    if(empty()){
        return 0;
    }
    if(head <= tail){
        return tail - head + 1;
    }
    else{
        return N - head + tail + 1;
    }
}

// Function to insert an element at a specified position
void insert(int pos, int fir, int sec){
    if(full()){
        return;
    }
    if(pos < 0 || pos > total_size()){
        return; // Invalid position
    }
    if(pos == 0){
        push_front(fir, sec);
    }
    else if(pos == total_size()){
        push_back(fir, sec);
    }
    else{
        // Shift elements to make space for the new element
        int current_size = total_size();
        for(int i = current_size - 1; i >= pos; --i){
            int idx = (head + i) % N;
            int next_idx = (head + i + 1) % N;
            dq[next_idx] = dq[idx];
        }
        int insert_idx = (head + pos) % N;
        dq[insert_idx].f = fir;
        dq[insert_idx].s = sec;
        tail = (tail + 1) % N;
    }
}

// Function to delete an element from a specified position
void delete_pos(int pos){
    if(empty()){
        return;
    }
    if(pos < 0 || pos >= total_size()){
        return; // Invalid position
    }
    if(pos == 0){
        pop_front();
    }
    else if(pos == total_size() - 1){
        pop_back();
    }
    else{
        // Shift elements to fill the gap
        int current_size = total_size();
        for(int i = pos; i < current_size - 1; ++i){
            int idx = (head + i) % N;
            int next_idx = (head + i + 1) % N;
            dq[idx] = dq[next_idx];
        }
        tail = (tail - 1 + N) % N;
    }
}
