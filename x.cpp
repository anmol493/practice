#include<bits/stdc++.h>
#include<algorithm>
#include<string>
#include<cstring>
#include<climits>

using namespace std;
class help
{
  public:
  int sum;
  int msum;
  int fr;
  int bk;
};
void btree(int a[],help *tree,int tinx,int s,int e)
{
  if(s==e)
  {
    help x;
    x.sum=a[s];
    x.msum=a[s];
    x.fr=a[s];
    x.bk=a[s];
    tree[tinx]=x;
    return;
  }
  int mid=(s+e)/2;
  btree(a,tree,2*tinx,s,mid);
  btree(a,tree,2*tinx+1,mid+1,e);
  help x;
  x.sum=tree[2*tinx].sum+tree[2*tinx+1].sum;
  x.msum=max(max(tree[2*tinx].msum,tree[2*tinx+1].msum),tree[2*tinx].bk+tree[2*tinx+1].fr);
  x.fr=max(tree[2*tinx].fr,tree[2*tinx].sum+tree[2*tinx+1].fr);
  x.bk=max(tree[2*tinx+1].bk,tree[2*tinx+1].sum+tree[2*tinx].bk);
  tree[tinx]=x;
}
void update(int a[],help *tree,int tinx,int s,int e,int ainx,int value)
{
  if(s==e)
  {
    help x;
    a[ainx]=value;
    x.sum=value;
    x.msum=value;
    x.fr=value;
    x.bk=value;
    tree[tinx]=x;
    return;
  }
  int mid=(s+e)/2;
  if(mid<ainx)
  update(a,tree,2*tinx+1,mid+1,e,ainx,value);
  else
  update(a,tree,2*tinx,s,mid,ainx,value);
  help x;
  x.sum=tree[2*tinx].sum+tree[2*tinx+1].sum;
  x.msum=max(max(tree[2*tinx].msum,tree[2*tinx+1].msum),tree[2*tinx].bk+tree[2*tinx+1].fr);
  x.fr=max(tree[2*tinx].fr,tree[2*tinx].sum+tree[2*tinx+1].fr);
  x.bk=max(tree[2*tinx+1].bk,tree[2*tinx+1].sum+tree[2*tinx].bk);
  tree[tinx]=x;
}
help query(int a[],help* tree,int tinx,int l,int r,int s,int e)
{
  if(l>e || s>r)
  {
   
    help x;
    x.sum=INT_MIN;
    x.msum=INT_MIN;
    x.fr=INT_MIN;
    x.bk=INT_MIN;
    return x;
  }
  if(l<=s && e<=r)
  {
    return tree[tinx];
  }
  int mid=(s+e)/2;
  help z=query(a,tree,2*tinx,l,r,s,mid);
  help y=query(a,tree,2*tinx+1,l,r,mid+1,e);
  help x;
   x.sum=z.sum+y.sum;
  x.msum=max(max(z.msum,y.msum),z.bk+y.fr);
  x.fr=max(z.fr,z.sum+y.fr);
  x.bk=max(y.bk,y.sum+z.bk);
  return x;
}
int main()
{
   int n;
   cin>>n;
   int a[n];
   for(int i=0;i<n;i++)
   cin>>a[i];
   help* tree = new help[4*n];
   btree(a,tree,1,0,n-1); 
   int m;
   cin>>m;
   while(m--)
   {
     int l,r;
     cin>>l>>r;
     help x=query(a,tree,1,l-1,r-1,0,n-1);
     cout<<x.msum<<endl;
   }
   delete []tree;
}
