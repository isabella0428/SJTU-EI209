int main() {
    cout<<"Welcome to Huffman System!"<<endl;               //输出提示信息
    cout<<"I(initialization) E(encoding) D(Decoding) P(Code Printing) T(Tree printing)"<<endl;
    char Command;                                           //输入命令
    in>>Command;

    hfTree<char>* MyTree;                                   //利用默认构造函数定义一棵树

    hfTree<char>* (*I)()  = initial;                        //利用函数指针实现主菜单的功能
    void (*E)(const hfTree<char> & MyTree) = Encoding;
    void (*D)(const hfTree<char> & MyTree) = Decoding;
    void (*P)(const hfTree<char> &MyTree) = CodePrinting;
    void (*T)(const hfTree<char> & MyTree) = Treeprinting;

    int flag = false;
    while(Command != 'Q')                         //直到输入'Q'命令后再退出循环
    {   if(Command != 'I' && flag == false)
        //未初始化时无法进行其他操作，打印错误信息并提示用户重新输入
        cout<<"Not Initialized yet!!"<<endl;
        if(Command=='I' )
        {
            MyTree = initial();                   //初始化哈弗曼树
            flag = true;
            cout<<"Initialization ended!"<<endl;
        }

        if(Command == 'E'&&flag != 0 ) {          //根据已建好的哈弗曼树进行编码并将结果输出到文件中
            Encoding(*MyTree);
            cout<<"Encoding ended!"<<endl;
        }


        if(Command == 'D'&&flag != 0 )            //读入文件进行解码，并将解码的结果输出到文件中
        {Decoding(*MyTree);
         cout<<"Decoding ended!"<<endl;}

        if(Command == 'P'&&flag != 0)             //将编码按要求打印在屏幕上并输出到文件中
        {CodePrinting(*MyTree);
         cout<<"Code Printing ended!"<<endl;}

        if(Command == 'T'&&flag != 0)             //将已建好的哈夫曼树以凹入表的形式输出到文件中
        {Treeprinting(*MyTree);
        cout<<"Tree Printing Ended!"<<endl;}

        in>>Command;
    }
    return 0;
}
