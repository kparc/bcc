#include"m.h"

typedef struct pB pB;typedef pB*B;  //!< forward decl for recursion
typedef struct pB{S a;B n;SZ s;}pB; //!< memblock: addr,next,size
typedef struct {B f;B u;B frsh;SZ top;}pHP;typedef pHP*HP;//!< heap: first free block,first used,first available blank,top free addr
static HP hp;ZS HMAX;static SZ heap_split_thresh,heap_alignment,heap_max_blocks;

#ifdef TA_TEST
//#define DBG(a...) O(a)
#define DBG(a...)

#ifndef STRESS
#define CHK(fn)
#else
#define CHK(fn) if(!ta_check())O("ta_check() fail %s\n",fn),exit(1);
#endif

#include<stdlib.h>
#include<sys/types.h>
#include<sys/sysctl.h>
#include<sys/mman.h>
#include<errno.h>

#define GB(n) (n>>30)

SZ phy(){SZ m=0;
#if defined(__EMSCRIPTEN__)
 m=__builtin_wasm_memory_size(0)*64*1024;
#elif defined(__linux__) || defined(__OpenBSD__)
 m=sysconf(_SC_PHYS_PAGES))*sysconf(_SC_PAGE_SIZE);
#elif defined(__APPLE__)
 SZ ln=sizeof(m);sysctlbyname("hw.memsize",&m,&ln, NULL, 0);
#endif
 R m;}

S ma(SZ n){S r=mmap(0,n,PROT_READ|PROT_WRITE,MAP_ANON|MAP_PRIVATE,0,0);$(r==MAP_FAILED,O("%s (n=%zu)\n",strerror(errno),n),exit(1))R r;}

#else
#define DBG(a...)
#define CHK(fn)
#endif

#ifdef TA_MAIN
I ta_test(){
  S base;SZ
    phys=phy(),
    heap=phys>>2,
    nblk=256,
    splt=16,
    algn=sizeof(S);
    base=ma(heap);

 ta_init(base,base+heap,nblk,splt,algn);

 O("phys %zug heap %zug base %p hmax %p\n",GB(phys),GB(heap),base,base+heap);

 R 0;}

I main(I c,char**v){R ta_test();}
#endif

V ta_init(S base,S max,SZ hpb,SZ splt,SZ algn) {
    hp=(HP)base;
    HMAX = max,
    heap_max_blocks = hpb,
    heap_split_thresh = splt,
    heap_alignment = algn;

    hp->f=hp->u=0;
    hp->frsh=(B)(hp+1);
    hp->top=(SZ)(hp->frsh+hpb);

    B b=hp->frsh;
    SZ i=heap_max_blocks-1;
    W(i--)b->n=b+1,++b;
    b->n=0;}

ZV insert_block(B b){
    DBG("insert_block %p\n",b);
#ifndef TA_NO_COMPACT
    B p=hp->f,prev=0;//< if compaction is enabled, insert block into free list, sorted by addr
    W(p){$((SZ)b->a<=(SZ)p->a,DBG("insert %p\n",p);break);prev=p,p=p->n;}
    $(prev,prev->n=b){hp->f=b;}
    b->n=p;}
#else
    b->n=hp->f,hp->f=b;}//<! if disabled, add block has new head of the free list
#endif

#ifndef TA_NO_COMPACT
ZV release_blocks(B sc,B to){DBG("release_blocks %p %p\n",sc,to);B nxt;W(sc!=to)nxt=sc->n,sc->n=hp->frsh,hp->frsh=sc,sc->a=(S)0,sc->s=0,sc=nxt;}
ZV compact(){
    DBG("compact()\n");
    B ptr=hp->f,prev,scan;
    W(ptr){
        prev=ptr;scan=ptr->n;
        W(scan&&(SZ)prev->a+prev->s==(SZ)scan->a){DBG("compact() merge=%p\n",scan);prev=scan,scan=scan->n;}//merge
        if(prev!=ptr){
            SZ new_size = (SZ)prev->a-(SZ)ptr->a + prev->s;
            DBG("compact() new_size=%zu\n",new_size);
            ptr->s = new_size;
            B next = prev->n;
            release_blocks(ptr->n,prev->n);
            ptr->n=next;//relink
        }
        ptr = ptr->n;}}
#endif

V ta_free(V*p){
    DBG("ta_free %p:\n",p);
    B b=hp->u,prev=0;
    W(b){//DBG("...ta_free b=%p -> ",b);
        if(p==b->a){
            if(prev){
                prev->n=b->n;
            }else{
                hp->u=b->n;
            }
            INSERT(b)
            DBG("1\n");CHK("ta_free1");
        }
        prev=b;b=b->n;
    }
    DBG("0\n");CHK("ta_free0");}

static B alloc_block(SZ n){DBG("alloc_block(%zu):\n",n);ALGN(n)
    B ptr=hp->f,prev=0;SZ tp=hp->top;
    W(ptr){
        const C is_top=((SZ)ptr->a+ptr->s>=tp)&&((SZ)ptr->a+n<=(SZ)HMAX);
        if(is_top||ptr->s>=n){
            $(prev,prev->n=ptr->n)hp->f=ptr->n;
            ptr->n=hp->u,hp->u=ptr;
            if(is_top){//resize top block
                ptr->s=n,hp->top=(SZ)ptr->a+n;
#ifndef TA_NO_SPLIT
            }else if(hp->frsh){
                SZ excess = ptr->s-n;
                $(excess >= heap_split_thresh,
                    ptr->s   = n;
                    B split  = hp->frsh;
                    hp->frsh  = split->n;
                    split->a = (S)((SZ)ptr->a+n);
                    DBG("split %p\n",split->a);
                    split->s = excess;
                    INSERT(split)
                );//else;
#endif
            }
            R ptr;}
        prev = ptr,
        ptr  = ptr->n;}

    // no matching free blocks, see if any other blocks available
    SZ new_top=tp+n;
    R hp->frsh&&new_top<=(SZ)HMAX?
        ptr       = hp->frsh,
        hp->frsh  = ptr->n,
        ptr->a    = (S)tp,
        ptr->n    = hp->u,
        ptr->s    = n,
        hp->u     = ptr,
        hp->top   = new_top,
        ptr:0;}

V*ta_alloc(SZ n){DBG("ta_alloc %zu...\n",n);B b=alloc_block(n);S r=b?b->a:0;DBG("ta_alloc %p\n",r);CHK("ta_alloc")R r;}
ZV*ta_memclear(V*p,SZ n){SZ*ptrw=(SZ*)p,numw=(n&-SZT)/SZT;W(numw--)*ptrw++=0;n&=SZT-1;S ptrb=(S)ptrw;W(n--)*ptrb++=0;R p;}
V*ta_calloc(SZ n,SZ sz){DBG("ta_calloc(%zu,%zu)\n",n,sz);B b=alloc_block(n*=sz);S r=b?ta_memclear(b->a,n):(S)0;DBG("ta_calloc -> %p\n",r);CHK("ta_calloc");R r;}

#ifdef TA_TEST
static SZ ta_count(B b){SZ c=0;W(b)b=b->n,c++;R c;}
CNT(ta_avail,f)CNT(ta_used,u)CNT(ta_fresh,frsh)
C ta_check(){R heap_max_blocks==ta_avail()+ta_used()+ta_fresh();}
#endif

//:~
