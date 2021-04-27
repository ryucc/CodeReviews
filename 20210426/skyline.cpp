typedef pair<int, int> pr;

template <typename T>
struct cmpr {
    bool operator()(const T & p1, const T & p2) const {
        if  (p1.first == p2.first) return p1.second < p2.second;
        return p1.first < p2.first;
    }
};

template <typename T>
struct cmph {
    bool operator()( const T& p1, const T & p2) const {
        return p1.second > p2.second;
    }
};
    
class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        
        multiset<pr, cmph<pr>> hpq; //height priority queue
        multiset<pr, cmpr<pr>> rpq; // right coordinate priority queue
        
        vector<vector<int>> ret;
        
        for(vector<int> & vec: buildings) {
            int l=vec[0], r=vec[1] ,h=vec[2];
            
            //  remove all right < current left bracket
            while (!rpq.empty() && (*rpq.begin()).first < l) {
                pr tmp = *rpq.begin();
                rpq.erase(rpq.begin());
                hpq.erase(hpq.find(tmp));
                if (!hpq.size()) {
                    ret.push_back(vector<int>{tmp.first, 0});
                }
                else if (tmp.second > (*hpq.begin()).second)
                    ret.push_back(vector<int>{tmp.first, (*hpq.begin()).second});
                
            }
            // register current left and right block if feasible
            
            if (!hpq.size()|| (h > (*hpq.begin()).second))  { 
                if (ret.size() && ret.back()[0] == l) {
                    ret.back()[1] = max(ret.back()[1], h);
                } else {
                    ret.push_back(vector<int> {l, h}); 
                }
            }
            
            
            pr rborder = make_pair(r, h);
            hpq.insert(rborder);
            rpq.insert(rborder);
            
        }
        //  remove all right < current left bracket
        while (!rpq.empty()) {
            pr tmp = *rpq.begin();
            rpq.erase(rpq.begin());
            hpq.erase(hpq.find(tmp));
            if (!hpq.size()) {
                ret.push_back(vector<int>{tmp.first, 0});
            }
            else if (tmp.second > (*hpq.begin()).second)
                ret.push_back(vector<int>{tmp.first, (*hpq.begin()).second});

        }
        return ret;
    }
};
