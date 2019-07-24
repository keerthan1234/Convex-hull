#include <bits/stdc++.h>
//#include<boost/python.htpp>
#define endl '\n'
using namespace std;
class Point{
	public:
		float x,y;
		Point(float a, float b){
			x = a;
			y = b;
		}
		Point(){
			x = 0;
			y = 0;
		}
		Point(float a){
			x = 0;
		}
		float getx(){
			return x;
		}
		float gety(){
			return y;
		}
		void print(){
			cout << x << " " << y ;
		}
		void printx(){
			cout << x ;
		}
		void printy(){
			cout << y ;
		}

};
Point pivot;
float Sqr_dist(Point p1, Point p2)
{
    return (p1.x - p2.x)*(p1.x - p2.x) +  (p1.y - p2.y)*(p1.y - p2.y);
}


int angle_direction(Point p, Point q, Point r)
{
    float val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0;
    return (val > 0)? 1: 2; //2 means counter-clockwise
}

bool Polar_angle( Point p1,  Point p2)
{
   int order = angle_direction(pivot, p1, p2);
   if (order == 0)
     return (Sqr_dist(pivot, p2) >= Sqr_dist(pivot, p1));

   return (order == 2);
}
class Graham_scan{
	public:
		vector<Point> ans;
		ofstream writeF;
		Point nextToTop(stack<Point> &Stck)
		{
		    Point p = Stck.top();
		    Stck.pop();
		    Point res = Stck.top();
		    Stck.push(p);
		    return res;
		}

		int swap(Point &p1, Point &p2)
		{
		    Point temp = p1;
		    p1 = p2;
		    p2 = temp;
		}
		vector<Point> ConvertToConvexHull(vector<Point>& points)
		{
		   int n = points.size();
		   float min_y = points[0].y, min = 0;
		   for (int i = 1; i < n; i++)
		   {
		     float y = points[i].y;
		     if ((y < min_y) || (min_y == y &&
		         points[i].x < points[min].x))
		        min_y = points[i].y, min = i;
		   }
		   swap(points[0], points[min]);
		   pivot = points[0];
		   sort(&points[1], &points[n], Polar_angle);
		   int m = 1;
		   for (int i=1; i<n; i++)
		   {
		       while (i < n-1 && angle_direction(pivot, points[i], points[i+1]) == 0)
		          i++;
		  		points[m] = points[i];
		      	m++;
		   }

		   if (m < 3) return(ans);
		   stack<Point> Stck;
		   Stck.push(points[0]);
		   Stck.push(points[1]);
		   Stck.push(points[2]);
		   for (int i = 3; i < m; i++)
		   {
		      while (angle_direction(nextToTop(Stck), Stck.top(), points[i]) != 2)
		         Stck.pop();
		      Stck.push(points[i]);
		   }

		   while (!Stck.empty())
		   {
		       Point p = Stck.top();
		       ans.push_back(p);
		       Stck.pop();
		   }

		   return(ans);
		}

		void writeToFile(){
			writeF.open("Graham_scan/hull.txt");
			for (int i=0;i<ans.size();i++){
				writeF << ans[i].getx()<< "," <<  ans[i].gety() << endl;
			}
			writeF.close();
	
		}
};


class Jarvis_March{
	public:
		vector<Point> ans;
		ofstream writeF;
		vector<Point> ConvertToConvexHull(vector<Point>& points)
		{
			int n = points.size();
		    if (n < 3) return(ans);
		    int l = 0;
		    for (int i = 1; i < n; i++)
		        if (points[i].x < points[l].x)
		            l = i;
		    int p = l, q;
		    do
		    {
		        ans.push_back(points[p]);
		        q = (p+1)%n;
		        for (int i = 0; i < n; i++)
		        {
		           if (angle_direction(points[p], points[i], points[q]) == 2)
		               q = i;
		        }
		        p = q;


		    } while (p != l);

		}
		void writeToFile(){
			writeF.open("Jarvis_march/hull.txt");
			for (int i=0;i<ans.size();i++){
				writeF << ans[i].getx()<< "," <<  ans[i].gety() << endl;
			}
			writeF.close();
	
		}

};

int main(){
	int n;
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	//cout << "No of points - " << "\n";
	cin >> n;
	vector<Point> points;
	ofstream myfile;
	myfile.open("points.txt");
	for (int i=0;i<n;i++){
		float a,b;
		cin >> a >> b;
		Point p = Point(a,b);
		points.push_back(p);
		myfile << a << "," << b << endl;
	}
	myfile.close();

	Graham_scan j = Graham_scan();
	j.ConvertToConvexHull(points);
	j.writeToFile();
	for (int i=0;i<j.ans.size();i++){
		cout << j.ans[i].getx() << " " << j.ans[i].gety();
		cout << "\n";
	}
}
