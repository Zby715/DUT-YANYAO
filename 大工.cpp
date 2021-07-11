#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphics.h> //调用EasyX库
#define N 100
typedef struct horen //定义结构体
{
    int num;             //序号
    char name[25];       //姓名
    char sex[15];        //性别 0为女  1为男
    int ruxiao;          //入校时间
    char shenfen[100];   //在校身份
    char xi[100];        //专业
    char lingyu[100];    //研究领域
    char jianjie[1000];  //简介
    char chengjiu[1000]; //成就

} HOREN;
HOREN t[N];
void c1(HOREN *sp, int n);
void begin();
void menu();
int over();
void putin(HOREN *sp);
void putout(HOREN *sp, int n);
void c2(HOREN t[], int n);
int countnumber(HOREN t[]);
void c3(HOREN t[], int n);
void c4(HOREN *sp);
void c5(int n);
void flush();
int count;
//主函数
int main()
{
    int flag = 1;
    begin();
    menu();
    while (flag)
    {
        count = countnumber(t);
        int n;
        printf("******************************************************当前为菜单页面****************************************************\n请输入：");
        scanf("%d", &n);
        if (n == 1)
            c1(t, count);
        else if (n == 2)
            c2(t, count);
        else if (n == 3)
        {
            c3(t, count);
            putout(t, count + 1);
        }
        else if (n == 4)
        {
            c4(t);
            putout(t, count);
        }
        else if (n == 5)
        {
            c5(count);
            putout(t, count);
        }
        else if (n == 6)
            flag = over();
    }
    return 0;
}
//菜单图形化显示
void menu()
{

    //划线操作
    //常量文本的图形输出 菜单 自由窗体
    initgraph(500, 800, SHOWCONSOLE | NOCLOSE); // 创建一个宽 1280 x 高 640 像素的窗口
    setlinecolor(RGB(106, 64, 255));            // 1.设置当前画线颜色为 lan色
    setlinestyle(PS_DASH, 5);                   // 2.设置当前画线样式为 ----,宽度为 5
    line(20, 20, 450, 20);                      // 3.绘制线段 起点坐标(10,20)，终点坐标(450,20)  上
    line(20, 20, 20, 750);                      //左
    line(450, 20, 450, 750);                    //右
    line(20, 750, 450, 750);                    //下
    line(20, 160, 450, 160);
    setbkmode(TRANSPARENT);
    settextcolor(RGB(135, 206, 235));
    settextstyle(25, 0, _T("宋体"));

    outtextxy(100, 80, _T("  请输入操作的数字代号           "));
    outtextxy(100, 200, _T("   1.校友信息总览              "));
    outtextxy(100, 300, _T("   2.检索优秀校友              "));
    outtextxy(100, 400, _T("   3.添加或删除校友信息        "));
    outtextxy(100, 500, _T("   4.修改校友信息              "));
    outtextxy(100, 600, _T("   5.按入校年份排序            "));
    outtextxy(100, 700, _T("   6.退出程序                  "));
}
//总览
void c1(HOREN *sp, int n)
{
    printf("                                           大工优秀校友总览\n");
    printf("------------------------------------------------------------------------------------------------------------------------\n");
    FILE *fp;
    int i;
    fp = fopen("大工优秀校友.docx", "rb");
    if (((fp = fopen("大工优秀校友.docx", "r")) == NULL))
    {
        printf("File open error");
        exit(0);
    }
    for (i = 0; i < n; i++)
    {
        fread(sp, sizeof(HOREN), 1, fp);
        printf("△序号    姓名      性别     入校时间      在校身份              专业           研究领域                \n ");
        printf("*%-7d%-12s%-10s%-12d%-18s%-18s%s\n ", sp->num, sp->name, sp->sex, sp->ruxiao, sp->shenfen, sp->xi, sp->lingyu);
        printf("*简介：%s\n", sp->jianjie);
        printf(" *主要成就：%s\n", sp->chengjiu);
        printf("\n------------------------------------------------------------------------------------------------------------------------");
        printf("\n");
    }
    fclose(fp);
}
//开始图形显示
void begin()
{                                          //封面
    IMAGE img;                             //定义图片
    initgraph(1180, 650);                  // 创建一个宽 1180 x 高 650像素的窗口
    loadimage(&img, _T("首页.png"), 0, 0); //读取图片
    putimage(0, 0, &img);                  //显示图片
    getchar();                             // 暂停程序运行，查看输出结果
    closegraph();
}
//结束图片显示
int over()
{
    getchar();
    //封面
    IMAGE img;                             //定义图片
    initgraph(1180, 650);                  // 创建一个宽 1180 x 高 650像素的窗口
    loadimage(&img, _T("再见.png"), 0, 0); //读取图片
    putimage(0, 0, &img);                  //显示图片
    getchar();                             // 暂停程序运行，查看输出结果
    closegraph();                          // 关闭图形界面
    return 0;
}
//计算系统当前存储人数
int countnumber(HOREN t[])
{
    putin(t);
    int count = 0;
    int i;
    for (i = 0; (t[i].num) > 0; i++)
    {
        count++;
    }
    return count;
}
//文件读入结构体
void putin(HOREN *sp)
{
    FILE *fp;
    int i;
    fp = fopen("大工优秀校友.docx", "rb");
    if (((fp = fopen("大工优秀校友.docx", "r")) == NULL))
    {
        printf("File open error");
        exit(0);
    }
    for (i = 0; !feof(fp); i++)
    {
        fread(sp + i, sizeof(HOREN), 1, fp);
    }
    fclose(fp);
}
//结构体写入文件
void putout(HOREN *sp, int n)
{
    FILE *fp;
    int i;
    fp = fopen("大工优秀校友.docx", "w");
    if (((fp = fopen("大工优秀校友.docx", "w")) == NULL))
    {
        printf("File open error");
        exit(0);
    }
    for (i = 0; i < n; i++)
    {
        fwrite(sp + i, sizeof(HOREN), 1, fp);
    }
    fclose(fp);
}
//序号刷新
void flush()
{
    int i;
    for (i = 0; t[i].num != 0; i++)
        t[i].num = i + 1;
}
//检索
void c2(HOREN t[], int n) //检索
{
    HOREN *sp = t;
    int a, f = 1;
    while (f)
    {
        sp = t;
		printf("########################################################当前为检索页面#################################################\n按姓名搜索请输1  按入校年份搜索请输2   按专业搜索请输3  退出检索请输4\n");
        scanf("%d", &a);
        if (a == 1)
        {
            char na[20];
            printf("请输入姓名\n");
            scanf("%s", na);
            int i;
            int fla = 0;
            int num = 0;
            for (i = 0; i < n; i++)
            {
                if (strcmp(t[i].name, na) == 0)
                {
                    fla = 1;
                    sp = &t[i];
					num++;
                    printf("------------------------------------------------------------------------------------------------------------------------\n");
                    printf("△序号    姓名      性别     入校时间      在校身份              专业           研究领域                \n ");
                    printf("*%-7d%-12s%-10s%-12d%-18s%-18s%s\n ", sp->num, sp->name, sp->sex, sp->ruxiao, sp->shenfen, sp->xi, sp->lingyu);
                    printf("*简介：%s\n", sp->jianjie);
                    printf(" *主要成就：%s\n", sp->chengjiu);
                }
            }
            if (fla == 0)
                printf("查无此人\n");
            else
                printf("！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！共查询出%d人！！！！！！！！！！！！！！！！！！\n", num);
        }
        else if (a == 2)
        {
            int time;
            int num = 0;
            printf("请输入入校时间\n");
            scanf("%d", &time);
            int i;
            int fla = 0;
            for (i = 0; i < n; i++)
            {
                if (time == t[i].ruxiao)
                {
                    fla = 1;
                    num++;
                    sp = &t[i];
                    printf("------------------------------------------------------------------------------------------------------------------------\n");
                    printf("△序号    姓名      性别     入校时间      在校身份              专业           研究领域                \n ");
                    printf("*%-7d%-12s%-10s%-12d%-18s%-18s%s\n ", sp->num, sp->name, sp->sex, sp->ruxiao, sp->shenfen, sp->xi, sp->lingyu);
                    printf("*简介：%s\n", sp->jianjie);
                    printf(" *主要成就：%s\n", sp->chengjiu);
                }
            }
            if (fla == 0)
                printf("查无此人\n");
            else
                printf("！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！共查询出%d人！！！！！！！！！！！！！\n", num);
        }
        else if (a == 3)
        {
            char na[20];
            printf("请输入所在专业\n");
            scanf("%s", na);
            int i;
            int fla = 0;
            int num = 0;
            for (i = 0; i < n; i++)
            {
                if (strcmp(t[i].xi, na) == 0)
                {
                    fla = 1;
                    num++;
                    sp = &t[i];
                    printf("------------------------------------------------------------------------------------------------------------------------\n");
                    printf("△序号    姓名      性别     入校时间      在校身份              专业           研究领域                \n ");
                    printf("*%-7d%-12s%-10s%-12d%-18s%-18s%s\n ", sp->num, sp->name, sp->sex, sp->ruxiao, sp->shenfen, sp->xi, sp->lingyu);
                    printf("*简介：%s\n", sp->jianjie);
                    printf(" *主要成就：%s\n", sp->chengjiu);
                }
            }
            if (fla == 0)
                printf("查无此人\n");
            else
                printf("！！！！！！！！！！！！！！！！！！！！！！！！！！！共查询出%d人！！！！！！！！！！！！！！！！！\n", num);
        }
        else if (a == 4)
            f = 0;
    }
}
//增添或删除
void c3(HOREN *sp, int n)
{
    int d, flag = 1;

    printf("####################################################当前为增删页面##############################################\n");
    printf("增加校友请输1           删除校友请输2             \n");
    scanf("%d", &d);
    if (d == 1)
    {
        int i;
        for (i = 0; i < n; i++)
        {
            if (sp->num > 0)
                sp++;
        }
        sp->num = i + 1;
        printf("姓名：\n");
        scanf("%s", &sp->name);
        printf("性别：\n");
        scanf("%s", &sp->sex);
        printf("入校时间：\n");
        scanf("%d", &sp->ruxiao);
        printf("在校身份：\n");
        scanf("%s", &sp->shenfen);
        printf("专业：\n");
        scanf("%s", &sp->xi);
        printf("所在领域：\n");
        scanf("%s", &sp->lingyu);
        printf("简介：\n");
        scanf("%s", &sp->jianjie);
        printf("主要成就：\n");
        scanf("%s", &sp->chengjiu);
        flush();
    }
    else if (d == 2)
    {
        int i, j, num;
        printf("输入你想删除的人的序号：\n");
        scanf("%d", &num);
        for (i = 0; i < n; i++)
        {
            if (t[i].num == num)
            {
                for (j = i; t[j + 1].num != 0; j++)
                    t[j] = t[j + 1];
                t[j].num = 0;
            }
        }
        count -= 2;
        flush();
    }
}
//修改信息
void c4(HOREN *sp)
{
    printf("######################################################当前为修改页面###################################################\n");
    printf("请输入你要修改的校友的序号，要修改的选项\n");
    int n;
    scanf("%d", &n);
    int m;
    printf("姓名1     性别2      入校时间3     在校身份4     专业5      研究领域6      简介7     主要成就8\n");
    scanf("%d", &m);
    char s[1000] = {"\0"};
    int time;
    if (m == 1)
    {
        printf("请输入姓名：");
        getchar();
        scanf("%s", s);
        strcpy(t[n - 1].name, s);
    }
    else if (m == 2)
    {
        printf("请输入性别：");
        getchar();
        scanf("%s", s);
        strcpy(t[n - 1].sex, s);
    }
    else if (m == 3)
    {
        printf("请输入入校时间：");
        getchar();
        scanf("%d", &time);
        t[n - 1].ruxiao = time;
    }
    else if (m == 4)
    {
        printf("请输入在校身份：");
        getchar();
        scanf("%s", s);
        strcpy(t[n - 1].shenfen, s);
    }
    else if (m == 5)
    {
        printf("请输入专业：");
        getchar();
        scanf("%s", s);
        strcpy(t[n - 1].xi, s);
    }
    else if (m == 6)
    {
        printf("请输入研究领域：");
        getchar();
        scanf("%s", s);
        strcpy(t[n - 1].lingyu, s);
    }
    else if (m == 7)
    {
        printf("请输入简介：");
        getchar();
        scanf("%s", s);
        strcpy(t[n - 1].jianjie, s);
    }
    else if (m == 8)
    {
        printf("请输入主要成就：");
        getchar();
        scanf("%s", s);
        strcpy(t[n - 1].chengjiu, s);
    }
}
//按入校时间排序
void c5(int n)
{
    HOREN T;
    int k;
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (k = i, j = i + 1; j < n; j++)
            if (t[j].ruxiao < t[k].ruxiao)
            {
                k = j;
            }
        T = t[i];
        t[i] = t[k];
        t[k] = T;
    }
    flush();
}
