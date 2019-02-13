#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include "TH1.h"
#include "TGraph.h"
#include "TH2.h"
#include "TStyle.h"
#include "TStopwatch.h"
#include "TFile.h"
#include "TChain.h"
#include "TTree.h"
#include "TString.h"
#include "TCanvas.h"
#include "TDatime.h"
#include "TF1.h"
#include "TMath.h"
#include "TAxis.h"
#include "TLegend.h"
#include "TText.h"
#include "TApplication.h"
using namespace std;
const double PI=3.1415926;
const int NCX=576;
const int NZX=96;
double timepar[NCX][NZX];
TH1D *hist1dD(char *histname,int Xstep,double xlow,double xup,char*xtitle,char *ytitle);
TH1F *hist1d(char *histname,int Xstep,double xlow,double xup,char*xtitle,char *ytitle);
TH1S *hist1dS(char *histname, Int_t Xstep,Double_t xlow,Double_t xup,char*xtitle,char *ytitle);
TH2S *hist2dS(char *hist2dname,int Xstep,double xlow,double xup,int Ystep,double ylow,double yup,char *xtitle,char *ytitle);
TH2F *hist2d(char *hist2dname,int Xstep,double xlow,double xup,int Ystep,double ylow,double yup,char *xtitle,char *ytitle);
void MycanvasSetting(TCanvas *cc,double leftmargin,double rightmargin,double topmargin,double bottommargin); 
void MyPadSetting(TVirtualPad *cc,double leftmargin,double rightmargin,double topmargin,double bottommargin);
void HistPFX1dSetting(  TH1F *hh,  char *hist1dname, double xlow, double xup, double ylow, double yup,  char *xtitle,   char *ytitle );
void GraphSetting(TGraph*tgraph ,  char*xtitle,char *ytitle);      


int main(int argc, char *argv[]){
      string filepath = argv[1];
      string filepath2 = argv[2];

	  gStyle->SetOptStat(0);
	  gStyle->SetOptFit(0);
	  TStopwatch *ts1=new TStopwatch();
	  ts1->Start();
      TDatime *tdate =new TDatime();
      int systime = tdate->GetTime();
      int sysdate = tdate->GetDate();

	  char buf[200];
	  int eventID1,rsectorID1,moduleID1,submoduleID1,crystalID1,layerID1,comptonPhantom1,comptonCrystal1,RayleighPhantom1,RayleighCrystal1;
	  int eventID2,rsectorID2,moduleID2,submoduleID2,crystalID2,layerID2,comptonPhantom2,comptonCrystal2,RayleighPhantom2,RayleighCrystal2;
	  float energy1,energy2;
	  double time1,time2;
	  float S,theta;
	 
	  int co,nComP1,nComP2,nComC1,nComC2,nRayP1,nRayP2,nRayC1,nRayC2;
	  int A1,A2,T1,T2;
	  int Adc1 ,Adc2;
	  double  Tdiff;   //UNIT  : keV, keV, ns;
	  float mS,mtheta;
      int Ax1,Ax2,Tx1,Tx2;
	  int xadc1,xadc2;
	  double xtdiff;

	  
	  sprintf(buf,"%s/test*.root",filepath.c_str());
      TChain *ch =new TChain("Coincidences");
	  ch->Add(buf); 
	  ch->SetBranchAddress("eventID1",      &eventID1    );
	  ch->SetBranchAddress("eventID2",      &eventID2    );
	  ch->SetBranchAddress("rsectorID1",    &rsectorID1  );
	  ch->SetBranchAddress("moduleID1",     &moduleID1   );
	  ch->SetBranchAddress("submoduleID1",  &submoduleID1);
	  ch->SetBranchAddress("crystalID1",    &crystalID1  );
	  ch->SetBranchAddress("layerID1",      &layerID1    );
	  ch->SetBranchAddress("rsectorID2",    &rsectorID2  );
	  ch->SetBranchAddress("moduleID2",     &moduleID2   );
	  ch->SetBranchAddress("submoduleID2",  &submoduleID2);
	  ch->SetBranchAddress("crystalID2",    &crystalID2  );
	  ch->SetBranchAddress("layerID2",      &layerID2    );
	  ch->SetBranchAddress("energy1",       &energy1     );
	  ch->SetBranchAddress("energy2",       &energy2     );
	  ch->SetBranchAddress("time1",         &time1       );
	  ch->SetBranchAddress("time2",         &time2       );
	  ch->SetBranchAddress("comptonPhantom1",    &comptonPhantom1);
	  ch->SetBranchAddress("comptonPhantom2",    &comptonPhantom2);
	  ch->SetBranchAddress("comptonCrystal1",    &comptonCrystal1);
	  ch->SetBranchAddress("comptonCrystal2",    &comptonCrystal2);
	  ch->SetBranchAddress("RayleighPhantom1",   &RayleighPhantom1);
	  ch->SetBranchAddress("RayleighPhantom2",   &RayleighPhantom2);
	  ch->SetBranchAddress("RayleighCrystal1",   &RayleighCrystal1);
	  ch->SetBranchAddress("RayleighCrystal2",   &RayleighCrystal2);
	  ch->SetBranchAddress("sinogramS",          &S      );
	  ch->SetBranchAddress("sinogramTheta",      &theta  );

      sprintf(buf,"%s/Timeparameter_CableDelay5ns_sigma300ps_OnePariesModule3ns.root",filepath2.c_str());
	  TFile *f=new TFile(buf);
	  TTree *tr=(TTree*)f->Get("tr");
	  tr->SetBranchAddress("timepar", &timepar);
      tr->GetEntry(0);

	  sprintf(buf,"%s/CoinwithTimepar_CableDelay5ns_sigma300ps_OnePariesModule3ns.root",filepath2.c_str());
	  TFile *file=new TFile(buf,"recreate");
	  TTree *tree=new TTree("coin","coin");
	  tree->Branch("co", &co,"co/I");
	  tree->Branch("A1", &A1,"A1/I");
	  tree->Branch("T1", &T1,"T1/I");
	  tree->Branch("A2", &A2,"A2/I");
	  tree->Branch("T2", &T2,"T2/I");
	  tree->Branch("Adc1", &Adc1,"Adc1/I");
	  tree->Branch("Adc2", &Adc2,"Adc2/I");
	  tree->Branch("Tdiff", &Tdiff,"Tdiff/D");
	  tree->Branch("nComP1", &nComP1,"nComP1/I");
	  tree->Branch("nComP2", &nComP2,"nComP2/I");
	  tree->Branch("nComC1", &nComC1,"nComC1/I");
	  tree->Branch("nComC2", &nComC2,"nComC2/I");
	  tree->Branch("nRayP1", &nRayP1,"nRayP1/I");
	  tree->Branch("nRayP2", &nRayP2,"nRayP2/I");
	  tree->Branch("nRayC1", &nRayC1,"nRayC1/I");
	  tree->Branch("nRayC2", &nRayC2,"nRayC2/I");
	  tree->Branch("S", &mS,"S/F");
	  tree->Branch("theta", &mtheta,"theta/F");


	  long entries =ch->GetEntries();

	  for(long KK=0;KK<entries;KK++){
	  //for(long KK=0;KK<1e5;KK++){
	      if(KK%(entries/10)==0)cout<<"----     "<<(KK/(entries/10))*10<<"%  has been done !!   ----"<<endl;
		  ch->GetEntry(KK);
	      
		  //if(eventID1!=eventID2 )continue;
		  //if(energy1<0.425||energy1>0.65 ||energy2<0.425||energy2>0.65)continue;
		  //if(comptonPhantom1>0||comptonPhantom2>0)continue;
		  if(eventID1==eventID2)co =1;
		  else                  co =0;
		  nComP1 = comptonPhantom1;
		  nComP2 = comptonPhantom2;
		  nComC1 = comptonCrystal1;
		  nComC2 = comptonCrystal2;
		  nRayP1 = RayleighPhantom1;
		  nRayP2 = RayleighPhantom2;
		  nRayC1 = RayleighCrystal1;
		  nRayC2 = RayleighCrystal2;

		  xadc1 = int(energy1*1000) ;
	      xadc2 = int(energy2*1000) ;
	      Ax1  = ( moduleID1*32  +  int(submoduleID1/2.0)*8  +  int(crystalID1/8.0));
	      Ax2  = ( moduleID2*32  +  int(submoduleID2/2.0)*8  +  int(crystalID2/8.0));
	      Tx1  = (rsectorID1*16+(submoduleID1%2)*8+crystalID1%8);
	      Tx2  = (rsectorID2*16+(submoduleID2%2)*8+crystalID2%8);
	      xtdiff = ((time2-time1)*1e9 +timepar[Tx2][Ax2]-timepar[Tx1][Ax1] );
		  if(xtdiff>=0){
		  /////////////////////////////////////////////////////////////////
		     Adc1 = xadc1;
		 	Adc2 = xadc2;
			A1   = Ax1;
			A2   = Ax2;
			T1   = Tx1;
			T2   = Tx2;
			Tdiff = xtdiff;
		  }
		  else{
		    Adc2 = xadc1;
		 	Adc1 = xadc2;
			A2   = Ax1;
			A1   = Ax2;
			T2   = Tx1;
			T1   = Tx2;
			Tdiff = -xtdiff;
		    nComP1 = comptonPhantom2;
		    nComP2 = comptonPhantom1;
		    nComC1 = comptonCrystal2;
		    nComC2 = comptonCrystal1;
		    nRayP1 = RayleighPhantom2;
		    nRayP2 = RayleighPhantom1;
		    nRayC1 = RayleighCrystal2;
		    nRayC2 = RayleighCrystal1;
		  }

		  mS=S;
		  mtheta=theta;
		  tree->Fill();
	  
	  
	  
	  }

	  file->cd();
      tree->Write();
	  file->Close();
	  f->Close();
   


	  return 1;
}

inline void MyPadSetting(TVirtualPad *cc,double leftmargin,double rightmargin,double topmargin,double bottommargin){      
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

inline   void MycanvasSetting(TCanvas *cc,double leftmargin,double rightmargin,double topmargin,double bottommargin){      
        cc->SetLeftMargin(leftmargin);
        cc->SetRightMargin(rightmargin);
        cc->SetTopMargin(topmargin);
        cc->SetBottomMargin(bottommargin);	  
        cc->SetTickx();
        cc->SetTicky();
		cc->SetBorderMode(0);
        cc->SetBorderSize(0);
        cc->SetFrameFillColor(10);
        cc->SetFrameBorderMode(0);
        cc->SetFrameBorderSize(0);
           
      }
inline   TH1D *hist1dD(char *histname, Int_t Xstep,Double_t xlow,Double_t xup,char*xtitle,char *ytitle){      
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

inline   TH1S *hist1dS(char *histname, Int_t Xstep,Double_t xlow,Double_t xup,char*xtitle,char *ytitle){      
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

inline   TH1F *hist1d(char *histname, Int_t Xstep,Double_t xlow,Double_t xup,char*xtitle,char *ytitle){      
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

inline TH2F *hist2d(char *hist2dname,int Xstep,double xlow,double xup,int Ystep,double ylow,double yup,char *xtitle,char *ytitle){   
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

inline TH2S *hist2dS(char *hist2dname,int Xstep,double xlow,double xup,int Ystep,double ylow,double yup,char *xtitle,char *ytitle){   
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

inline  void HistPFX1dSetting(  TH1F *hh,  char *hist1dname, double xlow, double xup, double ylow, double yup,  char *xtitle,   char *ytitle ){   
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

inline   void GraphSetting(TGraph*tgraph , char*xtitle,char *ytitle){      
      //tgraph->SetMinimum(ylow);
      //tgraph->SetMaximum(yup);
      tgraph->SetLineWidth(2.);
      tgraph->GetXaxis()->SetTitle(xtitle);
      tgraph->GetYaxis()->SetTitle(ytitle);
      tgraph->GetXaxis()->SetTitleSize(0.055);
      tgraph->GetXaxis()->SetTitleOffset(1.1);
      tgraph->GetXaxis()->SetLabelSize(0.045);
      tgraph->GetYaxis()->SetTitleSize(0.055);
      tgraph->GetYaxis()->SetTitleOffset(1.1);
      tgraph->GetYaxis()->SetLabelSize(0.045);
      tgraph->GetXaxis()->SetNdivisions(510);
      tgraph->GetXaxis()->CenterTitle();
      tgraph->GetYaxis()->CenterTitle();
     }

