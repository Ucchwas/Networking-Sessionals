#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>
#include<cstring>
#include<string>
#include<iostream>
using namespace std;
int ch[1000];
int k=1,p=0,h=1;
int dow[1000];
string task1(string name,int m)
{
    int s=name.size();
    int p=s%m;
    int z=m-p;

    for(int i=0; i<z; i++)
        name.append("~");
    return name;
}

void task2(string name,int m)
{
    int s=name.size();
    for(int j=1; j<=s; j++)
    {
        for (int i = 7; i >= 0; --i)
        {
            ch[k]=putchar( (name[j-1] & (1 << i)) ? '1' : '0' )-48;
            //printf(" %d ",ch[k]);
            k++;
        }
        if(j%m==0)
            printf("\n");
    }
}

void task3(int c[100],int m)
{
    int a, b, d, r = 0, d1; //Max bits here i kept is 30
    //cout << " Enter the No of Data Bits you want to Enter : ";
    a=8*m;
    while (a + r + 1 > pow (2, r))
    {
        r++;
    }
    /*  cout << "No of data bits to be added " << r << " : Total Bits :" << a +
           r << endl;
      cout << " Enter the Data Bits One by One :" << endl;
      //for (int i = 1; i <= a; ++i)
         // cin >> c[i];
      cout << endl << " Data bits entered : ";
      for (int i = 1; i <= a; ++i)
          cout << c[i] << " ";
      cout << endl;*/
    int data[a + r];
    d = 0;
    d1 = 1;
    for (int i = 1; i <= a + r; ++i)
    {
        if ((i) == pow (2, d))
        {
            data[i] = 0;
            ++d;
        }
        else
        {
            data[i] = c[d1];
            ++d1;
        }
    }
    //cout << " Data Bits are Encoded with Parity bits(0): \n";
    //for (int i = 1; i <= a + r; ++i)
       // cout << data[i] << " ";
    d1 = 0;
    int min, max = 0, parity, s, j;
    /*Parity Bit Calculation */
    for (int i = 1; i <= a + r; i = pow (2, d1))
    {
        ++d1;
        parity = 0;
        j = i;
        s = i;
        min = 1;
        max = i;
        for (j; j <= a + r;)
        {
            for (s = j; max >= min && s <= a + r; ++min, ++s)
            {
                if (data[s] == 1)
                    parity++;
            }
            j = s + i;
            min = 1;
        }
        if (parity % 2 == 0) // Even Parity
        {
            data[i] = 0;
        }
        else
        {
            data[i] = 1;
        }
    }
    //int d[100];
    //cout << endl << " Hamming codeword bits for even parity are : \n";
    for (int i = 1; i <=a + r; ++i){
        cout << data[i] ;
        dow[h]=data[i];
        h++;
    }
    cout << endl;
    p=a+r;
}

int main()
{
    string n,g;
    int m;
    printf("Enter Data Strings:");
    getline(cin,n);
    printf("Enter number of data bytes in a row:");
    cin>>m;
    printf("Enter generator polynomial:");
    cin>>g;
    printf("Data strings after padding:");
    string t2=task1(n,m);
    cout<<t2<<endl;
    printf("data block:\n");
    task2(t2,m);
    int b[8*m];
    printf("\n");
    printf("Data block after adding check bits:\n");
    for(int j=1; j<=t2.size()/m; j++)
    {
        for(int i=1; i<=8*m; i++)
        {
            b[i]=ch[8*(j-1)+i];
        }
        task3(b,m);
    }
    /*for(int i=1,j=9;j<=8*m+9,i<=8*m;j++,i++)
        b[i]=ch[j];
    task3(b,m);*/
    int u=t2.size()/m;
    int z[1000];
    int k=1;
    for(int i=1;i<=p;i++){
        for(int j=1;j<=u;j++){
           z[k]=dow[p*(j-1)+i];
           // printf("%d",dow[j]);
           k++;
        }
    }
    printf("Data bits after column-wise serialization:\n");
    for(int i=1;i<=p*u;i++)
        printf("%d",z[i]);
     int i,j,l;
    k=0;
    //Get Frame
    int fs;
    //cout<<"\n Enter Frame size: ";
    //cin>>fs;

    int f[20];

    //cout<<"\n Enter Frame:";
    for(i=0;i<fs;i++)
    {
       // cin>>f[i];
    }

    //Get Generator
    /*int gs;
    cout<<"\n Enter Generator size: ";
    cin>>gs;

    int g[20];

    cout<<"\n Enter Generator:";
    for(i=0;i<gs;i++)
    {
        cin>>g[i];
    }*/

    cout<<"\n Sender Side:";
    cout<<"\n Frame: ";
    for(i=0;i<fs;i++)
    {
        cout<<f[i];
    }
    /*cout<<"\n Generator :";
    for(i=0;i<gs;i++)
    {
        cout<<g[i];
    }*/

    //Append 0's
    int rs=g.size()-1;
    //cout<<"\n Number of 0's to be appended: "<<rs;
    for (i=fs;i<fs+rs;i++)
    {
        f[i]=0;
    }

    int temp[20];
    for(i=0;i<20;i++)
    {
        temp[i]=f[i];
    }

    cout<<"\n Message after appending 0's :";
    for(i=0; i<fs+rs;i++)
    {
        cout<<temp[i];
    }

    //Division
    for(i=0;i<fs;i++)
    {
        j=0;
        k=i;
        //check whether it is divisible or not
        if (temp[k]>=g[j])
        {
            for(j=0,k=i;j<g.size();j++,k++)
            {
                if((temp[k]==1 && g[j]==1) || (temp[k]==0 && g[j]==0))
                {
                    temp[k]=0;
                }
                else
                {
                    temp[k]=1;
                }
            }
        }
    }

    //CRC
    int crc[15];
    for(i=0,j=fs;i<rs;i++,j++)
    {
        crc[i]=temp[j];
    }

    cout<<"\n CRC bits: ";
    for(i=0;i<rs;i++)
    {
        cout<<crc[i];
    }

    cout<<"\n Transmitted Frame: ";
    int tf[15];
    for(i=0;i<fs;i++)
    {
        tf[i]=f[i];
    }
    for(i=fs,j=0;i<fs+rs;i++,j++)
    {
        tf[i]=crc[j];
    }
    for(i=0;i<fs+rs;i++)
    {
        cout<<tf[i];
    }

    cout<<"\n Receiver side : ";
    cout<<"\n Received Frame: ";
    for(i=0;i<fs+rs;i++)
    {
        cout<<tf[i];
    }

    for(i=0;i<fs+rs;i++)
    {
        temp[i]=tf[i];
    }

    //Division
    for(i=0;i<fs+rs;i++)
    {
        j=0;
        k=i;
        if (temp[k]>=g[j])
        {
            for(j=0,k=i;j<g.size();j++,k++)
            {
                if((temp[k]==1 && g[j]==1) || (temp[k]==0 && g[j]==0))
                {
                    temp[k]=0;
                }
                else
                {
                    temp[k]=1;
                }
            }
        }
    }

    cout<<"\n Reaminder: ";
    int rrem[15];
    for (i=fs,j=0;i<fs+rs;i++,j++)
    {
        rrem[j]= temp[i];
    }
    for(i=0;i<rs;i++)
    {
        cout<<rrem[i];
    }

    int flag=0;
    for(i=0;i<rs;i++)
    {
        if(rrem[i]!=0)
        {
            flag=1;
        }
    }

    if(flag==0)
    {
        cout<<"\n Since Remainder Is 0 Hence Message Transmitted From Sender To Receriver Is Correct";
    }
    else
    {
        cout<<"\n Since Remainder Is Not 0 Hence Message Transmitted From Sender To Receriver Contains Error";
    }
    getch();
}

