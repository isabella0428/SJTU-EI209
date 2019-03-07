//定义模板类
template<class Type>
class hfTree {
public:
    //定义节点类
    struct Node {
        Type data;                  //节点数据类型
        int weight;                 //节点所对应的字符出现次数
        int parent, left, right;    //节点的父亲，左儿子右儿子在数组中的位置
    };
private:
    Node *elem;                     //Node类型的数组指针
    int length;                     //字符个数

public:
    //定义哈夫曼编码类
    struct hfCode {
        Type data;                  //字符
        string Code;                //对应的哈夫曼编码
    };

    hfTree(const Type *x, const int *w, int size);  //根据给定数值初始化哈弗曼树

    void getCode(hfCode result[]) const;            //返回哈弗曼编码数组的数组名指针

    hfTree(const hfTree &myTree);                   //哈弗曼树的拷贝构造函数

    ~hfTree() { delete[] elem; }                    //析构函数

    Node *GetElem() const { return elem; }          //返回哈弗曼树的节点数组名指针

    int GetLength() const { return length; }        //返回哈弗曼树的字符个数
};

//定义哈夫曼树的拷贝构造函数
template <class Type>
hfTree<Type>::hfTree(const hfTree<Type> & myTree)
{
    delete [] elem;                         //释放指针内存
    elem = new Node[myTree.GetLength()];    //申请新的空间
    for(int i=0;i<myTree.GetLength();++i)
    {
        elem[i] = myTree.GetElem()[i];      //对应元素赋值
    }
    length = myTree.length;                 //长度赋值
}

//定义哈夫曼树的初始化函数
template <class Type>
hfTree<Type>::hfTree(const Type *v,const int *w,int size)
{
    const int MAX_INT = 32767;              //出现次数的上界
    int min1,min2;                          //出现次数最少的两个
    int x,y;                                //x对应出现次数第二少的，y对应最少的

    length = 2*size;
    elem = new Node[length];

    for(int i=size;i<length;++i)            //叶节点的字符，出现次数和父母孩子所在位置初始化
    {
        elem[i].weight = w[i-size];
        elem[i].data = v[i-size];
        elem[i].parent = elem[i].left=elem[i].right=0;
    }
    for(int i=0;i<size;++i)            //将非叶节点的数值初始化为'\0'(为了之后打印方便)
    { elem[i].data = '\0'; }

    //合并树
    for(int i=size-1;i>0;--i)
    {
        min1=min2=MAX_INT; x=y=0;           //通过遍历挑选出出现次数最少的两个节点
        for(int j=i+1;j<length;++j) {
            if (elem[j].parent == 0) {
                if (elem[j].weight < min1) {
                    min2 = min1;
                    min1 = elem[j].weight;
                    x = y;
                    y = j;
                }
                else if (elem[j].weight < min2) {
                    min2 = elem[j].weight;
                    x = j;
                }
            }
        }
        elem[i].weight = min1 + min2;               //进行对赋值处理
        elem[i].left = x;
        elem[i].right = y;
        elem[i].parent = 0;
        elem[x].parent = i;
        elem[y].parent = i;
    }
}



//生成哈夫曼编码
template<class Type>
void hfTree<Type>::getCode (hfCode result[]) const
{
    int size = length/2;
    int p,s;                                //s为目前处理的节点   p是s的父亲节点
    for(int i=size;i<length;++i)
    {
        result[i-size].data = elem[i].data;
        result[i-size].Code ="";
        p = elem[i].parent; s=i;
        while(p)
        {
            if(elem[p].left==s)             //若s为父亲节点的左儿子，则在编码最前面加'0'
                result[i-size].Code = '0'+result[i-size].Code;
            else                            //若s为父亲节点的右儿子，则在编码最前面加'1'
                result[i-size].Code = '1' + result[i-size].Code;
            s = p;
            p = elem[p].parent;
        }
    }
}
