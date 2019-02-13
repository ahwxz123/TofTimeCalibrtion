#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
//#include "io.h"
#include "TH1.h"
#include "TH2.h"
#include "TStyle.h"
#include "TStopwatch.h"
#include "TFile.h"
#include "TChain.h"
#include "TTree.h"
#include "TString.h"
#include "TCanvas.h"
#include "TVirtualPad.h"
#include "TDatime.h"
#include "TF1.h"
#include "TMath.h"
#include "TText.h"
#include "TApplication.h"
using namespace std;
const double PI=3.1415926;
const double R=830;
const unsigned int Nslotbyte=64;
//const unsigned int NPixels=29184;
const unsigned int Nbin=1024;
//const unsigned int ELUTN=29884416;
const int NCX=576;
const int NZX=96;
const int Nmod=36;
const int NZbank=3;
const int NCbank=36;
const int NZsub=12;
const int NCsub=72;
const int NZbank_pmod=3;
const int NCbank_pmod=1;
const int NZsub_pbank=4;
const int NCsub_pbank=2;
double peakV[NZX][NCX];


string exeversion="----------version v2-------------  ";//add pixels energy spectrum;
string exeversion1="----------Iteration,Saving the parameter-------------  ";//add pixels energy spectrum;
string exeversion2="----------all  mean adn entries in hist diff -------------  ";//add pixels energy spectrum;

TH1D *hist1dD(char *histname,int Xstep,double xlow,double xup,char*xtitle,char *ytitle);
TH1F *hist1d(char *histname,int Xstep,double xlow,double xup,char*xtitle,char *ytitle);
TH1S *hist1dS(char *histname, Int_t Xstep,Double_t xlow,Double_t xup,char*xtitle,char *ytitle);
TH2S *hist2dS(char *hist2dname,int Xstep,double xlow,double xup,int Ystep,double ylow,double yup,char *xtitle,char *ytitle);
TH2F *hist2d(char *hist2dname,int Xstep,double xlow,double xup,int Ystep,double ylow,double yup,char *xtitle,char *ytitle);
void MycanvasSetting(TCanvas *cc,double leftmargin,double rightmargin,double topmargin,double bottommargin); 
void MyPadSetting(TVirtualPad *cc,double leftmargin,double rightmargin,double topmargin,double bottommargin);
void HistPFX1dSetting(  TH1F *hh,  char *hist1dname, double xlow, double xup, double ylow, double yup,  char *xtitle,   char *ytitle );
//void getFiles( string path, vector<string>& files );
int Mirror(int xx);
int FanNumber(int xx);
int main(int argc, char* argv[])
{
//TApplication *a = new TApplication("a", 0, 0);
	  cout<<exeversion <<endl;
	  cout<<exeversion1<<endl;
	  cout<<exeversion2<<endl;
	  gStyle->SetOptStat(11);
	  gStyle->SetOptFit(111);
	  TStopwatch *ts1=new TStopwatch();
	  ts1->Start(); 
      string  filepath = argv[1];
	  string  Niterstring = argv[2];
      int Nfiles= atoi( Niterstring.c_str() );

      const int Niter=2;
      char buf[100];
	  double FOV= 30;
      const int FanSize=11;
      unsigned int dataeff[Nslotbyte];
      unsigned int data;
	  const int energylow=0;
	  const int energyhigh=1024;

	  int index1,index2,bankindex1,bankindex2, eindex1, eindex2;
	  //int bankpeak1[NPixels],bankpeak2[NPixels];
	  int temp,temp1,temp2;
	  double cc;
	  double mtemp,stemp;
	  int Tx,Ax;
	  int Tmax,Tmin;
	  double tMean,tSigma;
	  for(int i=0 ;i<NZX;i++){
		for(int j=0;j<NCX;j++){
			peakV[i][j]=0.;
		}
	  }
	  cout<<buf<<endl;
	  

      int Adc1= -1,Adc2 = -1;
	  double Tdiff= -1, Tdiffraw=-1, DeltaT = -1;
      int A1= -1,  A2= -1,    T1= -1,  T2= -1;
      int co=-1,co1=-1,co2=-1;

	  TH1F *TimeCalib[NZX][NCX];
	  for(int i=0 ;i<NZX;i++){
		  for(int j=0 ;j<NCX;j++){
			  sprintf(buf,"TimeCalib_%d_%d",i,j);
			  TimeCalib[i][j] = hist1d(buf,100,-5,5,"TimeDiff","Entries");
		  }
	  }

	  TChain *tree =new TChain("coin");	
	  for(int i=0;i<Nfiles;i++){
	   	sprintf(buf,"%s/RawCoinwithTimepar%d.root",filepath.c_str(),i+1);
		tree->Add(buf);
	  }

	cout<<buf<<endl;
	
	//tree->SetBranchAddress("co",    &co  );
	tree->SetBranchAddress("A1",    &A1  );
	tree->SetBranchAddress("T1",    &T1  ); 
	tree->SetBranchAddress("Adc1",    &Adc1  );
	tree->SetBranchAddress("A2",    &A2  );
	tree->SetBranchAddress("T2",    &T2  );
	tree->SetBranchAddress("Adc2",    &Adc2  );
	tree->SetBranchAddress("Tdiff",    &Tdiff  );
	tree->SetBranchAddress("Tdiffraw",    &Tdiffraw  );
	long entries =tree->GetEntries();
	
	TFile *file;
	TTree *tr;
for(int FF=0;FF<Niter;FF++){


	//for(int KK=0;KK<entries;KK++){
	for(int KK=0;KK<1e6;KK++){
		tree->GetEntry(KK);

        if(A1<0||A1>47||A2<0||A2>47||T1<0||T2>607||T1<0||T2>607)continue;
        if(Adc1<425||Adc1>650||Adc2<425||Adc2>650)continue;
		temp1 = FanNumber(T2-Mirror(T1))+FanSize/2;
		temp2 = FanNumber(T1-Mirror(T2))+FanSize/2;
		if(temp1<0||temp1>=FanSize||temp2<0||temp2>=FanSize)continue;

		/*if(temp1<0||temp1>=FanSize||temp2<0||temp2>=FanSize){
			cout<<" FanNumber Invalind !!!"<<endl;
			continue;
		}*/
		//TimeCalib[T1][temp1]->Fill(Tdiff-(timepar[T1]-timepar[T2]) );
		//TimeCalib[T2][temp2]->Fill(-Tdiff+(timepar[T1]-timepar[T2]) );
		TimeCalib[A1][T1]->Fill(-Tdiff-(peakV[A2][T2]) );
		TimeCalib[A2][T2]->Fill(Tdiff-(peakV[A2][T2]) );
	}


	
	for(int i=0;i<NZX;i++){
		for(int j=0; j<NCX;j++){
			peakV[i][j] = peakV[i][j]+TimeCalib[i][j]->GetMean();
		}
	}

//////****************************************************************//;	
		

	
	sprintf(buf,"%s/TimeCalib_Iter%d.root",filepath.c_str(),FF);
	
	file=new TFile(buf,"recreate");
	tr =new TTree("tr","FanDiffMean");
	tr->Branch("timepar",&peakV,"peakV[96][576]/F");
	file->cd();
	for(int i=0;i<NZX;i++){
		for(int j=0; j<NCX;j++){
			TimeCalib[i][j]->Write();
		}
	}
	tr->Fill();
	tr->Write();
	file->Close();


	for(int i=0;i<NZX;i++){
		for(int j=0; j<NCX;j++){
			TimeCalib[i][j]->Reset();;
		}
	}	
	

	//----------------------------------------------
	cout<<"Iteration "<<FF<<"  is done!-----"<<endl;
}//Iteration is done!


		ts1->Stop();
		cout<<"Total times ->"<<ts1->RealTime()<<endl;
	return 0;
}


   void MyPadSetting(TVirtualPad *cc,double leftmargin,double rightmargin,double topmargin,double bottommargin){      
        cc->SetLeftMargin(leftmargin);
        cc->SetRightMargin(rightmargin);
        cc->SetTopMargin(topmargin);
        cc->SetBottomMargin(bottommargin);	  
        cc->SetBorderMode(0);
        cc->SetBorderSize(0);
        cc->SetFrameFillColor(10);
        cc->SetFrameBorderMode(0);
        cc->SetFrameBorderSize(0);
        cc->SetFrameLineWidth(2);        
      }

   void MycanvasSetting(TCanvas *cc,double leftmargin,double rightmargin,double topmargin,double bottommargin){      
        cc->SetLeftMargin(leftmargin);
        cc->SetRightMargin(rightmargin);
        cc->SetTopMargin(topmargin);
        cc->SetBottomMargin(bottommargin);	  
        cc->SetBorderMode(0);
        cc->SetBorderSize(0);
        cc->SetFrameFillColor(10);
        cc->SetFrameBorderMode(0);
        cc->SetFrameBorderSize(0);
           
      }
   TH1D *hist1dD(char *histname, Int_t Xstep,Double_t xlow,Double_t xup,char*xtitle,char *ytitle){      
      TH1D *Myhist1d=new TH1D(histname,histname,Xstep,xlow,xup);
      //Myhist1d->SetMinimum(ylow);
      //Myhist1d->SetMaximum(yup);
      Myhist1d->SetLineWidth(2.);
      Myhist1d->GetXaxis()->SetTitle(xtitle);
      Myhist1d->GetYaxis()->SetTitle(ytitle);
      Myhist1d->GetXaxis()->SetTitleSize(0.055);
      Myhist1d->GetXaxis()->SetTitleOffset(1.1);
      Myhist1d->GetXaxis()->SetLabelSize(0.045);
      Myhist1d->GetYaxis()->SetTitleSize(0.055);
      Myhist1d->GetYaxis()->SetTitleOffset(1.1);
      Myhist1d->GetYaxis()->SetLabelSize(0.045);
      Myhist1d->GetXaxis()->SetNdivisions(510);
      Myhist1d->GetXaxis()->CenterTitle();
      Myhist1d->GetYaxis()->CenterTitle();
      return Myhist1d;
     }

   TH1S *hist1dS(char *histname, Int_t Xstep,Double_t xlow,Double_t xup,char*xtitle,char *ytitle){      
      TH1S *Myhist1d=new TH1S(histname,"",Xstep,xlow,xup);
      //Myhist1d->SetMinimum(ylow);
      //Myhist1d->SetMaximum(yup);
      Myhist1d->SetLineWidth(2.);
      Myhist1d->GetXaxis()->SetTitle(xtitle);
      Myhist1d->GetYaxis()->SetTitle(ytitle);
      Myhist1d->GetXaxis()->SetTitleSize(0.055);
      Myhist1d->GetXaxis()->SetTitleOffset(1.1);
      Myhist1d->GetXaxis()->SetLabelSize(0.045);
      Myhist1d->GetYaxis()->SetTitleSize(0.055);
      Myhist1d->GetYaxis()->SetTitleOffset(1.1);
      Myhist1d->GetYaxis()->SetLabelSize(0.045);
      Myhist1d->GetXaxis()->SetNdivisions(510);
      Myhist1d->GetXaxis()->CenterTitle();
      Myhist1d->GetYaxis()->CenterTitle();
      return Myhist1d;
     }

   TH1F *hist1d(char *histname, Int_t Xstep,Double_t xlow,Double_t xup,char*xtitle,char *ytitle){      
      TH1F *Myhist1d=new TH1F(histname,"",Xstep,xlow,xup);
      //Myhist1d->SetMinimum(ylow);
      //Myhist1d->SetMaximum(yup);
      Myhist1d->SetLineWidth(2.);
      Myhist1d->GetXaxis()->SetTitle(xtitle);
      Myhist1d->GetYaxis()->SetTitle(ytitle);
      Myhist1d->GetXaxis()->SetTitleSize(0.055);
      Myhist1d->GetXaxis()->SetTitleOffset(1.1);
      Myhist1d->GetXaxis()->SetLabelSize(0.045);
      Myhist1d->GetYaxis()->SetTitleSize(0.055);
      Myhist1d->GetYaxis()->SetTitleOffset(1.1);
      Myhist1d->GetYaxis()->SetLabelSize(0.045);
      Myhist1d->GetXaxis()->SetNdivisions(510);
      Myhist1d->GetXaxis()->CenterTitle();
      Myhist1d->GetYaxis()->CenterTitle();
      return Myhist1d;
     }


 TH2F *hist2d(char *hist2dname,int Xstep,double xlow,double xup,int Ystep,double ylow,double yup,char *xtitle,char *ytitle){   
      TH2F *Myhist2d = new TH2F(hist2dname,"",Xstep,xlow,xup,Ystep,ylow,yup);
      //Myhist2d->SetMinimum(ylow);
      //Myhist2d->SetMaximum(yup);
      Myhist2d->SetLineWidth(2.);
      Myhist2d->GetXaxis()->SetTitle(xtitle);
      Myhist2d->GetYaxis()->SetTitle(ytitle);      
      Myhist2d->GetXaxis()->SetTitleSize(0.055);
      Myhist2d->GetXaxis()->SetTitleOffset(1.1);
      Myhist2d->GetXaxis()->SetLabelSize(0.055);
      Myhist2d->GetYaxis()->SetTitleSize(0.055);
      Myhist2d->GetYaxis()->SetTitleOffset(1.1);
      Myhist2d->GetYaxis()->SetLabelSize(0.055);
      Myhist2d->GetXaxis()->SetNdivisions(505);
      Myhist2d->GetYaxis()->SetNdivisions(505);
      Myhist2d->GetXaxis()->CenterTitle();
      Myhist2d->GetYaxis()->CenterTitle();
      //Myhist2d->GetXaxis()->SetNdivisions(512);
    return Myhist2d;
  }



 TH2S *hist2dS(char *hist2dname,int Xstep,double xlow,double xup,int Ystep,double ylow,double yup,char *xtitle,char *ytitle){   
      TH2S *Myhist2d = new TH2S(hist2dname,"",Xstep,xlow,xup,Ystep,ylow,yup);
      //Myhist2d->SetMinimum(ylow);
      //Myhist2d->SetMaximum(yup);
      Myhist2d->SetLineWidth(2.);
      Myhist2d->GetXaxis()->SetTitle(xtitle);
      Myhist2d->GetYaxis()->SetTitle(ytitle);      
      Myhist2d->GetXaxis()->SetTitleSize(0.055);
      Myhist2d->GetXaxis()->SetTitleOffset(1.1);
      Myhist2d->GetXaxis()->SetLabelSize(0.055);
      Myhist2d->GetYaxis()->SetTitleSize(0.055);
      Myhist2d->GetYaxis()->SetTitleOffset(1.1);
      Myhist2d->GetYaxis()->SetLabelSize(0.055);
      Myhist2d->GetXaxis()->SetNdivisions(505);
      Myhist2d->GetYaxis()->SetNdivisions(505);
      Myhist2d->GetXaxis()->CenterTitle();
      Myhist2d->GetYaxis()->CenterTitle();
      //Myhist2d->GetXaxis()->SetNdivisions(512);
    return Myhist2d;
  }



  void HistPFX1dSetting(  TH1F *hh,  char *hist1dname, double xlow, double xup, double ylow, double yup,  char *xtitle,   char *ytitle ){   
      hh->SetNameTitle(hist1dname, ""); 
      hh->SetMarkerStyle(20);
      hh->SetMarkerColor(4);
      hh->SetMarkerSize(0.5);
      hh->SetLineColor(4);
      //hh->SetMarkerSize(1.5);
      //hh->SetBins( Xstep, xlow, xup);  
      hh->SetMinimum(ylow);
      hh->SetMaximum(yup);
      hh->GetYaxis()->SetRangeUser(ylow, yup);
      hh->GetXaxis()->SetRangeUser(xlow, xup);
      hh->GetXaxis()->SetTitle(xtitle);
      hh->GetYaxis()->SetTitle(ytitle);      
      hh->GetXaxis()->SetTitleSize(0.055);
      hh->GetXaxis()->SetTitleOffset(1.1);
      hh->GetXaxis()->SetLabelSize(0.055);
      hh->GetYaxis()->SetTitleSize(0.055);
      hh->GetYaxis()->SetTitleOffset(1.1);
      hh->GetYaxis()->SetLabelSize(0.055);
      hh->GetXaxis()->SetNdivisions(510);
      hh->GetYaxis()->SetNdivisions(510);
      hh->GetXaxis()->CenterTitle();
      hh->GetYaxis()->CenterTitle();
  
      return ;
  }
  
  int Mirror(int xx){
     int NCX=576;
    return (xx>=288 ? (xx-288):(xx+288));
}
 int FanNumber(int xx){
     int NCX=576;
	 if(xx>=NCX/2.) return xx-NCX;
	 else if(xx<-NCX/2.)return xx+NCX;
	 else return xx;
 }
/*
 void getFiles( string path, vector<string>& files ){  
    //文件句柄  
    long   hFile   =   0;  
    //文件信息  
    struct _finddata_t fileinfo;  
    string p;  
    if((hFile = _findfirst(p.assign(path).append("\\*.bin").c_str(),&fileinfo)) !=  -1)  
    {  
        do  
        {  
            //如果是目录,迭代之  
            //如果不是,加入列表  
            if((fileinfo.attrib &  _A_SUBDIR))  
            {  
                if(strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0)  
                    getFiles( p.assign(path).append("\\").append(fileinfo.name), files );  
            }  
            else  
            {  
                files.push_back(p.assign(path).append("\\").append(fileinfo.name) );  
            }  
        }while(_findnext(hFile, &fileinfo)  == 0);  
        _findclose(hFile);  
    }  
}
*/
