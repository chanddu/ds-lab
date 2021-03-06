int getmin(vector <int> antler1, vector <int> antler2, int capacity)
{
    int n = antler1.size();
    // Let us build the canCycle[subset] array, using bitmasks to generate the subsets:
    bool canCycle[1<<n];
    memset(canCycle, 0, sizeof(canCycle));
    for (int mask = 0; mask < (1<<n); mask++) {
        int t = 0;
        // Save the antlers of the moose in the set in an array.
        int ant[32];
        for (int i = 0; i < n; i++) {
            if (mask & (1<<i)) {
                ant[t++] = antler1[i];
                ant[t++] = antler2[i];
            }
        }
        // sort the natlers:
        sort(ant, ant + t);
        canCycle[mask] = true; //assume the set is valid
        for (int i = 0; i<t; i += 2) {
            if ( abs(ant[i] - ant[i+1]) > capacity ) {
                // These two consecutive antlers make an invalid match. If this
                // happens even when sorted, it is impossible to make a cycle
                // with this set of moose.
                canCycle[mask] = false;
            }
        }
    }
    
    // Dynamic programming to count the maximum number of components (since the components
    // will be cycles or loops, the maximum number of non-overlapping cycles:)
    int maxCycles[1<<n];
    // When a subset can't be split in valid cycles, maxCycles[i] will be 0.
    // Except for the empty subset, in which 0 is a valid result.
    memset(maxCycles, 0, sizeof(maxCycles));
    for (int mask = 1; mask < (1<<n); mask++) {
        for (int sub = mask; sub > 0; sub = ( (sub - 1) & mask ) ) {
            if (canCycle[sub] && ( (sub==mask) || (maxCycles[mask-sub] > 0) ) ) {
                maxCycles[mask] = std::max(maxCycles[mask], 1 + maxCycles[mask-sub]);
            }
        }
    }
    // The maximum number of components is c:
    int c = maxCycles[ (1<<n) - 1];
    return (c > 0) ? (n - c) : -1;
}
