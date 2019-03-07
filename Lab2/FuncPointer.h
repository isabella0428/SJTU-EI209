hfTree<char>* initial()                                     //初始化哈弗曼树
{
    int n;
    cout<<"Please input the number of characters:"<<endl;
    in>>n;                                                  //输入叶节点个数
    in.get();
    cout<<"Please input the characters:(no spaces)"<<endl;
    char * chars;
    chars = new char [n + 1];                               //输入叶节点的值
    in.getline(chars,n + 1);


    int * weights;
    weights = new int [n];
    cout<<"Please input the weights:(separated by spaces)"<<endl;
    for(int i=0;i<n;++i)                                    //输入节点的出现的次数
    {
        in>>weights[i];
    }
    ofstream out2;                                          //重载输出流
    out2.open("hfmTree.txt");
    hfTree<char>* MyTree = new hfTree<char>(chars,weights,n);
    out2<<"characters:"<<endl;
    for(int i=0;i<n;i++)
    {
        out2<<chars[i]<<" ";                                //输出字符
    }
    out2<<endl;

    out2<<"weights:"<<endl;
    for(int i=0;i<n;i++)
    {out2<<weights[i]<<" ";}                                //输出出现次数
    out2<<endl;

    out2<<"parents:"<<endl;
    for(int i=n;i<2*n;i++)
    {out2<<MyTree -> GetElem()[i].parent<<" ";}      //输出父亲节点在数组中所在位置的下标

    out2<<endl;
    return MyTree;
}


//编码给定文件
void Encoding(const hfTree<char> & MyTree)
{   ifstream in3;
    in3.open("plainFile.txt");                  //重载输入流
    ofstream out3;
    out3.open("codeFile.txt");                  //重载输出流
    int num = MyTree.GetLength()/2;
    hfTree<char>::hfCode result[num];
    MyTree.getCode(result);

    char now= in3.get();
    while(now!=EOF)                             //读入文件中的字符
    {
        for(int i = 0;i<num;i++)
        {
            if(now == result[i].data)
            {out3<<result[i].Code<<" ";         //输出字符对应编码
            break;}
        }
        now = in3.get();
    }
    out3.close();
    in3.close();
}


//解码给定文件
void Decoding(const hfTree<char> &MyTree)
{
    ifstream in4;                           //重载输入流
    ofstream out4;                          //重载输出流
    in4.open("codeFile.txt");
    out4.open("textFile.txt");
    string cur;
    int num = MyTree.GetLength()/2;
    hfTree<char>::hfCode result[num];
    MyTree.getCode(result);

    for(int i = 0;i < MyTree.GetLength(); ++i)          //文件输入编码
    {
        getline(in4,cur,' ');
        for(int i = 0;i < MyTree.GetLength(); ++i)
        {
            if(cur == result[i].Code)
            {out4<<result[i].data; break;}              //文件输出编码对应字符
        }
    }
    in4.close();
    out4.close();
}


//打印编码
void CodePrinting(const hfTree<char> &MyTree)
{
    ifstream in5;                           //重载文件输入流
    in5.open("codeFile.txt");
    ofstream out5;                          //重载文件输出流
    out5.open("codePrint.txt");
    int sum = 0;
    char cur = in5.get();
    while(cur != EOF)                       //读入文件中的编码
    {
        if(cur == ' ')                      //跳过用作分割的空格
        {
            cur = in5.get();
            continue;
        }
        if(sum < 50)                        //每行打印不超过50个字符
        {
            cout<<cur;
            sum++;
        }
        else
        {
            sum = 1;
            cout<<endl;
            cout<<cur;
        }
        cur = in5.get();
    }
    in5.close();
    out5.close();
    cout<<endl;
}

void PrintHelp (hfTree<char>::Node p,const hfTree<char> & MyTree, ofstream& out6,string ss);


//利用递归以凹入表的形式打印哈弗曼树
void Treeprinting(const hfTree<char> & MyTree)
{
   ofstream out6;                               //重载文件输出流
   out6.open("treePrint.txt");
   string ss = "";
   PrintHelp(MyTree.GetElem()[1],MyTree, out6,ss);      //递归打印哈弗曼树
}

void PrintHelp (hfTree<char>::Node p,const hfTree<char> & MyTree, ofstream& out6,string ss)
{
    if(p.parent != 0)
        ss += "\t";                                             //利用空格表示层次关系
    if (p.left == 0)                                            //叶节点执行完则输出后返回
    {if (p.data != '\0')
        out6 << ss<<p.weight << "(" << p.data << ")"<<endl;     //如果为叶节点则输出节点值出现次数和字符
    else
        out6 << ss<<p.weight<<endl;                             //如果为非叶节点则仅输出节点值出现次数
    return;
    }
    PrintHelp(MyTree.GetElem()[p.left], MyTree, out6,ss);
    if (p.data != '\0')
        out6 <<ss<< p.weight << "(" << p.data << ")"<<endl;     //如果为叶节点则输出节点值出现次数和字符
    else
        out6 << ss<<p.weight<<endl;                             //如果为非叶节点则仅输出节点值出现次数
    PrintHelp(MyTree.GetElem()[p.right], MyTree, out6,ss);
}
