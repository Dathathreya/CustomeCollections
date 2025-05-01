/*
lib:          Based on old-yan/CP-template (core logic adapted to C)
author:       Adapted by Gemini
*/

#include <stdio.h> // For printf, scanf, fprintf, stderr

// Define the maximum size for arrays using a preprocessor macro
#define Q_MAX 500000

// Use standard C unsigned int for size_type and integer values
typedef unsigned int size_type;

struct Node {
    unsigned int ver;
    unsigned int at_back; // 0 for false, 1 for true
    unsigned int x;
    size_type m_next;
};

// Declare the data arrays globally and statically
// Bucket array: Q_MAX + 1 buckets needed (0 to Q_MAX)
static size_type global_bucket[Q_MAX + 1];
// Item array: Q_MAX items needed (one for each query operation '0' or '1')
static struct Node global_item[Q_MAX];

struct LinkBucket {
    // The struct now primarily manages the indices and cursor for the global arrays
    size_type m_bucket_cnt; // Number of buckets initialized
    size_type m_item_cnt;   // Max capacity of items (Q_MAX)
    size_type m_cursor;     // Next available item index
};

// Declare a static instance of the LinkBucket manager
static struct LinkBucket buckets;

// Function to initialize the LinkBucket (resets indices and cursor for global arrays)
void LinkBucket_init(size_type bucket_cnt, size_type item_cnt_capacity) {
    if (bucket_cnt > Q_MAX + 1) {
        fprintf(stderr, "Error: Bucket count exceeds global array size.\n");
        // In a real application without stdlib.h, you might have a custom error handler or simply stop.
        // For this example, we'll print and assume the caller handles the error or the size is correct.
        buckets.m_bucket_cnt = 0; // Indicate invalid state
        buckets.m_item_cnt = 0;
        buckets.m_cursor = 0;
        return;
    }
     if (item_cnt_capacity > Q_MAX) {
        fprintf(stderr, "Error: Item capacity exceeds global array size.\n");
        buckets.m_bucket_cnt = 0; // Indicate invalid state
        buckets.m_item_cnt = 0;
        buckets.m_cursor = 0;
        return;
    }


    buckets.m_bucket_cnt = bucket_cnt;
    buckets.m_item_cnt = item_cnt_capacity; // Should be Q_MAX

    // Initialize buckets with -1 (indicating empty linked list head)
    // Casting -1 to an unsigned type results in the maximum value (UINT_MAX)
    // which serves as a valid "end of list" marker for unsigned indices.
    for (size_type i = 0; i < buckets.m_bucket_cnt; ++i) {
        global_bucket[i] = (size_type)-1;
    }

    buckets.m_cursor = 0;
}

// Function to push an item to the front of a bucket using global arrays
void LinkBucket_push_front(size_type buc_id, unsigned int ver, unsigned int at_back, unsigned int x) {
    if (buc_id >= buckets.m_bucket_cnt) {
        fprintf(stderr, "Error: Invalid bucket ID %u.\n", buc_id);
        return; // Or handle error appropriately
    }
    if (buckets.m_cursor >= buckets.m_item_cnt) {
        // This should not happen if Q_MAX is set correctly based on the problem constraints
        fprintf(stderr, "Error: LinkBucket item capacity exceeded!\n");
        // In a real application without stdlib.h, this is a critical error.
        // We'll just print an error and hope the program terminates naturally or due to other issues.
        return;
    }

    global_item[buckets.m_cursor].ver = ver;
    global_item[buckets.m_cursor].at_back = at_back;
    global_item[buckets.m_cursor].x = x;
    global_item[buckets.m_cursor].m_next = global_bucket[buc_id];
    global_bucket[buc_id] = buckets.m_cursor++;
}

// No LinkBucket_destroy needed as memory is statically allocated

static unsigned int buf[Q_MAX];
static unsigned int l_ptr = 0, r_ptr = 0; // Pointers/indices for the buffer

static unsigned int res[Q_MAX]; // Result array

// Recursive DFS function
void dfs(unsigned int cur_ver, unsigned int initial_at_back, unsigned int initial_x) {
    // Process the current node (coming from a push_front operation)
    if (initial_at_back) {
        buf[r_ptr++] = initial_x;
    } else {
        // If initial_x is a valid index (not the dummy -1), store the result
        // (unsigned int)-1 is UINT_MAX
        if (initial_x != (unsigned int)-1) {
            res[initial_x] = buf[l_ptr++];
        }
    }

    // Iterate through the linked list in the bucket corresponding to the current version
    // Access global_bucket using cur_ver
    size_type current_node_idx = global_bucket[cur_ver];
    while (current_node_idx != (size_type)-1) {
        // Access global_item using current_node_idx
        struct Node current_node = global_item[current_node_idx];
        // Recursive call for the version stored in the node
        dfs(current_node.ver, current_node.at_back, current_node.x);
        current_node_idx = current_node.m_next;
    }

    // Backtrack: Undo the buffer operation
    if (initial_at_back) {
        r_ptr--;
    } else {
         // (unsigned int)-1 is UINT_MAX
         if (initial_x != (unsigned int)-1) {
             buf[--l_ptr] = res[initial_x];
         }
    }
}

void solve_rollbackdsu() {
    unsigned int q;
    scanf("%u", &q);

    // Initialize LinkBucket using global arrays, size based on Q_MAX
    // Need q+1 buckets (0 to q), and up to q items
    LinkBucket_init(q + 1, q);

    unsigned int cur_query_idx = 0; // Index for '1' operations

    for (unsigned int i = 1; i <= q; i++) {
        char op;
        unsigned int t;
        // Read character and then unsigned integer
        scanf(" %c %u", &op, &t); // Note the space before %c to consume whitespace
        t++; // Adjust to 1-based indexing for buckets as in C++ code

        if (op == '0') {
            unsigned int x;
            scanf("%u", &x);
            // Push to bucket t using global arrays
            LinkBucket_push_front(t, i, 1, x); // ver, at_back=true, x
        } else { // op == '1'
            // Push to bucket t using global arrays
            LinkBucket_push_front(t, i, 0, cur_query_idx++); // ver, at_back=false, query_idx
        }
    }

    // Start DFS from the initial state (version 0)
    // Simulate processing nodes in bucket 0
    size_type initial_node_idx = global_bucket[0];
    while (initial_node_idx != (size_type)-1) {
        struct Node initial_node = global_item[initial_node_idx];
         // Recursive call for the version stored in the node
        dfs(initial_node.ver, initial_node.at_back, initial_node.x);
        initial_node_idx = initial_node.m_next;
    }

    // Print the results
    for (unsigned int i = 0; i < cur_query_idx; ++i) {
        printf("%u\n", res[i]);
    }

    // No explicit memory freeing needed for static/global arrays
}

int main() {
    // Using standard C I/O which might be slower than the original LinuxIO
    solve_rollbackdsu();
    return 0; // Indicate successful execution
}
