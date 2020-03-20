//
//MUZAFFER KADİR YILMAZ 348296
//
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cmath>

using namespace std;

class image
{
    public:
    image();
    image(string file);
    unsigned char w,h;
    int width,height,pxNumber;
    string inputFile;
    void print();
    void takeToMatris();
    void thresholdMask(int value);
    void sobelMask();
    char matris[255][255];

    friend ostream& operator>>(string& FilePath,image& img);
    friend ostream& operator<<(string& FilePath,image& img);


    image operator+(image& img2)
    {
        image out;
        out=img2;
        for(int i = 0;i<width;i++)
        {
            for(int j=0; j<height;j++)
            {
                if(matris[j][i]==1||img2.matris[j][i]==1)
                out.matris[j][i]=1;
                else
                out.matris[j][i]=0;
            }
        }
        return out;
    }
    image operator*(image& img2)
    {
        image out;
        out=img2;
        for(int i = 0;i<width;i++)
        {
            for(int j=0; j<height;j++)
            {
                if(matris[j][i]==1 && img2.matris[j][i]==1)
                out.matris[j][i]=1;
                else
                out.matris[j][i]=0;
            }
        }
        return out;
    }
    image operator!()
    {
        image out;
        out.width=width;
        out.height=height;
        for(int i = 0;i<width;i++)
        {
            for(int j=0; j<height;j++)
            {
                if(matris[j][i]==1)
                out.matris[j][i]=0;
                else
                out.matris[j][i]=1;
            }
        }
        return out;
    }





};
image::image(){}

image::image(string file)
{
    inputFile=file;
    ifstream input(inputFile,ios::binary);
    input>>h;
    input>>w;
    width=(int)w;
    height=(int)h;
    pxNumber=width*height;
    cout<<(int)width<<"-"<<(int)height<<endl;
    input.close();
}

void image::takeToMatris()
{
    char buffer[pxNumber];
    ifstream input(inputFile,ios::binary);
    input.read(buffer,pxNumber);
    input.close();
    int px=0;
    for(int i = 0;i<width;i++)
    {
        for(int j=0; j<height;j++)
        {
            matris[j][i]=buffer[px];
            px+=1;
        }
    }
}

void image::print()
{
    ofstream output("output.txt", ios::binary);

    for(int i = 0;i<width;i++)
    {
        for(int j=0; j<height;j++)
        {
            //cout<<(int)matris[j][i];
            if(matris[i][j]==1)
            output<<"*";
            else
            output<<"-";

        }
        output<<endl;
        //cout<<endl;
    }
    output.close();
}

void image::thresholdMask(int value)
{

    for(int i = 0;i<width;i++)
    {
        for(int j=0; j<height;j++)
        {

            if(matris[j][i]>=value)
            {
            matris[j][i]=1;
            cout<<"*";
            }
            else if(matris[j][i]<value)
            {
            matris[j][i]=0;
            cout<<"-";
            }
        }
        cout<<endl;
    }
}

void image::sobelMask()
{
    char sobelX[3][3]={{1,0,-1},{2,0,-2},{1,0,-1}};
    char sobelY[3][3]={{1,2,1},{0,0,0},{-1,-2,-1}};
    char matrisX[255][255];
    char matrisY[255][255];

    for(int i = 1;i<width-1;i++)
    {
        for(int j=1; j<height-1;j++)
        {
        matrisX[j][i]=
        matris[j-1][i-1]*sobelX[0][0]+matris[j][i-1]*sobelX[1][0]+
        matris[j+1][i-1]*sobelX[2][0]+matris[j-1][i]*sobelX[0][1]+
        matris[j][i]*sobelX[1][1]+matris[j+1][i]*sobelX[2][1]+
        matris[j-1][i+1]*sobelX[0][2]+matris[j][i+1]*sobelX[1][2]+
        matris[j+1][i+1]*sobelX[2][2];

        matrisY[j][i]=
        matris[j-1][i-1]*sobelY[0][0]+matris[j][i-1]*sobelY[1][0]+
        matris[j+1][i-1]*sobelY[2][0]+matris[j-1][i]*sobelY[0][1]+
        matris[j][i]*sobelY[1][1]+matris[j+1][i]*sobelY[2][1]+
        matris[j-1][i+1]*sobelY[0][2]+matris[j][i+1]*sobelY[1][2]+
        matris[j+1][i+1]*sobelY[2][2];
        }
    }
    for(int i = 1;i<width-1;i++)
    {
        for(int j=1; j<height-1;j++)
        {
            matris[j][i]=sqrt((matrisX[j][i]*matrisX[j][i])+(matrisY[j][i]*matrisY[j][i]));
        }
    }
}

ostream& operator>>(string& FilePath,image& img)
{
    img.inputFile=FilePath;
    ifstream input(img.inputFile,ios::binary);
    input>>img.h;
    input>>img.w;
    img.width=(int)img.w;
    img.height=(int)img.h;
    img.pxNumber=img.width*img.height;
    cout<<(int)img.width<<"-"<<(int)img.height<<endl;
    input.close();
}

ostream& operator<<(string& FilePath,image& img)
{
    ofstream output(FilePath, ios::binary);

    for(int i = 0;i<img.width;i++)
    {
        for(int j=0; j<img.height;j++)
        {
            //cout<<(int)matris[j][i];
            if(img.matris[i][j]==1)
            output<<"*";
            else
            output<<"-";

        }
        output<<endl;
        //cout<<endl;
    }
    output.close();
}


int main()
{
    string file="image1.bin";
    string file2="image2.bin";
    string file3="output.txt";

    image a;
    image b;
    image c;

    file>>a;
    file2>>b;


    a.takeToMatris();
    a.sobelMask();
    a.thresholdMask(100);
    a.print();

    b.takeToMatris();
    b.sobelMask();
    b.thresholdMask(100);
    b.print();

    //c = a+b;
    //c= a*b;
    //c = !a;
    //file3<<c;

    //c.print();


    return 0;
}
