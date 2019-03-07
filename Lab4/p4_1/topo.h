//
// Created by Lyu Yi on 2018/12/23.
//

#ifndef INC_4_1_1_H
#define INC_4_1_1_H

#include <iostream>
#include <map>
#include <vector>
#include <stack>
#include <fstream>
using namespace std;

struct node
{
    char name[10];            //课程名
    int  credit;              //总学分
};

int num_terms, t_max_credit, t_Course, t_E;     //总学期数，学分上限，必修课数，边数
vector<node> G[1000];                           //边表
map<string, int> mp;                            //映射表，从字符型到整型

void create_graph()
{
    int i;
    cout<<"\t\t\t欢迎使用教学计划编制系统\n";
    cout<<"输入学期总数: ";
    cin>>num_terms;
    cout<<"请输入学期的学分上限: ";
    cin>>t_max_credit;
    cout<<"请输入教学计划的课程数: " ;
    cin>>t_Course;
    cout<<"请输入各个课程的先修课程的总和(边总数): ";
    cin>>t_E;
    cout<<"请输入"<<t_Course<<"个课程的课程号(最多30个字符,大写字母+数字如C10)\n";
    node data;
    for(i = 1; i <= t_Course; i++)
    {
        cout<<"请输入第"<<i<<"个";
        cin>>data.name;
        G[i].push_back(data);               //建立边表
        mp[G[i][0].name] = i;               //建立映射
    }
    cout<<"请输入"<<t_Course<<"个课程分别对应的学分值";
    for(i = 1; i <= t_Course; i++) cin>>G[i][0].credit;
    cout<<"请输入下列课程的先修课程(输入以#结束)\n";
    char s[30];
    for(i = 1; i <= t_Course; i++)
    {
        cout<<G[i][0].name<<"的先修课程: ";
        while(true)
        {
            cin>>s;
            if(s[0] == '#') break;          //输入示例：c03 #
            G[i].push_back(G[mp[s]][0]);    //将先修课程插入到对应课程的vector中
        }
    }
    cout<<"\t\t\t录入数据成功\n";
}


void solve1(int ans[])                      //课程数平均
{   ofstream out;
    out.open("Schedule.txt");
    int q = 1, cnt = 0;
    out<<"Strategy 1:"<<endl;
    while (q <= num_terms)
    {
        int num = t_Course / num_terms;
        out<<"\n第"<<q<<"个学期应学课程: ";
        while(num--)
        {
            out<<G[ans[cnt++]][0].name<<(num != 0 ? ' ' : '\n');
        }
        if (q == num_terms) cout<<"OK Over!\n";
        q++;
    }
    out.close();
}

void solve2(int ans[])
{   ofstream out;
    out.open("Schedule.txt");
    int q = 1, cnt = 0;
    out<<"Strategy 2"<<endl;
    while (q <= num_terms)
    {
        int C = G[ans[cnt]][0].credit;
        out<<"\n第"<<q<<"个学期应学课程: ";
        while(cnt < t_Course && C <= t_max_credit)      //不超过学分上限
        {
            out<<G[ans[cnt]][0].name;
            if(cnt+1 < t_Course) C = C + G[ans[cnt+1]][0].credit;
            cnt++;
        }
        if(cnt >= t_Course || q == num_terms)
        {
            cout << endl;
            cout<<"OK Over!\n";
            break;
        }
        q++;
    }
    out.close();
}

void topo_sort()
{
    int i, j, Innode[1000];
    for(int i = 0;i < 1000; i++)
        Innode[i] = 0;                         //初始化
    for(i = 1; i <= t_Course; i++)
    {
        int k = G[i].size();                //vector内置函数
        for(j = 1; j < k; j++)
            Innode[mp[G[i][j].name]]++;        //计算先修课程的门数
    }

    int ans[1000], cnt = 0;                 //初始化
    for(int i = 0;i < 1000; i++)
        ans[i] = 0;

    stack<int> s;
    for(i = 1; i <= t_Course; i++)
    {
        if(!Innode[i]) s.push(i);              //入度不为零，入栈
    }

    while(!s.empty())
    {
        int cur = s.top(); s.pop();
        ans[cnt++] = cur;
        int k = G[cur].size();
        for(j = 1; j < k; j++)
        {
            int num = mp[G[cur][j].name];       //更新入度状态
            Innode[num]--;
            if(!Innode[num]) s.push(num);          //如果入度为零，入栈
        }
    }
    if(cnt != t_Course) cout<<"Error!";
    else
    {
        puts("OK!");
        while(true)
        {
            cout<<"\n\t\t\t请选择功能:\n";
            cout<<"\t\t\t1.平均分配\n";
            cout<<"\t\t\t2.靠前分配\n";
            cout<<"\t\t\t3.退出\n";
            int strategy;
            cin>>strategy;
            switch(strategy)
            {
                case 1: solve1(ans); break;
                case 2: solve2(ans); break;
            }
            if(strategy == 3) break;
        }
    }
}

#endif //INC_4_1_1_H
