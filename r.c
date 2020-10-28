//!\file reference impls
#include<stdio.h>//printf
typedef int I;typedef unsigned int UI;typedef long long J;typedef void V;
#define ZI static I
#define R return
#define O printf
#define P(x,y) {if(x)R(y);}
#define W(a...) while((a))
#define N(n,a...) {I _n=(n),i=0;W(i<_n){a;++i;}}
#define rI ((I*)r)
#define xI ((I*)x)
I c(I n){I c=0;W(n!=1){n=n&1?(n<<1)+n+1:n>>1;c++;}R c;}//!< all numbers lead to one
inline ZI cmp(I*x,I i,I*y,I j){R x[i]<y[j]?-1:x[i]>y[j];}//!< comparator

ZI mrg(I*b,I*x,I l,I h,I d){
  I t,u,m=(UI)(l+h+1)/2;
  P(h==m,(b[l]=-1,l))
  u=cmp(x,h=mrg(b,x,m,h,d),x,l=mrg(b,x,l,m,d));
  if(u?d^(u<0):h<l)m=l,l=h,h=m;
  for(t=l;;u=cmp(x,m,x,h),l=(u?d^(u<0):m<h)?m:(b[l]=h,h=m,b[l]))
    P((m=b[l])<0,(b[l]=h,t))}

I main(V){
  I l=9;O("c[%d]=%d\n",l,c(l));

  I d=0,r[10]={0},o[10]={0},x[10]={8,9,3,5,6,0,7,2,1,4};
  I j=mrg(rI,xI,0,10,d);N(10,o[i]=j;j=r[j])
  N(10,O("%d ",x[o[i]]))O("\n");R 0;}

//:~
