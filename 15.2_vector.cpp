#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

const double PI = 2.0 * acos(0.0);

struct vector2 {
	double x, y;

	explicit vector2(double _x = 0, double _y = 0) : x(x_), y(y_) {}

	bool operator == (const vector2& rhs) const {
		return (x == rhs.x && y == rhs.y);
	}

	// Lexicographic order
	bool operator < (const vector2& rhs) const {
		return x != rhs.x ? x < rhs.x : y < rhs.y;
	}

	vector2 operator + (const vector2& rhs) const {
		return vector2(x + rhs.x, y + rhs.y);
	}

	vector2 operator - (const vector2& rhs) const {
		return vector2(x - rhs.x, y - rhs.y);
	}

	vector2 operator * (double rhs) const {
		return vector2(x * rhs, y * rhs);
	}

	double norm() const { 
		return hypot(x, y); // return square root of the sum of the squares of x and y
	}	

	// return unit vector with same direction
	vector2 normalize() const {
		return vector2(x / norm(), y / norm());
	}

	double polar() const { 
		return fmod(atan2(y, x) + 2 * PI, 2 * PI); 
	}

	double dot(const vector2& rhs) const {
		return x * rhs.x + y * rhs.y;
	}

	double cross(const vector2& rhs) const {
		return x * rhs.y - y * rhs.x;
	}

	vector2 project(const vector2& rhs) const {
		vector2 r = rhs.normalize();
		return r * r.dot(*this);
	}
};

// (|a-p| - |b-p|)
double howMuchCloser(const vector2& p, const vector2& a, const vector2& b) {
	return (b - p).norm() - (a - p).norm();
}

double ccw(const vector2& a, const vector2& b) {
	return a.cross(b);
}

// Positive if a to b is ccw from p
double ccw(const vector2& p, const vector2& a, const vector2& b) {
	return ccw(a - p, b - p);
}

// false if line is parallel or same, x is cross point
bool lineIntersection(const vector2& a, const vector2& b, const vector2& c, const vector2& d, vector2& x) {
	double det = (b - a).cross(d - c);

	// Parallel
	if (fabs(det) < 1e-10) return false;

	x = a + (b - a) * ((c - a).cross(d - c) / det);

	return true;
}

bool parallelSegments(vector2 a, vector2 b, vector2 c, vector2 d, vector2& p) {
	if (b < a) swap(a, b);
	if (d < c) swap(c, d);

	//	Not Parallel		Not Overlapped
	if (ccw(a, b, c) != 0 || b < c || d < a) return false;

	// p is one of the cross point
	if (a < c)
		p = c;
	else
		p = a;

	return true;
}

// Check whether p is in the line segment between a and b
bool inBoundingRectangle(vector2 p, vector2 a, vector2 b) {
	if (b < a) swap(a, b);
	return p == a || p == b || (a < p && p < b);
}

// p is the cross point of a-b and c-d
bool segmentIntersection(vector2 a, vector2 b, vector2 c, vector2 d, vector2& p) {
	if (!lineIntersection(a, b, c, d, p))
		return parallelSegments(a, b, c, d, p);

	return inBoundingRectangle(p, a, b) && inBoundingRectangle(p, c, d);
}

bool segmentIntersection(vector2 a, vector2 b, vector2 c, vector2 d) {
	double ab = ccw(a, b, c) * ccw(a, b, d);
	double cd = ccw(c, d, a) * ccw(c, d, b);

	//if two segment are in the same line or at the end of line
	if (ab == 0 && cd == 0) {
		if (b < a) swap(a, b);
		if (d < c) swap(c, d);
		return !(b < c || d < a);
	}
	return ab <= 0 && cd <= 0;
}

vector2 perpendicularFoot(const vector2& p, const vector2& a, const vector2& b) {
	return a + (p - a).project(b - a);
}

double pointToLine(const vector2& p, const vector2& a, const vector2& b) {
	return (p - perpendicularFoot(p, a, b)).norm();
}

double area(const vector<vector2>& p) {
	double ret = 0;
	for (int i = 0; i < p.size(); i++) {
		int j = (i + 1) % p.size();
		ret += p[i].x * p[j].y - p[j].x * p[i].y;
	}
	return fabs(ret) / 2.0;
}

bool isInside(vector2 q, const vector<vector2>& p) {
	int crosses = 0;
	for (int i = 0; i < p.size(); i++) {
		int j = (i + 1) % p.size();

		// q에서 가로로 선을 그으면 p[i]와 p[j] 사이를 지나는가?
		// q를 살짝 올려서 오른쪽으로 그어서 체크
		if ((p[i].y > q.y) != (p[j].y > q.y)) {
			double atX = (p[j].x - p[i].x) * (q.y - p[i].y) / (p[j].y - p[i].y) + p[i].x;
			if (q.x < atX) {
				++crosses;
			}
		}
	}
	return crosses % 2 > 0;
}

typedef vector<vector2> polygon;
polygon giftWrap(const vector<vector2>& points) {
	int n = points.size();
	polygon hull;

	vector2 pivot = *min_element(points.begin(), points.end());
	hull.push_back(pivot);
	while (true)
	{
		vector2 ph = hull.back(), next = points[0];
		for (int i = 1; i < n; i++)
		{
			double cross = ccw(ph, next, points[i]);
			double dist = (next - ph).norm() - (points[i] - ph).norm();
			if (cross > 0 || (cross == 0 && dist < 0))
			{
				next = points[i];
			}
		}
		if (next == pivot) break;
		hull.push_back(next);
	}
	return hull;
}

// Unverified function
#include <stack>
polygon grahamScan(const vector<vector2>& points) {
	int n = points.size();
	polygon hull;
	vector<vector2> orderedPoints = points;

	vector2 pivot = *min_element(points.begin(), points.end());
	swap(pivot, orderedPoints[0]);
	auto it = orderedPoints.begin();
	it++;

	sort(it, orderedPoints.end(), [pivot](vector2& a, vector2& b) {return (a - pivot).polar() < (b - pivot).polar(); });

	stack<int> hullIdx;
	hullIdx.push(0);
	hullIdx.push(1);
	hullIdx.push(2);

	for (int i = 3; i < orderedPoints.size(); i++)
	{
		int topIdx = hullIdx.top();
		hullIdx.pop();
		while (ccw(orderedPoints[i], orderedPoints[hullIdx.top()], orderedPoints[topIdx]) < 0) {
			topIdx = hullIdx.top();
			hullIdx.pop();
		}
		hullIdx.push(topIdx);
		hullIdx.push(i);
	}

	while(!hullIdx.empty())
	{
		hull.push_back( orderedPoints[hullIdx.top()] );
		hullIdx.pop();
	}
	return hull;
}

bool polygonIntersects(const polygon& p, const polygon& q) {
	int n = p.size(), m = q.size();
	
	// 포함되어 있는 경우
	if (isInside(p[0], q) || isInside(q[0], p)) return true;

	// 겹치는 경우 서로 닿는 두 변이 존재
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (segmentIntersection(p[i], p[(i + 1) % n], q[j], q[(j + 1) % m]))
				return true;
		}
	}
	return false;
}

struct Rectangle {
	int x1, y1, x2, y2;
};

int unionArea(const vector<Rectangle>& rects) {
	if (rects.empty()) return 0;

	typedef pair<int, pair<int, int> > Event;
	vector<Event> events;
	vector<int> ys;

	for (int i = 0; i < rects.size(); i++)
	{
		ys.push_back(rects[i].y1);
		ys.push_back(rects[i].y2);
		events.push_back(Event(rects[i].x1, make_pair(1, i)));
		events.push_back(Event(rects[i].x2, make_pair(-1, i)));
	}

	// 정렬 후 중복 제거
	// 중복 양이 많다면 set이 유리함
	sort(ys.begin(), ys.end());
	ys.erase(unique(ys.begin(), ys.end()), ys.end());

	sort(events.begin(), events.end());
	int ret = 0;

	vector<int> count(ys.size() - 1, 0);
	for (int i = 0; i < events.size(); i++) {
		int x = events[i].first, delta = events[i].second.first;
		int rectangle = events[i].second.second;

		int y1 = rects[rectangle].y1, y2 = rects[rectangle].y2;
		for (int j = 0; j < ys.size(); j++)
		{
			if (y1 <= ys[j] && ys[j] < y2)
				count[j] += delta;
		}

		int cutLength = 0;
		for (int j = 0; j < ys.size() - 1; j++)
		{
			if (count[j] > 0)
				cutLength += ys[j + 1] - ys[j];
		}
		if (i + 1 < events.size())
			ret += cutLength * (events[i + 1].first - x);
	}
	return ret;
}

double diameter(const polygon& p) {
	int n = p.size();
	int left = min_element(p.begin(), p.end()) - p.begin();
	int right = max_element(p.begin(), p.end()) - p.begin();

	// x축 기준으로 좌, 우 끝점에 y축에 수직인 직선을 붙인다.
	vector2 calipersA(0, 1);
	double ret = (p[right] - p[left]).norm();

	// p[i]에서 다음 점까지의 방향을 나타내는 단위 벡터
	vector<vector2> toNext(n);
	for (int i = 0; i < n; i++)
	{
		toNext[i] = (p[(i + 1) % n] - p[i]).normalize();
	}
	// a, b는 회전하며 붙어있는 곳을 가리킴
	int a = left, b = right;
	// 반 바퀴 돌 때까지 반복
	while (a != right || b != left) {
		// a에서 다음으로 가는 각도 vs b에서 다음으로 가는 각도 중 작은 쪽부터 회전
		double cosThetaA = calipersA.dot(toNext[a]);
		double cosThetaB = -calipersA.dot(toNext[b]);
		if (cosThetaA > cosThetaB) {
			calipersA = toNext[a];
			a = (a + 1) % n;
		}
		else {
			calipersA = toNext[b] * -1;	// 책은 그냥 - 만 붙임. ???
			b = (b + 1) % n;
		}
		ret = max(ret, (p[a] - p[b]).norm());
	}
	return ret;
}