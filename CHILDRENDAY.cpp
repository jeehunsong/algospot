// https://algospot.com/judge/problem/read/CHILDRENDAY

// BUGFIX
// Error in condition for solution: Reminder of N is M, Not reminder of (N+M) is zero
// Fix for availNum starting with zero
// Totally failed, read the textbook, and then twice the size of the vector in solve(). before this, solve() check whether the number of toys is over (N+M) or not with complicated if-else

//#define DEBUG

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <queue>

using namespace std;

vector<int> avail;
int N, M;	// N is max 10000
string availNum;

void makeAvail() {
	// availNum is larger than 0
	avail.clear();

	for (int i = 0; i < availNum.length() ; ++i)
	{
		avail.push_back(availNum[i] - '0');
	}
	sort(avail.begin(), avail.end());

#ifdef DEBUG
	for (auto i: avail) cout << i << " ";
	cout << endl;
#endif
}

void solve() {
	vector<int> reminderToParent(N * 2, -1);
	vector<int> appended(N * 2);
	reminderToParent[0] = 0;	// starting point
	queue<int> bfs;
	bfs.push(0);

	while(!bfs.empty()) {
		int reminder = bfs.front();
		bfs.pop();
#ifdef DEBUG
		cout << "reminder " << reminder << endl;
#endif

		for (int i = 0; i < avail.size() ; ++i)
		{
			int appendNum = avail[i];
			int nextReminder = reminder * 10 + appendNum;
			if ((reminder < N && nextReminder >= N) ||
				(reminder >= N)) {
				nextReminder = (nextReminder % N) + N;
			}

			if (reminderToParent[nextReminder] == -1)
			{
				reminderToParent[nextReminder] = reminder;
				appended[nextReminder] = appendNum;
				bfs.push(nextReminder);
			}
		}
	}

	if (reminderToParent[N + M] == -1) {
		cout << "IMPOSSIBLE" << endl;
	}
	else {
		string sol;
		int pos = N + M;
		while(pos != 0) {
		    sol += to_string(appended[pos]);
		    pos = reminderToParent[pos];
		}
		reverse(sol.begin(), sol.end());
		cout << sol << endl;
	}
}

int main()
{
	ios_base::sync_with_stdio(false);

	int numCase;
	cin >> numCase;
	while(numCase--) {
	    cin >> availNum >> N >> M;
#if 0
	    if (availNum == 0) {
	    	cout << "IMPOSSIBLE" << endl;
	    	continue;
	    }
#endif
	    makeAvail();

	    // increase toys 1 per person ==> increase N total toys
	    solve();
	}
}