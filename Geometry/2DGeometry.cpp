#include<bits/stdc++.h>
using namespace std;
const double eps=1e-6,pi=acos(-1.0);

//Header
inline int dcmp(double x) {
	if(fabs(x)<eps)
		return 0;
	return x<0?-1:1;
}
inline double sqr(double x) {
	return x*x;
}

//Point
struct Point {
	double x,y;
	Point(double _x=0,double _y=0):x(_x),y(_y){};
	inline void in() {
		scanf("%lf%lf",&x,&y);
	}
};
inline Point operator + (Point A,Point B) {
	return Point(A.x+B.x,A.y+B.y);
}
inline Point operator - (Point A,Point B) {
	return Point(A.x-B.x,A.y-B.y);
}
inline Point operator * (Point A,double p) {
	return Point(A.x*p,A.y*p);
}
inline Point operator / (Point A,double p) {
	return Point(A.x/p,A.y/p);
}
inline bool operator < (const Point &a,const Point &b) {
	return a.x<b.x||(a.x==b.x&&a.y<b.y);
}
inline bool operator == (const Point &a,const Point &b) {
	return !dcmp(a.x-b.x)&&!dcmp(a.y-b.y);
}
inline double Distance(Point A,Point B) {
	return sqrt(sqr(A.x-B.x)+sqr(A.y-B.y));
}
inline double Dot(Point A,Point B) {
	return A.x*B.x+A.y*B.y;
}
inline double Norm(Point A) {
	return A.x*A.x+A.y*A.y;
}
inline double Length(Point A) {
	return sqrt(Dot(A,A));
}
inline double GetAngle(Point A,Point B) {
	return acos(Dot(A,B))/Length(A)/Length(B);
}
inline double GetAngle(Point v) {
	return atan2(v.y,v.x);
}
inline double Cross(Point A,Point B) {
	return A.x*B.y-A.y*B.x;
}
inline Point Unit(Point x) {
	return x/Length(x);
}
inline Point Normal(Point x) {
	return Point(-x.y,x.x)/Length(x);
}
inline Point Rotate(Point A,double rad) {
	return Point(A.x*cos(rad)-A.y*sin(rad),A.x*sin(rad)+A.y*cos(rad));
}
inline double Area2(const Point &A,const Point &B,const Point &C) {
	return Cross(B-A,C-A);
}
inline void getLineGeneralEquation(const Point &p1,const Point &p2,double &a,double &b,double &c) {
	a=p2.y-p1.y;
	b=p1.x-p2.x;
	c=-a*p1.x-b*p1.y;
}
inline Point GetLineIntersection(Point P,Point v,Point Q,Point w) {
	Point u=P-Q;
	double t=Cross(w,u)/Cross(v,w);
	return P+v*t;
}
inline double DistanceToLine(Point P,Point A,Point B) {
	Point v1=B-A,v2=P-A;
	return fabs(Cross(v1,v2))/Length(v1);
}
inline double DistanceToSegment(Point P,Point A,Point B) {
	if(A==B)
		return Length(P-A);
	Point v1=B-A,v2=P-A,v3=P-B;
	if(dcmp(Dot(v1,v2))<0)
		return Length(v2);
	else if(dcmp(Dot(v1,v3))>0)
		return Length(v3);
	else
		return fabs(Cross(v1,v2))/Length(v1);
}
inline Point GetLineProjection(Point P,Point A,Point B) {
	Point v=B-A;
	return A+v*(Dot(v,P-A)/Dot(v,v));
}
inline bool SegmentProperIntersection(Point a1,Point a2,Point b1,Point b2) {
	double c1=Cross(a2-a1,b1-a1),c2=Cross(a2-a1,b2-a1);
	double c3=Cross(b2-b1,a1-b1),c4=Cross(b2-b1,a2-b1);
	return dcmp(c1)*dcmp(c2)<0&&dcmp(c3)*dcmp(c4)<0;
}
inline bool OnSegment(Point p,Point a1,Point a2) {
	return dcmp(Cross(a1-p,a2-p))==0&&dcmp(Dot(a1-p,a2-p))<0;
}
inline double PolygonArea(Point *p,int n) {
	double area=0.0;
	for(int i=1;i<n-1;i++)
		area+=Cross(p[i]-p[0],p[i+1]-p[0]);
	return area/2.0;
}
inline Point GetMidPoint(Point A,Point B) {
	return Point((A.x+B.x)/2.0,(A.y+B.y)/2.0);
}
inline int PointinPolygon(Point p,vector<Point> poly) {
	int n=poly.size(),flg=0;
	for(int i=0;i<n;i++) {
		if(OnSegment(p,poly[i],poly[(i+1)%n]))
			return -1;
		int k=dcmp(Cross(poly[(i+1)%n]-poly[i],p-poly[i]));
		int d1=dcmp(poly[i].y-p.y);
		int d2=dcmp(poly[(i+1)%n].y-p.y);
		if(k>0&&d1<=0&&d2>0)
			flg++;
		if(k<0&&d2<=0&&d1>0)
			flg++;
	}
	if(flg)
		return 1;
	return 0;
}

//Segment and Line
struct Segment {
	Point p,v;
	Segment(){}
	Segment(Point _p,Point _v):p(_p),v(_v){}
	inline void in() {
		p.in();
		v.in();
	}
};
struct Line {
	Point p,v;
	double ang;
	Line(){}
	Line(Point _p,Point _v):p(_p),v(_v){ang=atan2(v.y,v.x);}
	inline Point point(double a) {
		return p+v*a;
	}
	inline bool operator < (const Line &rhs) const {
		return ang<rhs.ang;
	}
	inline Line move(double d) {
		return Line(p+Normal(v)*d,v);
	}
	inline void in() {
		p.in();
		v.in();
		ang=atan2(v.y,v.x);
	}
};
inline Line LineTransHorizon(Line l,int d) {
	Point vl=Normal(l.v);
	Point p1=l.p+vl*d;
	return Line(p1,l.v);
}
inline Point GetLineIntersection(Line a,Line b) {
	return GetLineIntersection(a.p,a.v,b.p,b.v);
}
inline bool OnLeft(const Line &L,const Point &p) {
	return Cross(L.v,p-L.p)>0;
}
inline Line GetParallel(Point p,Line l) {
	return Line(p,l.v);
}
inline Line GetVertical(Point p,Line l) {
	return Line(p,Normal(l.v));
}
inline Point GetVerticalFoot(Point p,Line l) {
	return GetLineIntersection(GetVertical(p,l),l);
}
inline Line GetPerpendicularLine(Segment l) {
	return GetVertical(GetMidPoint(l.p,l.v-l.p),Line(l.p,l.v));
}

//Angle
struct Angle {
	Point p,u,v;
	double ang;
	Angle(){}
	Angle(Point _p,Point _u,Point _v):p(_p),u(_u),v(_v){ang=GetAngle(u,v);}
	inline void in() {
		p.in();
		u.in();
		v.in();
		ang=GetAngle(u,v);
	}
};
inline Line GetAngleBisector(Angle A) {
	Point Unitu=Unit(A.u),Unitv=Unit(A.v);
	return GetPerpendicularLine(Segment(Point(A.p+Unitu),Point(A.p+Unitv)));
}

//Circle
struct Circle {
	Point c;
	double r;
	Circle(Point _c=0,double _r=0):c(_c),r(_r){}
	Point point(double a) {
		return Point(c.x+cos(a)*r,c.y+sin(a)*r);
	}
	inline void in() {
		c.in();
		scanf("%lf",&r);
	}
};
inline double ChordLength(Point a,Point b,Circle C) {
	double ang1,ang2;
	Point v1,v2;
	v1=a-C.c;v2=b-C.c;
	ang1=atan2(v1.y,v1.x);
	ang2=atan2(v2.y,v2.x);
	if(ang2<ang1)
		ang2+=2*pi;
	return C.r*(ang2-ang1);
}
inline int GetLineCircleIntersection(Line L,Circle C,double &t1,double &t2,vector<Point>&sol){
	double a=L.v.x,b=L.p.x-C.c.x,c=L.v.y,d=L.p.y-C.c.y;
	double e=sqr(a)+sqr(c),f=2*(a*b+c*d),g=sqr(b)+sqr(d)-sqr(C.r);
	double delta=sqr(f)-4.0*e*g;
	//cout<<a<<" "<<b<<" "<<c<<" "<<d<<" "<<e<<" "<<f<<" "<<g<<" "<<delta<<endl;
	if(dcmp(delta)<0)
		return 0;
	if(dcmp(delta)==0) {
		t1=t2=-f/(e*2);
		sol.push_back(L.point(t1));
		return 1;
	}
	t1=(-f-sqrt(delta))/(e*2);
	sol.push_back(L.point(t1));
	t2=(-f+sqrt(delta))/(e*2);
	sol.push_back(L.point(t2));
	return 2;
}
inline int GetCircleCircleIntersection(Circle C1,Circle C2,vector<Point>&sol) {
	double d=Length(C1.c-C2.c);
	if(dcmp(d)==0) {
		if(dcmp(C1.r-C2.r)==0)
			return -1;
		return 0;
	}
	if(dcmp(C1.r+C2.r-d)<0)
		return 0;
	if(dcmp(fabs(C1.r-C2.r)-d)>0)
		return 0;
	double a=GetAngle(C2.c-C1.c);
	double da=acos((sqr(C1.r)+sqr(d)-sqr(C2.r))/(2*C1.r*d));
	Point p1=C1.point(a-da),p2=C1.point(a+da);
	sol.push_back(p1);
	if(p1==p2)
		return 1;
	sol.push_back(p2);
	return 2;
}
inline int GetTangents(Point p,Circle C,Point *v) {
	Point u=C.c-p;
	double dist=Length(u);
	if(dist<C.r)
		return 0;
	else if(dcmp(dist-C.r)==0) {
		v[0]=Rotate(u,pi/2);
		return 1;
	}
	else {
		double ang=asin(C.r/dist);
		v[0]=Rotate(u,-ang);
		v[1]=Rotate(u,ang);
		return 2;
	}
}
inline int GetTangents(Circle A,Circle B,Point *a,Point *b) {
	int cnt=0;
	if(A.r<B.r) {
		swap(A,B);
		swap(a,b);
	}
	int d2=Distance(A.c,B.c);
	int rdiff=A.r-B.r;
	int rsum=A.r+B.r;
	if(d2<sqr(rdiff))
		return 0;
	double base=atan2(B.c.y-A.c.y,B.c.x-A.c.x);
	if(d2==0&&A.r==B.r)
		return -1;
	if(d2==sqr(rdiff)) {
		a[cnt]=A.point(base);
		b[cnt]=B.point(base);
		cnt++;
		return 1;
	}
	double ang=acos((A.r-B.r)/sqrt(d2));
	a[cnt]=A.point(base+ang);b[cnt]=B.point(base+ang);cnt++;
	a[cnt]=A.point(base-ang);b[cnt]=B.point(base-ang);cnt++;
	if(d2==sqr(rsum)) {
		a[cnt]=A.point(base);
		b[cnt]=B.point(pi+base);
		cnt++;
	}
	else if(d2>sqr(rsum)) {
		double ang=acos((A.r-B.r)/sqrt(d2));
		a[cnt]=A.point(base+ang);b[cnt]=B.point(pi+base+ang);cnt++;
		a[cnt]=A.point(base-ang);b[cnt]=B.point(pi+base-ang);cnt++;
	}
	return cnt;
}
inline Circle CircumscribedCircle(Point p1,Point p2,Point p3) {
	double Bx=p2.x-p1.x,By=p2.y-p1.y;
	double Cx=p3.x-p1.x,Cy=p3.y-p1.y;
	double D=2*(Bx*Cy-By*Cx);
	double cx=(Cy*(sqr(Bx)+sqr(By))-By*(sqr(Cx)+sqr(Cy)))/D+p1.x;
	double cy=(Bx*(sqr(Cx)+sqr(Cy))-Cx*(sqr(Bx)+sqr(By)))/D+p1.y;
	Point p=Point(cx,cy);
	return Circle(p,Length(p1-p));
}
inline Circle InscribedCircle(Point p1,Point p2,Point p3) {
	double a=Length(p2-p3);
	double b=Length(p3-p1);
	double c=Length(p1-p2);
	Point p=(p1*a+p2*b+p3*c)/(a+b+c);
	return Circle(p,DistanceToLine(p,p1,p2));
}
inline double RadtoDegree(double x) {
	return x*180/pi;
}
inline double DegreetoRad(double x) {
	return x*pi/180;
}

//ConveHull Yes.
inline int ConvexHull(Point *p,int n,Point *ans) {
	sort(p,p+n);
	int m=0;
	for(int i=0;i<n;i++) {
		while(m>1&&Cross(ans[m-1]-ans[m-2],p[i]-ans[m-2])<=0)
			m--;
		ans[m++]=p[i];
	}
	int k=m;
	for(int i=n-2;~i;i--) {
		while(m>k&&Cross(ans[m-1]-ans[m-2],p[i]-ans[m-2])<=0)
			m--;
		ans[m++]=p[i];
	}
	if(n>1)
		m--;
	return m;
}
inline vector<Point> CutPolygon(vector<Point> poly,Point A,Point B) {
	vector<Point> ans;
	int n=poly.size();
	for(int i=0;i<n;i++) {
		Point C=poly[i];
		Point D=poly[(i+1)%n];
		if(dcmp(Cross(B-A,C-A))>=0)
			ans.push_back(C);
		if(dcmp(Cross(B-A,C-D))!=0) {
			Point w=GetLineIntersection(A,B-A,C,D-C);
			if(OnSegment(w,C,D))
				ans.push_back(w);
		}
	}
	return ans;
}

//HalfplaneIntersection
inline int HalfplaneIntersection(Line *L,int n,Point *poly) {
	sort(L,L+n);
	int fst,lst;
	Point *p=new Point[n];
	Line *q=new Line[n];
	q[fst=lst=0]=L[0];
	for(int i=0;i<n;i++) {
		while(fst<lst&&!OnLeft(L[i],p[lst-1]))
			lst--;
		while(fst<lst&&!OnLeft(L[i],p[fst]))
			fst++;
		q[++lst]=L[i];
		if(fabs(Cross(q[lst].v,q[lst-1].v))<eps) {
			lst--;
			if(OnLeft(q[lst],L[i].p))
				q[lst]=L[i];
		}
		if(fst<lst)
			p[lst-1]=GetLineIntersection(q[lst-1],q[lst]);
	}
	while(fst<lst&&!OnLeft(q[fst],p[lst-1]))
		lst--;
	if(lst-fst<=1)
		return 0;
	p[lst]=GetLineIntersection(q[lst],q[fst]);
	int m=0;
	for(int i=fst;i<=lst;i++)
		poly[m++]=p[i];
	return m;
}

string op[6]={"CircumscribedCircle","InscribedCircle","TangentLineThroughPoint","CircleThroughAPointAndTangentToALineWithRadius","CircleTangentToTwoLinesWithRadius","CircleTangentToTwoDisjointCirclesWithRadius"},tp;
Point p1,p2,p3,p4,val[100];
Circle c1,c2;
Line l1,l2;
double ans[100],r;
vector<Point>sol;
int main() {
	while(cin>>tp) {
		if(tp==op[0]) {
			p1.in();p2.in();p3.in();
			c1=CircumscribedCircle(p1,p2,p3);
			printf("(%.6lf,%.6lf,%.6lf)\n",c1.c.x,c1.c.y,c1.r);
		}
		else if(tp==op[1]) {
			p1.in();p2.in();p3.in();
			c1=InscribedCircle(p1,p2,p3);
			printf("(%.6lf,%.6lf,%.6lf)\n",c1.c.x,c1.c.y,c1.r);
		}
		else if(tp==op[2]) {
			c1.in();p1.in();
			int sz=GetTangents(p1,c1,val);
			for(int i=0;i<sz;i++) {
				ans[i]=RadtoDegree(GetAngle(val[i]));
				while(dcmp(ans[i])<0)
					ans[i]+=180.0;
				while(dcmp(ans[i]-180.00)>=0)
					ans[i]-=180.0;
			}
			sort(ans,ans+sz);
			putchar('[');if(!sz)putchar(']');
			for(int i=0;i<sz;i++)
				printf("%.6lf%c",ans[i],i==sz-1?']':',');
			putchar('\n');
		}
		else if(tp==op[3]) {
			p1.in();p2.in();p3.in();
			scanf("%lf",&r);
			c1=Circle(p1,r);
			Point normal=Normal(p3-p2);
			normal=Unit(normal)/*normal/Length(normal)*/*r;
			Point t1=p2+normal,t2=p3+normal;
			l1=Line(t1,t2-t1);
			t1=p2-normal,t2=p3-normal;
			l2=Line(t1,t2-t1);
			sol.clear();
			double tp,tq;
			int a=GetLineCircleIntersection(l1,c1,tp,tq,sol);
			int b=GetLineCircleIntersection(l2,c1,tp,tq,sol);
			sort(sol.begin(),sol.end());
			putchar('[');
			for(unsigned i=0;i<sol.size();i++) {
				if(i)
					putchar(',');
				printf("(%.6lf,%.6lf)",sol[i].x,sol[i].y);
			}
			putchar(']');putchar('\n');
		}
		else if(tp==op[4]) {
			vector<Point>ans;
			p1.in();p2.in();p3.in();p4.in();
			scanf("%lf",&r);
			Line l1=Line(p1,p2-p1),l2=Line(p3,p4-p3);
			ans.clear();
			Line la=l1.move(-r),lb=l1.move(r),lc=l2.move(-r),ld=l2.move(r);
			ans.push_back(GetLineIntersection(la,lc));
			ans.push_back(GetLineIntersection(la,ld));
			ans.push_back(GetLineIntersection(lb,lc));
			ans.push_back(GetLineIntersection(lb,ld));
			sort(ans.begin(),ans.end());
			printf("[(%.6lf,%.6lf)",ans[0].x,ans[0].y);
			for(int i=1;i<4;i++)
				printf(",(%.6lf,%.6lf)",ans[i].x,ans[i].y);
			printf("]\n");
		}
		else if(tp==op[5]) {
			printf("[");
			c1.in();c2.in();
			scanf("%lf",&r);
			if(c1.r<c2.r)
				swap(c1,c2);
			double d=Length(c1.c-c2.c)-c1.r-c2.r;
			sol.clear();
			Circle ca=Circle(c1.c,c1.r+r),cb=Circle(c2.c,c2.r+r);
			int num=GetCircleCircleIntersection(ca,cb,sol);
			if(num>0) {
				sort(sol.begin(),sol.end());
				printf("(%.6lf,%.6lf)",sol[0].x,sol[0].y);
			}
			for(int i=1;i<num;i++)
				printf(",(%.6lf,%.6lf)",sol[i].x,sol[i].y);
			printf("]\n");
		}
	}
	return 0;
}
