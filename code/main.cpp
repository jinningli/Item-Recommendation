#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <memory.h>
using namespace std;

int boundary[100] = {0, 94317, 194099, 194106, 194129, 228202};
int totline = 5974450;

int RND(int low, int high){
    int a = rand();
    int b = RAND_MAX;
    double rate = ((double)rand())/RAND_MAX;
    return (int)(rate * (high-low) + low);
}

string num2str(double i) {
    stringstream ss;
    ss << i;
    return ss.str();
}

string num2str(int i) {
    stringstream ss;
    ss << i;
    return ss.str();
}

int str2num(string s) {
    int num;
    stringstream ss(s);
    ss>>num;
    return num;
}

double str2numd(string s) {
    double num;
    stringstream ss(s);
    ss>>num;
    return num;
}

void datastdlize(string infiledir, string outfiledir, bool onlinetest = false, double rate = -1, string outfiledirtest = ""){
    fstream fin;
    fin.open(infiledir.c_str());
    fstream fout;
    system((string("touch ")+outfiledir).c_str());
    fout.open(outfiledir.c_str());
    cerr<<" File Open Success At: "<<infiledir<<endl;
    cerr<<"Start Standardize...\n";
    int user = 0;
    int item = 0;
    int weekday = 0;
    int hour = 0;
    int feature1 = 0;
    int feature2 = 0;
    double score = 0;
    int cnt = 0;
    int totnum = (int)(rate * totline);
    if(rate > 0){
        cerr<<"Start Parse Operation...\n";
        int nownum = 0;
        bool totest[6000000];
        memset(totest, 0, sizeof(totest));
        int now = 0;
        while(nownum < totline - totnum){
            now = RND(1, 5974454);
            if(!totest[now]){
                totest[now] = true;
                nownum ++;
            }else{
                continue;
            }

        }
        fstream fouttest;
        system((string("touch ")+outfiledirtest).c_str());
        fouttest.open(outfiledirtest.c_str());
        while (fin >> user) {
            cnt ++;
            fin >> item >> weekday >> hour >> feature1 >> feature2 >> score;
            if(totest[cnt]){
                fouttest << score << " " << user + boundary[0] << ":" << 1 << " " << item + boundary[1] << ":" << 1 << " "
                     << weekday + boundary[2] << ":" << 1 << " " << hour + boundary[3] << ":" << 1 << " "
                     << feature1 + boundary[4] << ":" << 1 << " " << feature2 + boundary[5] << ":" << 1 << endl;
            }else {
                fout << score << " " << user + boundary[0] << ":" << 1 << " " << item + boundary[1] << ":" << 1 << " "
                     << weekday + boundary[2] << ":" << 1 << " " << hour + boundary[3] << ":" << 1 << " "
                     << feature1 + boundary[4] << ":" << 1 << " " << feature2 + boundary[5] << ":" << 1 << endl;
            }
            if(cnt % 100000 == 0){
                cerr<<cnt<<endl;
            }
        }
        cerr<<"Standardize Success!\n";
        fin.close();
        fout.close();
        fouttest.close();
        return;
    }
    if(!onlinetest) {
        while (fin >> user) {
            fin >> item >> weekday >> hour >> feature1 >> feature2 >> score;
            fout << score << " " << user + boundary[0] << ":" << 1 << " " << item + boundary[1] << ":" << 1 << " "
                 << weekday + boundary[2] << ":" << 1 << " " << hour + boundary[3] << ":" << 1 << " "
                 << feature1 + boundary[4] << ":" << 1 << " " << feature2 + boundary[5] << ":" << 1 << endl;
            cnt ++;
            if(cnt % 100000 == 0){
                cerr<<cnt<<endl;
            }
        }
    }else{
        while(fin>>user){
            fin>>item>>weekday>>hour>>feature1>>feature2;
            fout<<0<<" "<<user + boundary[0]<<":"<<1<<" "<< item + boundary[1]<<":"<<1<<" "
                << weekday + boundary[2] <<":"<<1<<" "<< hour + boundary[3] <<":"<<1<<" "
                << feature1 + boundary[4]<<":"<<1<<" "<<feature2 + boundary[5]<<":"<<1<<endl;
            cnt ++;
            if(cnt % 100000 == 0){
                cerr<<cnt<<endl;
            }
        }
    }
    cerr<<"Standardize Success!\n";
    fin.close();
    fout.close();
}

void OutputStdlize(string iniinfo, string probinfo, string submitdir = "../submission.csv"){
    cerr<<"Start Output Standardize...\n";
    fstream fin;
    fin.open(iniinfo.c_str());
    fstream fin2;
    fin2.open(probinfo.c_str());
    fstream fout;
    system(("rm " + submitdir).c_str());
    system(("touch " + submitdir).c_str());
    fout.open(submitdir.c_str());
    fout<<"uid#iid,pred"<<endl;
    int user = 0;
    int item = 0;
    int weekday = 0;
    int hour = 0;
    int feature1 = 0;
    int feature2 = 0;
    double prob = 0;
    int cnt = 0;
    while(fin>>user){
        fin>>item>>weekday>>hour>>feature1>>feature2;
        fin2>>prob;
        fout<<user<<"#"<<item<<","<<prob<<endl;
        cnt ++;
//        if(cnt == 1524461){
//            cerr<<user<<"#"<<item<<","<<prob<<endl;
//        }
//        if(user == 94263 && item == 25634){
//            cerr<<user<<"#"<<item<<","<<prob<<endl;
//        }
        if(cnt % 100000 == 0){
            cerr<<cnt<<endl;
        }
    }
    fin.close();
    fin2.close();
    fout.close();
    cerr<<"Output Standardize Success!\n";
}

void searchmax(string searchdir){
    fstream fin;
    fin.open(searchdir.c_str());
    int user = 0;
    int item = 0;
    double weekday = 0;
    double hour = 0;
    int feature1 = 0;
    int feature2 = 0;
    int maxf1 = 0;
    int maxf2 = 0;
    double score = 0;
    int linecnt = 0;
    while(fin>>user){
        fin>>item>>weekday>>hour>>feature1>>feature2>>score;
        maxf1 = feature1 > maxf1? feature1 : maxf1;
        maxf2 = feature2 > maxf2? feature2 : maxf2;
        linecnt ++;
    }
    cerr<<"Search Report:\n";
    cerr<<"Max Feature 1:\t"<<maxf1<<endl<<"Max Feature 2:\t"<<maxf2<<endl;
    cerr<<"Line count:\t"<<linecnt<<endl;
    fin.close();
}


void through(string dir){
    freopen(dir.c_str(), "r", stdin);
    char tmp[1000];
    int cnt = 0;
    while(cin.getline(tmp, 1000)){
        cnt ++;
        printf("Line: %d,\t%s\n", cnt, tmp);
    }
}


void searchmode(){
    cerr<<"Start Search Mode...\n";
    system("mkdir ../locallog0502");
    for(int i = 69; i < 200; i +=20){
        if(i == 16) continue;
        cerr<<"Processing No."<<i<<" ...\n";
        string logdir = "../locallog0502/log" + num2str((int)time(NULL)) + ".txt";
//        system(("touch " + logdir).c_str());
        string num = num2str(i);
//        string syscall = "rm ../output_libfm" + num + ".txt";
//        system(syscall);
//        cout<<syscall<<endl;
        string syscall= "../libfm-1.42.src/bin/libFM -task"
                                       " r -train ../train_info_libfm.txt "
                                       " -test ../test_info_libfm.txt "
                                       " -dim ’1,1," +num
                        + "’ -iter 400"
                                        " -method mcmc -init_stdev 0.1"
                                        " -out ../output_libfm" + num +".txt" + " 2>&1 | tee " + logdir;
//        cerr<<syscall<<endl;
        system(syscall.c_str());
        cerr<<"Process No."<<i<<" Success!\n";
        OutputStdlize("../test_info.tsv", "../output_libfm" + num + ".txt", "../submission" + num +".csv");
    }
    cerr<<"Search Mode Success!\n";
}

int dataset[] = {17, 18, 19, 21, 23,
                 25, 27};
double score[2000000];
void average(){
    fstream fin;
    int dataSetSize = sizeof(dataset) / 4;
    char tmp[233];
    double probin = 0;
    int k = 0;
    for(int i = 0; i < 7; i ++){
        string namedir = "../submission" + num2str(dataset[i]) + ".csv";
        fin.open(namedir);
        fin.getline(tmp, 233);
        while(fin>>tmp[0]){
            if(tmp[0]!=',') continue;
            fin>>probin;
            score[++k] += probin;
            if(k % 100000 == 0){
                cerr<<k<<endl;
            }
        }
        k = 0;
        cerr<<namedir<<endl;
        fin.close();
    }
    fstream fout;
    system("rm ../output_libfm.txt");
    system("touch ../output_libfm.txt");
    fout.open("../output_libfm.txt");
    for(int j = 1; j <= 1524458; j ++){
        score[j] /= (double)dataSetSize;
        fout<<score[j]<<"\n";
    }
    fout.close();
    system("rm ../submission_avg.csv");
    system("touch ../submission_avg.csv");
    OutputStdlize("../test_info.tsv", "../output_libfm.txt", "../submission_avg.csv");
}

int main() {
    srand(time(NULL));
//    through("../output_libfm.txt");
    // searchmode();
//    average();
    return 0;
}
